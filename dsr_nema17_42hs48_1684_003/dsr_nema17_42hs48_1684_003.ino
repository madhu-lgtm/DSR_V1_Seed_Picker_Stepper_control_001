/*
Code Version 3 :- micro step selection based in range 5rpm to 100rpm
Code Version 2 :- implement RPM calculator in setup section for the micro step and dt selected
Code Version 1 :- Check accel lib and micro stepping 
---------------- Components Used ----------------
Driver Used  = TB6600
Stepper Used = Nema 17, 42HS48-1684, 
Gear Box = No
Micro Step used = 1 (Full Step Mode - 200SPR) S1 = 1, S2 = 1, S3 = 0
Current Set = 2Amp  S4 = 1, S5 = 0, S6 = 0
Input Volatge = 12v (8amp) for driver 
Arduino = Nano original
12v to 5v buck (for powering Nano)
--------------------------------------------------

-------------- Connections -------------------
TB6600 to Nano
 ENA- , DIR- and PUL-  ->   gnd of arduino
 ENA+                  ->   D7
 DIR+                  ->   D8
 PUL+                  ->   D9 
-----------------------------------------------


Created on :- 04-02-2026
Created by :- K Madhu Mohan Chary 
For code enquiry :- madhu@marutdrones.com 

*/
// #include <AccelStepper.h>

// Used Common cathode setup on driver
const byte pul_pin = 9; //pulse pin 
const byte dir_pin = 8; //direction pin
const byte ena_pin = 7; //enable pin

//Create object of AccelStepper
// AccelStepper seed_stepper(AccelStepper::DRIVER,pul_pin,dir_pin);

//int dt = 400; //min 400(375rpm) ; max 1000(150rpm) @ 1.5Amp 200 SPR (minimum rpm itself is 150rpm)
//int dt = 1500; //min 140(535.71rpm) ; max 1500(50rpm) @ 1.5Amp 400A SPR (Will not fall in our range of rpm)
//int dt = 1750; //min 100(375rpm) max 1750(21.43rpm) @ 1.5Amp 800 SPR (Will Struggle at low rpm)
//int dt = 1500; //min 70(267.86rpm) max 1500(12.5rpm) @ 1.5Amp 1600 SPR (low Vibrations at 12.5rpm) 10000 -1.88rpm
//int dt = 12000; //min 15(625rpm) max 1500(6.25rpm) @ 1.5Amp 3200 SPR (********Recomended***********) 
//int dt = 1500; //min 7 max 1500 @ 1.5Amp 64000 SPR (Not Recomended)

//micro step selection based in range 5rpm to 100rpm
unsigned long SPR = 3200; //Steps per rotation (unsigned long for rpm calculation)
unsigned long dt = 100; //micro seconds
int dt_min = 100; //100 -> 93.75rpm @3200SPR (or)   200 -> 93.75 @1600SPR
int dt_max = 1000; //1000 -> 9.38rpm @3200SPR (or)  2000 -> 9.38 @1600SPR
float rpm ; //rpm must be float or double 

void setup() {
  pinMode(pul_pin,OUTPUT);
  pinMode(dir_pin,OUTPUT);
  pinMode(ena_pin,OUTPUT);
  digitalWrite(ena_pin,LOW);
  digitalWrite(dir_pin,LOW);
  Serial.begin(9600);

  delay(100);
  
  // seed_stepper.setMaxSpeed(2000);
  // seed_stepper.setSpeed(1000);

  rpm = 30000000.0 / (SPR * dt); //importent
  Serial.print("With SPR = ");
  Serial.print(SPR);
  Serial.print(" and dt = ");
  Serial.print(dt);
  Serial.print(" Calculated RPM = ");
  Serial.println(rpm);
}

void loop()
{

  //seed_stepper.runSpeed();
  digitalWrite(pul_pin,LOW);
  delayMicroseconds(dt);
  digitalWrite(pul_pin,HIGH);
  delayMicroseconds(dt);
}





