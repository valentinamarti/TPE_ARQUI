#include <timeuser.h>
#include <lib.h>

// Container defines
#define NAME "TIMEUSER"
#define CX0 220 //Constant X0
#define CY0 200 //Constant Y0
#define WIDTH 600
#define HEIGHT 150

static int container_id;

void sleep(int seconds){
    do_sys_sleep(seconds);
}

void run_timeuser(){
    container_id = do_sys_new_container(NAME,CX0,CY0,WIDTH,HEIGHT); 
    set_container_id(container_id);

    setBorder(container_id, TIME_BORDER);
    setBackground(container_id, TIME_BACKGROUND);

    int hrs, min, sec; 
    do_sys_get_time(&hrs, &min, &sec);
    newLine();
    printf(" %dhrs : %dmin : %dsec \n", HELP_HEADINGS, hrs, min, sec);
    
    sleep(5000);
    exitContainer(container_id);
}
