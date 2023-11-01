#include <timeuser.h>
#include <lib.h>

#define CONTAINER_TIMEUSER_ID 1     // desps cambiarlo este no es el que va

void sleep(int seconds){
    do_sys_sleep(seconds);
}

void run_timeuser(){
    //supongo aca creo el container
    set_container_id(CONTAINER_TIMEUSER_ID);
    int hrs, min, sec; 
    do_sys_get_time(&hrs, &min, &sec);
    printf(" %dhrs : %dmin : %dsec \n", 0, hrs, min, sec);
}
