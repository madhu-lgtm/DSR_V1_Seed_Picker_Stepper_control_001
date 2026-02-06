## Components Used
- Micro Controller Used :- Arduino nano original
- Stepper Motor Used :- NEMA 17 , JK42HS48 - 1684 -01
- Driver Used :- TB6600 ; (Short Pul- , Dir- , ENA-) ; set 3200 Micro step S1=0,S2=0,S3=1 ; set 1.5amp S4=1,S5=1,S6=0
- Servo Tester For pwm input

## Connections
- D9       -> Pul+ of TB6600
- D8       -> Dir+ of TB6600
- D7       -> ENA+ of TB6600
- GND      -> ENA- (short with Pul- and Dir-) of TB6600 
- D2 or D6 -> PWM input from servo tester or FC or Reciver (D2 or D6 Depends on program you selected)
- 5v       -> for Servo tester if used
- GND      -> servo Gnd or fc gnd or reciver gnd
##### Driver to Stepper
- A+       -> red Wire of stepper
- A-       -> blue Wire of stepper
- B+       -> Green Wire of stepper
- B-       -> Blackk Wire of stepper


## Rpm and Torque evaluations at 1.5Amp and 3200 micro steps with input voltage 12v
-  Holding Torque @9.38 RPM = 1.5 kgcm
-  Running Torque @93.75 RPM = 2.5 kgcm
-  Holding Torque @9.38 RPM = 0.5 kgcm
-  Running Torque @93.75 = 2 kgcm
-  For More details check "dsr_nema17_42hs48_1684_004"

## For Intial Testing on drone Use 
- "dsr_nema17_42hs48_1684_007" which has some limitations and noise , use it only for checking seed dispensing.
- Warning! Do not use "dsr_nema17_42hs48_1684_007" for seed calibration purposes.

  
