#include "main.h"
//#include "helpers.hpp"




/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127

#define X_OFFSET -0.1778
#define Y_OFFSET -0.001
#define X_INITIAL -1.366
#define Y_INITIAL 0.69
//int HEADING_INITIAL 282 //was 283

/*const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;*/


///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(11, 0, 20);
  chassis.pid_drive_constants_set(20, 0, 100);
  chassis.pid_turn_constants_set(3, 0.05, 20, 15);
  chassis.pid_swing_constants_set(6, 0, 65);

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .

// Gps Navigation plus inertial
// Our own autonomouse
/*void gpsNav(){ //Original
  //pros::Task HeadUpdate(headUpdate);
  //int curHead;
  //pistonTog();
  //gps1.initialize_full(X_OFFSET, Y_OFFSET, X_INITIAL, Y_INITIAL, HEADING_INITIAL);
  chassis.pid_drive_set(-29_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  pistonTog();
  chassis.pid_turn_set(345_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::Task Load(load);
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(4000);
  chassis.pid_turn_set(80_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(4000);
  /*chassis.pid_turn_set(null_deg, TURN_SPEED);
  chassis,pid_wait();
  chassis.pid_drive_set(null_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  */
//}

/*void gpsNav(){
  //pros::Task HeadUpdate(headUpdate);
  //int curHead;
  //pistonTog();
  //gps1.initialize_full(X_OFFSET, Y_OFFSET, X_INITIAL, Y_INITIAL, HEADING_INITIAL);
  chassis.pid_drive_set(-29_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  deployMolly();
  pros::delay(100);
  pistonTog();
  chassis.pid_turn_set(345_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  pros::Task Load(load);
  pros::Task Eject(eject);
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  pros::delay(4000);
  chassis.pid_turn_set(70_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  pros::delay(4000);
  
}*/


void redLeft(){
  chassis.drive_angle_set(283); //Tells IMU what its heading is
  pros::Task HeadUpdate(headUpdate);
  //int curHead;
  //pistonTog();
  //gps1.initialize_full(X_OFFSET, Y_OFFSET, X_INITIAL, Y_INITIAL, HEADING_INITIAL);
  chassis.pid_drive_set(-29_in, DRIVE_SPEED-20, true);
  chassis.pid_wait_quick();
  pros::delay(100);
  pistonTog();
  //deployMolly();
  chassis.pid_turn_set(35.20_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  pros::Task Load(load);
  //pros::Task Eject(eject);
  chassis.pid_drive_set(15_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  pros::delay(2000);
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(335_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  pros::delay(2000);
  chassis.pid_turn_set(40_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(11_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  pros::delay(2000);
  chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  Load.remove();
  //intakeGroup.move(0);
  chassis.pid_turn_set(335_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-20_in, 127, true);
  chassis.pid_wait_quick();
  /*chassis.pid_turn_set(null_deg, TURN_SPEED);
  chassis,pid_wait();
  chassis.pid_drive_set(null_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  */
}
void redRight(){
  chassis.drive_angle_set(290); //Tells IMU what its heading is
  pros::Task HeadUpdate(headUpdate);
  chassis.pid_drive_set(-29_in, DRIVE_SPEED-20, true);
  chassis.pid_wait_quick();
  pros::delay(100);
  pistonTog();
  chassis.pid_turn_set(170_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  pros::Task Load(load);
  chassis.pid_drive_set(18_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  pros::delay(1000);
  pistonTog();

  chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(270_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  //chassis.pid_turn_set(300_deg, TURN_SPEED);
  //chassis.pid_wait_quick();
  chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  pros::delay(100);
  pistonTog();
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
}

void blueRight(){
  chassis.drive_angle_set(70); //Tells IMU what its heading is
  pros::Task HeadUpdate(headUpdate);
  //int curHead;
  //pistonTog();
  //gps1.initialize_full(X_OFFSET, Y_OFFSET, X_INITIAL, Y_INITIAL, HEADING_INITIAL);
  chassis.pid_drive_set(-29_in, DRIVE_SPEED-20, true);
  chassis.pid_wait_quick();
  pros::delay(100);
  pistonTog();
  //deployMolly();
  chassis.pid_turn_set(320_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  pros::Task Load(load);
  //pros::Task Eject(eject);
  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  pros::delay(2000);
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  pros::delay(2000);
  chassis.pid_turn_set(31_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(11_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  pros::delay(2000);
  chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  Load.remove();
  //intakeGroup.move(0);
  chassis.pid_turn_set(335_deg, TURN_SPEED);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-20_in, 127, true);
  chassis.pid_wait_quick();
  /*chassis.pid_turn_set(null_deg, TURN_SPEED);
  chassis,pid_wait();
  chassis.pid_drive_set(null_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  */
}