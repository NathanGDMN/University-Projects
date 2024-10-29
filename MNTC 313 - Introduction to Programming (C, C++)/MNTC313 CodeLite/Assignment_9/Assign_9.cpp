#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

//Implement the data structure here
#define QUEUESIZE 100 //Maximum size (+1) of the queue used in script

struct data{
    char hiringStatus;
    int employeeID;
};


class employee {
    public:
        data queue[QUEUESIZE];
        int firstElementPosition, positionAfterLastElement;
 
       //Constructor
       employee(){
           firstElementPosition = 0; 
           positionAfterLastElement = 0;
       } 

        bool checkEmpty(){
            if (firstElementPosition == positionAfterLastElement){
                return true;
            }else{
                return false;
            }
        }
    
        void addElement(char c, int i){
            queue[positionAfterLastElement].hiringStatus = c;
            queue[positionAfterLastElement].employeeID = i;
            
            if (positionAfterLastElement == QUEUESIZE){
                positionAfterLastElement = 0;
            }else{
                positionAfterLastElement += 1;
            }
        }
        
        int removeElement(){
            int removedElement = queue[firstElementPosition].employeeID;
            
            if (firstElementPosition == QUEUESIZE){
                firstElementPosition = 0;
            }else{
                firstElementPosition += 1;
            }
            
            return removedElement;
        }
    
        void printQueue(){
            if (checkEmpty()) {
                return;
            }
            bool complete = false;
            int currentPosition = firstElementPosition;
            while (complete == false) {
                printf("%c%d ", queue[currentPosition].hiringStatus, queue[currentPosition].employeeID);
                if (currentPosition == QUEUESIZE) {
                    currentPosition = 0;
                }else{
                    currentPosition += 1;
                }
                if (currentPosition == positionAfterLastElement) {
                    complete = true;
                }
        }
    }
};

int main(int argc, const char * argv[]) {

    //Ask for the number of HR operations and read
    int numberOfHROperations;
    printf("Enter the number of HR operations:\n");
    scanf("%d", &numberOfHROperations);
    
    //Ask for the operations and IDs
    printf("Input the operations and IDs:\n");
    
    //Read the operations and IDs from stdin
    std::vector<int> operations;
    std::vector<char> ids;
    for (int i = 0; i < numberOfHROperations; i++){
        char operation;
        int id;
        scanf("%c%d", &operation, &id);
        operations.push_back(operation);
        ids.push_back(id);
    }
    
    //Solve the question
    employee list;
    for (int j = 0; j < numberOfHROperations; j++){
        if (operations[j] == '+'){ //Add element
            list.addElement(operations[j], ids[j]);
        }
        if (operations[j] == '-'){//Remove element
            list.removeElement();
        }
    }
    
    //Determine elements that should be left based off user input not on position
    int remainingElements[numberOfHROperations]; //Elements that should be left based off user input not on position
    
        //Creating list of removed item positions
    int removeElements[numberOfHROperations]; //List of positions of removed items
    int numberOfRemovedElements = 0;
    for (int k = 0; k < numberOfHROperations; k++){
        if (ids[k] == '+'){ //For items that were added
            int checkID = operations[k];
            for (int l = k; l < numberOfHROperations; l++){ //Assuming all the addition commands come before the subtraction commands
                if (checkID = operations[l] && ids[k] == '-'){
                    removeElements[numberOfRemovedElements] = l;
                    numberOfRemovedElements += 1;
                }
            }
        }
    }
    
        //
    for (int m = 0; m < numberOfHROperations; m++){
        if (ids[m] == '+'){ //For items that were added
            for (int l = 0; l < numberOfHROperations; l++){
                if (l == numberOfRemovedElements[l] && ids[k] == '-'
            }
        }
    }
    
    
    printf("A print should be after this");
    list.printQueue(); //I dont know why this print queue wont work
    
    
    return 0;
}
