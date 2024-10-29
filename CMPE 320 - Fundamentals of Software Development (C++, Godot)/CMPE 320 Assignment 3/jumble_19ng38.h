#include <exception>
#ifndef jumble_19ng38_H
#define jumble_19ng38_H


class JumblePuzzle{
    //-----Class Fields-----
        char** jumble;    //2D array holding crossword puzzle
        int size;               //Size of puzzle (ex. 10 if crossword is 10x10)
        int row;                //Row first letter of word is on in crossword
        int column;             //Column first letter of word is on in crossword
        char direction;         //Direction word is spelt out in n, e, s, w --north,east,south,west 
    
    public:
    //-----Constructors-----
        JumblePuzzle(const char*, const char*); //JumblePuzzle("word", "difficulty")
        JumblePuzzle(JumblePuzzle&);      //Copy Constructor
    
    //-----Destructors-----
        ~JumblePuzzle();

    //-----Required Class Methods-----
        char** getJumble();     //Returns Crossword Puzzle as a 2D array
        int getSize();          //Returns size of puzzle (ex. 10 if crossword is 10x10)
        int getRowPos();        //Returns row index of first letter of word puzzle
        int getColPos();        //Returns column index of first letter of word in puzzle
        char getDirection();    //Returns direction in which the word is spelt : n, e, s, or w

    //-----Created Class Methods------
        int gererateNumberBetween(int, int);    //Generates random number between a (lower bound) and b (upper bound) inclusive
        void showJumble(char**,  int);          //To use for testing

    //-----Operators to be overloaded-----
    JumblePuzzle operator = (JumblePuzzle);     //Should trigger copy constructor
};

struct BadJumbleException : public std::exception{
    public:
        const char* what() const throw(){
            return "ERROR: Bad Jumble!";
        }
};

#endif