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

void fetch_order_from_floor(int * opp_vektor, int * ned_vektor){
    
    int * floor_lib[2]={opp_vektor, ned_vektor};
    
    for(int f = 0; f < N_FLOORS; f++){
        for(int b=0; b<N_BUTTONS-1; b++){
            if(elevio_callButton(f,b)){
                *(floor_lib[b]+f)=1;
            }
        }
    }
}

void activate_floor_order_lights(int * opp_vektor, int * ned_vektor){
    int array_size=4;
    int opp_knapp = BUTTON_HALL_UP;
    int ned_knapp= BUTTON_HALL_DOWN;

    for(int i =0; i < array_size; i++){
        elevio_buttonLamp(i, opp_knapp, *(opp_vektor+i));
        elevio_buttonLamp(i, ned_knapp, *(ned_vektor+i));
    }
}


void fetch_order_from_elevator(int * ko_vektor){
    for (int f=0; f < N_FLOORS; f++){
        if(elevio_callButton(f, BUTTON_CAB)){
            add_to_ko(ko_vektor, f);

        }
    }
}



void add_to_ko(int* ko, int added_floor){
    
    if(check_if_element_not_in_queue(ko, added_floor)){

    for(int k_index = 0; k_index<ko_size; k_index++){
        if(*(ko+k_index)==-1){
            *(ko+k_index)=added_floor;
            break;
        }
    }
    }
}
int check_if_element_not_in_queue(int* queue, int element){

    int element_not_found=1;
    for(int n=0; n< ko_size; n++){
        if(*(queue+n)==element){
            element_not_found=0;
        }
    }
    return element_not_found;

}

void activate_elevator_lights(int * ko){

    /*
    for(int i =0; i < ko_size; i++){
        if(*(ko+i)!=-1){
            elevio_buttonLamp(*(ko+i), BUTTON_CAB, 1);
        }
    }*/
    for(int j=0; j < N_FLOORS; j++){
        if(check_if_element_not_in_queue(ko, j)){
            elevio_buttonLamp(j, BUTTON_CAB, 0);
        }
        else{
            elevio_buttonLamp(j, BUTTON_CAB, 1);
        }
    }
}




int check_for_orders_at_floor(int floor, int * heis_ko, int * opp_ko, int * ned_ko, MotorDirection * direction){
    int stop =0;
    if(floor ==-1){
        return stop;
    }
    if (*direction == DIRN_UP){
        if(*(opp_ko+floor)==1){
            stop = 1;
        }
    }else if(*direction== DIRN_DOWN){
        if(*(ned_ko+floor)==1){
            stop = 1;
        }
    }
    if(check_if_element_not_in_queue(heis_ko, floor)==0){
        stop = 1;
    }
    return stop;

}

void delete_and_sort_queue(int floor, int * heis_ko, int * opp_ko, int *ned_ko){
    *(opp_ko+floor)=0;
    *(ned_ko+floor)=0;
    for (int i = 0; i < ko_size-1; i++){
        if (*(heis_ko+i)==floor){
            for(int j=0; j < ko_size-i-1; j++){
                *(heis_ko+i+j)=*(heis_ko+i+j+1);
            }
        }
    }
}