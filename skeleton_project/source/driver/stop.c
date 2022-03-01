#include "overordnet_include.h"


int check_stopbutton_pushed(int * heis_ko, int * stop_array_opp, int * stop_array_ned,int * heispanel_lys_array, MotorDirection * direction){
    if(elevio_stopButton() == 0){                               //Hvis knappen ikke er trykket inn 
        return 0;                                               //returnerer vi 0 eller "false"
    }
    *direction=DIRN_STOP;
    elevio_motorDirection(DIRN_STOP);                           //Hvis ikke er den trykket inn, og vi skal stoppe
    activate_stop_light();                                      //Så skrur vi på lyset
    delete_queue_stopbutton_pressed(heis_ko, stop_array_opp, stop_array_ned, heispanel_lys_array);   //sletter alle bestillinger
    return 1;                                                   //returnerer 1 eller "true", slik at vi får hoppet inn i en if-setning 
                                                                //som har continue, slik at vi hopper tilbake til toppen av while-løkken
                                                                //så slipper vi å ha break
}

void activate_stop_light(){
        elevio_stopLamp(1);                                 //skrur på stop-lyset
        if(elevio_floorSensor() > -1){                      //Hvis vi er i en etasje:
            elevio_doorOpenLamp(1);                         //Så skruv vi på etasje-lyset
        }
}

void deactivate_stop_light(){
        elevio_stopLamp(0);                             //skrur av lyset
        //BYTT UT INNHOLDET I IF-SETNINGEN UNDER MED TIDSLOGIKK, HVIS STOPPKNAPPEN IKKE ER TRYKKET LENGER, OG TIDSDIFFERANSEN ER PÅ 3 SEK, SÅ SKAL DØREN LUKKES
        if(elevio_floorSensor() == -1){                 //Hvis vi ikke er i en etasje lenger
            elevio_doorOpenLamp(0);                     
        }
   
}

void delete_queue_stopbutton_pressed(int * heis_ko, int * stop_array_opp, int * stop_array_ned, int * heispanel_lys_array){
                                                        //5 elementer i heis_ko
    int opp_stop_array_ned_storrelse = 4;                       //4 elementer i både opp og ned heis_ko
    for(int element = 0; element < ko_size; element++){
        *(heis_ko + element) = -1;                      //her skal alle elementene i køen settes til
    }                                                   // -1 som er "udefinert"
    for(int element = 0; element < opp_stop_array_ned_storrelse; element++){
        *(stop_array_opp + element) = 0;                        //skal settes til false
        *(stop_array_ned + element) = 0;
        *(heispanel_lys_array+element)=0;
    }   
    update_floor_order_lights(stop_array_opp, stop_array_ned, heispanel_lys_array);
}


void stop_button_flag_discarder(int * stop_button_flag, int * floor_sensor){
       if(((*stop_button_flag==1)&&(*floor_sensor==-1))){
               *stop_button_flag=0;
           }
}

void stop_at_floor_procedure(int * floorstop_flag, int * stop_button_flag, time_t * ref_time, MotorDirection * direction,int * floor_sensor, int * heispanel_lys_array, int * heis_ko, int * stop_array_opp, int* stop_array_ned ){
        const double processor_freq = 2.9 * pow(10,4);

                    if(*floorstop_flag==1||((*stop_button_flag==1)&&(*floor_sensor>-1))){
                        elevio_doorOpenLamp(1);
                        *direction=DIRN_STOP;
                        
                            
                        if (*ref_time==0){
                            *ref_time= clock()/processor_freq;
                        }else if(elevio_obstruction()==1){
                            *ref_time= clock()/processor_freq;
                        }

                        
                        
                        if(check_for_three_seconds(*ref_time)){
                            
                                *ref_time=0;
                                *stop_button_flag=0;
                                elevio_doorOpenLamp(0);
                                delete_and_sort_queue(*floor_sensor, heis_ko, stop_array_opp, stop_array_ned, heispanel_lys_array);
                            }

                    
                    
                    }

}

int check_for_three_seconds(time_t ref_time){                                       //Tar inn en tidsreferanse basert på datamaskinen sin klokkefrek, 
      double processor_freq = 2.9 * pow(10,4);                                                                               //så skal vi sammenligne den med hvor mange klokketicks/freq som har gått siden
                                                   //Så returnerer vi enten True eller False, ut ifra det.
                                           //2.9 GHz er prosessoren sin oppgitte klokkefrekvens på PC-en, men vi må endre på potensen her
    if(fabs(difftime(ref_time, clock()/processor_freq)) >= 3){      
        printf("time: %f\n", fabs(difftime(ref_time, clock()/processor_freq)));                //Hvis differansen er på 3 sek, så returnerer vi True
            return 1;                                                               //Hvis ikke returnerer vi False.
    }                                                                               //Har funnet ut at pow(10,4) er det som egentlig funker og gir oss "realistiske resultater"
    else{                                                                       
        return 0;
    }
}
