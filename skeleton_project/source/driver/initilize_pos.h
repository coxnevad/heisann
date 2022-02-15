#pragma once
#include <stdio.h>
#include "elevio.h"
#include <time.h>


//funksjon som skal initialisere posisjonen til heisen tar inn en referanse til global variabel g_floor og endre den
void startup_procedure(int *floor_ref, MotorDirection *direction_ref);