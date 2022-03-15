#include "head_include_file.h"

void activate_stop_light();
void delete_queue_stopbutton_pressed(int * elevator_queue, int * stop_array_up, int * stop_array_down, int * elevator_panel_lights_array);

int check_stopbutton_pushed(int * elevator_queue, int * stop_array_up, int * stop_array_down,int * elevator_panel_lights_array, MotorDirection * direction){
    //If not pushed:
    if(elevio_stopButton() == 0){                                
        return 0;                                               
    }
    //if pushed:
    *direction=DIRN_STOP;
    elevio_motorDirection(DIRN_STOP);                           
    activate_stop_light();                                      
    delete_queue_stopbutton_pressed(elevator_queue, stop_array_up, stop_array_down, elevator_panel_lights_array);   
    return 1;                                                                                                                                                                                
}

void activate_stop_light(){
        //Turn on light
        elevio_stopLamp(1);   
        //if in a defined floor state, open door                              
        if(elevio_floorSensor() > -1){                      
            elevio_doorOpenLamp(1);                         
        }
}

void deactivate_stop_light(){
        //Turn off light
        elevio_stopLamp(0);    
        //If in an undefined state, close door                         
        if(elevio_floorSensor() == -1){                 
            elevio_doorOpenLamp(0);                     
        }
   
}

void delete_queue_stopbutton_pressed(int * elevator_queue, int * stop_array_up, int * stop_array_down, int * elevator_panel_lights_array){
                                                        
    //First iterate through the elevator queue and delete/reset the queue                      
    for(int element = 0; element < queue_size; element++){
        *(elevator_queue + element) = -1;                      
    }
    //Then iterate through the stop and light arrays 
    int stop_array_up_and_down_size = 4;                                              
    for(int element = 0; element < stop_array_up_and_down_size; element++){
        *(stop_array_up + element) = 0;                        
        *(stop_array_down + element) = 0;
        *(elevator_panel_lights_array+element)=0;
    }   
    update_floor_order_lights(stop_array_up, stop_array_down, elevator_panel_lights_array);
}


void stopbutton_flag_discarder(int * stop_button_flag, int * floor_sensor){
       if(((*stop_button_flag==1)&&(*floor_sensor==-1))){
               *stop_button_flag=0;
           }
}

void stop_at_floor_procedure(int * floorstop_flag, int * stop_button_flag, time_t * ref_time, MotorDirection * direction,int * floor_sensor, int * elevator_panel_lights_array, int * elevator_queue, int * stop_array_up, int* stop_array_down ){
        const double processor_freq = 2.9 * pow(10,4);

        //If the stop flags are active and the elevator is in a defined floor state:
                    //Stop elevator and open door
                    if(*floorstop_flag==1||((*stop_button_flag==1)&&(*floor_sensor>-1))){
                        elevio_doorOpenLamp(1);
                        *direction=DIRN_STOP;
                        
                        //timer logic    
                        if (*ref_time==0){
                            *ref_time= clock()/processor_freq;
                        }else if(elevio_obstruction()==1){
                            *ref_time= clock()/processor_freq;
                        }

                        
                        //If 3 seconds have passed:
                        if(check_for_three_seconds(*ref_time)){
                            
                                *ref_time=0;
                                *stop_button_flag=0;
                                elevio_doorOpenLamp(0);
                                delete_and_sort_queue(*floor_sensor, elevator_queue, stop_array_up, stop_array_down, elevator_panel_lights_array);
                            }


                    }

}

int check_for_three_seconds(time_t ref_time){                                        
    double processor_freq = 2.9 * pow(10,4);                                                                                                      

    //If 3 seconds or more have passed, return "1" or "TRUE"                                                                                     
    if(fabs(difftime(ref_time, clock()/processor_freq)) >= 3){      
        printf("time: %f\n", fabs(difftime(ref_time, clock()/processor_freq)));                
            return 1;                                                               
    }  
    //Else return "0" or "FALSE"                                                                             
    else{                                                                       
        return 0;
    }
}
