#include "floor_state.h"



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




void fetch_order_from_floor(int * stop_array_opp, int * stop_array_ned, int* heispanel_lys_array, int * heis_ko){
    
    int * floor_lib[3]={stop_array_opp, stop_array_ned, heispanel_lys_array};
    
    for(int f = 0; f < N_FLOORS; f++){
        for(int b=0; b<N_BUTTONS; b++){
            if(elevio_callButton(f,b)){
                
                *(floor_lib[b]+f)=1;
               add_to_ko(heis_ko, f);      //OBSOBSOBS. må legge til en ny array som bestemmer lys i køen. for nå skrus flere lys på. 
            }
        }
    }
}

void update_floor_order_lights(int * stop_array_opp, int * stop_array_ned, int * heispanel_lys_array){
    int array_size=4;
    int opp_knapp = BUTTON_HALL_UP;
    int ned_knapp= BUTTON_HALL_DOWN;
    int heis_knapp = BUTTON_CAB;

    for(int i =0; i < array_size; i++){
        elevio_buttonLamp(i, opp_knapp, *(stop_array_opp+i));
        elevio_buttonLamp(i, ned_knapp, *(stop_array_ned+i));
        elevio_buttonLamp(i, heis_knapp, *(heispanel_lys_array+i));
    }
}

int check_for_orders_at_floor(int floor_sensor, int * stop_array_opp, int * stop_array_ned,int* heispanel_lys_array, MotorDirection * direction, int *heis_ko){
    int stop =0;
    if(floor_sensor ==-1){
        return stop;
    }
    if (*direction == DIRN_UP){
        if(*(stop_array_opp+floor_sensor)==1){
            stop = 1;
            
        }
    }else if(*direction== DIRN_DOWN){
        if(*(stop_array_ned+floor_sensor)==1){
            stop = 1;
            
        }
    }else if(*direction== DIRN_STOP){
        if((*(stop_array_opp+floor_sensor)==1)||(*(stop_array_ned+floor_sensor)==1)){
        stop = 1;
        
        }
    }
    
    if(*(heispanel_lys_array+floor_sensor)==1){
        stop = 1;
       
    
    }
    if(*heis_ko==floor_sensor){
        stop = 1;
       
    }
    return stop;

}


void decide_direction_state(int * heis_ko, MotorDirection * direction, float * current_floor){
     if(*heis_ko==-1){
                *direction=DIRN_STOP;
            }else if(*current_floor < *heis_ko){
                *direction=DIRN_UP;
            }else if(*heis_ko < *current_floor){
                *direction=DIRN_DOWN;
            }
}
