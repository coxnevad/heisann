#include "head_include_file.h"

//Checks if a floor is not in the queue system, if the floor is not found return 1 = TRUE, if found return 0 = FALSE
int check_if_floor_not_in_queue(int* queue, int floor){

    int floor_not_found=1;            
    for(int n=0; n< queue_size; n++){
        if(*(queue+n)==floor){
            floor_not_found=0;
        }
    }
    return floor_not_found;

}

//Adds a floor order to the queue system
void add_to_queue(int* elevator_queue, int added_floor){
    //If the floor is not in the queue:
    if(check_if_floor_not_in_queue(elevator_queue, added_floor)){
    //add the floor:
    for(int k_index = 0; k_index<queue_size; k_index++){
        if(*(elevator_queue+k_index)==-1){
            *(elevator_queue+k_index)=added_floor;
            break;
        }
    }
    }
}

void delete_and_sort_queue(int floor_sensor, int * elevator_queue, int * stop_array_up, int *stop_array_down, int * elevator_panel_lights_array){
    //set the specific array elements from high "1" to low "0"
    *(stop_array_up+floor_sensor)=0;
    *(stop_array_down+floor_sensor)=0;
    *(elevator_panel_lights_array+floor_sensor)=0;
    //Then sort the main elevator queue
    for (int i = 0; i < queue_size-1; i++){
        if (*(elevator_queue+i)==floor_sensor){
            for(int j=0; j < queue_size-i-1; j++){
                *(elevator_queue+i+j)=*(elevator_queue+i+j+1);
            }
        }
    }
}

void fetch_order_from_floor_and_add_to_elevator_queue(int * stop_array_up, int * stop_array_down, int* elevator_panel_lights_array, int * elevator_queue){
    
    int * floor_lib[3]={stop_array_up, stop_array_down, elevator_panel_lights_array};
    
    for(int f = 0; f < N_FLOORS; f++){
        for(int b=0; b<N_BUTTONS; b++){
            //If button is pushed:
            if(elevio_callButton(f,b)){   
                *(floor_lib[b]+f)=1;
               add_to_queue(elevator_queue, f);       
            }
        }
    }
}