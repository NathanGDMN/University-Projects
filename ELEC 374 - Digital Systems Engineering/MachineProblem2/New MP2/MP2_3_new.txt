#include "cuda_runtime.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define debug 0 //If debug = 1, certain print statements will be enabled

/* 3. Create a matrixAddition Kernel where each thread calculates a row of output values.
Parameters: pointer to output matrix C, two Pointers to input matricies A and B,
dimensions of matricies A and B (remember they're square matriceies so this can be single int)
*/
__global__ void matrixAddition_kernel(float*d_a, float*d_b, float*d_c, int sizeOfMatricies) {
	int idx = blockIdx.x*blockDim.x + threadIdx.x;			//Assume block 

	idx = idx*sizeOfMatricies; //To account for already computed indicies 
							   //Ex. thread 1 (idx=0) will compute output elements 0 (5*0),1(5*0+1),2,3,4
							   //	thread 2 (idx=1) will compute output elements 5 (5*1),6 (5*1+1),7,8,9

	int n = sizeOfMatricies*sizeOfMatricies;
	if (idx < n) { //Avoid accessing beyond end off matricies
		for (int i = 0; i < sizeOfMatricies; i++) {
			//Each thread will calculate a row of output matrix:
			d_c[idx + i] = d_a[idx + i] + d_b[idx + i];
		}
	}
}

/* Created a matrixAddition function. Should basically be the same as the kernel function.
This function will be used to check whether the kernel function created correct output (used to check)
*/
void matrixAddition(float *a, float *b, float *c, int sizeOfMatricies) { //Note acc
	for (int i = 0; i < sizeOfMatricies; i++) {
		for (int j = 0; j < sizeOfMatricies; j++) {
			*(c + i*sizeOfMatricies + j) = *(a + i*sizeOfMatricies + j) + *(b + i*sizeOfMatricies + j);
			//C[i][j] = A[i][j] + B[i][j];
		}
	}
}

//Function to check if two matricies are equal (to be used to compare outputs):
int correct_output(float *a, float *b, int sizeOfMatricies) {
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

//Additional function to help with debugging:
void printMatrix(float *a, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%f ", *(a + i*size + j));
		}
		printf("\n");
	}
}

//Function for generating  randomly intitialized square matricies of a given length
void fillMatrix(float *a, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			*(a + i*size + j) = rand() % 100; //Every element will be a random number in range of 0 to 100
		}
	}
}

int main(int argc, char *argv[]) {
	cudaDeviceProp deviceProps;

	//Get Device Name (They did this in tutorial so I'll do it here)
	cudaGetDeviceProperties(&deviceProps, 0);
	printf("CUDA device [%s]\n", deviceProps.name);
	printf("\tNumber of Mulitprocessors: %d\n", deviceProps.multiProcessorCount);
	printf("\tMax Threads Per Block: %d\n", deviceProps.maxThreadsPerBlock);
	printf("\tMax Dimension of a Block: %d\n", deviceProps.maxThreadsDim);
	printf("\tMax Dimension of a Grid: %d\n", deviceProps.maxGridSize);

	/*
	1. Define two square input matricies A and B, and matching output matrix
	Note: they're floats
	*/
	const int dimOfMatricies = 2000; //Value determines size of matricies Ex. dimOfMatricies = 5 will result in 5x5 matricies
	printf("Dimensions of Matricies: %dx%d\n", dimOfMatricies, dimOfMatricies);

	//1b. Calculate amount of memory they take:
	int nbytes = dimOfMatricies*dimOfMatricies*sizeof(float);

	//1c. Allocate host memory for matricies:
	float *a = 0;
	float *b = 0;
	float *c = 0;
	cudaMallocHost((void**)&a, nbytes); //Allocates host memory for matrix A, and points pointer a to first value.
	cudaMallocHost((void**)&b, nbytes);
	cudaMallocHost((void**)&c, nbytes);

	if (debug == 1) {
		printf("Memory Locations of matricies:\n");
		printf("\ta = %x\n", &a);
		printf("\tb = %x\n", &b);
		printf("\tc = %x\n", &c);
	}

	//1d. Store input matricies into memory
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
	int blckWidth = 4; //block width and length (16 threads per block)
	int threadsPerBlock = blckWidth*blckWidth;
	int threadsNeeded = dimOfMatricies*dimOfMatricies;
	int numBlocks = threadsNeeded / threadsPerBlock;
	if (numBlocks < 1) numBlocks++;

	dim3 dimBlocks = dim3(16, 1);				// 16 threads per block 
	dim3 dimGrid = dim3(numBlocks, 1);

	//create cuda event handles
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaDeviceSynchronize();
	float gpu_time = 0.0f;

	//asynchronously issue work to the GPU (all stream 0)
	cudaEventRecord(start, 0);

	//Copy inputs to device
	cudaMemcpyAsync(d_a, a, nbytes, cudaMemcpyHostToDevice, 0);
	cudaMemcpyAsync(d_b, b, nbytes, cudaMemcpyHostToDevice, 0);

	//Call Kernel
	matrixAddition_kernel << <dimGrid, dimBlocks, 0, 0 >> >(d_a, d_b, d_c, dimOfMatricies);
	//Note: only section after >>> is the actual function parameters

	//Copy outputs from device
	cudaMemcpyAsync(c, d_c, nbytes, cudaMemcpyDeviceToHost, 0);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop); //stop is updated here
	cudaEventElapsedTime(&gpu_time, start, stop);

	//print the GPU times
	printf("time spent executing by the GPU: %.2f\n", gpu_time);

	//Calculate matrixAddition using CPU:
	float *d = 0;
	cudaMallocHost((void**)&d, nbytes);
	matrixAddition(a, b, d, dimOfMatricies); //d is output matrix

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
	cudaFreeHost(d);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	cudaDeviceReset();

	return 0;

}