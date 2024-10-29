#include "cuda_runtime.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define debug 0 //If debug = 1, certain print statements will be enabled

/*
1. Code __global__(GPU) function for matrixMultiplication
*/
__global__ void matrixMultiplication_kernel(float*d_a, float*d_b, float*d_c, int sizeOfMatricies) {
	int Row = blockIdx.y*blockDim.y + threadIdx.y;
	int Col = blockIdx.x*blockDim.x + threadIdx.x;
	if (Row < sizeOfMatricies && Col < sizeOfMatricies) {
		float Pvalue = 0;
		for (int k = 0; k < sizeOfMatricies; k++) {
			Pvalue += d_a[Row*sizeOfMatricies + k] * d_b[k*sizeOfMatricies + Col];
		}
		d_c[Row*sizeOfMatricies + Col] = Pvalue;
	}

}

/*
1b. Create regular C function (to run on CPU) for matrixMultiplication
*/
void matrixMultiplication(float *a, float *b, float *c, int sizeOfMatricies) {
	for (int i = 0; i < sizeOfMatricies; i++) {  		//i =row
		for (int j = 0; j < sizeOfMatricies; j++) {		//j =col
			//For each value of matrix c (c[i][j]):
			float sum = 0;
			for (int k = 0; k < sizeOfMatricies; k++) {
				sum += *(a + i*sizeOfMatricies + k) * *(b + k*sizeOfMatricies + j);
				//sum = sum  + (a[Row][i] * b[i][Col]
			}
			*(c + i*sizeOfMatricies + j) = sum;
		}
	}
}

//Helpful Functions from MP2:
void fillMatrix(float *a, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			*(a + i*size + j) = rand() % 100; //Every element will be a random number in range of 0 to 100
		}
	}
}
int correct_output(float *a, float *b, int sizeOfMatricies) {
	//Checks if two matrices are equal returns 1 if yes 0 if no.
	for (int i = 0; i < sizeOfMatricies; i++) {
		for (int j = 0; j < sizeOfMatricies; j++) {
			if (*(a + i*sizeOfMatricies + j) != *(b + i*sizeOfMatricies + j)) {
				//If a[i][j] != b[i][j]:
				return 0;
			}
		}
	}
	return 1;
}
void printMatrix(float *a, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%f ", *(a + i*size + j));
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	cudaDeviceProp deviceProps;

	//Get Device Name (They did this in tutorial so I'll do it here)
	cudaGetDeviceProperties(&deviceProps, 0);
	printf("CUDA device [%s]\n", deviceProps.name);
	if (debug == 1) {
		printf("\tNumber of Mulitprocessors: %d\n", deviceProps.multiProcessorCount);
		printf("\tMax Threads Per Block: %d\n", deviceProps.maxThreadsPerBlock);
		printf("\tMax Dimension of a Block: %d\n", deviceProps.maxThreadsDim);
		printf("\tMax Dimension of a Grid: %d\n", deviceProps.maxGridSize);
	}
	
	//Set Size of Matricies:
	const int dimOfMatricies = 2000; //Value determines size of matricies Ex. dimOfMatricies = 5 will result in 5x5 matricies
	printf("Dimensions of Matricies: %dx%d\n", dimOfMatricies, dimOfMatricies);

	//Calculate amount of memory they take:
	int nbytes = dimOfMatricies*dimOfMatricies*sizeof(float);

	//Allocate host memory for matricies:
	float *a = 0;
	float *b = 0;
	float *c = 0;
	float *cCopy = 0;					//Pointer to a copy of second output matrix, to be used to observe GPU to host tranfer time
	cudaMallocHost((void**)&a, nbytes); //Allocates host memory for matrix A, and points pointer a to first value.
	cudaMallocHost((void**)&b, nbytes);
	cudaMallocHost((void**)&c, nbytes);
	cudaMallocHost((void**)&cCopy, nbytes);

	if (debug == 1) {
		printf("Memory Locations of matricies:\n");
		printf("\ta = %x\n",&a);
		printf("\tb = %x\n", &b);
		printf("\tc = %x\n", &c);
	}

	//Generate input matricies into memory

	srand(time(NULL));
	fillMatrix(a, dimOfMatricies);
	fillMatrix(b, dimOfMatricies);

	if (debug == 1) {
		printf("Matrix A:\n");
		printMatrix(a, dimOfMatricies);
		printf("Matrix B:\n");
		printMatrix(b, dimOfMatricies);
	}

	//1e. Allocate device memory for matricies:
	float *d_a = 0;
	float *d_b = 0;
	float *d_c = 0;
	cudaMalloc((void**)&d_a, nbytes); //Allocates memory for matrix A, and points pointer a to first value.
	cudaMemset(d_a, 255, nbytes);	  //Sets all allocated bytes to 255 (they did this in tutorial so i did it here)
	cudaMalloc((void**)&d_b, nbytes);
	cudaMemset(d_b, 255, nbytes);
	cudaMalloc((void**)&d_c, nbytes);
	cudaMemset(d_c, 255, nbytes);

	//Set kernel launch configuration
	int blckWidth = 16;
	int threadsPerBlock = blckWidth*blckWidth;
	int threadsNeeded = ceil(dimOfMatricies*dimOfMatricies); //Because in this configuration one thread only produces one value
	int blocksNeeded = ceil(threadsNeeded / threadsPerBlock);
	if (blocksNeeded < 1) blocksNeeded++;
	int gridWidth = ceil(sqrt(blocksNeeded)); //Note grid will be square

	if (debug == 1) {
		printf("Block Width: %d\n", blckWidth);
		printf("Grid Width: %d\n", gridWidth);
	}

	dim3 dimBlocks = dim3(blckWidth, blckWidth);
	dim3 dimGrid = dim3(gridWidth, gridWidth);

	//create cuda event handles
	cudaEvent_t start, stopToDevice, startToHost, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stopToDevice);
	cudaEventCreate(&startToHost);
	cudaEventCreate(&stop);

	cudaDeviceSynchronize();
	float gpu_time = 0.0f;
	float toGPU_time = 0.0f;
	float fromGPU_time = 0.0f;

	//asynchronously issue work to the GPU (all stream 0)
	cudaEventRecord(start, 0);

	//Copy inputs to device
	cudaMemcpyAsync(d_a, a, nbytes, cudaMemcpyHostToDevice, 0);
	cudaMemcpyAsync(d_b, b, nbytes, cudaMemcpyHostToDevice, 0);

	//Save time it took to write to device
	cudaEventRecord(stopToDevice, 0);

	//Call Kernel
	matrixMultiplication_kernel << <dimGrid, dimBlocks, 0, 0 >> >(d_a, d_b, d_c, dimOfMatricies);
	//Note: only section after >>> is the actual function parameters

	//Save time before saving to host
	cudaEventRecord(startToHost, 0);

	//Copy outputs from device
	cudaMemcpyAsync(c, d_c, nbytes, cudaMemcpyDeviceToHost, 0);
	cudaMemcpyAsync(cCopy, d_c, nbytes, cudaMemcpyDeviceToHost, 0); //A second matrix is recorded as question asked for tranfer to two matricies

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stopToDevice);
	cudaEventSynchronize(startToHost);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&gpu_time, start, stop);			//Note: gpu_time includes toGPU_time and fromGPU_time
	cudaEventElapsedTime(&toGPU_time, start, stopToDevice);
	cudaEventElapsedTime(&fromGPU_time, startToHost, stop);

	//print the GPU times
	printf("time spent executing by the GPU: %.2f\n", gpu_time);
	printf("time spent transferring input data to the GPU: %.2f\n", toGPU_time);
	printf("time spent transferring output data to host: %.2f\n", fromGPU_time);

	//Calculate matrixMultiplication using CPU:
	float *d = 0;
	cudaMallocHost((void**)&d, nbytes);
	matrixMultiplication(a, b, d, dimOfMatricies); //d is output matrix

												   //Check Output
	bool bFinalResults = (bool)correct_output(c, d, dimOfMatricies); //check if c(from GPU) = d(from CPU)
	if (bFinalResults == true) {
		printf("Test PASSED\n");
	}

	if (debug == 1) {
		printf("Matrix C:\n");
		printMatrix(c, dimOfMatricies);
		printf("Correct Matrix:\n");
		printMatrix(d, dimOfMatricies);
	}

	//release resources
	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	cudaFreeHost(a);
	cudaFreeHost(b);
	cudaFreeHost(c);
	cudaFreeHost(cCopy);
	cudaFreeHost(d);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	cudaDeviceReset();

	return 0;

}