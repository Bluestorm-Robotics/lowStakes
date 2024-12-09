#pragma once

#include "api.h"

//Port Definitions

//Three wire
#define goalGrabber_port 'A'

// RJ45 Ports
#define elevator_Motor -4
#define loader_Motor -14
#define GPS_PORT 18 //Currently Not installed

// Your motors, sensors, etc. should go here.  Below are examples
inline pros::MotorGroup intakeGroup({ loader_Motor, elevator_Motor });
inline pros::Motor intake(loader_Motor);
inline pros::Motor elevator(elevator_Motor);
inline pros::adi::DigitalOut piston (goalGrabber_port);

inline pros::Gps gps1(GPS_PORT); //change values (also not installed)