#include "floor_state.h"


void update_previous_floor_state(int current_floor, int *previous_floor){
    if (current_floor > -1){
        *previous_floor=current_floor;        
    }
}

void update_stop_light(){
        elevio_stopLamp(1);
}
   

void stop_direct_consequence(MotorDirection *current_direction){
    *current_direction = DIRN_STOP;
    elevio_motorDirection(DIRN_STOP); 
   
}

void its_time_to_stop(MotorDirection *current_direction){
    update_stop_light();
    stop_direct_consequence(current_direction);
}