#include <iostream>
#ifndef fraction_19ng38_H
#define fraction_19ng38_H

class Fraction{
    public:
        //-----Class Fields-----
        int numerator;
        int denominator;

        //-----Constructors-----
        Fraction();
        Fraction(int);
        Fraction(int,int);

        //-----Class Methods-----
        void normalize();
        int greatestCommonDivisor(int, int);

        int getNumerator();
        int getDenominator();

        //-----Operators to be overloaded-----
        //Binary:
        Fraction operator + (Fraction);
        Fraction operator - (Fraction);
        Fraction operator * (Fraction);
        Fraction operator / (Fraction);
        Fraction operator += (Fraction);
        //Unary:
        void operator - (); //Negation
        void operator ++ (); //Pre-increment
        void operator ++ (int); //Post-increment
        //Comparison
        bool operator < (Fraction);
        bool operator <= (Fraction);
        bool operator == (Fraction);
        bool operator != (Fraction);
        bool operator >= (Fraction);
        bool operator > (Fraction);

        friend std::ostream &operator<<(std::ostream &output, const Fraction &F );
        friend std::istream &operator<<(std::istream &input, const Fraction &F );
};

// struct FractionException : public exception{
//     public:
//         const char* what() const throw(){ //const--should not change the state of the object, throw()--function cannot throw an exception
//             return "FractionException: Illegal denominator value.";
//         }
// } ;

#endif