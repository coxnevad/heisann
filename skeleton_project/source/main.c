#include <stdlib.h>
#include <signal.h>

#include "driver/overordnet_include.h"

int main(){
    
    //lager globale variabler
    int g_floor_sensor=-1; //starter å"minus 1 fordi det er defionert som udefinert
    float g_current_floor=0;
    int g_previous_floor=-1;

    MotorDirection g_elevator_direction=DIRN_STOP;

    int g_oppStopp[4]={0,0,0,0};
    int g_nedStopp[4]={0,0,0,0};
    int g_heispanel_lys[4]={0,0,0,0};
    int g_overordnet_ko[5]={-1,-1,-1,-1,-1};

    int g_floorstop_flag=0;
    int g_stop_button_flag_case=0;
 
    time_t g_ref_time=0;
    

    
    elevio_init();    
    startup_procedure(&g_floor_sensor, &g_elevator_direction);
    update_previous_floor_state(g_floor_sensor, &g_previous_floor);
    elevio_floorIndicator(g_previous_floor);


    
    printf("=== Program ===\n");
    printf("Velkommen til Gruppe en si heislab\n");
    printf("Remember to kill all lemons on your way out\n");
    while(1){
        //routine check
       
        g_floor_sensor=elevio_floorSensor();
        update_previous_floor_state(g_floor_sensor, &g_previous_floor);
        elevio_floorIndicator(g_previous_floor);
        

        

        if (check_stopbutton_pushed(&g_overordnet_ko[0], &g_oppStopp[0], &g_nedStopp[0], &g_heispanel_lys[0], &g_elevator_direction)){  //Sender inn funksjonen, hvis knappen er trykket ned
            g_stop_button_flag_case=1;
            g_ref_time=0;
            continue;                                                        //Hopp tilbake til toppen av while løkken
            
        }else{
            deactivate_stop_light();                                      
            
            fetch_order_from_floor(&g_oppStopp[0], &g_nedStopp[0],&g_heispanel_lys[0], &g_overordnet_ko[0]);
            update_floor_order_lights(&g_oppStopp[0], &g_nedStopp[0], &g_heispanel_lys[0]);
            decide_direction_state(&g_overordnet_ko[0], &g_elevator_direction, &g_current_floor);
            update_current_floor_state(&g_current_floor,g_floor_sensor, &g_elevator_direction, &g_previous_floor);
            
            g_floorstop_flag= check_for_orders_at_floor(g_floor_sensor, &g_oppStopp[0], &g_nedStopp[0],&g_heispanel_lys[0] ,&g_elevator_direction, &g_overordnet_ko[0]);
            stop_at_floor_procedure(&g_floorstop_flag, &g_stop_button_flag_case, &g_ref_time, &g_elevator_direction, &g_floor_sensor, &g_heispanel_lys[0], &g_overordnet_ko[0], &g_oppStopp[0], &g_nedStopp[0]);
                    
            elevio_motorDirection(g_elevator_direction);

            stop_button_flag_discarder(&g_stop_button_flag_case, &g_floor_sensor);
        }



        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
