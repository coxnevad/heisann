#pragma once
#include <stdio.h>
#include "elevio.h"
#include <time.h>

#define ko_size 5



void update_previous_floor_state(int current_floor, int *previous_floor);

void its_time_to_stop(MotorDirection *current_direction);
void update_stop_light();
void stop_direct_consequence(MotorDirection *current_direction);
void stop_delete_queue(); //Implementer senere når vi har laget køsystem

void fetch_order_from_floor(int * opp_vektor, int * ned_vektor);

void activate_floor_order_lights(int * opp_vektor, int * ned_vektor);

void fetch_order_from_elevator(int * ko_vektor);
void add_to_ko(int* ko, int added_floor);
int check_if_element_not_in_queue(int* queue, int element);

void activate_elevator_lights(int * ko);