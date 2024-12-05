#pragma once

#include "api.h"


//Constants
inline const int DRIVE_SPEED = 40;
inline const int TURN_SPEED = 40;
inline const int SWING_SPEED = 40;
inline const int elevatorRPMFlag = 100; //Threashold for detecting elevator jam


//Changing Variables
inline int pistonCount = 0; // Counts piston uses
inline bool pistonStat = false; //Tracks if piston is enabled
inline int elevatorRPM;



inline void turnToHead(float deg){ //deg is requested heading
    float current = gps1.get_heading(); //Current heading
    float turn = abs(current - deg); // Absoloute value of degrees to turn
    if(current > deg){ //If requested heading is less than current heading turn left
        chassis.pid_turn_set(-turn, TURN_SPEED, true);
    }
    else{ // If requested heading is MORE than current heading turn right
        chassis.pid_turn_set(-turn, TURN_SPEED, true);
    }
    //chassis.pid_turn_set(deg - current, TURN_SPEED, true);
    /*if (gps1.get_heading() < deg){ //Verification check (not yet implemented)
    
    }*/
}

inline void pistonTog(){ //Toggles piston
    pistonStat = !pistonStat; //Toggle switch
    piston.set_value(pistonStat);
    /*if(pistonStat) {// if true
        pistonCount++;
        master.print(0, 0, "Pneumatics: %d", count); // print to controller screen (Cant call master in helpers)
    }*/
}
inline void load(bool enabled){
    if (enabled){
        intakeGroup.move(127);
        pros::delay(1000);
        while(enabled){
            elevatorRPM = elevator.get_actual_velocity();
            if(elevatorRPM < elevatorRPMFlag){  
                //master.print(0,0, "RPM: %d", elevatorRPM);
                elevator.move(-127); //Move in reverse
                intake.move(0);
                pros::delay(1000);
                intakeGroup.move(127);
                pros::delay(500);
            }
            else intakeGroup.move(127);
            pros::delay(500);
        }
    }
    else intakeGroup.move(0);
}

inline void headUpdate(){
    while(true){
        master.print(0,0, "heading: %f", gps1.get_heading());
        pros::delay(500);
    }
}


inline void turnToIMU(float deg){ //deg is requested heading
    float current = chassis.drive_imu_get(); //Current heading
    float turn = abs(current - deg); // Absoloute value of degrees to turn
    if(current > deg){ //If requested heading is less than current heading turn left
        chassis.pid_turn_set(-turn, TURN_SPEED, true);
    }
    else{ // If requested heading is MORE than current heading turn right
        chassis.pid_turn_set(-turn, TURN_SPEED, true);
    }
    //chassis.pid_turn_set(deg - current, TURN_SPEED, true);
    /*if (gps1.get_heading() < deg){ //Verification check (not yet implemented)
    
    }*/
}