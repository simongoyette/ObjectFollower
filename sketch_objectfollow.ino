/*
The goal of this program is to have the elegoo robot car follow objects
*/

#include <Servo.h>   //Includes the servo library
Servo myservo;    //Creates an object called myservo

int echoPin = 12;    //Configures the echo pin as pin 12
int trigPin = 13;   //Configures the trig pin as pin 13
float DF;   
float DR;   
float DL;   

float Duration, Distance;

#define PWMA 5   //Configures the left wheel speed as pin 5
#define AIN1 8   //Configures the left wheel forward as pin 8
#define PWMB 6   //Configures the right wheel speed as pin 6
#define BIN1 7   //Configures the right wheel forward as pin 7
#define STBY 3    //Configures the STBY as pin 3

int OFF = 0;    //The speed of the car is 0
int ON = 100;   //The speed of the car is 100

float Distance_result();    //Declares the Distance_result function

float Distance_result() {   //To test the ultrasonic sensor using pulses
    digitalWrite(trigPin, LOW);   //Sets the trigPin as LOW
    delayMicroseconds(2);    //2 microsecond delay
    digitalWrite(trigPin, HIGH);   //Sets the trigPin as HIGH
    delayMicroseconds(10);    //10 microsecond delay
    digitalWrite(trigPin, LOW);   //Sets the trigPin as LOW
    Duration = pulseIn(echoPin, HIGH);   //Float variable that measures how far the nearest object is
    Distance = Duration / 58.0;   //Gives us the result in cm
    return Distance;   //Returns it as float
}


void Forward()    //Function to make robot car move forwards
 {
  digitalWrite(AIN1,1);   //Sets the left wheel forward as HIGH
  analogWrite(PWMA,ON);   //Sets the left wheel speed as 100
  digitalWrite(BIN1,1);   //Sets the right wheel forward as HIGH
  analogWrite(PWMB,ON);   //Sets the right wheel speed as 100
}

void Stop()   //Function to make robot car stop
{ 
  digitalWrite(AIN1,1);   //Sets the left wheel forward as HIGH
  analogWrite(PWMA,OFF);    //Sets the left wheel speed as 0
  digitalWrite(BIN1,1);   //Sets the right wheel forward as HIGH
  analogWrite(PWMB,OFF);    //Sets the right wheel speed as 0
}

void Backward()   //Function to make robot go backwards
{
  digitalWrite(AIN1,0);   //Sets the left wheel forward as LOW
  analogWrite(PWMA,ON);   //Sets the left wheel speed at 100
  digitalWrite(BIN1,0);   //Sets the right wheel forward as LOW
  analogWrite(PWMB,ON);   //Sets the right wheel speed as 100
}

void Left()   //Function to make robot go left
{
    digitalWrite(AIN1,0);   //Sets the left wheel forward as LOW
    analogWrite(PWMA,ON);   //Sets the left wheel speed as 100
    digitalWrite(BIN1,1);   //Sets the right wheel forward as HIGH
    analogWrite(PWMB,ON);   //Sets the right wheel speed as 100
}

void Right()    //Function to make robot go right
{
    digitalWrite(AIN1,1);   //Sets the left wheel forward as HIGH
    analogWrite(PWMA,ON);   //Sets the left wheel speed as 100
    digitalWrite(BIN1,0);   //Sets the right wheel forward as LOW
    analogWrite(PWMB,ON);   //Sets the right wheel speed as 100
}  


void setup() {
    myservo.attach(10);   //Attaches the servo motor to pin 10
    pinMode(trigPin, OUTPUT);    //Sets the trigPin as an output
    pinMode(echoPin, INPUT);   //Sets the echoPin as an input
    pinMode(PWMA, OUTPUT);    //Sets the left wheel speed as an output
    pinMode(AIN1, OUTPUT);    //Sets the left wheel forward as an output
    pinMode(PWMB, OUTPUT);    //Sets the right wheel speed as an output
    pinMode(BIN1, OUTPUT);    //Sets the right wheel forward as an output
    pinMode(STBY, OUTPUT);    //Sets the STBY as an output
    digitalWrite(STBY, HIGH);   //Sets the STBY as HIGH
}

void loop() {
    myservo.write(90);    // Sets the servo facing forwards
    delay(500);   //Delay for 500 milliseconds
    DF = Distance_result();   // Saves the distance from the nearest object
    myservo.write(0);   // Sets the servo facing to the right
    delay(500);   //Delay for 500 milliseconds
    DR = Distance_result();    // Saves the distance from the nearest object 
    myservo.write(180);   // Sets the servo facing to the left
    delay(500);   //Delay for 500 milliseconds
    DL = Distance_result();    // Saves the distance from the nearest object

    if (DF >= DR) {    // If the distance forward is larger than distance right...
        if (DR >= DL) {    // If distance right is larger than distance left...
            Left();   // Turn left
            delay(700);
            Forward();
        } else {
            Right();    // Turn right
            delay(700);
            Forward();
        }
    } else {
        if (DF >= DL) {    // If the distance forward is larger than distance left...
            Left();   // Turn left
            delay(700);
            Forward();
        }
    }

    if (DF <= 10) {   // If the object is less than or equal to 10cm away...
        Backward();   // Robot goes
    } else if (10 < DF && DF <= 20) {   // If the object is between 10 and 20cm...
        Forward();    // Robot moves forward
    }
}