#include "catapult.hpp"

Catapult::Catapult() {
    this->isReady = false;
}

void Catapult::reset() {
    pros::Task task{[=] {
        while (this->limitSwitch.get_value() != 1) {
            this->motor.move_velocity(100);

            pros::delay(20);
        }

        this->motor.move_velocity(0);

        this->isReady = true;
    }};
}

void Catapult::fire() {
    pros::Task task{[=] {
        this->motor.move_velocity(100);

        pros::delay(500);

        this->motor.move_velocity(0);

        this->isReady = false;
    }};
}

bool Catapult::isCatapultReady() {
    return this->isReady;
}

void Catapult::cycle() {
    pros::Task task{[=] {
        if (!this->isCatapultReady()) this->reset();
    
        while (!this->isCatapultReady()) {
            pros::delay(50);
        }

        this->fire();

        this->reset();
    }};
}

pros::Motor Catapult::getMotor() {
    return this->motor;
}