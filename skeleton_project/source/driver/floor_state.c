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

void que_system(int *oppStopp_ref[4], int *nedStopp_ref[4],int *ko_ref[5]){
if (*ko_ref[0]==-1){

}

}
void add_to_queue_up_down(int *oppStopp_ref[4], int *nedStopp_ref[4]){
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
                if (btnPressed==1){
                       if(b==1){
                           *nedStopp_ref[f]=1;
                       }else if(b==0){
                           *oppStopp_ref[f]=1;
                       }
            }
        }

}}