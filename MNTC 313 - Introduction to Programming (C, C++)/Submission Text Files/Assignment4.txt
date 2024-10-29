//MNTC313 Assignment 4
//You will need to add headers, variables, calculations and print statements to complete the code
//Variables for user input have been provided already
//Do not alter the user input statement unless you are comfortable with user input already!

//Kingston’s Water Tower needs to be drained once a year, and the mayor has hired you as the 
//main engineer to make a few calculations about what the status of the draining is. Assume that 
//the tank can be approximated by a cylinder of radius 𝑅 = 25 𝑚. The average velocity of water 
//leaving through the pipe at the bottom of the tank is not constant and is a function of the 
//height of the water level in the tank.

//Write a program in C/C++ that helps you calculate the following for the Water Tower with a 
//given initial water heigh, ℎ, cylinder of radius, 𝑅, and the radius of pipe at the bottom, 𝑟, 
//considering time intervals of 𝑡 = 1 𝑠𝑒𝑔, in which you can assume a constant velocity:
//• The heigh value of the water inside the tank after 1800 seconds (30 min).
//• The heigh value of the water inside the tank after T seconds (use a value of T less than 
//3600).
//• The average value of the velocity when draining the tank after T seconds.
//• The mayor wants to know the status of the draining after T seconds. Add a condition to 
//output “Tank half drained” if the tank meets this criterion, or “Tank still not half drained” if it 
//does not.

#include <stdio.h>
#include <cmath>

int main()
{
	float initialHeight, tankRad, pipeRad;
	int finalT;
	
	scanf("%f, %f, %f, %d", &initialHeight, &tankRad, &pipeRad, &finalT);
	//In the console, enter initial height, tank radius, pipe radius and final time separated by a comma and a space
	
    float pi = 3.14;
    float g = 9.81; //m/s^2 (acceleration due to gravity)
    
    float initialVolume = pi*pow(tankRad, 2)*initialHeight;
    float pipeCrossArea = pi*pow(pipeRad, 2);
    float initialVelocity = 0.5 * sqrt(2*g*initialHeight); //Liquid velocity derived from height
    float volumeLoss, volume, velocity, height; //Values that change with time
    float height_30; //Due to the order of the print statements in the desired output, I have to save the 30 minute height rather than just print and reset it
    
    //Below is for a finalT of thirty minutes
    for(int t = 0; t <= 1800; t++){ //There are 1800 seconds in 30 minutes
        if (t==0) { //IF statement was used so I could move away from the initial variables thier values could be reused later
            volumeLoss = initialVelocity*pipeCrossArea;
            volume = initialVolume-volumeLoss;
        } else {
            volumeLoss = velocity*pipeCrossArea;
            volume = volume-volumeLoss; //Setting the new volume affecting height
        }
        height_30 = volume/(pi*pow(tankRad, 2)); //Derived from cylinder volume formula
        velocity = 0.5 * sqrt(2*g*height_30);
    }
    
    //Below is for a varying finalT
    for(int t = 0; t <= finalT; t++){
        if (t==0) { //IF statement was used so I could move away from the initial variables thier values could be reused later
            volumeLoss = initialVelocity*pipeCrossArea;
            volume = initialVolume-volumeLoss;
        } else {
            volumeLoss = velocity*pipeCrossArea;
            volume = volume-volumeLoss; //Setting the new volume affecting height
        }
        height = volume/(pi*pow(tankRad, 2)); //Derived from cylinder volume formula
        velocity = 0.5 * sqrt(2*g*height);
    }
    float averageVelocity = (velocity + initialVelocity) / 2;
    
    //Output
    printf("Average velocity value: %.2f m/s\n", averageVelocity);
    printf("Height value after 30 min: %.2f m\n", height_30);
    printf("Height value after %d seconds: ", finalT);
    printf("%.2f m\n", height);
    
    if (volume <= initialVolume/2)
        printf("Tank half drained\n");
    else
        printf("Tank still not half drained\n");
}