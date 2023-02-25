#include "globals.hpp"
#include "api.h"

class Catapult {
    private:
        pros::Motor motor = pros::Motor(catapult_motor_port);
        pros::ADIDigitalIn limitSwitch = pros::ADIDigitalIn(catapult_limit_switch_port);
        bool isReady;
    public:
        Catapult();
        void fire();
        void reset();
        void cycle();
        bool isCatapultReady();
        pros::Motor getMotor();
};