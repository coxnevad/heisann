#pragma once
#include <stdio.h>
#include "elevio.h"
#include <time.h>



void update_previous_floor_state(int current_floor, int *previous_floor);

void its_time_to_stop(MotorDirection *current_direction);
void update_stop_light();
void stop_direct_consequence(MotorDirection *current_direction);
void stop_delete_queue(); //Implementer senere når vi har laget køsystem
