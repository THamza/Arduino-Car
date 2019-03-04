int trigPin = 9;
int echoPin = 10;
float duration;
int distance;
int autoPilot = 0;
int Running = 0;

void Forward();
void Left();
void Back();
void Right(int del);
void For();
void Stop();

String message; //string that stores the incoming message

int In3 = 7;
int In4 = 8;
int ENA = 6;
int In1 = 12;
int In2 = 13;
int ENB = 11;
int SPEED = 250;

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input 
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(ENB, OUTPUT);
  Serial.begin(9600); //set baud rate
}


void loop()
{ 
  while(Serial.available())
  {//while there is data available on the serial monitor
    message+=char(Serial.read());//store string from serial command
  }
  if(!Serial.available())
  {   
      if (autoPilot == 1){
        if(message!=""){//if data is available
            Serial.println(message); //show the data     
            Serial.println("_____________________"); //show the data   
            //TODO: Fix the problem of buffering the first character  
            //no-pilot
            if(message == "n") { 
              autoPilot = 0; 
            }
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
            duration = pulseIn(echoPin, HIGH);
            distance= duration*0.034/2;
            Serial.print("Distance: ");
            Serial.println(distance);
            if(distance >= 25 && Running == 0)
              For();
            if(distance <= 25 && Running != 0){
              Stop();
              delay(200);
              Right(800);
            }
          }
      }

      if (autoPilot == 0){
        if(message!=""){
            Serial.println(message); //show the data 
            Serial.println("_____________________"); //show the data   
            //TODO: Fix the problem of buffering the first character  
            //pilot  
            if(message == "p"){  
              autoPilot = 1;
            }
            if(message =="s")
              Back();
            if(message=="d")
              Right(200);
            if(message =="a")
              Left();
            if(message =="w")
              Forward(); 
            
          }
        }
        message=""; //clear the data
      
    }
}

void Forward(){
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(ENA, SPEED);
  
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(ENB, SPEED);
    delay(200);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(ENA, 0);
  
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(ENB, 0);
}

void For(){
    Running = 1;
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(ENA, SPEED);
  
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    analogWrite(ENB, SPEED);
}

void Stop(){ 
    Running = 0;
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(ENA, 0);
  
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    analogWrite(ENB, 0);
}

void Left(){
    digitalWrite(In4, HIGH);
    digitalWrite(In3, LOW);
    analogWrite(ENB, SPEED);
    delay(200);
    digitalWrite(In4, HIGH);
    digitalWrite(In3, LOW);
    analogWrite(ENB, 0);
}

void Right(int del){
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(ENA, SPEED);
    delay(del);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(ENA, 0);
}

void Back(){
  
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(ENA, SPEED);
  
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    analogWrite(ENB, SPEED);
    delay(200);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(ENA, 0);
  
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    analogWrite(ENB, 0);
    
    
}

