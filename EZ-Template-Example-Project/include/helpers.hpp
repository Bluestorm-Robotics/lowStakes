#pragma once

#include "api.h"

int pistonCount = 0; // Counts piston uses
bool pistonStat = false; //Tracks if piston is enabled

//Constants
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;


//Changing Variables


void turnToHead(double deg){ //Doubles are 64 bit compared to 32 bit floats
    double current = gps1.get_heading();
    chassis.pid_turn_set(deg - current, TURN_SPEED, true);
    /*if (gps1.get_heading() < deg){ //Verification check
    
    }*/
}

void pistonTog(){ //Toggles piston
    pistonStat = !pistonStat; //Toggle switch
    piston.set_value(pistonStat);
    /*if(pistonStat) {// if true
        pistonCount++;
        master.print(0, 0, "Pneumatics: %d", count); // print to brain screen (Cant call master in helpers)
    }*/
}