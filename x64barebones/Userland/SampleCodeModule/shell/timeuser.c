#include <timeuser.h>
#include <lib.h>

// Container defines
#define NAME "TIMEUSER"
#define TIMESIZE 3
#define CX0 200  //Constant X0
#define CY0 200  //Constant Y0
#define WIDTH 200
#define HEIGHT 300
#define WHITE 0  

static int container_id;

void sleep(int seconds){
    do_sys_sleep(seconds);
}

void run_timeuser(){
    int aux = do_sys_new_container(NAME,CX0,CY0,WIDTH,HEIGHT); 
    container_id = aux;
    set_container_id(container_id);
    setFontSize(TIMESIZE);
    int hrs, min, sec; 
    do_sys_get_time(&hrs, &min, &sec);
    printf(" %dhrs : %dmin : %dsec \n", 0, hrs, min, sec);

    char* buff1[30] = {0};
    char* buff2[30] = {0};
    while(1){
        
        scanf("%s %s", WHITE, buff1, buff2); 
    }    
}
