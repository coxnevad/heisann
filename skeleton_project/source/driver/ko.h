/**
 * @file ko.h
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
 * @brief Adds a floor order to the elevator queue
 * 
 * @param[in,out] elevator_queue An array that represents the queue system of the elevator.
 * @param[in] added_floor A variable to the floor order that is being added to the queue.
 */
void add_to_queue(int* elevator_queue, int added_floor);

/**
 * @brief Loops over the elevator queue and checks if an element is in the queue.
 * 
 * @param[in] queue An array that represents the queue system we want to iterate through.
 * @param element A variable to the element we want to look for in the queue system.
 * @return Return a value of "0" or "FALSE" if the element is in the queue, return "1" or "TRUE" if the element is not in the queue.
 */
int check_if_element_not_in_queue(int* queue, int element);

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