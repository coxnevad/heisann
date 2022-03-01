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
 * Works by moving the elevator and checking if the floor is still undefined (-1). if the floor becomes defined, 
 * it will update the floor variable sent in, along with the direction 
 * 
 * @param[in,out] floor_ref takes i a pointer to a floor referance
 * @param[in,out] direction_ref takes in a pointer to the motor direction 
 * 
 * 
 */
void startup_procedure(int *floor_ref, MotorDirection *direction_ref);