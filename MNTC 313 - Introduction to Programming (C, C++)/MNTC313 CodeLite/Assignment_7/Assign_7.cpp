#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
	//-----Input-----
    //Variables to be inputted required for stress calculation 
    float weight, firstDepth, depthIncrement, firstKValue, KIncrement;
    int numberOfDepths, numberOfKValues;
  
    printf("Input rock unit weight (kN/m3):\n");
    scanf("%f", &weight);
    
    printf("Input number of depth values:\n");
    scanf("%d", &numberOfDepths);

    printf("Input first depth value (m):\n");
    scanf("%f", &firstDepth);
    
    printf("Input depth increment (m):\n");
    scanf("%f", &depthIncrement);
    
    printf("Input number of k values:\n");
    scanf("%d", &numberOfKValues);
    
    printf("Input first k value (m):\n");
    scanf("%f", &firstKValue);
    
    printf("Input k increment (m):\n");
    scanf("%f", &KIncrement);
    
    //-----Output-----
    float verticalStress, KValue;
    printf("Vertical stress values (kPa):\n");
    
    //Output File Declaration
    float horizontalStress[numberOfDepths][numberOfKValues];
    string outputFile = "outputFileA.txt";
    FILE* fileOutput = fopen(outputFile.c_str(), "w");
    
    for (int i=0; i < numberOfDepths; i++){
        KValue = firstKValue; //Used to recycle variable
        
        //Vertical Stress Calculations
        verticalStress = weight * firstDepth;
        printf("%.0f\n", verticalStress);
              
        //Horizontal Stress Calculations and Output File Writing
        fprintf(fileOutput, "%.0f,", firstDepth); //Printing first column of text file
        for (int j = 0; j < numberOfKValues; j++){
            horizontalStress [i][j] = KValue * verticalStress;
            
            if (j == numberOfKValues-1){ //To remove comma and start new line 
                fprintf(fileOutput, "%.0f\n", horizontalStress [i][j]); 
            } else {
                fprintf(fileOutput, "%.0f,", horizontalStress [i][j]);
            }
            
            KValue += KIncrement; //Increase k value
        }
        
        firstDepth += depthIncrement; //Increase depth variable
    }
}
