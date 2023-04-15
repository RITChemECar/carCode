// #include <iostream>
// using namespace std;

const int sensorPin = A0;  // Analog input pin that senses Vout
int sensorValue = 0;       // sensorPin default value
float Vin = 5;             // Input voltage
float Vout = 0;            // Vout default value
float Rref = 270;           // Reference resistor's value in ohms (you can give this value in kiloohms or megaohms - the resistance of the tested resistor will be given in the same units)
float R = 0;                // Tested resistors default value
// int switchPin=13;              //Switch pin
bool switchState = 0;            //switch state
const byte LEDPin1 = 9;         // LED pin out red
//const byte LEDPin2 = 12;         // LED pin out green
int MosfetPin1 = 7;       // transistor output pin
int MosfetPin2 = 12;
int cond = 5000;            // Stopping Resistance |NEEDS ADJUSTMENT|
int value;
int ledPin = 9;
int onOff = 2;

void setup ()
{
  pinMode(MosfetPin1, INPUT);  // Initialize LED pin output
  pinMode(MosfetPin2, INPUT);
  pinMode(LEDPin1, OUTPUT);  // Initialize LED pin output
  //pinMode(LEDPin2, OUTPUT);  // Initialize LED pin output
  digitalWrite(MosfetPin1, LOW);
  digitalWrite(MosfetPin2, HIGH);

  // digitalWrite(switchPin, HIGH);
  carSwitchedOn();
}


//this stuff loops constantly
//it reads from the switch state and uses that to see if the car has been turned on yet. ! means the car is on, 0 is off
void loop ()
{
  value = analogRead(sensorPin);
  if(value > 25){
    digitalWrite(ledPin, LOW);

  }

  else{
    digitalWrite(ledPin, HIGH); //Turn led on
    digitalWrite(switchPin, 0);
  }

  switchState = digitalRead(switchPin);  //read from the switch pin and get it's state (1 or 0)
  //if switched on, tell the car it is in fact, switched on
  // if (switchState == 1)
  // {
  //   carSwitchedOn();
  //   iodineClockNotFinish();
  // }

  // //if the car is switched off, then do switched off stuff
  // else
  // {
  //   carSwitchedOff();
  // }    
  //carSwitchedOff();  
} 


//what to do while the car is switched ON, and powered on
void carSwitchedOn()
{
  //calculate how restive the resistor is this moment
  // digitalWrite(MosfetPin1, LOW);
  // digitalWrite(MosfetPin2, LOW);
  digitalWrite(onOff, HIGH);
  calculateResistance();
  // check to see if current is running through mosfet pin 1
  // if(analogRead(MosfetPin1) = HIGH){
  //   digitalWrite(MosfetPin2, LOW);
  // }
  // else{
  //   digitalWrite(MosfetPin2, HIGH);
  // }

  //if the reaction has finished (car go stop)
  if(reactionFinished())
  {
    iodineClockFinish();
  }

  //if the reaction has not finished (car go vroom vroom)
  else
  {
    iodineClockNotFinish();
  }
}


//what to do while the car is switched OFF, but powered on
void carSwitchedOff()
{
  digitalWrite(LEDPin1, HIGH);          //makes color of led Red indicating arduino off
  //digitalWrite(LEDPin2, LOW);
  digitalWrite(MosfetPin2, LOW);
  //digitalWrite(onOff, LOW);
}


//what to do once the clock reaction has been detected to reach it's end
void iodineClockFinish()
{
  digitalWrite(MosfetPin1, 0);          //prevents current through mosfet i.e. turns off motor
  digitalWrite(LEDPin1, HIGH);        //Makes Orange color tricolor led
  //digitalWrite(LEDPin2, HIGH);
}


//what to do while the clock reaction has not finished
void iodineClockNotFinish()
{
  analogWrite(MosfetPin1, HIGH);      //allows current through mosfet i.e. turns on motor
  // if(analogRead(MosfetPin1) == 0){
  //   digitalWrite(MosfetPin2, HIGH);
  // }

  // else{
  //   digitalWrite(MosfetPin1, LOW);
  // }
  // digitalWrite(LEDPin1, LOW);       //Makes green color tricolor led
  // digitalWrite(LEDPin2, HIGH);
  
}


//returns if the clock reaction has reached it's end
bool reactionFinished()
{
  return R > cond; //if the current resistance is greater than the needed resistance then the reaction has not finished]
}


//calculate the resister's value and set it into R
void calculateResistance()
{
  //read the value from the sensorPin (Arduino can sense from 0-1023, 1023 is 5V)
  sensorValue = analogRead(sensorPin);
  Vout = (Vin * sensorValue) / 1023;    // Convert Vout to volts
  R = Rref * (1 / ((Vin / Vout) - 1));  // Formula to calculate tested resistor's value                
  Serial.println(R);                    // Give calculated resistance in Serial Monitor
  
}
