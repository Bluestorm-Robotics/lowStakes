#pragma once

#include "api.h"

//Port Definitions

//Three wire
#define goalGrabber_port 'A'
#define ejecter_port 'B'
#define mollyport 'H'

// RJ45 Ports
#define elevator_Motor 4
#define elevator_Motor2 14
#define loader_Motor 0
#define loader_Motor2 15
#define ladyBrown_PORT -16

//Sensors
#define GPS_PORT 18 //Currently Not installed
#define ROTATION_PORT 6
#define OPTICAL_PORT 4
 
// Your motors, sensors, etc. should go here.  Below are examples
inline pros::MotorGroup intakeGroup({ loader_Motor, loader_Motor2, elevator_Motor, elevator_Motor2 });
inline pros::MotorGroup elevator({ elevator_Motor, elevator_Motor2});
inline pros::Motor elevatorLeft(elevator_Motor);
inline pros::Motor elevatorRight(elevator_Motor2);

inline pros::MotorGroup intake({ loader_Motor, loader_Motor2 });
inline pros::Motor intake1(loader_Motor);
inline pros::Motor intake2(loader_Motor2);

inline pros::Motor ladyBrown (ladyBrown_PORT);
inline pros::Rotation lbRot_sensor(ROTATION_PORT);

//Pistons
inline pros::adi::DigitalOut piston (goalGrabber_port);
inline pros::adi::DigitalOut ejecter (goalGrabber_port);
inline pros::adi::DigitalOut mollyPiston (mollyport);


//Sensors
inline pros::Gps gps1(GPS_PORT); //change values (also not installed)
inline pros::Optical opitcal1(OPTICAL_PORT); //rgb sensor on elevator

//PID
inline void set_LadyBrown(int input) { //wraper for motor
  ladyBrown.move(input);
}

//inline ez::PID ladyBrownPID{0.45, 0, 0, 0, "LadyBrown"};
/*
p kP
i kI
d kD
p_start_i i will start when error is within this*/
//inline ez::PID ladyBrownPID{7.5, 0, 50, 0, "LadyBrown"};

inline ez::PID ladyBrownPID{8, 0, 80, 0, "LadyBrown"}; //latest working
//inline ez::PID ladyBrownPID{16, 0, 140, 0, "LadyBrown"};

inline void Lady_wait() {
  while (ladyBrownPID.exit_condition({ladyBrown}, true) == ez::RUNNING) {
    pros::delay(ez::util::DELAY_TIME);
  }
}
