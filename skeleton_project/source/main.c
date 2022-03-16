/**
 * @file main.c
 * @author Simon Krane & Clemens Sundby Øxnevad
 * @brief This is our main program, also known as main.c
 * @version 0.1
 * @date 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <stdlib.h>
#include <signal.h>

#include "driver/head_include_file.h"

int main(){
    
   //initialize global variables
    //floor_state_variables
    int g_floor_sensor=-1; 
    float g_current_floor=0;
    int g_previous_floor=-1;
    //direction_variable
    MotorDirection g_elevator_direction=DIRN_STOP;


    //queue and lights arrays
    int g_up_Stop[4]={0,0,0,0};
    int g_down_Stop[4]={0,0,0,0};
    int g_elevator_panel_lights[4]={0,0,0,0};
    int g_elevator_queue[5]={-1,-1,-1,-1,-1};

    //status flag variables
    int g_floorstop_flag=0;
    int g_stop_button_flag_case=0;
    //time reference variable. 
    time_t g_ref_time=0;
    

    //startup proceedure
    elevio_init();    
    startup_procedure(&g_floor_sensor, &g_elevator_direction);
    update_previous_floor_state(g_floor_sensor, &g_previous_floor);
    elevio_floorIndicator(g_previous_floor);


    

    while(1){
        //routine check       
        g_floor_sensor=elevio_floorSensor();
        update_previous_floor_state(g_floor_sensor, &g_previous_floor);
        elevio_floorIndicator(g_previous_floor);
        

        
        //checks if stop button is pushed or not
        if (check_stopbutton_pushed(&g_elevator_queue[0], &g_up_Stop[0], &g_down_Stop[0], &g_elevator_panel_lights[0], &g_elevator_direction)){  //Sender inn funksjonen, hvis knappen er trykket ned
            //raises flag and deactivates the timer. 
            g_stop_button_flag_case=1;
            g_ref_time=0;
            continue;                                                        
            
        }else{
            //runs as intended
            deactivate_stop_light();                                      
            
            //updates floor, position, direction and queues
            fetch_order_from_floor_and_add_to_elevator_queue(&g_up_Stop[0], &g_down_Stop[0],&g_elevator_panel_lights[0], &g_elevator_queue[0]);
            update_floor_order_lights(&g_up_Stop[0], &g_down_Stop[0], &g_elevator_panel_lights[0]);
            decide_direction_state(&g_elevator_queue[0], &g_elevator_direction, &g_current_floor);
            update_current_floor_state(&g_current_floor,g_floor_sensor, &g_elevator_direction, &g_previous_floor);
            
            //sets flag for a stop at a floor
            g_floorstop_flag= check_for_orders_at_floor(g_floor_sensor, &g_up_Stop[0], &g_down_Stop[0],&g_elevator_panel_lights[0] ,&g_elevator_direction, &g_elevator_queue[0]);
            //takes action based on the flags
            stop_at_floor_procedure(&g_floorstop_flag, &g_stop_button_flag_case, &g_ref_time, &g_elevator_direction, &g_floor_sensor, &g_elevator_panel_lights[0], &g_elevator_queue[0], &g_up_Stop[0], &g_down_Stop[0]);
            //updates the working motor direction        
            elevio_motorDirection(g_elevator_direction);


            //discards stop_button flag in case of returning from stop. 
            stopbutton_flag_discarder(&g_stop_button_flag_case, &g_floor_sensor);
        }



        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
