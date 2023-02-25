#include "macros.hpp"

// TODO: implement roller macros
void run_rollers_match() {}
void run_rollers_skills() {}

void fire_endgame() {
    left_endgame.set_value(1);
    right_endgame.set_value(1);
}

void fire_left_endgame() {
    left_endgame.set_value(1);
}

void fire_right_endgame() {
    right_endgame.set_value(1);
}

void reset_endgame() {
    left_endgame.set_value(0);
    right_endgame.set_value(0);
}