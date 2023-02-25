#include "macros.hpp"
#include "main.h"

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
    while (true) {
        chassis_controller->getModel()->tank(
            controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
            controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)
        );

        if (intake_in_button.isPressed()) intake->setTarget(200); // 200 RPM
        else if (intake_out_button.isPressed()) intake->setTarget(-200); // -200 RPM
        else intake->setTarget(0); // 0 RPM

        if (catapult_fire_button.changedToPressed()) catapult.cycle();
        else if (catapult_reset_button.changedToPressed()) catapult.reset();
        
        if (catapult_manual_button.isPressed()) catapult.getMotor().move_velocity(200); // 200 RPM
        else catapult.getMotor().move_velocity(0); // 0 RPM

        if (endgame_button.isPressed()) fire_endgame();
        else reset_endgame();

        if (endgame_left_button.isPressed()) fire_left_endgame();
        else left_endgame.set_value(0);

        if (endgame_right_button.isPressed()) fire_right_endgame();
        else right_endgame.set_value(0);

        pros::delay(10);
    }
}