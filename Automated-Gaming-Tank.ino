#include <Servo.h>
String bluetoothRead, Str_x, Str_y, Str_p;
int x ;
int y ;
int points;
int length;
int laser=13;
int pwmMotorA=11;
int pwmMotorB=12;
int izqA = 5;
int izqB = 6;
int derA = 9;
int derB = 10;
int vel = 130;
int vel2 = 110;// velocity (0-255)

// Declare the Servo pin
int servoup = 3;
int servodown = 4;
// Create a servo object
Servo Servo1;
Servo Servo2;



void setup() {
  Serial.begin(115200);
  pinMode(pwmMotorA, OUTPUT); 

  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(pwmMotorB, OUTPUT); 
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
  analogWrite(pwmMotorA,110);
  analogWrite(pwmMotorB,110);

  Servo1.attach(servoup);
  Servo2.attach(servodown);

  pinMode(laser, OUTPUT);

}


void loop() {
  int i = 0;
  char commandbuffer[1000];


  if (Serial.available() > 0){

    delay(10);

    while (Serial.available()) {
      digitalWrite(laser,HIGH);
      commandbuffer[i++] = Serial.read();

    }
    commandbuffer[i++] = '\0';
    bluetoothRead = (char*)commandbuffer;
    length = bluetoothRead.length();


    if (bluetoothRead.substring(0, 1).equals("x")) {

      i = 1;
      while (bluetoothRead.substring(i, i + 1) != ("y")) {
        i++;
      }

      Str_x = bluetoothRead.substring(1, i);
      x = Str_x.toInt();



      Str_y = bluetoothRead.substring(i + 1,length - 1);
      y = Str_y.toInt();

      Str_p = bluetoothRead.substring(length - 1, length);
      points = Str_p.toInt();


      i = 1;

      Stop();

      if (y > 80)
      {
         down();

      } else if (y < 30)
      {
      
         up();

      }


      if (x < 25) {
        Left();


      }
      if (x < 40)
      {

        servo_left();

      }
      if (x > 130)
      {
        Right();

      }
      if (x > 150)
      {
        servo_right();
      }


      if (x < 140 && x > 40) {
        if (points == 1) {
          Forward();

        }
        if (points == 0) {
          Stop();
        }
        if (points == 2) {
          Back();
        }
      }



    }
  }
  else {digitalWrite(laser,LOW);
    analogWrite(pwmMotorA,0);
  analogWrite(pwmMotorB,0);
 
  }
}


void Left() {

  Serial.println("left");
  digitalWrite(derB, HIGH);
  digitalWrite(izqB,LOW);
  digitalWrite(derA,LOW);
 digitalWrite(izqA, HIGH);

}


void Right() {
  Serial.println("right");
 digitalWrite(derB,LOW);
  digitalWrite(izqB, HIGH);
  digitalWrite(izqA, LOW);
 digitalWrite(derA, HIGH);
}


void Back() {
  Serial.println("back");
 digitalWrite(derA, LOW);
digitalWrite(izqA, LOW);
  digitalWrite(derB, HIGH);
digitalWrite(izqB,HIGH);
}


void Forward() {
  Serial.println("forward");
digitalWrite(derB,LOW);
digitalWrite(izqB, LOW);
 digitalWrite(derA,HIGH);
digitalWrite(izqA, HIGH);

}


void Stop() {
  Serial.println("stop");
 digitalWrite(derB,LOW);
 digitalWrite(izqB, LOW);
digitalWrite(derA,LOW);
 digitalWrite(izqA,LOW);
}


void up() {
  Serial.println("down");
  Servo1.write(90);

}
void down() {

  Serial.println("up");
  Servo1.write(100);

}


void servo_left() {
  Serial.println("servo_right");
  Servo2.write(110);


}
void servo_right() {
  Serial.println("servo_left");
  Servo2.write(50);
}




