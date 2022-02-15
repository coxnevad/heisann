#pragma once
#include <stdio.h>
#include "elevio.h"
#include <time.h>



void update_previous_floor_state(int current_floor, int *previous_floor);

void its_time_to_stop(MotorDirection *current_direction);
void update_stop_light();
void stop_direct_consequence(MotorDirection *current_direction);
void stop_delete_queue(); //Implementer senere når vi har laget køsystem


void que_system(int *oppStopp_ref[4], int *nedStopp_ref[4],int *ko_ref[5]);

void add_to_queue_up_down(int *oppStopp_ref[4], int *nedStopp_ref[4]);