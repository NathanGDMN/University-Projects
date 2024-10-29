//MNTC313 Assignment 6 Code
//You will need to add headers, variables, calculations and print statements to complete the code
//Variables for user input have been provided already
//Do not alter the user input statement unless you are comfortable with user input already!

#include <stdio.h>
#include <cmath>

void checkBridge(float stres, float strai);

int main()
{
	float elasticMod, strain;
	
	scanf("%f, %f", &strain, &elasticMod);
	//In the console, enter elastic modulus (MPa) and strain values on a single line separated by a comma and space. 
	
    float stress = elasticMod * strain; //Formula given
    printf("Stress value: %.2f MPa\n", stress);
    
    checkBridge(stress, strain);
}

void checkBridge(float stres, float strai){
    float concreteStrength;
    
    if (strai > 0){ //In Tension
        printf("Bridge deck in tension\n");
        concreteStrength = 5; //Concrete tensile strength
        if (abs(stres) > concreteStrength)
            printf("Danger: tensile strength exceeded\n");
        else
            printf("Bridge deck safe\n");
    }else if (strai < 0){ //In Compression
        printf("Bridge deck in compression\n");
        concreteStrength = 30; //Concrete conpressive strength
        if (abs(stres) > concreteStrength)
            printf("Danger: compressive strength exceeded\n");
        else
            printf("Bridge deck safe\n");
    }else{
        printf(" “No stress in bridge\n");
    }
}
