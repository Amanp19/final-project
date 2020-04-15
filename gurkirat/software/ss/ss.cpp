#include <Arduino.h>
#include <SoftwareSerial.h>
#include  <Servo.h>


Servo myservo;


SoftwareSerial mySerial(10, 11);

const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;

String data ;

int x = 505;
int y = 513;
int z = 510;
int c = 0;
int c_angle = 90;

int thres[] = {400,600,400,600,800,900};


void setup() {

  Serial.begin(9600);
  Serial.println("XBEE Receiver");

  mySerial.begin(9600);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  myservo.attach(9);
  myservo.write(c_angle);

}

void loop() {
  /*if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }

  delay(1);
  */
if(mySerial.available())
{
  while( mySerial.available())
    {
      char temp = mySerial.read();
      data += temp;
      delay(1);
    }

  //Serial.println(data);

  if(data.indexOf("X") != -1 and data.indexOf("Y") != -1 )
  {
    //Serial.println("Got Useful Data");
    String x_data = data.substring(data.indexOf("X")+2, data.indexOf("-"));
    String y_data = data.substring(data.indexOf("Y")+2, data.indexOf("_"));
    String c_data = data.substring(data.indexOf("C")+2);

    x = x_data.toInt();
    y = y_data.toInt();
    c = c_data.toInt();

    //Serial.println(x);
    //Serial.println(y);
    //Serial.println(c);

    if (x > thres[0] and x < thres[1] and y > thres[2] and y < thres[3])
    {
      Serial.println("STOP");
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
    }

    else
    {
      if(x >= thres[1])
      {
        Serial.println("FORWARD");
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
      }
      else if(x <= thres[0])
      {
        Serial.println("BACKWARD");
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
      }
      else if(y >= thres[3])
      {
        Serial.println("RIGHT");
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
      }
      else if(y <= thres[2])
      {
        Serial.println("LEFT");
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
      }
    }


    if(c > thres[4] and c < thres[5])
    {
      //myservo.detach();
      ;
    }

    else
    {
      if(c <= thres[4])
        {
          Serial.print("Camera Moving Left");
          //myservo.attach(9);
          //delay(5);
          c_angle += 2;
          Serial.println(c_angle);
          if(c_angle > 179)
          {
            c_angle = 180;
          }
          myservo.write(c_angle);
        }
      if(c >= thres[5])
        {
          Serial.print("Camera Moving Right");
          //myservo.attach(9);
          //delay(5);
          c_angle -= 2;
          Serial.println(c_angle);
          if(c_angle < 1)
          {
            c_angle = 0;
          }
          myservo.write(c_angle);
        }
    }

    delay(200);
  }
  else
  {
    Serial.println("STOP");
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }



  data = "";


}

}
