#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/initilize_pos.h"
#include "driver/floor_state.h"



int main(){
    
    //lager globale variabler
    int g_floor=-1; //starter å"minus 1 fordi det er defionert som udefinert
    int g_previous_floor=-1;
    MotorDirection g_elevator_direction=DIRN_STOP;
    int oppStopp[4]={0,0,0,0};
    int nedStopp[4]={0,0,0,0};
    int ko[5]={-1,-1,-1,-1, -1};

    int temp=0;  //midlertidig testkonstant
    
    
    
    elevio_init();
    
    
    //initialiserer posisjonen
    startup_procedure(&g_floor, &g_elevator_direction);
    update_previous_floor_state(g_floor, &g_previous_floor);
    elevio_floorIndicator(g_previous_floor);
    elevio_stopLamp(0);


    elevio_motorDirection(DIRN_UP);
    
    printf("=== Example Program ===\n");
   
    printf("Press the stop button on the elevator panel to exit\n");
elevio_stopLamp(0);
    while(1){
        g_floor=elevio_floorSensor();
        update_previous_floor_state(g_floor, &g_previous_floor);
        elevio_floorIndicator(g_previous_floor);
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
        printf("kpoen %d");
/*
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        */
        
        }
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
