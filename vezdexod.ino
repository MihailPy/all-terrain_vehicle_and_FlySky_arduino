
#include "SoftwareSerial.h"
#include "FlySkyIBus.h"


SoftwareSerial MS(2,3);

void forward()
{
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void backward()
{
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
void left()
{
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}

void right()
{
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void setup() {
  MS.begin(115200);
  Serial.begin(9600);
  IBus.begin(MS);
}

void loop() {
  IBus.loop();

  //for (int i = 0; i < 10; i++)
  //{
    //Serial.print(" CH" ); Serial.print(i); Serial.print(" "); Serial.print(IBus.readChannel(i));
  //}
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  int forth_and_back = IBus.readChannel(1);
  int left_right = IBus.readChannel(3);
  int mode = IBus.readChannel(9);
  int go = 0;
  int val1;
  int val2;
  int lr[2];
  int fb;
  if (mode == 1000){go = 0;}
  else if (mode == 2000){go = 1;}
  if (forth_and_back < 1497)
  {
    if (go == 0){forward();}
    else if (go == 1){left();}
    val1 = forth_and_back - 1503;
    val1 = abs(val1);
    val1 = val1 / 2;
    fb = 5;

    if (val1 > 255) {val1 = 255;}
  }
  else if (forth_and_back > 1502)
  {
    if (go == 0){backward();}
    else if (go == 1){right();}
    
    val1 = (forth_and_back - 1497) / 2;
    fb = 6;

    if (val1 > 255) {val1 = 255;}
  }
  else
  {
    //backward();
    val1 = 0;
  } 

  if (left_right > 1502)
  {
    
    val2 = (left_right - 1497) / 2;
    lr[0] = val1;
    lr[1] = val1 - val2;
    if (lr[1] < 0){lr[1] = 0;}
    else if (lr[1] > 255) {lr[1] = 255;}
  }
  else if (left_right < 1497)
  {
    
    val2 = left_right - 1503;  
    val2 = abs(val2);
    val2 = val2 / 2;
    lr[0] = val1 - val2;
    lr[1] = val1;
    if (lr[0] < 0) {lr[0] = 0;}
    else if (lr[0] > 255) {lr[0] = 255;}
  }
  else
  {
    val2 = 0;
    lr[0] = val1;
    lr[1] = val1;
  } 

  
  int l = lr[0];
  int r = lr[1];

  
  analogWrite(5, r);
  analogWrite(6, l);
  Serial.print(l);
  Serial.print("      ");
  Serial.println(r);
  
}
