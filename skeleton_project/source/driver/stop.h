#pragma once
#include "overordnet_include.h"

int check_stopbutton_pushed(int * heis_ko, int * stop_array_opp, int * stop_array_ned,int * heispanel_lys_array, MotorDirection * direction);
void activate_stop_light();
void deactivate_stop_light();
void delete_queue_stopbutton_pressed(int * heis_ko, int * stop_array_opp, int * stop_array_ned, int * heispanel_lys_array);

void stop_button_flag_discarder(int * stop_button_flag, int * floor_sensor);

void stop_at_floor_procedure(int * floorstop_flag, int * stop_button_flag, time_t * ref_time, MotorDirection * direction,int * floor_sensor, int * heispanel_lys_array, int * heis_ko, int * stop_array_opp, int* stop_array_ned );

int check_for_three_seconds(time_t ref_time);