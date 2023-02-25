#include "lemlib/api.hpp"
#include "okapi/api.hpp"
#include "catapult.hpp"
#include "api.h"

extern std::shared_ptr<okapi::ChassisController> chassis_controller;
extern lemlib::Chassis chassis;

extern pros::Motor intake_motor;
extern pros::Imu inertial_sensor;

extern pros::Controller controller;

extern pros::Motor catapult_motor;
extern Catapult catapult;

extern std::shared_ptr<okapi::AsyncVelocityController<double, double>> intake;

extern pros::ADIDigitalOut left_endgame;
extern pros::ADIDigitalOut right_endgame;

extern okapi::ControllerButton intake_in_button;
extern okapi::ControllerButton intake_out_button;
extern okapi::ControllerButton catapult_fire_button;
extern okapi::ControllerButton catapult_manual_button;
extern okapi::ControllerButton catapult_reset_button;

extern okapi::ControllerButton endgame_button;
extern okapi::ControllerButton endgame_left_button;
extern okapi::ControllerButton endgame_right_button;