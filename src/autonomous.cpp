#include "autonomous.hpp"

/**
 * @brief Roller autonomous routine
 * 
 * Starts with the robot right next to the roller
 * Scores the roller, and fires the preloads (discs)
 * into the high goal on the opposite side of the
 * field, without crossing the auton line
 */
void roller() {

}

/**
 * @brief Side autonomous routine
 * 
 * Starts with the robot a tile away
 * from the side roller, and fires the
 * preloads (discs) into the high goal
 * on the opposite side of the field,
 * without crossing the auton line.
 * It then moves to the side roller,
 * and scores it.
 */
void side() {

}

void skills() {}

void none() {
    std::cout << "No autonomous selected, doing nothing" << std::endl;
} 