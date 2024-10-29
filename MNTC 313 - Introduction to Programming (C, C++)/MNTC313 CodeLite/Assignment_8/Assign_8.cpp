#include <stdio.h>
#include <iostream>
using namespace std;

/*Structures*/
struct info {
    int numberOfCustomers;
    float averageItemPrice;
    float averageItemWeight;
};

/*Classes*/
class economics{
    public:
        /*Fields*/
        float costPerKg = 4.70; //Given transportation cost per kilogram
        float targetRevenue = 36000; //The given average expected revenue per center 
        int numElements;

        /*Constructor*/
        economics(int size){
            numElements=size;
        }
        
        /*Methods*/
        int totalCustomers(info array[]){
            int customers = 0;
            for (int m=0; m<numElements; m++){
                customers += array[m].numberOfCustomers;
            }
            return customers;
        };
        
        float totalWeight(info array[]){
            float weight = 0;
            for (int m=0; m<numElements; m++){
                weight += array[m].numberOfCustomers * array[m].averageItemWeight;
            }
            return weight;
        };
        
        float totalRevenue(info array[]){
            float weight;
            float revenue = 0;
            for (int m=0; m<numElements; m++){
                weight = array[m].numberOfCustomers * array[m].averageItemWeight;
                revenue += array[m].numberOfCustomers * array[m].averageItemPrice - weight * costPerKg;
            }
            return revenue;
        };
        
        float avgRevenue(info array[]){
            float weight;
            float revenue = 0;
            for (int m=0; m<numElements; m++){ //Calculate total revenue
                weight = array[m].numberOfCustomers * array[m].averageItemWeight;
                revenue += array[m].numberOfCustomers * array[m].averageItemPrice - weight * costPerKg;
            }
            float avg = revenue/numElements; //avgRevenue = totalRevenue/numberOfCenters
            return avg;
        };
};
 
 //-------------------------------------------------
int main()
{
    //-----Input-----
    int numberOfCenters;
    printf("Input number of centers:\n");
    scanf("%d", &numberOfCenters);
    
    info centerData[numberOfCenters];
    
    printf("Input customer data for all centers:\n");
    for (int i=0; i < numberOfCenters; i++){
        scanf("%d", &centerData[i].numberOfCustomers);
    }

    printf("Input item average price data for all centers:\n");
    for (int j=0; j < numberOfCenters; j++){
        scanf("%f", &centerData[j].averageItemPrice);
    }
    
    printf("Input item average weight data for all centers:\n");
    for (int k=0; k < numberOfCenters; k++){
        scanf("%f", &centerData[k].averageItemWeight);
    }
    
    //-----Output-----
    economics centers(numberOfCenters); //Inputs array length into class to be used in loops
    
    printf("Total customers: %d\n", centers.totalCustomers(centerData));
    printf("Total weight: %.0f kg\n", centers.totalWeight(centerData));
    printf("Total revenue: $%.0f\n", centers.totalRevenue(centerData));
    
    printf("Average revenue: $%.0f\n", centers.avgRevenue(centerData));
    
    if (centers.avgRevenue(centerData) > centers.targetRevenue) //From testing to match example case, revenues alreay deduct costs so the 'revenue' is really profit
        printf("Company is profitable\n");
    else
        printf("Company is not profitable\n");
    
    
}
 //-------------------------------------------------
