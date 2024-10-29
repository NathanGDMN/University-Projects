#include "jumble_19ng38.h"
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>
//For showJumble():
#include <iostream>
using namespace std;

//-----Constructors-----
//----------------------
JumblePuzzle::JumblePuzzle(const char* word, const char* difficulty){
    int wordLen = strlen(word);

    //Make sure word length is between 3 and 10 characters (inclusive)
    if (wordLen < 3 || wordLen > 10){
        printf("\nSupplied word must be between 3 and 10 characters in length.\n");
        throw BadJumbleException();
    } 

    //Determine Size of crossword
    if (strcasecmp(difficulty, "easy") == 0){   //strcasecmp() compares strings without sensitivity to case
        size = wordLen * 2;
    }else if(strcasecmp(difficulty, "medium") == 0){
        size = wordLen * 3;
    }else if(strcasecmp(difficulty, "hard") == 0){
        size = wordLen * 4;
    }else{ //Difficulty inputted does not match options:
        printf("\nAvailable difficulties are: 'easy', 'medium', or 'hard'.\n");
        throw BadJumbleException();
    }

    //Create Empty Crossword
    jumble = new char*[size];       //Initialize char**  
    for (int i=0; i<size; i++){
        jumble[i] = new char[size];                 
    }
    for (int i=0; i<size; i++){     
        for(int j=0; j<size; j++){
            jumble[i][j] = '-';     //Fills array with dashes
        }
    }

    //Randomly pick direction word will be placed in
    srand(time(NULL));
    int d = rand()%2; //d will equal 0(left to right) or 1(up to down)
    if (d == 0){
        direction = 'w';    //w for west (left to right)
    } else if (d == 1){
        direction = 's';    //s for south (up to down)
    }else{
        printf("\nError assigning direction\n");
    }

    //Generate random position in crossword (to place word)
    srand(time(NULL));
    if (direction  == 's'){
        row = gererateNumberBetween(0, size-wordLen);   //size-wordLen = maximum index that will fit word
        column  = rand() % size;                        //column index doesnt matter if word is up and down
    }else{  //direction  == 'w'
        row = rand() % size;                            //row index doesnt matter if word is side to side
        column = gererateNumberBetween(0, size-wordLen);
    }

    //Place word in position
    for (int i = 0; i<wordLen; i++){
        if (direction == 's'){
            jumble[row + i][column] = word[i];      //Increment row if direction is south (build down)
        }else{  //direction  == 'w'
            jumble[row][column+ i] = word[i];       //Increment column if direction is west (build right) 
        }              
    }  

    //Fill rest of crossword with randomly generated letters
    srand(time(NULL));
    for (int i = 0; i<size; i++){           //For each row
        for (int j = 0; j<size; j++){       //For each column in said row
            if (jumble[i][j] == '-'){ 
                char randomChar = 'a' +  rand()%26;     //Generates random letter from A-Z
                jumble[i][j] = randomChar;
            }
        }
    }
}

JumblePuzzle::JumblePuzzle(JumblePuzzle& jp){
    jumble = jp.getJumble();  
    size = jp.getSize();              
    row = jp.getRowPos();
    column = jp.getColPos();            
    direction = jp.getDirection();
}

//-----Destructor-----
//----------------------

JumblePuzzle::~JumblePuzzle(){  
    for (int i=0; i<size; i++){
        jumble[i] = NULL;
        delete jumble[i];                
    }
    jumble = NULL;
    delete jumble;
}

//-----Required Class Methods-----
//-------------------------------
char** JumblePuzzle::getJumble(){
    return jumble;
}

int JumblePuzzle::getSize(){
    return size;
}

int JumblePuzzle::getRowPos(){
    return row;
}

int JumblePuzzle::getColPos(){
    return column;
}

char JumblePuzzle::getDirection(){
    return direction;
}

//-----Created Class Methods-----
//-------------------------------

int JumblePuzzle::gererateNumberBetween (int a, int b){   //Generates random number between a (lower bound) and b (upper bound) inclusive
    /*
    Logic:
    If i want number between 1-10(inclusive), 
        difference(|1-10|) = 9, 
        rand()%difference will produce a random number between 0-9(inclusive), 
        said number + lower bound (in this case 1), 
        will give a number between 1-10(inclusive)  
    */
    
    //Check if bounds are set correctly
    if (a >= b){
        printf("\ngererateNumberBetween(): Bounds set incorrectly\n");
        return -1;
    }
    
    //Implement logic
    int difference  = abs(a - b);

    srand(time(NULL));
    int i = rand()%difference;

    return a + i; 
} 

void JumblePuzzle::showJumble(char** jumble, const int size) { //For testing
    int i, j;
	cout << "\n  ";
    //Print x-axis label
	for (i = 0; i < size; i++){
		if (i < 10){
			cout << " " << i << " ";
        }else{
			cout << i << " ";
        }
    }
	cout << endl;
    //Print remaining rows:
	for (i = 0; i < size; i++) {
		//Print y-axis label:
        if (i < 10){
			cout << " " << i << " ";
        }else{
			cout << i << " ";
        }
        //Print crossword:
		for (j = 0; j < size; j++){
            cout << jumble[i][j] << "  ";
            //printf("%c  ", jumble[i][j]);
        }
		cout << endl;
	}
	cout << endl;
} // end showJumble

//-----Overloaded Assignment Operators-----
//-----------------------------------------
JumblePuzzle JumblePuzzle::operator = (JumblePuzzle jp){
    JumblePuzzle toBeReturned(jp);
    return toBeReturned;
}

//----------------------------------------------------------
//--------------------Main For Testing--------------------//
// int main(){
    // //generateNumberBetweenTest:
    // int number  = gererateNumberBetween(1,10);
    // printf("%d", number);

    ////placing word in puzzle, logic test:
    // char text[] = "hello";
    // char* textPtr = text;
    // printf("%d\n",strlen(text));
    // for(int i=0; i<strlen(text); i++){
    //     printf("%d",i);
    //     printf("%c\n", text[i]);
    //     //textPtr++;
    // }

    // //2D pointer test:
    // char** crossword = new char*[10];
    // for (int i=0; i<10; i++){
    //     crossword[i] = new char[10];
    // }

    // for (int i=0; i<10; i++){
    //     for(int j=0; j<10; j++){
    //         crossword[i][j] = '-';
    //     }
    // }

    // crossword[2][6] = 'a';          
    // printf("%c", crossword[4][3]);

    // //place in word position test:
    // // const char* word = "hello";
    // // printf("%c",  word[4]);

    // //filling in crossword test:
    //char crossword[10][10] = {0};
    // for (int i = 0; i<10; i++){           //For each row
    //     //printf("row");
    //     for (int j = 0; j<10; j++){       //For each column in said row
    //         //printf("column");
    //         if (crossword[i][j] == '-'){    //If element == 0 -- testing to make sure array was initialized correctly
    //             printf("%c", crossword[i][j]);
    //             char randomChar = 'a' +  rand()%26;
    //             printf("%c", randomChar);   //Print random char -- testing random char function
    //             crossword[i][j] = randomChar;
    //             // printf("%c", crossword[i][j]);
    //         }
    //         if(j == 9){
    //             printf("\n");
    //         } 
    //     }
    // }
    //showJumble(crossword, 10);

    // //Test JumblePuzzle(char*, char*) constuctor
    // JumblePuzzle jp1("HELLO","easy");
    // jp1.showJumble(jp1.getJumble(), jp1.getSize());
    // printf("%d, %d, %c", jp1.getRowPos(), jp1.getColPos(), jp1.getDirection());

    // //Test JumblePuzzle(JumblePuzzle&) copy constructor
    // JumblePuzzle jp2(jp1);
    // jp1.showJumble(jp2.getJumble(), jp2.getSize());
    // printf("%d, %d, %c", jp2.getRowPos(), jp2.getColPos(), jp2.getDirection());

    // //Test BadJumbleException
    // JumblePuzzle jp3("to", "easy");

// }