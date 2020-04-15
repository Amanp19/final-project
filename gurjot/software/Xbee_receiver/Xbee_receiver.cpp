#include <Arduino.h>
#include <SoftwareSerial.h> // Library for creating virtual UART port

SoftwareSerial mySerial(10, 11); // Defining Virtual UART port at pin 10 and 11
// The above UART port will be used for communication with XBEE module


String data; // To store incoming data

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);// Starting Serial UART communication
  mySerial.begin(9600);// Starting Serial UART communication with XBEE

  Serial.println("XBEE Receiver Test");


}

void loop()
{

if(mySerial.available()) // If any data is coming from Xbee
{
  while( mySerial.available()) // Keep reading data while it is coming
    {
      char temp = mySerial.read(); // Store the received byte in a char variable
      data += temp; // Append that char variable to string
      delay(1); // Very small delay for Serial data incoming stabilisation
    }
}
}
