/**
 * @file PWM-motor-control.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to drive wheel motors through a motor controller.
 * @version 1.0
 * @date 2021-07-04
 *
 * @copyright Copyright (c) 2021
 *
 */

int E1 = 6; // Left wheel PWM pin (must be a PWM pin)
int M1 = 7; // Left wheel direction digital pin
int E2 = 5; // Right wheel PWM pin (must be a PWM pin)
int M2 = 4; // Right wheel direction digital pin

void setup()
{
    pinMode(M1, OUTPUT); // Configure pin M1 for output
    pinMode(M2, OUTPUT); // Configure pin M2 for output
}

void loop()
{
    int u; // A variable for the motor PWM command [0-255]

    // -------------------------Forwards and Backwards----------------------------------
    
        // Tell the motor driver board what to do
        digitalWrite(M1, LOW);  // Drive forward (left wheels)
        digitalWrite(M2, HIGH); // Drive forward (right wheels)
        analogWrite(E1, 128);     // PWM speed command (left wheels)
        analogWrite(E2, 128);     // PWM speed command (right wheels)

        // Brief delay (perhaps not necessary)
        delay(10000);

        analogWrite(E1, 0);     // PWM speed command (left wheels)
        analogWrite(E2, 0);     // PWM speed command (right wheels)

        delay(5000);
        
        digitalWrite(M1, HIGH);  // Drive backwards (left wheels)
        digitalWrite(M2, LOW); // Drive backwards (right wheels)
        analogWrite(E1, 128);     // PWM speed command (left wheels)
        analogWrite(E2, 128);     // PWM speed command (right wheels)

        delay(10000);

        analogWrite(E1, 0);     // PWM speed command (left wheels) 
        analogWrite(E2, 0);     // PWM speed command (right wheels)

        delay(5000);

         // Tell the motor driver board what to do
        digitalWrite(M1, LOW);  // Drive forward (left wheels)
        digitalWrite(M2, HIGH); // Drive forward (right wheels)
        analogWrite(E1, 255);     // PWM speed command (left wheels)
        analogWrite(E2, 255);     // PWM speed command (right wheels)

        // Brief delay (perhaps not necessary)
        delay(5000);

        analogWrite(E1, 0);     // PWM speed command (left wheels)
        analogWrite(E2, 0);     // PWM speed command (right wheels)

        delay(2500);
        
        digitalWrite(M1, HIGH);  // Drive backwards (left wheels)
        digitalWrite(M2, LOW); // Drive backwards (right wheels)
        analogWrite(E1, 255);     // PWM speed command (left wheels)
        analogWrite(E2, 255);     // PWM speed command (right wheels)

        delay(5000);

        analogWrite(E1, 0);     // PWM speed command (left wheels)
        analogWrite(E2, 0);     // PWM speed command (right wheels)

        delay(5000);
        
    // ---------------------------Turn on the spot-------------------------------
        
        //Turn on spot
        digitalWrite(M1, LOW);  // Drive forward (left wheels)
        digitalWrite(M2, LOW); // Drive backwards (right wheels)
        analogWrite(E1, 128);     // PWM speed command (left wheels)
        analogWrite(E2, 128);     // PWM speed command (right wheels)

        delay(4000);

        analogWrite(E1, 0);     // PWM speed command (left wheels)
        analogWrite(E2, 0);     // PWM speed command (right wheels)

        delay(2000);

        digitalWrite(M1, HIGH);  // Drive backwards (left wheels)
        digitalWrite(M2, HIGH); // Drive forwards (right wheels)
        analogWrite(E1, 128);     // PWM speed command (left wheels)
        analogWrite(E2, 128);     // PWM speed command (right wheels)

        delay(4000);
        

    // ------------------------------Turn Left and right-----------------------------
        digitalWrite(M1, LOW);  // Drive forward (left wheels)
        digitalWrite(M2, HIGH); // Drive forwards (right wheels)
        analogWrite(E1, 255);     // PWM speed command (left wheels)
        analogWrite(E2, 128);     // PWM speed command (right wheels)

        delay(4000);

        analogWrite(E1, 0);     // PWM speed command (left wheels)
        analogWrite(E2, 0);     // PWM speed command (right wheels)

        delay(2000);

        digitalWrite(M1, LOW);  // Drive forwards (left wheels)
        digitalWrite(M2, HIGH); // Drive forwards (right wheels)
        analogWrite(E1, 128);     // PWM speed command (left wheels)
        analogWrite(E2, 255);     // PWM speed command (right wheels)

        delay(4000);
}
