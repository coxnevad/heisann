#include "floor_state.h"


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


void update_current_floor_state(float* current_floor, int floor_sensor, MotorDirection *direction, int * previous_floor){
    float differance=0.0;                               //variabelen som skal inneholde differansen (i fabsoluttverdi) mellom den forrige og eventuelt nye verdien til current floor. 
    float former_current_floor_value =*current_floor;   //Den tidligere verdien av *current_floor*, det ene leddet i difereansseregnestykket
    float possible_new_current_floor_value =0;          //Den mulige nye verdien current floor skal bli til. 
    if(floor_sensor == -1){                             //sjekker for om vi er mellom to etasjer. 
        switch (*direction) 
        {
        case DIRN_DOWN:                                                                             //(hele switch-case)
            possible_new_current_floor_value = *previous_floor - 0.5;                               //sjekker retningen og tar avhengig av retningen + eller - 
            break;                                                                                  //verdien av tidligere etasje.
        case DIRN_UP:
           possible_new_current_floor_value = *previous_floor + 0.5;
            break;
        
        
        default:
            possible_new_current_floor_value= *current_floor;
            break;  
        }                                                                                            //Sjekker om det er en gyldig differanse mellom tidligere og eventuelt nye verdi av current_floor
        differance=fabs((possible_new_current_floor_value)-(former_current_floor_value));                //beholder verdien om differansen er mindre enn 1, forkaster den hvis ikke. 
        if(differance <1){
            *current_floor=possible_new_current_floor_value;
        }

        /*
        har ett problem ved tilfelet når vi stopper mellom to etasjer og skal til etasjen vi sist var i, da ender vi opp i en loop, der "current_floor" vil 
        hele tiden tro at den er over eller under fordi retningen bestemmer og vil motvirke den tidligere retningen og dermed "spinne"

        Vi endte med å ikke løse problemet, bare ignorerte alle tilfeller når currentfloor, vil oppdatere seg med en verdi større eller er lik 1. 
        Feilen er ikke borte, den bare påvirker ikke programmet lengre. 
        */
    }else{
        *current_floor = floor_sensor;
    }
    
}

void update_previous_floor_state(int floor_sensor, int *previous_floor){
    if (floor_sensor > -1){
        *previous_floor=floor_sensor;        
    }
}

int check_stopbutton_pushed(int * heis_ko, int * opp_ko, int * ned_ko,int * heispanel_lys, MotorDirection * direction){
    if(elevio_stopButton() == 0){                               //Hvis knappen ikke er trykket inn 
        return 0;                                               //returnerer vi 0 eller "false"
    }
    *direction=DIRN_STOP;
    elevio_motorDirection(DIRN_STOP);                           //Hvis ikke er den trykket inn, og vi skal stoppe
    activate_stop_light();                                      //Så skrur vi på lyset
    delete_queue_stopbutton_pressed(heis_ko, opp_ko, ned_ko, heispanel_lys);   //sletter alle bestillinger
    return 1;                                                   //returnerer 1 eller "true", slik at vi får hoppet inn i en if-setning 
                                                                //som har continue, slik at vi hopper tilbake til toppen av while-løkken
                                                                //så slipper vi å ha break
}



void delete_queue_stopbutton_pressed(int * heis_ko, int * opp_ko, int * ned_ko, int * heispanellys){
                                                        //5 elementer i heis_ko
    int opp_ned_ko_storrelse = 4;                       //4 elementer i både opp og ned ko
    for(int element = 0; element < ko_size; element++){
        *(heis_ko + element) = -1;                      //her skal alle elementene i køen settes til
    }                                                   // -1 som er "udefinert"
    for(int element = 0; element < opp_ned_ko_storrelse; element++){
        *(opp_ko + element) = 0;                        //skal settes til false
        *(ned_ko + element) = 0;
        *(heispanellys+element)=0;
    }   
    activate_floor_order_lights(opp_ko, ned_ko, heispanellys);
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

void fetch_order_from_floor(int * opp_vektor, int * ned_vektor, int* heis_lys_ko, int * overordnet_ko){
    
    int * floor_lib[3]={opp_vektor, ned_vektor, heis_lys_ko};
    
    for(int f = 0; f < N_FLOORS; f++){
        for(int b=0; b<N_BUTTONS; b++){
            if(elevio_callButton(f,b)){
                
                *(floor_lib[b]+f)=1;
               add_to_ko(overordnet_ko, f);      //OBSOBSOBS. må legge til en ny array som bestemmer lys i køen. for nå skrus flere lys på. 
            }
        }
    }
}

void activate_floor_order_lights(int * opp_vektor, int * ned_vektor, int * heis_vektor){
    int array_size=4;
    int opp_knapp = BUTTON_HALL_UP;
    int ned_knapp= BUTTON_HALL_DOWN;
    int heis_knapp = BUTTON_CAB;

    for(int i =0; i < array_size; i++){
        elevio_buttonLamp(i, opp_knapp, *(opp_vektor+i));
        elevio_buttonLamp(i, ned_knapp, *(ned_vektor+i));
        elevio_buttonLamp(i, heis_knapp, *(heis_vektor+i));
    }
}
/*
void fetch_order_from_elevator(int * ko_vektor){
    for (int f=0; f < N_FLOORS; f++){
        if(elevio_callButton(f, BUTTON_CAB)){
            add_to_ko(ko_vektor, f);

        }
    }
}*/

void add_to_ko(int* ko, int added_floor){
    
    if(check_if_element_not_in_queue(ko, added_floor)){

    for(int k_index = 0; k_index<ko_size; k_index++){
        if(*(ko+k_index)==-1){
            *(ko+k_index)=added_floor;
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
/*
void activate_elevator_lights(int * ko){                //Trengs denne?, tror ikke det

    
    for(int i =0; i < ko_size; i++){
        if(*(ko+i)!=-1){
            elevio_buttonLamp(*(ko+i), BUTTON_CAB, 1);
        }
    }
    for(int j=0; j < N_FLOORS; j++){
        if(check_if_element_not_in_queue(ko, j)){
            elevio_buttonLamp(j, BUTTON_CAB, 0);
        }
        else{
            elevio_buttonLamp(j, BUTTON_CAB, 1);
        }
    }
}*/

int check_for_orders_at_floor(int floor_sensor, int * opp_ko, int * ned_ko,int* heis_lys, MotorDirection * direction, int *ko){
    int stop =0;
    if(floor_sensor ==-1){
        return stop;
    }
    if (*direction == DIRN_UP){
        if(*(opp_ko+floor_sensor)==1){
            stop = 1;
            
        }
    }else if(*direction== DIRN_DOWN){
        if(*(ned_ko+floor_sensor)==1){
            stop = 1;
            
        }
    }else if(*direction== DIRN_STOP){
        if((*(opp_ko+floor_sensor)==1)||(*(ned_ko+floor_sensor)==1)){
        stop = 1;
        
        }
    }
    
    if(*(heis_lys+floor_sensor)==1){
        stop = 1;
       
    
    }
    if(*ko==floor_sensor){
        stop = 1;
       
    }
    return stop;

}

void delete_and_sort_queue(int floor_sensor, int * heis_ko, int * opp_ko, int *ned_ko, int * heis_lys){
    *(opp_ko+floor_sensor)=0;
    *(ned_ko+floor_sensor)=0;
    *(heis_lys+floor_sensor)=0;
    for (int i = 0; i < ko_size-1; i++){
        if (*(heis_ko+i)==floor_sensor){
            for(int j=0; j < ko_size-i-1; j++){
                *(heis_ko+i+j)=*(heis_ko+i+j+1);
            }
        }
    }
}

/*void update_special_floor_order_case(int * opp_ko, int * ned_ko){
    *(opp_ko+3)=*(ned_ko+3);
    *(ned_ko+0)=*(opp_ko+0);
}*/