/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/chakkraphanchanthanak/IOTproject/src/IOTproject.ino"
/*
 * Project IOTproject
 * Description: ParkingSystem
 * Author: Chakkraphan Chanthanak
 * Date: 05.02.2021
 */
// setup() runs once, when the device is first turned on.
void setup();
void myHandler1(const char *event, const char *data);
void myHandler2(const char *event, const char *data);
void loop();
void CarEntered();
void carExited();
#line 8 "/Users/chakkraphanchanthanak/IOTproject/src/IOTproject.ino"
Servo myservo;
int pos;

int led1 = D0;
int led2 = D1;

int carIn = D4;
int carOut = D5;

 // Put initialization like pinMode and begin functions here.
void setup() {
 pinMode(carIn,INPUT_PULLUP);
 pinMode(carOut,INPUT_PULLUP);

 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 myservo.attach(A5);

  // Subscribe to the integration response event
  Particle.subscribe("hook-response/EVENT_ENTER", myHandler1, MY_DEVICES);

    // Subscribe to the integration response event
  Particle.subscribe("hook-response/EVENT_EXIT", myHandler2, MY_DEVICES);
}

void myHandler1(const char *event, const char *data) {
  // Handle the integration response
}

void myHandler2(const char *event, const char *data) {
  // Handle the integration response
}
    
// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  CarEntered();
  carExited();
}

void CarEntered() {
  // Car Enter function
  String data = String(10);
  int carEnter = digitalRead(carIn);
  if (carEnter == LOW)
  {
   digitalWrite(led1, HIGH);
   delay(500); // delayed for half a second

    for (pos = 140; pos >= 45; pos -= 1) {
      myservo.write(pos);
      delay(50);
    }
    delay(1000);
    for (pos = 45; pos <= 140; pos += 1) {
      // in steps of 1 degree
      myservo.write(pos);
      delay(50);
    }
   Particle.publish("EVENT_ENTER", data, PRIVATE);
  }
  else 
  {
    digitalWrite(led1, LOW);
  }
}

void carExited() {
  // Car Exit function
  String data = String(10);
  int carExit = digitalRead(carOut);
  if (carExit == LOW)
  {
   digitalWrite(led2, HIGH);
   delay(500); // delayed for half a second

    for (pos = 140; pos >= 45; pos -= 1) {
      myservo.write(pos);
      delay(50);
    }
    delay(1000);
    for (pos = 45; pos <= 140; pos += 1) {
      // in steps of 1 degree
      myservo.write(pos);
      delay(50);
    }
  Particle.publish("EVENT_EXIT", data, PRIVATE);
  }
  else 
  {
    digitalWrite(led2, LOW);
  }
}
