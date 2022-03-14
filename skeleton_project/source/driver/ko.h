/**
 * @file ko.h
 * @author Simon Krane & Clemens Sundby Øxnevad
 * @brief This file handles the queue system of the elevator. How to add an element to the queue, checking if an element is a part fo the queue and deleting and sorting of a queue.
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "head_include_file.h"

/**
 * @brief This is the function that adds a floor order to the elevator queue
 * 
 * @param[in,out] elevator_queue The array that represents the queue system of the elevator.
 * @param[in] added_floor The floor that is being added to the queue.
 */
void add_to_queue(int* elevator_queue, int added_floor);

/**
 * @brief This is a function that checks if an element is not in the queue. 
 * It loops over the elevator queue and checks if an element is in the queue.
 * 
 * @param[in] queue The array that represents the queue system we want to iterate through.
 * @param element The element we want to look for in the queue system.
 * @return int Return 0 (FALSE) if we find the element in the queue, 1 if the element is not in the queue.
 */
int check_if_element_not_in_queue(int* queue, int element);

/**
 * @brief This is the function that is supposed to delete orders of the elevator queue, light array or the stop arrays when the elevator stops at a floor.
 * The arrays are easily handled by setting the indexed floor in the array to zero.
 * The elevator queue is supposed to "delete the first element" and then sort the queue.
 * 
 * @param[in] floor The variable that shows the current floor of the elevator.
 * @param[out] elevator_queue The array that represents the queue system of the elevator.
 * @param[out] stop_array_up The array that indicates if the elevator floor panel up buttons are pushed. 
 * @param[out] stop_array_down The array that indicates if the elevator floor panel down buttons are pushed. 
 * @param[out] elevator_panel_lights_array The array that indicates if the elevator panel lights are on.
 */
void delete_and_sort_queue(int floor, int * elevator_queue, int * stop_array_up, int *stop_array_down, int * elevator_panel_lights_array);