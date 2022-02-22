#pragma once
#include <stdio.h>
#include "elevio.h"
#include <time.h>
#include <math.h>

#define ko_size 5
#define THREE_SECONDS_IN_STEPS 65

void update_current_floor_state(float* current_floor, int floor_sensor, MotorDirection *direction, int * previous_floor);

void update_previous_floor_state(int floor_sensor, int *previous_floor);

int check_stopbutton_pushed(int * heis_ko, int * opp_ko, int * ned_ko, MotorDirection * direction);
void activate_stop_light();
void deactivate_stop_light();
void delete_queue_stopbutton_pressed(int * heis_ko, int * opp_ko, int * ned_ko);

int emergency_stop();

void fetch_order_from_floor(int * opp_vektor, int * ned_vektor);

void activate_floor_order_lights(int * opp_vektor, int * ned_vektor);

void fetch_order_from_elevator(int * ko_vektor);
void add_to_ko(int* ko, int added_floor);
int check_if_element_not_in_queue(int* queue, int element);

void activate_elevator_lights(int * ko);

int check_for_orders_at_floor(int floor, int * heis_ko, int * opp_ko, int * ned_ko, MotorDirection * direction);

void delete_and_sort_queue(int floor, int * heis_ko, int * opp_ko, int *ned_ko);