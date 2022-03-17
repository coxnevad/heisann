/**
 * @file queue.h
 * @author Simon Krane & Clemens Sundby Øxnevad
 * @brief This file handles the queue system of the elevator. How to add an element to the queue, checking if an element is a part of the queue and deleting and sorting a queue.
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "head_include_file.h"

/**
 * @brief Deletes orders of the elevator queue, light array or the stop arrays when the elevator stops at a floor.
 * \n The arrays are handled by setting the indexed floor in the array to zero.
 * \n Deletes the first element of the elevator queue, then sorts the queue.
 * 
 * @param[in] floor A variable that shows the current floor of the elevator.
 * @param[out] elevator_queue An array that represents the queue system of the elevator.
 * @param[out] stop_array_up An array that indicates if the elevator floor panel up buttons are pushed. 
 * @param[out] stop_array_down An array that indicates if the elevator floor panel down buttons are pushed. 
 * @param[out] elevator_panel_lights_array An array that indicates if the elevator panel lights are on.
 */
void delete_and_sort_queue(int floor, int * elevator_queue, int * stop_array_up, int *stop_array_down, int * elevator_panel_lights_array);

/**
 * @brief Fetches and adds orders to the elevator queue if the elevator buttons are pushed. 
 * It also updates the arrays that contain the information related to the floor panels.
 * 
 * @param[in,out] stop_array_up An array that indicates if the elevator floor panel up buttons are pushed.
 * @param[in,out] stop_array_down An array that indicates if the elevator floor panel down buttons are pushed.
 * @param[in,out] elevator_panel_lights_array An array that indicates if the elevator panel lights are on.
 * @param[out] elevator_queue An array that represents the queue system of the elevator.
 */
void fetch_order_from_floor_and_add_to_elevator_queue(int * stop_array_up, int * stop_array_down, int* elevator_panel_lights_array, int* elevator_queue);