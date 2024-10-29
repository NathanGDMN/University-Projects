#pragma once

#include <string>

using namespace std;

class Shape {
    public:
    Shape();                    //No arguement constructor
    Shape(int, int, string);    //Constructor (length, width, outlineColour)
    virtual ~Shape();           //Destructor
    //Required Methods:
    virtual void draw() = 0;
    //Accessor Methods:
    int getLength();
	int getWidth();
    virtual string getOutlineColour();
    
    private:
    //Attributes:
    const int length, width;
    const string outlineColour;
};

class Fillable {
    public:
    Fillable();             //No arguement constructor
    Fillable(string);       //Constructor (fillColour);
    virtual ~Fillable();    //Destructor
    //Accessor Methods:
    virtual string getFillColour();

    private:
    //Attributes:
    string fillColour;
};

class TextObject {
    public:
    TextObject();           //No arguement constructor
    TextObject(string);     //Constructor (text);
    virtual ~TextObject();  //Destructor
    //Accessor Methods:
    virtual string getText();

    private:
    //Attributes:
    string text;
};


class Square : public Shape{
    public:
    Square(int, int, string);   //Constructor (length, width, outlineColour)
    ~Square();                  //Destructor
    //Overriden Methods:
    void draw();
};

class FilledSquare : public Square, public Fillable{
    public:
    FilledSquare(int, int, string, string);    //Constructor (length, width, outlineColour, fillColour)
    ~FilledSquare();                           //Destructor
    //Overriden Methods:
    void draw();
};

class FilledTextSquare : public Square, public Fillable, public TextObject{
    public:
    FilledTextSquare(int, int, string, string, string); //Constructor (length, width, outlineColour, fillColour, text)
    ~FilledTextSquare();                                //Destructor
    //Overriden Methods:
    void draw();
};

class Circle : public Shape{
    public:
    Circle(int, int, string);   //Constructor (length, width, outlineColour) 
    ~Circle();                  //Destructor
    //Overridden Methods:
    void draw();
};

class FilledCircle : public Circle, public Fillable{
    public:
    FilledCircle(int, int, string, string);   //Constructor (length, width, outlineColour, fillColour) 
    ~FilledCircle();                          //Destructor 
    //Overriden Methods:
    void draw();
};

class Arc : public Shape{
    public: 
    Arc(int, int, string);  //Constructor (length, width, type)
    ~Arc();                 //Destructor 
    //Overriden Methods:
    void draw();
};