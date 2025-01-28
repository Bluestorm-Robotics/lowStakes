#pragma once

#include "api.h"

//Port Definitions

//Three wire
#define goalGrabber_port 'A'
#define ejecter_port 'B'
#define mollyport 'H'

// RJ45 Ports
#define elevator_Motor 4
#define elevator_Motor2 -13
#define loader_Motor -14
#define loader_Motor2 -15

#define GPS_PORT 18 //Currently Not installed
#define OPTICAL_PORT 4
#define ladyBrown_PORT 16
 
// Your motors, sensors, etc. should go here.  Below are examples
inline pros::MotorGroup intakeGroup({ loader_Motor, loader_Motor2, elevator_Motor, elevator_Motor2 });
inline pros::MotorGroup elevator({ elevator_Motor, elevator_Motor2});
inline pros::Motor elevatorLeft(elevator_Motor);
inline pros::Motor elevatorRight(elevator_Motor2);

inline pros::MotorGroup intake({ loader_Motor, loader_Motor2 });
inline pros::Motor intake1(loader_Motor);
inline pros::Motor intake2(loader_Motor2);

inline pros::Motor ladyBrown (ladyBrown_PORT);
//Pistons
inline pros::adi::DigitalOut piston (goalGrabber_port);
inline pros::adi::DigitalOut ejecter (goalGrabber_port);
inline pros::adi::DigitalOut mollyPiston (mollyport);

//Sensors
inline pros::Gps gps1(GPS_PORT); //change values (also not installed)
inline pros::Optical opitcal1(OPTICAL_PORT); //rgb sensor on elevator

//PID
inline ez::PID ladyBrownPID{0.45, 0, 0, 0, "LadyBrown"};