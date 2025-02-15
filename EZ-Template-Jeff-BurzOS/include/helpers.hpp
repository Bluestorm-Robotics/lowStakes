#pragma once

#include "api.h"


//Constants
inline const int DRIVE_SPEED = 127; //was 110
inline const int TURN_SPEED = 115;
inline const int SWING_SPEED = 40;
inline const int elevatorRPMFlag = 10; //Threashold for detecting elevator jam //was 100 //was 50
//inline const int blue = 200;
//inline const int red = 30;


//Changing Variables
inline int pistonCount = 0; // Counts piston uses
inline bool pistonStat = false; //Tracks if piston is enabled
inline bool ejecterStat = false;
inline int elevatorRPM;
inline bool intakeTog = false;
inline bool mollyBStat = false; 
inline bool isJammed = false; //flag for if elevator is jammed (prevents ejecter)
inline bool is_auto_home = false;
inline bool dig_right = false;

//this is getting out of hand I need a better solution to this than a billion bool toggles

/*inline void turnToHead(float deg){ //deg is requested heading (DEPRICATED FUNCTION)
    float current = gps1.get_heading(); //Current heading
    float turn = abs(current - deg); // Absolute value of degrees to turn
    if(current > deg){ //If requested heading is less than current heading turn left
        chassis.pid_turn_set(-turn, TURN_SPEED, true);
    }
    else{ // If requested heading is MORE than current heading turn right
        chassis.pid_turn_set(-turn, TURN_SPEED, true);
    }
    //chassis.pid_turn_set(deg - current, TURN_SPEED, true);
    /*if (gps1.get_heading() < deg){ //Verification check (not yet implemented)
    
    }*/
//}

inline void pistonTog(){ //Toggles piston
    pistonStat = !pistonStat; //Toggle switch
    piston.set_value(pistonStat);
    /*if(pistonStat) {// if true
        pistonCount++;
        master.print(0, 0, "Pneumatics: %d", count); // print to controller screen (Cant call master in helpers)
    }*/
}

inline void ejectTog(){ //Toggles piston
    ejecterStat = !ejecterStat; //Toggle switch
    ejecter.set_value(ejecterStat);
    /*if(pistonStat) {// if true
        pistonCount++;
        master.print(0, 0, "Pneumatics: %d", count); // print to controller screen (Cant call master in helpers)
    }*/
}

inline void mollyBTog(){ //Toggles piston
    mollyBStat = !mollyBStat; //Toggle switch
    mollyPiston.set_value(mollyBStat);
    /*if(pistonStat) {// if true
        pistonCount++;
        master.print(0, 0, "Pneumatics: %d", count); // print to controller screen (Cant call master in helpers)
    }*/
}
/*inline void load(bool enabled){
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
            pros::delay(500);()
        }
    }
    else intakeGroup.move(0);
}*/
/*inline void eject(){
    opitcal1.set_led_pwm(100);
    while(true){
        if((opitcal1.get_rgb().blue < ) && (isJammed == false)){ //If blue value greater than red then eject
            ejectTog();
            pros::delay(700);
            ejectTog();
        }
        else pros::delay(500);
    }
}*/

inline void load(){
    intakeGroup.move(127);
    pros::delay(1000);
    while(true){
        elevatorRPM = elevator.get_actual_velocity();
        if(elevatorRPM < elevatorRPMFlag){  
            isJammed = true;
            //master.print(0,0, "RPM: %d", elevatorRPM);
            elevator.move(-127); //Move in reverse
            intake.move(0);
            pros::delay(1000);
            intakeGroup.move(127);
            pros::delay(500);
        }
        else{
            intakeGroup.move(127);
            isJammed = false;
        }
        pros::delay(500);
    }
}


inline void ladyBrown_task() {
  pros::delay(2000);  // Set EZ-Template calibrate before this function starts running
  while (true) {
    set_LadyBrown(ladyBrownPID.compute(lbRot_sensor.get_position()/100));
    pros::delay(ez::util::DELAY_TIME);
  }
}
//inline pros::Task Load(load); //global declaration
/*inline void deployMolly(){
    bool isDeploying = true;
    molmtr.move(100);
    pros::delay(500);
    molmtr.move_relative(-100, 100);
    /*while(isDeploying){
        if(molmtr.get_actual_velocity() < elevatorRPMFlag){  
            molmtr.move(0);
            isDeploying = false;
            molmtr.move_relative(-20, 100);
        }
        else pros::delay(100);
    }
}*/

inline void headUpdate(){
    while(true){
        float rgbVal = opitcal1.get_rgb().blue;
        master.print(0,0, "RGB: %f", rgbVal);
        pros::delay(500);
    }
}

inline void intakeVelocity(){
    while(true){
        float velocity = intake.get_actual_velocity();
        master.print(0,0, "Intake: %f", velocity);
        pros::delay(500);
    }
}


/*inline void turnToIMU(float deg){ //deg is requested heading
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
//}


