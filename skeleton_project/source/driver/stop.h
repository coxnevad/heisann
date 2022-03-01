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
 * @param[out] elevator_panel_lights_array The array that indicates if the elevator panel lights are pushed. This will be reset
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
 * SPØRR CLEMENS OM HVA VI SKAL SKRIVE HER
 * 
 * @param[in,out] stop_button_flag A flag that has to be reset in order for the bug to be fixed
 * @param[in] floor_sensor This is to indicate if the elevator is between two floors.
 */
void stop_button_flag_discarder(int * stop_button_flag, int * floor_sensor);

void stop_at_floor_procedure(int * floorstop_flag, int * stop_button_flag, time_t * ref_time, MotorDirection * direction,int * floor_sensor, int * elevator_panel_lights_array, int * elevator_queue, int * stop_array_up, int* stop_array_down );

int check_for_three_seconds(time_t ref_time);