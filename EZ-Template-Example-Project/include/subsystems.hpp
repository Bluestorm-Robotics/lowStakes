#pragma once

#include "api.h"

//Port Definitions

//Three wire
#define goalGrabber_port 'A'

// RJ45 Ports
#define loader_Motor 6
#define GPS_PORT 18 //Currently Not installed

// Your motors, sensors, etc. should go here.  Below are examples
inline pros::Motor intake(loader_Motor);
inline pros::adi::DigitalOut piston (goalGrabber_port);

inline pros::Gps gps1(GPS_PORT); //change values (also not installed)