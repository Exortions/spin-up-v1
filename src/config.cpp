#include "main.h"

pros::Motor left_front_motor(left_front_motor_port, pros::E_MOTOR_GEARSET_18, false);
pros::Motor left_middle_motor(left_middle_motor_port, pros::E_MOTOR_GEARSET_18, false);
pros::Motor left_back_motor(left_back_motor_port, pros::E_MOTOR_GEARSET_18, false);

pros::Motor right_front_motor(right_front_motor_port, pros::E_MOTOR_GEARSET_18, true);
pros::Motor right_middle_motor(right_middle_motor_port, pros::E_MOTOR_GEARSET_18, true);
pros::Motor right_back_motor(right_back_motor_port, pros::E_MOTOR_GEARSET_18, true);

pros::MotorGroup left_motors({left_front_motor, left_middle_motor, left_back_motor});
pros::MotorGroup right_motors({right_front_motor, right_middle_motor, right_back_motor});

pros::Motor intake_motor(intake_motor_port, pros::E_MOTOR_GEARSET_18, false);

std::shared_ptr<AsyncVelocityController<double, double>> intake = AsyncVelControllerBuilder()
    .withMotor(intake_motor_port)
    .withGearset(AbstractMotor::gearset::green)
    .withMaxVelocity(200)
    .build();

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Motor catapult_motor(catapult_motor_port, pros::E_MOTOR_GEARSET_18, false);

Catapult catapult;

pros::ADIDigitalIn catapult_limit_switch(catapult_limit_switch_port);

pros::ADIDigitalOut left_endgame(left_endgame_port);
pros::ADIDigitalOut right_endgame(right_endgame_port);

pros::Imu inertial_sensor(inertial_sensor_port);

lemlib::Drivetrain_t drivetrain {
    &left_motors,
    &right_motors,
    track_width,
    wheel_diameter,
    wheel_rpm
};

pros::Rotation left_rotation(left_rotation_port, true);
pros::Rotation right_rotation(right_rotation_port, false);
pros::Rotation back_rotation(back_rotation_port, false);

lemlib::TrackingWheel left_tracking_wheel(&left_rotation, tracking_wheel_diameter, left_tracking_wheel_offset);
lemlib::TrackingWheel right_tracking_wheel(&right_rotation, tracking_wheel_diameter, right_tracking_wheel_offset);
lemlib::TrackingWheel back_tracking_wheel(&back_rotation, tracking_wheel_diameter, back_tracking_wheel_offset);

lemlib::OdomSensors_t odom_sensors = {
    &left_tracking_wheel,
    &right_tracking_wheel,
    &back_tracking_wheel,
    nullptr,
    &inertial_sensor
};

lemlib::ChassisController_t lateralController {
    lateral_kp,
    lateral_kd,
    1, // small error range
    100, // small error timeout
    3, // large error range
    500, // large error timeout
    lateral_slew_rate
};

lemlib::ChassisController_t angularController {
    angular_kp,
    angular_kd,
    1, // small error range
    100, // small error timeout
    3, // large error range
    500, // large error timeout
    angular_slew_rate
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, odom_sensors);

std::shared_ptr<okapi::ChassisController> chassis_controller = okapi::ChassisControllerBuilder()
    .withMotors(
        {left_front_motor_port, left_middle_motor_port, left_back_motor_port},
        {-right_front_motor_port, -right_middle_motor_port, -right_back_motor_port}
    ).withDimensions(
        {AbstractMotor::gearset::green, // 200 rpm motor cartridge
        (36.0 / 60.0)}, // gear ratio (36:60)
        {{wheel_diameter * okapi::inch, track_width * okapi::inch}, imev5GreenTPR} // wheel diameter, track width
    ).build();

okapi::ControllerButton intake_in_button(okapi::ControllerDigital::L2);
okapi::ControllerButton intake_out_button(okapi::ControllerDigital::L1);
okapi::ControllerButton catapult_fire_button(okapi::ControllerDigital::R2);
okapi::ControllerButton catapult_manual_button(okapi::ControllerDigital::R1);
okapi::ControllerButton catapult_reset_button(okapi::ControllerDigital::A);

okapi::ControllerButton endgame_button(okapi::ControllerDigital::down);
okapi::ControllerButton endgame_left_button(okapi::ControllerDigital::left);
okapi::ControllerButton endgame_right_button(okapi::ControllerDigital::right);