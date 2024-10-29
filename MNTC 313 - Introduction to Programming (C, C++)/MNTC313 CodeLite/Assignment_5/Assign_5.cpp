//MNTC313 Assignment 5 Code
//You will need to add headers, variables, calculations and print statements to complete the code
//Variables for user input have been provided already
//Do not alter the user input statement unless you are comfortable with user input already!

#include <stdio.h>
#include <cmath>

#define N 12 //Number of coordinate values

int main()
{
	float coordinates[N][2]; //Initialize array
	
    //Sample input 2.1,10.0 5.5,8.2 5.5,10.1 10.8,3.6 4.0,11.3 2.8,7.5 6.3,10.0 6.3,1.1 8.0,4.0 4.3,7.0 6.3,5.1 10.8,3.3
    
	for (int i = 0; i < N; i++)
	{
		scanf("%f, %f", &coordinates[i][0],&coordinates[i][1]);
	}
	//In the console, enter the 12 coordinate values on a single line separated by comma and by spaces (ie. 1.1,5.6 5.5,8.2 etc.)
    //Each of the twelve coordinate values possess both an x and y coordinate. Each set of coordinates is seperated by spaces while the x and y values of any given coordinate are seperated by a comma.

    //First output in the twelve coordinates formatted like you would on paper
    for (int j = 0; j < N; j++)
	{
        if (j == (N/2) - 1) { //Creates the line break on after the sixth element
            printf ("(%.1f,", coordinates[j][0]);
            printf ("%.1f),\n", coordinates[j][1]);
        } else if (j == N - 1){ //Creates the line break and removes the comma after the last element
            printf ("(%.1f,", coordinates[j][0]);
            printf ("%.1f)\n", coordinates[j][1]);
        } else {
            printf ("(%.1f,", coordinates[j][0]);
            printf ("%.1f),", coordinates[j][1]);
        }
	}
    
    //Next output is the average x and y values of all the coordinates
    float sumOfX = 0; 
    float sumOfY = 0;
    float avgX, avgY;
    
    for (int k = 0; k < N; k++)
	{
        sumOfX = sumOfX + coordinates[k][0];
        sumOfY = sumOfY + coordinates[k][1];
    }
    
    avgX = sumOfX/N;
    avgY = sumOfY/N;
    
    printf("\n"); //Creates the one line gap between the coordinates and the average shown in the sample output
    printf ("Average center: (%.1f,", avgX);
    printf ("%.1f)\n", avgY);
    printf("\n"); //Creates the one line gap between the average shown in the sample output and the distances
    
    //Next output is the distance between each coordinate and the other tweleve coordinates
    //Distance can be calculated via calculating a change in x and change in y then using pythagorean theorem
    float referenceX, referenceY;
    float differenceX, differenceY, distance;
    
    //For the next output (the average distances)
    float sumOfDistances = 0;
    float averageDistances[N];
    
    for (int l = 0; l < N; l++)
	{
        referenceX = coordinates[l][0];
        referenceY = coordinates[l][1];
        
        //For the next output (the average distances)
        
        printf("Distance from point %d to\n", (l+1));
        
        for (int m = 0; m < N; m++)
        {
            printf("%d.- ", (m+1));
            
            differenceX = referenceX - coordinates[m][0];
            differenceY = referenceY - coordinates[m][1];
            distance = sqrt(pow(differenceX,2) + pow(differenceY,2)); //Pythagorean theorem
            
            if (m == N-1){ //Creates the line break and removes the comma after the last element
                printf("%.1f\n", distance);
            } else {
                printf("%.1f, ", distance);
            }
            
            //For the next output (the average distances)
            sumOfDistances = sumOfDistances + distance;
        }
        //For the next output (the average distances)
        averageDistances[l] = sumOfDistances/(N-1);
        sumOfDistances = 0; //Resets the variable for the next loop
    }
    printf("\n"); //Creates the one line gap between the distances and the average distance from each point
    
    //Next output is the average distance between each coordinate and the other tweleve coordinates
    for (int n = 0; n < N; n++)
	{
        printf("Average distance from point %d: ", (n+1));
        printf("%.1f km\n", averageDistances[n]);
    }
}