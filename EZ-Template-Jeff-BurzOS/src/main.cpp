#include "main.h"
lv_obj_t* image;


/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-1, -2, 3},     // Left Chassis Ports (negative port will reverse it!)
    {11, 12, -13},  //  pros::screen::print(TEXT_MEDIUM, 3, "owo whats this? a cowode?"); Right Chassis Ports (negative port will reverse it!)

    8,      // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    200);   // Wheel RPM
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

 ez::Piston ladyPiston('D', false);
void initialize() {
  // Print our branding over your terminal :D
  //ez::ez_template_print();
  //Load.suspend();
  //intake.move(0);
  pros::delay(500);  // Stop the user from doing anything while legacy ports configure
  pros::screen::print(TEXT_MEDIUM, 1, "owo whats this? a cowode?"); //bella
  pros::screen::print(TEXT_SMALL, 10, "im about to go uwu catgirl");
  pros::screen::print(TEXT_SMALL, 11, "in this place \n just because im angry - unkle k");

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(false);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0, 0);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();
  //piston.set_value(false); //disables piston //maybe not needed4

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      Auton("redRight\n Red right corner single side\n \n \n \n \n 1723A", redRight),
      Auton("redLeft\n Red left corner single side", redLeft),
      Auton("BlueRight\n Blue right corner", blueRight),
      Auton("BlueLeft", blueLeft),
      Auton("Skills Auton\n Does not use sidestakes", skillsAuton),
      Auton("NewSkills\n Uses sidestakes", newSkillsAuton),
      Auton("red_goalRush", winPointRed),
      Auton("blue_goalRush\n flipped red_goalrush\n UNTESTED", winPointBlue),
      Auton("IMUScale Tuner\n Turns 360 10 times", IMUScalingTuner),
      Auton("Loadertest\n Tests anti-jamming loader task", loaderTest)
      //Auton("drive_example", drive_example),
      //Auton("turn_example", turn_example),
      //Auton("PID Tuner", measure_offsets),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  //ladyBrown.tare_position();
  //lbRot_sensor.reset_position();
  //ladyBrownPID.exit_condition_set(80, 50, 300, 150, 500, 500);
  //ladyBrown.set_brake_mode(MOTOR_BRAKE_HOLD);
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");
  

}
/**
 * Simplifies printing tracker values to the brain screen
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}

/*void tempFar(int index) {
  return std::to_string(32 + (1.8 * chassis.left_motors[index].get_temperature()));
}*/

/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
void ez_screen_task() {
  while (true) {
    // Only run this when not connected to a competition switch
    if (!pros::competition::is_connected()) {
      // Blank page for odom debugging
      if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
        // If we're on the first blank page...
        if (ez::as::page_blank_is_on(0)) {
          // Display X, Y, and Theta
          ez::screen_print("x: " + util::to_string_with_precision(chassis.odom_x_get()) +
                               "\ny: " + util::to_string_with_precision(chassis.odom_y_get()) +
                               "\na: " + util::to_string_with_precision(chassis.odom_theta_get()),
                           1);  // Don't override the top Page line

          // Display all trackers that are being used
          screen_print_tracker(chassis.odom_tracker_left, "l", 4);
          screen_print_tracker(chassis.odom_tracker_right, "r", 5);
          screen_print_tracker(chassis.odom_tracker_back, "b", 6);
          screen_print_tracker(chassis.odom_tracker_front, "f", 7);
        }
        if(ez::as::page_blank_is_on(1)){ //Temps screen
           ez::screen_print("FrontLeft: " + std::to_string(chassis.left_motors[0].get_temperature()) + " *C" + //The number designation is the array value for chassis config (0 = first motor declared, 1 = 2nd motor, etc)
                            "\n BackLeft: " + std::to_string(chassis.left_motors[1].get_temperature()) + " *C" +
                            "\n FrontRight: " + std::to_string(chassis.right_motors[0].get_temperature()) + " *C" +
                            "\n BackRight: " + std::to_string(chassis.right_motors[1].get_temperature()) + " *C" +
                            "\n LadyBrown: " + std::to_string(ladyBrown.get_temperature()) + " *C" +
                            "\n Intake2: " + std::to_string(intake2.get_temperature()) + " *C" +
                            "\n Elevator1: " + std::to_string(elevatorLeft.get_temperature()) + " *C",
                          1);
                      // Temperature of a Motor
            // Level 1 - Temp greater than 55 deg C or 131 deg F - 50% Power
            // Level 2 - Temp greater than 60 deg C or 140 deg F - 25% Power - Less than 25% power is useless on a comp robot
            // Level 3 - Temp greater than 65 deg C or 149 deg F - 12.5% Power
            // Level 4 - Temp greater than 70 deg C or 158 deg F - 0% Power
        }
        /*if(ez::as::page_blank_is_on(2)){
          ez::screen_print(std::to_string(lbRot_sensor.get_position()/100), 4);
        }*/
      }
      if(ez::as::page_blank_is_on(2)){
        ez::screen_print(std::to_string(elevator.get_actual_velocity()), 1);
      }
    }

    // Remove all blank pages when connected to a comp switch
    else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
  
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
  /*ez::as::shutdown();
  LV_IMG_DECLARE(Image);
  image = lv_img_create(lv_scr_act());
  lv_img_set_src(image, &Image);
  lv_obj_set_size(image, 480, 272);
  lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);*/
  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  //chassis.pid_tuner_toggle();
  //chassis.pid_tuner_full_enable(true);  // Enable full PID Tuner
  // This is preference to what you like to drive on
  pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_BRAKE;
  chassis.drive_brake_set(driver_preference_brake);
  chassis.opcontrol_drive_activebrake_set(1.0);
  //pros::Task LadyBrown_task(ladyBrown_task);

  while (true) {
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) {
      // Enable / Disable PID Tuner
      //  When enabled:
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_LEFT)){
        //chassis.pid_tuner_toggle();
      }
      // Trigger the selected autonomous routine
      if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
        autonomous();
        chassis.drive_brake_set(driver_preference_brake);
      }
      chassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }

    //chassis.opcontrol_tank();  // Tank control
     //chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
    chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcademotor_group.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .
      ladyPiston.button_toggle(master.get_digital(DIGITAL_A));

      if (master.get_digital_new_press(DIGITAL_Y)) pistonTog();
      
      if (master.get_digital_new_press(DIGITAL_X)) mollyBTog();

      if (master.get_digital(DIGITAL_L1))intakeGroup.move(127);

      else if (master.get_digital(DIGITAL_L2)) intakeGroup.move(-127);
  
      else intakeGroup.move(0);

      /*if (master.get_digital_new_press(DIGITAL_A)){
        ladyBrownPID.target_set(15); //was 14.32
        Lady_wait();
      }*/
      //else if (master.get_digital(DIGITAL_R1)) ladyBrown.move(70);
      if (master.get_digital(DIGITAL_R1)) ladyBrown.move(70);
  
      else if (master.get_digital(DIGITAL_R2)) ladyBrown.move(-70);

      else ladyBrown.move(0);

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
