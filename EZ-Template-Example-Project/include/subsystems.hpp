#pragma once

#include "api.h"

//Port Definitions

//Three wire
#define goalGrabber_port 'A'
#define ejecter_port 'B'
#define mollyport 'H'

// RJ45 Ports
#define elevator_Motor 4
#define loader_Motor -14
#define GPS_PORT 18 //Currently Not installed
#define OPTICAL_PORT 15
#define molmtrPrt 9
 
// Your motors, sensors, etc. should go here.  Below are examples
inline pros::MotorGroup intakeGroup({ loader_Motor, elevator_Motor });
inline pros::Motor intake(loader_Motor);
inline pros::Motor elevator(elevator_Motor);
inline pros::Motor molmtr(molmtrPrt);

//Pistons
inline pros::adi::DigitalOut piston (goalGrabber_port);
inline pros::adi::DigitalOut ejecter (goalGrabber_port);
inline pros::adi::DigitalOut mollyPiston (mollyport);


inline pros::Gps gps1(GPS_PORT); //change values (also not installed)
inline pros::Optical opitcal1(OPTICAL_PORT); //rgb sensor on elevator