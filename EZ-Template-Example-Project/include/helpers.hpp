#include "main.h"


const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

bool pistonStat = false; //yes

void turnToHead(double deg){
    double current = gps1.get_heading();
    chassis.pid_turn_set(deg - current, TURN_SPEED, true);
    //if (gps1.get_heading()

}

void pistonTog(){
    pistonStat = !pistonStat;
    piston.set_value(pistonStat);
    if(pistonStat) {
        //count++;
        //master.print(0, 0, "Pneumatics: %d", count);
    }
}