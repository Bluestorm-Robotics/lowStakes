#pragma once

#include "api.h"

#define goalGrabber_port 'A'
#define loader_Motor 6

// Your motors, sensors, etc. should go here.  Below are examples
inline pros::Motor intake(loader_Motor);
// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

inline pros::adi::DigitalOut piston (goalGrabber_port);