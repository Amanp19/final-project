#include <Arduino.h>

#include <SoftwareSerial.h> // Library for creating virtual UART port


int x = 0; // Variables to store values

SoftwareSerial mySerial(10, 11); // Defining Virtual UART port at pin 10 and 11
// The above UART port will be used for communication with XBEE module



void setup() {
  Serial.begin(9600);// Starting Serial UART communication
  mySerial.begin(9600);// Starting Serial UART communication with XBEE


  pinMode(A0,INPUT); // X


  Serial.println("XBEE test");


}

void loop() {
  x = analogRead(A0);// Reading Value from the Joystick


  mySerial.println(x);// Send the data to XBEE
  Serial.println("Data Sent to XBEE");
  Serial.println(x);

  delay(200); // Small delay to make sure data transmission is completed and XBEE is not overwhelmed by incoming data




}
