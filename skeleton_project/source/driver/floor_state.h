/**
 * @file floor_state.h
 * @author Simon Krane & Clemens Sundby Øxnevad
 * @brief the file that handles the state of the floors and the elevator direction. 
 * @version 0.1
 * @date 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include "head_include_file.h"


/**
 * @brief Updates the floor state to the real time exact position of the elevator.
 * This function makes a semi-state for when the elevator is between two floors. 
 * \n It does this by:
 * \n 1. It checks if the elevator is in an undefined state or not.
 * \n 2. If the floor state is undefined, it checks the motor direction. Based on this it subtracts or adds "0.5" to the floor state value to indicate that the position of the elevator is between two floors. 
 * 
 * @param[in,out] current_floor A pointer to the value of the current floor state.
 * @param[in] floor_sensor A variable to the value of the floor state given the measurement of the floor sensor. 
 * @param[in] direction A pointer to the motor direction. 
 * @param[out] previous_floor A variable that gives the previous floor state value.   
 */
void update_current_floor_state(float* current_floor, int floor_sensor, MotorDirection *direction, int * previous_floor);

/**
 * @brief Updates the previous floor state after the elevator has changed its floor state. 
 * 
 * 
 * @param[in] floor_sensor A variable to the current floor state value given from the floor sensor. 
 * @param[out] previous_floor A pointer to the value of the previous floor state.
 */
void update_previous_floor_state(int floor_sensor, int *previous_floor);

/**
 * @brief Fetches and adds orders to the elevator queue if the elevator buttons are pushed. 
 * It also updates the arrays that contain the information related to the floor panels.
 * 
 * @param[in,out] stop_array_up An array that indicates if the elevator floor panel up buttons are pushed.
 * @param[in,out] stop_array_down An array that indicates if the elevator floor panel down buttons are pushed.
 * @param[in,out] elevator_panel_lights_array An array that indicates if the elevator panel lights are on.
 * @param[out] elevator_queue An array that represents the queue system of the elevator.
 */
void fetch_order_from_floor(int * stop_array_up, int * stop_array_down, int* elevator_panel_lights_array, int* elevator_queue);

/**
 * @brief Updates the floor order lights on both the elevator panel and the elevator floor panel.
 * It uses a for-loop to iterate through the arrays related to the lights, and turns the lights on or off based on the arrays.
 * 
 * @param[in] stop_array_up An array that indicates if the elevator floor panel up buttons are pushed.
 * @param[in] stop_array_down An array that indicates if the elevator floor panel down buttons are pushed.
 * @param[in] elevator_panel_lights_array An array that indicates if the elevator panel lights are on.
 */
void update_floor_order_lights(int * stop_array_up, int * stop_array_down, int * elevator_panel_lights_array);

/**
 * @brief Uses boolean logic to decide if we want to return a status flag to stop the elevator on a floor.
 * \n Based on the motor direction, last measured floor state and the elevator queue, the flag returns either a value of "0" or "1".
 * 
 * @param[in] floor_sensor A variable that contains the measured floor state.
 * @param[in] stop_array_up An array that indicates if the elevator floor panel up buttons are pushed.
 * @param[in] stop_array_down An array that indicates if the elevator floor panel down buttons are pushed.
 * @param[in] elevator_panel_lights_array An array that indicates if the elevator panel lights are on.
 * @param[in] direction A pointer to the motor direction. 
 * @param[in] elevator_queue An array that represents the queue system of the elevator.
 * @return A status flag of "1" if we want to stop the elevator, or "0" if we don't want to stop the elevator.
 */
int check_for_orders_at_floor(int floor_sensor, int * stop_array_up, int * stop_array_down,int* elevator_panel_lights_array, MotorDirection * direction, int * elevator_queue);

/**
 * @brief Updates the elevator direction based on the elevator floor state and the first element in the elevator queue. 
 * 
 * @param[in] elevator_queue An array that represents the queue system of the elevator.
 * @param[out] direction A pointer to the motor direction.
 * @param[in] current_floor A pointer to the current floor state of the elevator.
 */
void decide_direction_state(int * elevator_queue, MotorDirection * direction, float * current_floor);
