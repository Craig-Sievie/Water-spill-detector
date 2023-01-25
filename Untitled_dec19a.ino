#include "thingProperties.h"

//Define pins on the board
int GREEN_LED = 32;
int RED_LED = 23;
int MOISTURE = A6;
int BUTTON = 33;

//Define variables for th
int moisture_level;
int moisture_threshold = 1500;
int button_value;
int button_touched = 15;
int redflashdelay = 500;

void setup() {
  pinMode(GREEN_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(MOISTURE,INPUT);
  pinMode(BUTTON,INPUT);
  
  //test to show device is responding
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(RED_LED,HIGH);
  delay(500); 
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(RED_LED,LOW);
  
  // Initialize serial and wait for port to open:
  Serial.begin(115200);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  moisture_level_exceeded=0;
  
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  Serial.println("Loop");
  moisture_level = analogRead(MOISTURE);
  button_value = touchRead(BUTTON);
  Serial.print("moisture_level: ");
  Serial.println(moisture_level);
  Serial.print("button_value: ");
  Serial.println(button_value);
  
  //Check to see if there is a water leak
  if (moisture_level < moisture_threshold){
    moisture_level_exceeded = moisture_level_exceeded + 1;
    ArduinoCloud.update();
    alert_mode();
  }
  else{
    standby_mode();
  }
}


//###########################################################
//###########################################################

void alert_mode(){
  Serial.println("Alert Mode");
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,LOW);
  while (moisture_level < moisture_threshold){
    digitalWrite(RED_LED,HIGH);
    delay(redflashdelay);
    digitalWrite(RED_LED,LOW);
    delay(redflashdelay);
    moisture_level=analogRead(MOISTURE);
    Serial.print("moisture_level: ");
    Serial.println(moisture_level);
    Serial.print("button_value: ");
    Serial.println(button_value);
  }
  digitalWrite(RED_LED,HIGH);
}

//###########################################################
//###########################################################

void standby_mode(){
  Serial.println("Standby Mode");
  Serial.print("moisture_level: ");
  Serial.println(moisture_level);
  Serial.print("button_value: ");
  Serial.println(button_value);
  digitalWrite(GREEN_LED,HIGH);
  delay(500);
  if (button_value < button_touched){
    delay(1000);
    button_value = touchRead(BUTTON);
    if (button_value < button_touched){
      digitalWrite(RED_LED,LOW);
      moisture_level_exceeded = 0; 
    }
  }
  digitalWrite(GREEN_LED,LOW);
  delay(5000);
}

//###########################################################
//###########################################################
