//MNTC313 Assignment 2
//You will need to add headers, variables, calculations and print statements to complete the code
//Variables for user input have been provided already
//Do not alter the user input statement unless you are comfortable with user input already!

//Tim Cook has hired you to help him in the design of a special edition of the phone called the 
//QPhone. You are asked to estimate the amount of material required, and the cost of materials 
//to complete the phone. The dimensions of the phone’s height and width are shown on the 
//diagram below. Assume the phone is internally design with a circuit and parts that costs 
//$0.0183 per mm3
//Consider a phone’s depth of 7.4 mm (not shown in the diagram) and corners 
//as quarter circular of radius 15.16 mm. You are asked to estimate the battery cost to complete 
//the phone as well, which uses approximately a 45% of total volume of the phone. The 
//dimensions of the phone’s height and width are shown on the diagram below. Assume the 
//phone’s battery costs $ 0.0095 per mm3

#include <stdio.h>
#include <cmath>

int main()
{
	float pLength, pWidth, pDepth, pRadius; 
    float pi = 3.14;
    float internal_cost = 0.0183; //per mm^3 (Given in question)
    float battery_material_price = 0.00950; //per mm^3 (Given in question)
	
	scanf("%f, %f, %f, %f", &pLength, &pWidth, &pDepth, &pRadius);
	//In the console, enter length, width, depth and radius on a single line, each separated by a comma and space
    //According to the diagram and assignment text: Length=160.84mm, Width=78.09mm, Depth=7.4mm, Radius(corners)=15.16mm
    
    //Need: Surface Area, Volume, Material Cost, Battery Cost
    float FrontFace_area = (pLength * pWidth) - (4 * pow(pRadius,2)) + (pi * pow(pRadius,2)); //Formula is according to http://mathcentral.uregina.ca/QQ/database/QQ.09.10/h/connie1.html
	//Need: Surface Area, Volume, Material Cost, Battery Cost
    float Surface_area = FrontFace_area * 2 + (2 *(pLength-2*pRadius) + 2 *(pWidth-2*pRadius) + 2* pi * pRadius) * pDepth; //Perimeter around the side multiplied by the depth with give you the total side surface area of the phone. Add the front and back surface area and you've got the total surface area of the phone.
    float Volume = FrontFace_area * pDepth;
    float Material_cost = internal_cost * Volume;
    float Battery_cost = (0.45 * Volume) * battery_material_price;
    
    printf("iPhone surface area:\n");
    printf("%5.0f mm2 \n", Surface_area);
    
    printf("iPhone volume:\n");
    printf("%5.0f mm3 \n", Volume);
    
    printf("iPhone material cost:\n");
    printf("$%4.0f \n", Material_cost);
    
    printf("battery cost:\n");
    printf("$%3.0f \n", Battery_cost);
}