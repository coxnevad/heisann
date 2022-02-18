#include "initilize_pos.h"

//sjekker om den er i en udefinert etasje, er den det beveger den seg ned til den er i en definert etasje. 

void startup_procedure(int *floor_ref, MotorDirection *direction_ref){
    while(elevio_floorSensor()<0){
        elevio_motorDirection(DIRN_DOWN);
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);

        int temp_floor = elevio_floorSensor();
        printf("floor: %d \n",temp_floor);
        *direction_ref=DIRN_DOWN;
    }
    *floor_ref= elevio_floorSensor();
    *direction_ref = DIRN_STOP;
    elevio_motorDirection(DIRN_STOP);
    elevio_stopLamp(0);
}