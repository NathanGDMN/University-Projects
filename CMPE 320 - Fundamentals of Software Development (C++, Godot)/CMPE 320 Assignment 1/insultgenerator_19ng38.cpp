#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "insultgenerator_19ng38.h"
using namespace std;

//--------------------Header Class Implementation--------------------//
void InsultGenerator::initialize(){
    // The initialize() method should load all the source phrases from the InsultsSource.txt file into the attributes.
	// If the file cannot be read, the method should throw an exception.
    
    fstream f;
    f.open("InsultsSource.txt", ios::in);//Opens file InsultsSource.txt in read mode

    if(f.is_open()){
        
        string line;

        while(getline(f, line)){ //For every line in InsultsSource.txt:
            string currentWord = "";
            int c = 0; //Keeps track of what column next word should go in
            
            for (auto i : line){ //For each character in the line
                //Check if character is a space:

                if(isspace(i)){ //If character is a space, word is finished, save word
                    switch (c){
                        case 0:
                            column0.push_back(currentWord);
                            break;
                        case 1:
                            column1.push_back(currentWord);
                            break;
                    }

                    ++c;
                    currentWord = "";
                }else{ //If character is not a space, add character to existing set of characters to assemble word (currentWord)
                    currentWord = currentWord + i;
                }
            }
            //When end of line is reached:
            column2.push_back(currentWord);
        }

        f.close();

        linesInTextFile = column0.size();

    }else{//File did not open
        throw FileException();
    }
}

string InsultGenerator::talkToMe(){
    vector<string> insults = generate(1);
    string insult  = insults[0];
    return insult;
}

vector<string> InsultGenerator::generate(int insultAmount){
    // generate() generates the requested number of unique insults.
    // generate(n) should return an array of n unique insults in alphabetical order

    //-----Check if number is in range-----
    if (0 <= insultAmount && insultAmount<= 10000){

        vector<string> insults;

        for (int i = 0; i < insultAmount; i++){
            //cout << i << endl;

            start:
            //-----Generate random insult using three columns----
            //srand(time(0));
            int rand0 = rand() % linesInTextFile;
            int rand1 = rand() % linesInTextFile;
            int rand2 = rand() % linesInTextFile;

            string word0 = column0[rand0];
            string word1 = column1[rand1];
            string word2 = column2[rand2];

            string generatedInsult = "Thou " + word0 + " " + word1 + " " + word2 + "!";

            //-----Check if insult already exists-----
            bool duplicate = false;
            for (int i = 0; i < insults.size(); i++){
                if (generatedInsult == insults[i]){ 
                    duplicate = true;
                    break;
                }
            }

            if (duplicate){ //If duplicate is found
                goto start; //Generate new insult (will keep repeating till unique insult is generated)
            }
            
            //-----Save insult if no duplicate is found-----
            insults.push_back(generatedInsult);
            //cout << generatedInsult << endl;
        }

        sort(insults.begin(), insults.end());
        return insults;
    }else{//Number of insults requested was not in range
        throw NumInsultsOutOfBounds();
    }
}

void InsultGenerator::generateAndSave(string textfile, int insultAmount){
    vector<string> insults = generate(insultAmount);

    fstream f;
    f.open(textfile, ios::out); //Opens/creates file InsultsTarget.txt and opens it

    if(f.is_open()){
        
        for (int i = 0; i < insults.size(); i++){
            f << insults[i] << endl;
        }
        
        f.close();

    }else{//File did not open
        throw FileException();
    }
}



//--------------------Main For Testing--------------------//
// int main(){
//     InsultGenerator ig;
//     vector<string> insults;
//     ig.initialize();
//     cout << ig.talkToMe() << endl;
//     insults = ig.generate(10);
//     //ig.generateAndSave("InsultsTarget.txt", 10);

//     try {
// 		ig.generateAndSave("Nothing.txt", 40000);
// 	} catch (NumInsultsOutOfBounds& e) {
// 		cerr << e.what() << endl;
// 	}
// }