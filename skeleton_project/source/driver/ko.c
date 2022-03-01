#include "overordnet_include.h"

void add_to_ko(int* heis_ko, int added_floor){
    
    if(check_if_element_not_in_queue(heis_ko, added_floor)){

    for(int k_index = 0; k_index<ko_size; k_index++){
        if(*(heis_ko+k_index)==-1){
            *(heis_ko+k_index)=added_floor;
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

void delete_and_sort_queue(int floor_sensor, int * heis_ko, int * stop_array_opp, int *stop_array_ned, int * heispanel_lys_array){
    *(stop_array_opp+floor_sensor)=0;
    *(stop_array_ned+floor_sensor)=0;
    *(heispanel_lys_array+floor_sensor)=0;
    for (int i = 0; i < ko_size-1; i++){
        if (*(heis_ko+i)==floor_sensor){
            for(int j=0; j < ko_size-i-1; j++){
                *(heis_ko+i+j)=*(heis_ko+i+j+1);
            }
        }
    }
}

