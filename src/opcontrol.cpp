#include "main.h"

void celebrate(){
    right_side_motors.move_velocity(500);
    left_side_motors.move_velocity(-500);
}

void opcontrol(){
    // This is preference to what you like to drive on.
    chassis.set_drive_brake(MOTOR_BRAKE_COAST);

    bool rwing = 0;
    bool lwing = 0;
    bool blocking = 0;
    bool celebrating = 0;
    bool matchloading = 0;
    bool side = 0;

    while (true) {
        chassis.arcade_standard(ez::SPLIT); // Standard split arcade

		if (master.get_digital(DIGITAL_R1)) {
			intake.move_velocity(600);
		} else if (master.get_digital(DIGITAL_R2)) {
			intake.move_velocity(-600);
		} else {
			intake.move_velocity(0);
		}

        if(master.get_digital_new_press(DIGITAL_Y)){
            matchloading = !matchloading;
        } 

        if(matchloading){
            flywheel.move_velocity(600);
        } else{
            flywheel.move_velocity(0);
        }

        if(master.get_digital_new_press(DIGITAL_UP) && master.get_digital_new_press(DIGITAL_DOWN)){
            celebrating = !celebrating;
        }
        if(celebrating){
            celebrate();
        }

        if(master.get_digital_new_press(DIGITAL_L2)){
            rwing = !rwing;
            lwing = !lwing;
        }

        if(master.get_digital_new_press(DIGITAL_L1)){
            blocking = !blocking;
        }

        if(master.get_digital_new_press(DIGITAL_RIGHT)){
            side = !side;
        }

        right_wing.set_value(rwing);
        left_wing.set_value(lwing);
        blocker.set_value(blocking);
        side_hang.set_value(side);


        pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    }
}