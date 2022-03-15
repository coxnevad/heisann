#include "initilize_pos.h"

//If the elevator is in an undefined state, then it moves upwards untill it reaches a defined floor state.

void startup_procedure(int *floor_ref, MotorDirection *direction_ref){
    
    //While undefined state:
    while(elevio_floorSensor()<0){
        elevio_motorDirection(DIRN_UP);
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);

        int temp_floor = elevio_floorSensor();
        printf("floor: %d \n",temp_floor);
        *direction_ref=DIRN_UP;
    }
    
    //Update floor and motor states, also update the elevator lights.
    *floor_ref= elevio_floorSensor();
    *direction_ref = DIRN_STOP;
    elevio_motorDirection(DIRN_STOP);
    elevio_stopLamp(0);
    elevio_doorOpenLamp(0);
}