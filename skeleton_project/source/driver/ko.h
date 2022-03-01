#pragma once
#include "head_include_file.h"

void add_to_ko(int* elevator_queue, int added_floor);
int check_if_element_not_in_queue(int* queue, int element);
void delete_and_sort_queue(int floor, int * elevator_queue, int * stop_array_up, int *stop_array_down, int * elevator_panel_lights_array);