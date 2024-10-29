#include "fraction_19ng38.h"
#include <iostream>
#include <string>


//-----Constructors-----
Fraction::Fraction(){
    numerator = 0;
    denominator = 1;
}

Fraction::Fraction(int i){
    numerator = i;
    denominator = 1;
}

Fraction::Fraction(int one, int two){
    printf("constructor started");
    
    if(two < 0 ){ //If denominator negative
        numerator = -one;
        denominator = -two;  
    }else{
        numerator = one;
        denominator = two;  
    }

    //Fractions must be stored normalized
    normalize();
}

//-----Class Methods-----
void Fraction::normalize(){
    //Find GCD
    int GCD = greatestCommonDivisor(numerator, denominator);

    //Divide one and two by GCD
    numerator = numerator/GCD;
    denominator = denominator/GCD;
}

int Fraction::greatestCommonDivisor(int n, int d){
    
    //Find GCD
    int GCD;

    if(d <= n && n%d==0){
        GCD = d;
    }else if (n<d){
        GCD = greatestCommonDivisor(d, n);
    }else{
        GCD = greatestCommonDivisor(d,n%d);
    }

    return GCD;
}

int Fraction::getNumerator(){
    return numerator;
}
int Fraction::getDenominator(){
    return denominator;
}

//-----Overloaded Operators-----
Fraction Fraction::operator + (Fraction f){
    if (denominator == f.denominator){
        Fraction toBeReturned(numerator + f.numerator, denominator);
        return toBeReturned;
    }else{
        //Convert fractions to equivalent ones with same denominator
        Fraction A;
        Fraction B;

        A.numerator = numerator * f.denominator;
        A.denominator = denominator * f.denominator;

        B.numerator = f.numerator * denominator;
        B.denominator = f.denominator * denominator;

        //Add them 
        Fraction toBeReturned = A + B;
        //Return
        return toBeReturned;
    }
}
Fraction Fraction::operator - (Fraction f){
    if (denominator == f.denominator){
        Fraction toBeReturned(numerator - f.numerator, denominator);
        return toBeReturned;
    }else{
        //Convert fractions to equivalent ones with same denominator
        Fraction A;
        Fraction B;

        A.numerator = numerator * f.denominator;
        A.denominator = denominator * f.denominator;

        B.numerator = f.numerator * denominator;
        B.denominator = f.denominator * denominator;

        //Add them 
        Fraction toBeReturned = A - B;
        //Return
        return toBeReturned;
    }
}
Fraction Fraction::operator * (Fraction f){
    Fraction toBeReturned (numerator*f.numerator, denominator*f.denominator);
    return toBeReturned;
}
Fraction Fraction::operator / (Fraction f){
    Fraction A = (numerator, denominator);
    Fraction B (f.denominator, f.numerator); //Reciprocal of f
    return A*B;
}
Fraction Fraction::operator += (Fraction f){
    Fraction A = (numerator, denominator);
    Fraction toBeReturned = A + f;
    return toBeReturned;
}

void Fraction::operator - (){ //Negation
    numerator = 0 - numerator;
}
void Fraction::operator ++ (){ //Pre-inc
    numerator += denominator;
    normalize();
}
void Fraction::operator ++ (int){ //Post-inc
    numerator += denominator;
    normalize();
}

bool Fraction::operator < (Fraction f){
    double A = numerator/denominator;
    double B = f.numerator/f.denominator;

    if(A<B){
        return true;
    }else{
        return false;
    }
}
bool Fraction::operator <= (Fraction f){
    double A = numerator/denominator;
    double B = f.numerator/f.denominator;

    if(A<B || A==B){
        return true;
    }else{
        return false;
    }
}
bool Fraction::operator == (Fraction f){
    double A = numerator/denominator;
    double B = f.numerator/f.denominator;

    if(A=B){
        return true;
    }else{
        return false;
    }
}
bool Fraction::operator != (Fraction f){
    double A = numerator/denominator;
    double B = f.numerator/f.denominator;

    if(A=B){
        return false;
    }else{
        return true;
    }
}
bool Fraction::operator >= (Fraction f){
    double A = numerator/denominator;
    double B = f.numerator/f.denominator;

    if(A>B || A==B){
        return true;
    }else{
        return false;
    }
}
bool Fraction::operator > (Fraction f){
    double A = numerator/denominator;
    double B = f.numerator/f.denominator;

    if(A>B){
        return true;
    }else{
        return false;
    }
}

std::ostream &operator<<(std::ostream &output, const Fraction &F ) { 
    output << F.numerator << "/" << F.denominator;
    return output;            
}

std::istream &operator<<(std::istream &input, Fraction &F ) { 
    std::string Fraction;
    std::cout <<"input fraction (numerator/denominator): /n";   
    input >> Fraction;

    int delimiter = Fraction.find("/");

    std::string n = Fraction.substr(0, delimiter);
    std::string d = Fraction.substr(delimiter+1);

    F.numerator = stoi(n);
    F.denominator = stoi(d);

    return input;
}

//--------------------Main For Testing--------------------//
int main(){
    Fraction test3(20, 30);
	std::cout << "Should be \"2/3\": " << test3 << std::endl;
    Fraction test4(210, -60);
    std::cout << "Should be \"-7/2\": " << test4 << std::endl;
}
