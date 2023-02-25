#include "globals.hpp"

int left_front_motor_port = 1;
int left_middle_motor_port = 2;
int left_back_motor_port = 3;

int right_front_motor_port = 4;
int right_middle_motor_port = 5;
int right_back_motor_port = 6;

int intake_motor_port = 7;
int catapult_motor_port = 8;

char catapult_limit_switch_port = 'A';

char left_endgame_port = 'B';
char right_endgame_port = 'C';

int inertial_sensor_port = 9;

int left_rotation_port = 10;
int right_rotation_port = 11;
int back_rotation_port = 12;

float track_width = 10;
float wheel_diameter = 3.25;
float wheel_rpm = 360;

float tracking_wheel_diameter = 3.25;

float left_tracking_wheel_offset = 3;
float right_tracking_wheel_offset = 3;
float back_tracking_wheel_offset = 4;

float lateral_kp = 10;
float lateral_kd = 30;

float lateral_slew_rate = 5;

float angular_kp = 10;
float angular_kd = 30;

float angular_slew_rate = 5;