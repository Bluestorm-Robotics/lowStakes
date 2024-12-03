#pragma once

#include "api.h"

inline int pistonCount = 0; // Counts piston uses
inline bool pistonStat = false; //Tracks if piston is enabled

//Constants
inline const int DRIVE_SPEED = 80;
inline const int TURN_SPEED = 90;
inline const int SWING_SPEED = 90;


//Changing Variables


inline void turnToHead(double deg){ //Doubles are 64 bit compared to 32 bit floats
    double current = gps1.get_heading();
    chassis.pid_turn_set(deg - current, TURN_SPEED, true);
    /*if (gps1.get_heading() < deg){ //Verification check
    
    }*/
}

inline void pistonTog(){ //Toggles piston
    pistonStat = !pistonStat; //Toggle switch
    piston.set_value(pistonStat);
    /*if(pistonStat) {// if true
        pistonCount++;
        master.print(0, 0, "Pneumatics: %d", count); // print to brain screen (Cant call master in helpers)
    }*/
}