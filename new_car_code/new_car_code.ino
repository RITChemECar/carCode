//two variable's in charge of getting the photoresistor to work
const int photoResistor = A0;
const int newSwitch = A3;
//const int ledPin = 9;
int led = 5;
int value; //the value that the photoresistor reads

//two pins where MOSFETs (Metal Oxide Semiconductor Field Effect Transistor, google this for future people working on this)
int MosfetPin = 13;

int bridgePin5 = 5;
int bridgePin6 = 6;
int newPin1 = 7;

int f_hz = 10;
int var = 9;
int sensorValue;

int carSwitch = 2;
float R = 0;
int cond = 5000; // need adjustment
int prevPhotoResistorValue; 
int newPin = 12;

extern volatile long time;
extern volatile long time1;
extern volatile long time2;
boolean hasRun = false;

String dataLabel1 = "Photoresistor";
String dataLabel2 = "Time";

void setup() {
  pinMode(MosfetPin, OUTPUT);
  pinMode(var, OUTPUT);
  pinMode(carSwitch, INPUT);
  pinMode(bridgePin5, OUTPUT);
  pinMode(bridgePin6, OUTPUT);
  pinMode(newPin,OUTPUT);
  pinMode(newSwitch, INPUT);
  pinMode(newPin1, OUTPUT);
  digitalWrite(newPin1, HIGH);
  Serial.begin(9600);
  
}

 void loop() {
   float volts = analogRead(newSwitch) * (5.0 / 1023.0);
  


   if(volts < 3){
    carSwitchOn();
    //photo();
    time = millis();
    
   }//end of switch statement

   prevPhotoResistorValue = value;
   value = analogRead(photoResistor);
   Serial.print(value);
   Serial.print(", ");
   Serial.println(time);
   if(prevPhotoResistorValue - value >= 10){
      //Serial.println((prevPhotoResistorValue - value));
      //Serial.println("Terminated Session");
      noInterrupts();
      time = 0;
      interrupts();
      carSwitchOff();
      //digitalWrite(MosfetPin, LOW);
      //exit(0);
    }
    else{
      digitalWrite(5, HIGH);
    }  

  //  else{
  //    carSwitchOff();
  //   //Serial.println(volts);
  //  }
}

void jolt(){
  digitalWrite(bridgePin5, HIGH);
  digitalWrite(bridgePin6, HIGH);
}


//testing purposes
void squareWave(){
  digitalWrite(var, LOW);
  delay(20);
  digitalWrite(var, HIGH);
  delay(20);
}


//turns car on
void carSwitchOn(){
  digitalWrite(carSwitch, HIGH);
  digitalWrite(MosfetPin, HIGH);
  digitalWrite(newPin, LOW);
}

//code to turn car off, setting all output pins to 0 
void carSwitchOff(){
  analogWrite(var, 0);
  analogWrite(5, 0);
  analogWrite(carSwitch, 0);
  digitalWrite(MosfetPin, 0);
  digitalWrite(MosfetPin, LOW);
  digitalWrite(newPin1, LOW);
  // digitalWrite(bridgePin5, LOW);
  // digitalWrite(bridgePin6, LOW); 

}