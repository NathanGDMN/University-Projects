//MNTC313 Assignment 3 
//You will need to add headers, variables, calculations and print statements to complete the code
//Variables for user input have been provided already
//Do not alter the user input statement unless you are comfortable with user input already!

//QUESTION:
//Write a program using C/C++ to determine the projectile motion (height, vertical velocity) at a certain time.
//Your code should then employ the following logical conditions:
//• If time is greater or equal than zero, first print “Projectile released”
//o Print the position and velocity value with the following format: 
//“Position: xx.xx meters”
//“Velocity value: xx.xx meters/second”
//o If the projectile has a vertical velocity greater or equal than zero, print “Projectile 
//ascending”
//o Or, if the projectile has a negative vertical velocity, print “Projectile descending”
//▪ If the vertical position of the projectile is greater or equal than the initial 
//vertical position, print “Projectile above initial position”
//▪ Otherwise, print “Projectile below initial position”
//• Or, if time is lower than zero, print “Projectile not released”

#include <stdio.h>
#include <cmath>

int main()
{

    float time, initVel,initAng,initH;
    float pi = 3.14;
    float g = 9.81; //m/s^2 Acceleration due to gravity

	scanf("%f, %f, %f, %f", &time, &initVel, &initAng, &initH);
	//In the console, enter time, initial velocity, initial angle and initial heigth values on a single line separated by a comma and space. 

//Umm.. I originally thought that I had to re-output the input i typed without the spaces (ignore below)
//    printf("%.0f,", time);
//    printf("%.0f,", initVel);
//    printf("%.0f,", initAng);
//    printf("%.0f \n", initH);
    
    float radAng = initAng * (pi/180); //Angle input for the sine functions require a radian input
    
    //Need: vertical velocity, vertical position (*Appears we are only dealing with vertical height and position.)
    //Current Vertical Position Formula
    float height = (-0.5)*g*pow(time,2) + initVel*sin(radAng)*time + initH;
    //Current Vertical Velocity Formula
    float velocity = -1.0*g*time + initVel*sin(radAng);
    
    //If time is greater or equal than zero, first print “Projectile released”
    if (time >= 0) {
        printf("Projectile released\n");
        
        //o Print the position and velocity value with the following format: 
        //“Position: xx.xx meters”
        //“Velocity value: xx.xx meters/second” 
        printf("Position: %.2f meters\n", height);
        printf("Velocity value: %.2f meters/second\n", velocity);
        
        //If the projectile has a vertical velocity greater or equal than zero, print “Projectile ascending”
        //Or, if the projectile has a negative vertical velocity, print “Projectile descending”
        if (velocity >= 0)
            printf("Projectile ascending\n");
        else
            printf("Projectile descending\n");
        
        //▪ If the vertical position of the projectile is greater or equal than the initial 
        //vertical position, print “Projectile above initial position”
        //▪ Otherwise, print “Projectile below initial position”
        if (height >= 0)
            printf("Projectile above initial position\n");
        else
            printf("Projectile below initial position\n");

    //• Or, if time is lower than zero, print “Projectile not released”    
    }else{
        printf("Projectile not released\n");}
}
