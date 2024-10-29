#include <string>
#include <vector>

#ifndef insultgenerator_19ng38_H
#define insultgenerator_19ng38_H
using namespace std;

class InsultGenerator{
    public:
        //--------------------Class Fields--------------------
        int linesInTextFile;
        
        vector<string> column0;
        vector<string> column1;
        vector<string> column2;

        //string InsultsSource[3][50]; //Array to hold all the insults from "InsultsSource.txt"

        //--------------------Class Methods--------------------
        void initialize();
            // The initialize() method should load all the source phrases from the InsultsSource.txt file into the attributes.
	        // If the file cannot be read, the method should throw an exception.

        string talkToMe();
            // talkToMe() returns a single insult, generated at random.

        vector<string> generate(int); //string* is used instead of string[]
            // generate() generates the requested number of unique insults.
            // generate(n) should return an array of n unique insults in alphabetical order

        void generateAndSave(string, int);
            // generateAndSave() generates the requested number of unique insults and saves them to the filename
	        // supplied.  If the file cannot be written, the method should throw an exception.  Note that the
	        // insults in the file should be in alphabetical order!
};

//--------------------Exception Classes--------------------//
struct FileException : public exception{
    // The initialize() method should load all the source phrases from the InsultsSource.txt file into the attributes.
	// If the file cannot be read, the method should throw an exception.
    public:
        const char* what() const throw(){ //const--should not change the state of the object, throw()--function cannot throw an exception
            return "FileException: The input file could not be read from or written to.";
        }
};

struct NumInsultsOutOfBounds : public exception{
    //The program is to generate and save between 1 and 10,000 "Shakespearian" insults
    //If the amount of insults requested to be generated falls outside of said range, an exception is thrown
    public:
        const char* what() const throw(){ 
            return "NumInsultsOutOfBounds: The amount of insults specified falls out of program's range";
        }
};

#endif

