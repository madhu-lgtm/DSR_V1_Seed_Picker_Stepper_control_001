/*
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

//int dt = 400; //min 400 max 1000 @ 1.5Amp 200 SPR
//int dt = 1500; //min 140 max 1500 @ 1.5Amp 400A SPR
//int dt = 1750; //min 70 max 1750 @ 1.5Amp 800 SPR
//int dt = 1500; //min 35 max 1500 @ 1.5Amp 1600 SPR 
//int dt = 12000; //min 15 max 1500 @ 1.5Amp 32000 SPR
//int dt = 1500; //min 7 max 1500 @ 1.5Amp 64000 SPR

//micro step selection based in range 5rpm to 100rpm
unsigned long SPR = 200; //Steps per rotation (unsigned long for rpm calculation)
unsigned long dt = 1000; //milli seconds
double rpm ; //rpm must be float or double 

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





