#include <Arduino.h>
#include <SoftwareSerial.h>


SoftwareSerial mySerial(10, 11);

void setup() {


  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("XBEE Transmitter Test");


}

void loop()
{

  mySerial.println("HELLO");
  delay(2000);

}
