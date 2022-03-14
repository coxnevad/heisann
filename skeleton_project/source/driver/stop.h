/**
 * @file stop.h
 * @author Simon Krane & Clemens Sundby Øxnevad
 * @brief The file that handles both the elevator stopping at a floor and how the elevator stops if the stop button is pushed.
 * @version 0.1
 * @date 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include "head_include_file.h"

/**
 * @brief The function that handles the logic behind the stop button. 
 * If the stop button is pushed, the function will:
 * \n 1. Set the elevator direction to stopped, and stop the motor
 * \n 2. Turn on the stop light
 * \n 3. Delete the Elevator queue 
 * \n Then it returns 1 if the button was pushed, and 0 if not.
 * 
 * @param[out] elevator_queue The array that represents the queue system of the elevator.
 * @param[out] stop_array_up The array that indicates if the elevator floor panel up buttons are pushed. This will be reset.
 * @param[out] stop_array_down The array that indicates if the elevator floor panel down buttons are pushed. This will be reset.
 * @param[out] elevator_panel_lights_array The array that indicates if the elevator panel lights are on. This will be reset
 * @param[out] direction The variable that represents the direction of the elevator.
 * @return 1 if the stop button is pushed, 0 if it is not pushed.
 */
int check_stopbutton_pushed(int * elevator_queue, int * stop_array_up, int * stop_array_down,int * elevator_panel_lights_array, MotorDirection * direction);

/**
 * @brief A simple function to deactivate the stop light, it also decides if the door lamp is on or off based on the elevator being on a floor or between two floors.
 * 
 */
void deactivate_stop_light();

/**
 * @brief This is a function that is supposed to fix a bug that we had related to the stop button, and stopping between two floors.
 * The function is used each loop. If the stop button flag is high and the floor sensor is in an undefined state, then we set the stop button flag low, in order to avoid a bug where the elevator gets stuck between two floors.
 *  
 * 
 * @param[in,out] stop_button_flag A stop flag to indicate if the stop button has been pushed. It has to be reset in order for the bug to be fixed.
 * @param[in] floor_sensor A variable that shows what floor state the elevator is in. This is to indicate if the elevator is between two floors.
 */
void stop_button_flag_discarder(int * stop_button_flag, int * floor_sensor);

/**
 * @brief This is a function that handles the overall logic of stopping at a floor.
 * It activates the elevator door light, stops the elevator and makes sure that it takes 3 seconds before the elevator continues. 
 * 
 * @param[in] floorstop_flag A flag to indicate if the elevator has stopped at a floor.
 * @param[in,out] stop_button_flag A stop flag to indicate if the stop button has been pushed.
 * @param[in,out] ref_time The variable that controls the time of the elevator door. It is used here to make sure that it takes 3 seconds from opening the elevator door untill it closes.
 * @param[out] direction A variable that gives the current direction of the elevater.
 * @param[in] floor_sensor A variable that shows what floor state the elevator is in.
 * @param[in] elevator_panel_lights_array The array that indicates if the elevator panel lights are on.
 * @param[in] elevator_queue The array that represents the queue system of the elevator.
 * @param[in] stop_array_up The array that indicates if the elevator floor panel up buttons are pushed.
 * @param[in] stop_array_down The array that indicates if the elevator floor panel down buttons are pushed.
 */
void stop_at_floor_procedure(int * floorstop_flag, int * stop_button_flag, time_t * ref_time, MotorDirection * direction,int * floor_sensor, int * elevator_panel_lights_array, int * elevator_queue, int * stop_array_up, int* stop_array_down );

/**
 * @brief A simple function that is supposed to return 1 "TRUE" if 3 seconds or more have passed or 0 "FALSE" if less than 3 seconds have passed.
 * Here we use the difftime function from the time library with ref_time and the time generated from the number of clock cycles since programme start in order to check if 3 seconds have passed.
 * 
 * @param[in] ref_time The variable that controls the time of the elevator door. Here it is used to c
 * @return int If 3 seconds have passed return "1", else return "0"
 */
int check_for_three_seconds(time_t ref_time);