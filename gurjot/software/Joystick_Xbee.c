#include <Arduino.h>
#include <SoftwareSerial.h> 



int x = 0;

SoftwareSerial mySerial(10, 11);




void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
 
 
  pinMode(A0,INPUT); 


  Serial.println("XBEE test");


}

void loop() {
  x = analogRead(A0);

 
  mySerial.println(x);
  Serial.println("Data Sent to XBEE");
  Serial.println(x);

  delay(200); 

 

}
