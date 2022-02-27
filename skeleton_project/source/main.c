#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/initilize_pos.h"
#include "driver/floor_state.h"



int main(){
    
    //lager globale variabler
    int g_floor_sensor=-1; //starter å"minus 1 fordi det er defionert som udefinert
    float g_current_floor=0;
    int g_previous_floor=-1;
    MotorDirection g_elevator_direction=DIRN_STOP;
    int oppStopp[4]={0,0,0,0};
    int nedStopp[4]={0,0,0,0};
    int heislys[4]={0,0,0,0};
    int overordnet_ko[5]={-1,-1,-1,-1,-1};
    int g_floorstop=0;
    int g_floor_stop_case_e=0;
 


   

    const double processor_freq = 2.9 * pow(10,4);
    time_t g_ref_time=0;
    

    
    elevio_init();
    
    
    //initialiserer posisjonen
    startup_procedure(&g_floor_sensor, &g_elevator_direction);
    update_previous_floor_state(g_floor_sensor, &g_previous_floor);
    elevio_floorIndicator(g_previous_floor);


    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    
    while(1){
        //routine check
       
        g_floor_sensor=elevio_floorSensor();
        
        update_previous_floor_state(g_floor_sensor, &g_previous_floor);
        elevio_floorIndicator(g_previous_floor);
        
         
        //routine check dione
        //printf("previous floor = %f\n", difftime(t1, t2));

        

        if (check_stopbutton_pushed(&overordnet_ko[0], &oppStopp[0], &nedStopp[0], &heislys[0], &g_elevator_direction)){  //Sender inn funksjonen, hvis knappen er trykket ned
            g_floor_stop_case_e=1;
            continue;                                                        //Hopp tilbake til toppen av while løkken
            
        }else{
            deactivate_stop_light();                                         //skrur av lyset
            fetch_order_from_floor(&oppStopp[0], &nedStopp[0],&heislys[0], &overordnet_ko[0]);
            activate_floor_order_lights(&oppStopp[0], &nedStopp[0], &heislys[0]);

           // fetch_order_from_elevator(&overordnet_ko[0]);
            //activate_elevator_lights(&overordnet_ko[0]);

            //__________________

            if(overordnet_ko[0]==-1){
                g_elevator_direction=DIRN_STOP;
            }else if(g_current_floor < overordnet_ko[0]){
                g_elevator_direction=DIRN_UP;
            }else if(overordnet_ko[0]<g_current_floor){
                g_elevator_direction=DIRN_DOWN;
            }
            update_current_floor_state(&g_current_floor,g_floor_sensor, &g_elevator_direction, &g_previous_floor);

            g_floorstop= check_for_orders_at_floor(g_floor_sensor, &overordnet_ko[0], &oppStopp[0], &nedStopp[0], &g_elevator_direction);
            //printf("%i\n", g_floorstop);
            //______________________________
                    if(g_floorstop==1||(g_floor_stop_case_e==1&&g_floor_sensor>-1)){
                        elevio_doorOpenLamp(1);
                        g_elevator_direction=DIRN_STOP;
                        if (g_ref_time==0){
                            g_ref_time= clock()/processor_freq;
                        }
                        
                        
                        if(check_for_three_seconds(g_ref_time)){
                            if(elevio_obstruction()==0){
                                g_ref_time=0;
                                g_floor_stop_case_e=0;
                                elevio_doorOpenLamp(0);
                                delete_and_sort_queue(g_floor_sensor, &overordnet_ko[0], &oppStopp[0], &nedStopp[0], &heislys[0]);
                            }
                        

                    }}

            //______________________________

           //printf("ko=[%i, %i, %i, %i, %i]", overordnet_ko[0],overordnet_ko[1], overordnet_ko[2], overordnet_ko[3], overordnet_ko[4]);
           elevio_motorDirection(g_elevator_direction);
           
        }


    /*
        if(elevio_stopButton()){
            its_time_to_stop(&g_elevator_direction);
            break;
        }else{
            elevio_stopLamp(0);
        

            

        
        int floor = elevio_floorSensor();
       

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
                if (btnPressed==1){
                       printf("floor: %d. button: %d \n",f,b);}

            }
        }
        
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        
        }*/
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
