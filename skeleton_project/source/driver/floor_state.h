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
 * @brief updates the floor to the real time exact position of the elevator.
 * Makes it so it has a defined floor between two floors
 * 
 * @param[in,out] current_floor Takes in the previous value of the current floor state and modifies it if needed(pointer). 
 * @param[in] floor_sensor Gives the value of the floor sensor at the moment the function is called(copy)
 * @param[in] direction Gives the current direction of the elevater upon function call(pointer)
 * @param[out] previous_floor the variable that gives the last floor the elevator was on.(pointer) 
 */
void update_current_floor_state(float* current_floor, int floor_sensor, MotorDirection *direction, int * previous_floor);

/**
 * @brief updates the variable previous floor upon a chenge in floor location of the elevator. only counts whole floors. 
 * updates the variable to a defined floor if floor sensor is reporting a defined floor 
 * 
 * @param[in] floor_sensor gives the current value of the floor sensor as a pointer
 * @param[out] previous_floor gives a pointer to the value of the previous floor
 */
void update_previous_floor_state(int floor_sensor, int *previous_floor);

/**
 * @brief Fetches and adds orders to the elevator_queue based on if the elevatorbuttons are pushed. 
 * It also updates the arrays contains the information related to the floor panels.
 * 
 * @param[in,out] stop_array_up The array that indicates if the elevator floor panel up buttons are pushed.
 * @param[in,out] stop_array_down The array that indicates if the elevator floor panel down buttons are pushed.
 * @param[in,out] elevator_panel_lights_array The array that indicates if the elevator panel lights are pushed.
 * @param[out] elevator_queue The array that represents the queue system of the elevator.
 */
void fetch_order_from_floor(int * stop_array_up, int * stop_array_down, int* elevator_panel_lights_array, int* elevator_queue);

/**
 * @brief Updates the floor order lights on both the elevator panel and the elevator floor panel.
 * It uses a for-loop to iterate through the arrays related to the lights, and turns the lights on/off based on the arrays.
 * 
 * @param[in] stop_array_up The array that indicates if the elevator floor panel up buttons are pushed.
 * @param[in] stop_array_down The array that indicates if the elevator floor panel down buttons are pushed.
 * @param[in] elevator_panel_lights_array The array that indicates if the elevator panel lights are pushed.
 */
void update_floor_order_lights(int * stop_array_up, int * stop_array_down, int * elevator_panel_lights_array);

/**
 * @brief Uses boolean logic to decide if we want to return a status flag to stop the elevator on a floor with either the values,
 * 0 or 1 based on the current motordirection, the last measured floor state, the elevator queue and different arrays.
 * 
 * @param[in] floor 
 * @param[in] stop_array_up 
 * @param[in] stop_array_down 
 * @param[in] elevator_panel_lights_array 
 * @param[in] direction 
 * @param[in] elevator_queue 
 * @return status flag of 1 if we want to stop the elevator, 0 if we don't want to stop the elevator.
 */
int check_for_orders_at_floor(int floor, int * stop_array_up, int * stop_array_down,int* elevator_panel_lights_array, MotorDirection * direction, int * elevator_queue);

/**
 * @brief Updates the elevator direction based on if the elevator is not in a defined state, 
 * or if the current floor is greater/less than the first element in the elevator queue.
 * 
 * @param[in] elevator_queue The array that represents the queue system of the elevator.
 * @param[out] direction The variable that represents the direction of the elevator.
 * @param[in] current_floor A pointer to the address of the current floor of the elevator
 */
void decide_direction_state(int * elevator_queue, MotorDirection * direction, float * current_floor);


