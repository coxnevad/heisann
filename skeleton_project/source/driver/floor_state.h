#pragma once
#include "overordnet_include.h"



void update_current_floor_state(float* current_floor, int floor_sensor, MotorDirection *direction, int * previous_floor);
void update_previous_floor_state(int floor_sensor, int *previous_floor);


void fetch_order_from_floor(int * stop_array_opp, int * stop_array_ned, int* heispanel_lys_array, int* heis_ko);
void update_floor_order_lights(int * stop_array_opp, int * stop_array_ned, int * heispanel_lys_array);
int check_for_orders_at_floor(int floor, int * stop_array_opp, int * stop_array_ned,int* heispanel_lys_array, MotorDirection * direction, int * heis_ko);

void decide_direction_state(int * heis_ko, MotorDirection * direction, float * current_floor);


