#include <timeuser.h>
#include <lib.h>
#include <snake.h>

// Container defines
#define NAME "SNAKE"
#define CX0 100     //Constant X0
#define CY0 100     //Constant Y0
#define WIDTH 500
#define HEIGHT 500
static int container_id;



//--------------------------------------------------------------------

void load_snake(){
    container_id = do_sys_new_container(NAME,CX0,CY0,WIDTH,HEIGHT); 
    set_container_id(container_id);
    load_snake_menu();
    sleep(5000);
    exitContainer(container_id);
}



int load_snake_menu(){
    setBackground(container_id,WHITE);
    setFontSize(3);
    int current_player= 1;
    char c= UP_ARROW;
    

    while(c != '\n'){
        
        if(c==UP_ARROW || c== DOWN_ARROw){
            clear_sb();
            clear();
            if(c== UP_ARROW){
                current_player=1;
            }
            else{
                current_player=2;
            }
            puts("Jugadores:",BLACK);
            puts("1 Jugador",(current_player==1)?GREEN:BLACK);
            puts("2 jugadores",(current_player==2)?GREEN:BLACK);
        }
        c = getCharFromKernel();
    }

    return current_player;
}

