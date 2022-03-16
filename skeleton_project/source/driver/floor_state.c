#include "floor_state.h"



void update_current_floor_state(float* current_floor, int floor_sensor, MotorDirection *direction, int * previous_floor){
    float differance=0.0;                                
    float former_current_floor_value =*current_floor;   
    float possible_new_current_floor_value =0;  
    
    //If we are between two floors:         
    if(floor_sensor == -1){                              
        switch (*direction) 
        {
        case DIRN_DOWN:                                                                             
            possible_new_current_floor_value = *previous_floor - 0.5;                                
            break;                                                                                  
        case DIRN_UP:
           possible_new_current_floor_value = *previous_floor + 0.5;
            break;
        
        
        default:
            possible_new_current_floor_value= *current_floor;
            break;  
        }
        //Subtract new value from the last measurement of the "current" floor value to check for possible bugs. If the value is not too crazy, then update the current floor state.                                                                                            
        differance=fabs((possible_new_current_floor_value)-(former_current_floor_value));                 
        if(differance <1){
            *current_floor=possible_new_current_floor_value;
        }

    //else, the current floor is the value of the floor sensor.  
    }else{
        *current_floor = floor_sensor;
    }
    
}

void update_previous_floor_state(int floor_sensor, int *previous_floor){
    //if we are not in an undefined floor state:
    if (floor_sensor > -1){
        *previous_floor=floor_sensor;        
    }
}






void update_floor_order_lights(int * stop_array_up, int * stop_array_down, int * elevator_panel_lights_array){
    int array_size=4;
    int opp_knapp = BUTTON_HALL_UP;
    int ned_knapp= BUTTON_HALL_DOWN;
    int heis_knapp = BUTTON_CAB;

    for(int i =0; i < array_size; i++){
        //Update button lights
        elevio_buttonLamp(i, opp_knapp, *(stop_array_up+i));
        elevio_buttonLamp(i, ned_knapp, *(stop_array_down+i));
        elevio_buttonLamp(i, heis_knapp, *(elevator_panel_lights_array+i));
    }
}

int check_for_orders_at_floor(int floor_sensor, int * stop_array_up, int * stop_array_down,int* elevator_panel_lights_array, MotorDirection * direction, int *elevator_queue){
    int stop =0;
    //if the elevator is in an undefined floor state, do not update stop:
    if(floor_sensor ==-1){
        return stop;
    }

    //Based on the motor direction and arrays, update stop:
    if (*direction == DIRN_UP){
        if(*(stop_array_up+floor_sensor)==1){
            stop = 1;
            
        }
    }else if(*direction== DIRN_DOWN){
        if(*(stop_array_down+floor_sensor)==1){
            stop = 1;
            
        }
    }else if(*direction== DIRN_STOP){
        if((*(stop_array_up+floor_sensor)==1)||(*(stop_array_down+floor_sensor)==1)){
        stop = 1;
        
        }
    }
    
    if(*(elevator_panel_lights_array+floor_sensor)==1){
        stop = 1;
       
    }
    if(*elevator_queue==floor_sensor){
        stop = 1;
       
    }
    return stop;

}


void decide_direction_state(int * elevator_queue, MotorDirection * direction, float * current_floor){
    //If the queue is empty
     if(*elevator_queue==-1){
                *direction=DIRN_STOP;
            }
            //if the queue is not empty:
            else if(*current_floor < *elevator_queue){
                *direction=DIRN_UP;
            }else if(*elevator_queue < *current_floor){
                *direction=DIRN_DOWN;
            }
}
