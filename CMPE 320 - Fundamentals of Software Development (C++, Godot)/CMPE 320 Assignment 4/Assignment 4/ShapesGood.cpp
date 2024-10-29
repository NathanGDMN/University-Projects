#include <iostream>
#include <string>
#include "ShapesGood.h"

using namespace std;

//-----Shape-----
Shape::Shape() : length(0), width(0) {}
Shape::Shape(int len, int wid, string outColour) : length(len), width(wid), outlineColour(outColour) {}
Shape::~Shape() {}
void Shape::draw(){ cout << "UNABLE TO DRAW: Shape type not defined."; }
int Shape::getLength() { return length; }
int Shape::getWidth() { return width; }
string Shape::getOutlineColour() { return outlineColour; }

//-----Fillable-----
Fillable::Fillable() {};
Fillable::Fillable(string fColour) : fillColour(fColour) {}
Fillable::~Fillable() {}
string Fillable::getFillColour() { return fillColour; }

//-----TextObject-----
TextObject::TextObject() {};
TextObject::TextObject(string t) : text(t) {}
TextObject::~TextObject() {}; 
string TextObject::getText() { return text; } 


//-----Square-----
Square::Square(int len, int wid, string outColour) : Shape(len, wid, outColour) {}
Square::~Square() {}
void Square::draw(){ cout << "\nDrawing a " + getOutlineColour() + " square."; }

//-----FilledSquare-----
FilledSquare::FilledSquare(int len, int wid, string outColour, string fColour) : Square(len, wid, outColour), Fillable(fColour) {}
FilledSquare::~FilledSquare() {}
void FilledSquare::draw() { 
    Square::draw();
    cout << " With " + getFillColour() + " fill."; 
}

//-----FilledTextSquare-----
FilledTextSquare::FilledTextSquare(int len, int wid, string outColour, string fillColour, string text) : Square(len, wid, outColour), Fillable (fillColour), TextObject(text) {}
FilledTextSquare::~FilledTextSquare() {}
void FilledTextSquare::draw(){ 
    Square::draw();
    cout << " With " + getFillColour() + " fill."; 
    cout << " Containing the text: \"" << getText() << "\".";
}

//-----Circle-----
Circle::Circle(int len, int wid, string outColour) : Shape(len, wid, outColour) {}
Circle::~Circle() {}
void Circle::draw(){ cout << "\nDrawing a " + getOutlineColour() + " circle."; }

//-----Fillable Circle-----
FilledCircle::FilledCircle(int len, int wid, string outColour, string fColour) : Circle(len, wid, outColour), Fillable(fColour) {}
FilledCircle::~FilledCircle() {}
void FilledCircle::draw(){ 
    Circle::draw();
    cout << " With " + getFillColour() + " fill."; 
}

//-----Arc-----
Arc::Arc(int len, int wid, string outColour) : Shape(len, wid, outColour) {}
Arc::~Arc() {}
void Arc::draw(){
    cout << "\nDrawing a " + getOutlineColour() + " arc.";
}