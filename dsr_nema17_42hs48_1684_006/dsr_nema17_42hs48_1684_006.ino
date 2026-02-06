/*
Code Version 6 :- Avoid using pulsein and implement ISR
Code Version 5 :- Recheck accel lib , rpm calculation in loop
Code Version 4 :- Torque calculation on bench (Running Torque 2kgcm @3200SPR @1.5amp @93.75rpm )
Code Version 3 :- micro step selection based in range 5rpm to 100rpm
Code Version 2 :- implement RPM calculator in setup section for the micro step and dt selected
Code Version 1 :- Check accel lib and micro stepping 
---------------- Components Used ----------------
Driver Used  = TB6600
Stepper Used = Nema 17, 42HS48-1684, 
Gear Box = No
Micro Step used = 1/16 (Full Step Mode - 200SPR) S1 = 1, S2 = 1, S3 = 0
Current Set = 1.5Amp  S4 = 1, S5 = 1, S6 = 0
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
#include <AccelStepper.h>

// Used Common cathode setup on driver
const byte pul_pin = 9; //pulse pin 
const byte dir_pin = 8; //direction pin
const byte ena_pin = 7; //enable pin

//Create object of AccelStepper
AccelStepper seed_stepper(AccelStepper::DRIVER,pul_pin,dir_pin);

//int dt = 400; //min 400(375rpm) ; max 1000(150rpm) @ 1.5Amp 200 SPR (minimum rpm itself is 150rpm)
//int dt = 1500; //min 140(535.71rpm) ; max 1500(50rpm) @ 1.5Amp 400A SPR (Will not fall in our range of rpm)
//int dt = 1750; //min 100(375rpm) max 1750(21.43rpm) @ 1.5Amp 800 SPR (Will Struggle at low rpm)
//int dt = 1500; //min 70(267.86rpm) max 1500(12.5rpm) @ 1.5Amp 1600 SPR (low Vibrations at 12.5rpm) 10000 -1.88rpm
//int dt = 12000; //min 15(625rpm) max 1500(6.25rpm) @ 1.5Amp 3200 SPR (********Recomended***********) 
//int dt = 1500; //min 7 max 1500 @ 1.5Amp 64000 SPR (Not Recomended)

//micro step selection based in range 5rpm to 100rpm
unsigned long SPR = 3200; //Steps per rotation (unsigned long for rpm calculation)
unsigned long dt = 100; //micro seconds
int dt_min = 100; //100 -> 93.75rpm or 1.5625rps (0.5kgcm holding , 2kgcm running torque) @3200SPR @1.5amp (or)   200 -> 93.75 @1600SPR
int dt_max = 1000; //1000 -> 9.38rpm or 0.1563rps (1.5kgcm holding, 2.5kgcm running torque) @3200SPR @1.5amp (or)  2000 -> 9.38 @1600SPR
float rpm ; //rpm must be float or double 


//Torque 
int read_pos = 0; // for incoming serial data

//accel
float accel_lib_rpm ;
int set_step_per_sec = 0;
int min_step_per_sec = 500; 
int max_step_per_sec = 5000;

//picker
int min_seeder_pwm = 1051;
int max_seeder_pwm = 1951;
unsigned long read_seeder_pwm = 0;
int seeder_pwm_pin = 2;//interrupt pin


//ISR
volatile unsigned long pwm_start = 0;
volatile unsigned long pwm_width = 1500;

void pwmISR()
{
  if (digitalRead(seeder_pwm_pin) == HIGH)
  {
    pwm_start = micros();
  }
  else
  {
    pwm_width = micros() - pwm_start;
  }
}


void setup() {
  pinMode(pul_pin,OUTPUT);
  pinMode(dir_pin,OUTPUT);
  pinMode(ena_pin,OUTPUT);
  pinMode(seeder_pwm_pin,INPUT);
  digitalWrite(ena_pin,LOW);
  digitalWrite(dir_pin,LOW);
  Serial.begin(9600);

  delay(100);
  
  seed_stepper.setMaxSpeed(max_step_per_sec);// in steps per second = 3200 * 1.5625 = 5000 (max steps per second) @93.75rpm
  // 3200 * 0.1563 = 500 (min steps per second) @9.38rpm
  rpm = 30000000.0 / (SPR * dt); //importent
  
  Serial.print("With SPR = ");
  Serial.print(SPR);
  Serial.print(" and dt = ");
  Serial.print(dt);
  Serial.print(" Calculated RPM = ");
  Serial.println(rpm);

  attachInterrupt(digitalPinToInterrupt(seeder_pwm_pin),pwmISR,CHANGE);
                
                
}

void loop()
{
  
  //read_seeder_pwm = pulseIn(seeder_pwm_pin, HIGH);
  //read_seeder_pwm = 1951;
  read_seeder_pwm = pwm_width;
  set_step_per_sec = map(read_seeder_pwm, min_seeder_pwm, max_seeder_pwm, min_step_per_sec, max_step_per_sec);
  set_step_per_sec = constrain(set_step_per_sec, min_step_per_sec, max_step_per_sec);
  seed_stepper.setSpeed(set_step_per_sec);

  //comment when using on drone 
  // accel_lib_rpm = (float)(set_step_per_sec * 60.0) /SPR;
  // Serial.print(accel_lib_rpm,4);
  // Serial.println(" rpm");

  seed_stepper.runSpeed();


}





