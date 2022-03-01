#include "head_include_file.h"

void add_to_ko(int* elevator_queue, int added_floor){
    
    if(check_if_element_not_in_queue(elevator_queue, added_floor)){

    for(int k_index = 0; k_index<ko_size; k_index++){
        if(*(elevator_queue+k_index)==-1){
            *(elevator_queue+k_index)=added_floor;
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

void delete_and_sort_queue(int floor_sensor, int * elevator_queue, int * stop_array_up, int *stop_array_down, int * elevator_panel_lights_array){
    *(stop_array_up+floor_sensor)=0;
    *(stop_array_down+floor_sensor)=0;
    *(elevator_panel_lights_array+floor_sensor)=0;
    for (int i = 0; i < ko_size-1; i++){
        if (*(elevator_queue+i)==floor_sensor){
            for(int j=0; j < ko_size-i-1; j++){
                *(elevator_queue+i+j)=*(elevator_queue+i+j+1);
            }
        }
    }
}

