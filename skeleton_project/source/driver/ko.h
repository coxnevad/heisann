#pragma once
#include "overordnet_include.h"

void add_to_ko(int* heis_ko, int added_floor);
int check_if_element_not_in_queue(int* queue, int element);
void delete_and_sort_queue(int floor, int * heis_ko, int * stop_array_opp, int *stop_array_ned, int * heispanel_lys_array);