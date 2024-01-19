#include "main.h"

const int L1 = -14;
const int L2 = -15;
const int L3 = -16;
const int R1 = 17;
const int R2 = 13;
const int R3 = 19;

const int FLYWHEEL = -20;

const int INTAKE = 11;

const char LEFT_WING = 'D';
const char RIGHT_WING = 'C';
const char BLOCKER = 'A';
const char SIDE_HANG = 'B';

const int GYRO = 4;

pros::Motor left1_motor(L1, pros::E_MOTOR_GEARSET_06);
pros::Motor left2_motor(L2, pros::E_MOTOR_GEARSET_06);
pros::Motor left3_motor(L3, pros::E_MOTOR_GEARSET_06);
pros::Motor right1_motor(R1, pros::E_MOTOR_GEARSET_06);
pros::Motor right2_motor(R2, pros::E_MOTOR_GEARSET_06);
pros::Motor right3_motor(R3, pros::E_MOTOR_GEARSET_06);

pros::MotorGroup left_side_motors({left1_motor, left2_motor, left3_motor});
pros::MotorGroup right_side_motors({right1_motor, right2_motor, right3_motor});

pros::Motor intake(INTAKE);
pros::Motor flywheel(FLYWHEEL, pros::E_MOTOR_GEARSET_06);

pros::ADIDigitalOut left_wing(LEFT_WING);
pros::ADIDigitalOut right_wing(RIGHT_WING);
pros::ADIDigitalOut blocker(BLOCKER);
pros::ADIDigitalOut side_hang(SIDE_HANG);

// inertial sensor
pros::Imu inertial_sensor(GYRO);

// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {L1, L2, L3}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{R1, R2, R3}

  // IMU Port
  ,GYRO

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.666


  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);