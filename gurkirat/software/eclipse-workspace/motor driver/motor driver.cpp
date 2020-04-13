#include <Arduino.h>

const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;


void setup() {


  Serial.begin(9600);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

}

void loop() {

      Serial.println("STOP");
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);

      delay(2000);

        Serial.println("FORWARD");
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);

        delay(2000);


        Serial.println("BACKWARD");
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);

        delay(2000);


        Serial.println("RIGHT");
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);

        delay(2000);


        Serial.println("LEFT");
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);

        delay(2000);


}
