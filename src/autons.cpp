#include "main.h"
#include <cmath>

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

const int SQRT2 = sqrt(2);

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.85, 0, 6.5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.85, 0, 6.5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}


///
// Nice Robot Movement Functions
///
void open_wings(){
  left_wing.set_value(1);
  right_wing.set_value(1);
}

void close_wings(){
  left_wing.set_value(0);
  right_wing.set_value(0);
}

///
// Near Side Qualifications
///
void near_qual(){
  // initialize heading
  chassis.set_angle(135);

  blocker.set_value(1);

  // push alliance triball in the opponent's goal with the back of the robot
  chassis.set_drive_pid(-SQRT2*12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 180, SWING_SPEED);
  chassis.wait_drive();
  
  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  // push the triball from the match load zone
  chassis.set_drive_pid(8, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.set_swing_pid(ez::LEFT_SWING, -45, SWING_SPEED);
  open_wings();
  chassis.wait_drive();


  chassis.set_drive_pid(-SQRT2*8, DRIVE_SPEED);
  chassis.wait_drive();
  
  close_wings();
  pros::delay(500);

  chassis.set_drive_pid(-8, DRIVE_SPEED);
  chassis.wait_drive();

  // touch the elevation bar
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.set_drive_pid(-36, DRIVE_SPEED);
}

///
// Far Side Qualifications
///
void far_qual(){
  // initialize
  chassis.set_angle(0);
  blocker.set_value(1);

  intake.move_velocity(200);

  // push alliance triball to the middle
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_until(20);
  intake.move_velocity(-100);
  chassis.wait_drive();

  // fetch middle triball and push 3 in goal
  intake.move_velocity(0);
  
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  intake.move_velocity(200);

  chassis.set_drive_pid(30*SQRT2, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(28, DRIVE_SPEED);
  chassis.wait_until(8);
  intake.move_velocity(0);
  chassis.wait_drive();

  // fetch the other triball near the barrier
  chassis.set_drive_pid(-10, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(230, TURN_SPEED);
  chassis.wait_drive();

  intake.move_velocity(200);

  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();

  // push triball in
  chassis.set_turn_pid(75, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_until(20);
  intake.move_velocity(0);
  chassis.wait_drive();

  // touch elevation bar
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  
  chassis.set_drive_pid(-10, DRIVE_SPEED);
  chassis.wait_drive();
  
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  
  chassis.set_drive_pid(-26, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  open_wings();

  chassis.set_drive_pid(-26, DRIVE_SPEED);
  chassis.wait_drive();
}

///
// Near Side Eliminations
/// 
void near_elim(){
  // initialize
  chassis.set_angle(180);
  intake.move_velocity(200);
  blocker.set_value(1);

  // push two triballs to own side

  chassis.set_drive_pid(-48, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  open_wings();

  chassis.set_drive_pid(-28, DRIVE_SPEED);
  chassis.wait_drive();

  close_wings();

  // push alliance triball in opponent goal
  intake.move_velocity(-600);

  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();

  intake.move_velocity(0);
}

///
// Far Side Eliminations
///
void far_elim(){ 
  // initialize
  chassis.set_angle(0);
  blocker.set_value(1);

  intake.move_velocity(200);

  // push alliance triball to the middle
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_until(20);
  intake.move_velocity(-100);
  chassis.wait_drive();

  // fetch middle triball and push 3 in goal
  intake.move_velocity(0);
  
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  intake.move_velocity(200);

  chassis.set_drive_pid(30*SQRT2, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(28, DRIVE_SPEED);
  chassis.wait_until(8);
  intake.move_velocity(0);
  chassis.wait_drive();

  // fetch the other triball near the barrier
  chassis.set_drive_pid(-10, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(230, TURN_SPEED);
  chassis.wait_drive();

  intake.move_velocity(200);

  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();

  // place triball on field
  chassis.set_turn_pid(120, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_until(20);
  intake.move_velocity(0);
  chassis.wait_until(38);
  intake.move_velocity(-200);
  chassis.wait_drive();

  // fetch the triball under the elevation bar
  chassis.set_turn_pid(225, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(270, DRIVE_SPEED);
  chassis.wait_drive();

  intake.move_velocity(200);

  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();

  // turn back to score three triballs in the goal
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(48, DRIVE_SPEED);
  chassis.wait_until(40);
  intake.move_velocity(-200);
  chassis.wait_drive();

  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();

  open_wings();

  chassis.set_drive_pid(-SQRT2*12, DRIVE_SPEED);
  chassis.wait_drive();

  close_wings();

  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED);
  chassis.wait_drive();
}

///
// Skills
///
void skills(){

}


///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .