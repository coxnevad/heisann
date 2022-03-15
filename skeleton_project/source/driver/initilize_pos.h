/**
 * @file initilize_pos.h
 * @author Simon Krane & Clemens Sundby Øxnevad
 * @brief The programs that take care of the initialzation of the elevator
 * @version 0.1
 * @date 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#pragma once
#include <stdio.h>
#include "elevio.h"
#include <time.h>


/**
 * @brief Takes in the value of the floor sensor and moves the elevator until it has reached a defined floor.
 * \n Works by moving the elevator upwards and checking if the floor is still undefined with a value of "-1". \n If the floor reaches a defined state, 
 * it will update the floor variable sent in along with the direction of the motor. 
 * 
 * @param[in,out] floor_ref A pointer to a floor referance with the floor state value.
 * @param[in,out] direction_ref A pointer to the motor direction. 
 * 
 * 
 */
void startup_procedure(int *floor_ref, MotorDirection *direction_ref);