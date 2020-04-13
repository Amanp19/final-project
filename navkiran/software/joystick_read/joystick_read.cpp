#include <Arduino.h>

int  x = 0;
int y = 0;

void setup() {

  Serial.begin(9600);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);

}

void loop() {
  x = analogRead(A0);
  y = analogRead(A1);

  Serial.print("X : ");
  Serial.print(x);
  Serial.print("  Y: ");
  Serial.println(y);

}

