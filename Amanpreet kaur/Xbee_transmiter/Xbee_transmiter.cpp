#include <Arduino.h>
#include <SoftwareSerial.h> // Library for creating virtual UART port


int x = 0; // Variables to store values
int y = 0;
int x_cam = 0;


SoftwareSerial mySerial(10, 11); // Defining Virtual UART port at pin 10 and 11
// The above UART port will be used for communication with XBEE module

String data; // String Value for final output

void setup() {

  Serial.begin(9600);// Starting Serial UART communication
  mySerial.begin(9600);// Starting Serial UART communication with XBEE

  pinMode(A0,INPUT); // X
  pinMode(A1,INPUT); // Y


  pinMode(A2,INPUT); // X - 2nd Joystick

  Serial.println("Remote Joystick");  // A simple Print


}

void loop() {
  x = analogRead(A0); // Reading Values from both the Joysticks
  y = analogRead(A1);

  x_cam = analogRead(A2);

  data += "X:"; // Storing the values in a proper String Format
  data += (String)x;
  data += "-Y:";
  data += (String)y;
  data += "_C:";
  data += (String)x_cam;

  Serial.println(data);  // Printing the final String on Serial port

  Serial.println("Data Sent to Router");// SImple Print

  mySerial.println(data); // Send the data to XBEE


  delay(200); // Small delay to make sure data transmission is completed and XBEE is not overwhelmed by incoming data

  data = ""; // Erase the string data





  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }



}
