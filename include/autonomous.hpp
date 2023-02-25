#include "autoSelect/selection.h"
#include "macros.hpp"
#include "main.h"

enum AutonomousMode {
    RED_ROLLER,
    RED_SIDE,
    BLUE_ROLLER,
    BLUE_SIDE,
    SKILLS,
    NONE
};

inline void initialize_autonomous() {
    if (inertial_sensor.is_calibrating()) {
        pros::delay(250);

        initialize_autonomous();
    }

    selector::init();

    chassis.calibrate();

    chassis.setPose(0, 0, 0); // reset the chassis
}

inline AutonomousMode get_autonomous_mode(int mode) {
    switch (selector::auton) {
        case (1): return AutonomousMode::RED_ROLLER;
        case (2): return AutonomousMode::RED_SIDE;
        case (-1): return AutonomousMode::BLUE_ROLLER;
        case (-2): return AutonomousMode::BLUE_SIDE;
        case (0): return AutonomousMode::SKILLS;
        default: return AutonomousMode::NONE;
    }
}

void roller();
void side();
void skills();
void none();

inline std::function<void()> get_autonomous_callback(AutonomousMode mode) {
    std::map<AutonomousMode, std::function<void()>> autonomous_functions = {
        {AutonomousMode::RED_ROLLER, roller},
        {AutonomousMode::RED_SIDE, side},
        {AutonomousMode::BLUE_ROLLER, roller},
        {AutonomousMode::BLUE_SIDE, side},
        {AutonomousMode::SKILLS, skills},
        {AutonomousMode::NONE, none}
    };

    return autonomous_functions[mode];
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
inline void autonomous() {
    AutonomousMode mode = get_autonomous_mode(selector::auton);

    get_autonomous_callback(mode)();
}