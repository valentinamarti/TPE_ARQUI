#include <shell.h>
#include <stdint.h>
#include <lib.h>
#include <timeuser.h>
       
#define P_OS_ID ">^< "
#define BUFFER_SHELL_SIZE 50
#define NULL 0
#define DEFAULT_FONT_SIZE 2

// Container defines
#define NAME "SHELL"
#define CX0 10  //Constant X0
#define CY0 10  //Constant Y0
#define WIDTH 1005
#define HEIGHT 700


void help();
void divbyzero();
void opcode();
void time();
void snake();
void lettersize();
void registers();
void exit();

static char command[BUFFER_SHELL_SIZE] = {0};
static char argument[BUFFER_SHELL_SIZE] = {0};
static int container_id; 


static command_t commands[] = {  {"help", help, " "},
                            {"divbyzero", divbyzero, "does the nubmer passed as a parameter dividied by zero"},
                            {"opcode", opcode, "simulates a wrong opcode exception"}, 
                            {"time", time, "displays the hour (time ARG)"},
                            {"registers", registers, "prints the registers that were captures by the shift+alt+R hot key; if no registeres were captured it prints an error message"},
                            {"snake",snake, "play the snake game"}, 
                            {"lettersize", lettersize, "it changes the size of the letter to the number passed as a paramter (it is advised numbers between 1 and 5)"},    // esta recibe un cahr* que tiene q 
                            {"exit", exit, "it exits the shell"}  
                              };                               // psar a int para invocar a la fun changeLettersize


void load_shell(){
    int aux = do_sys_new_container(NAME,CX0,CY0,WIDTH,HEIGHT); 
    container_id = aux;
    set_container_id(container_id);

    setBorder(container_id, SHELL_BACKGROUND);
    setFontSize(5);
    newLine();
    puts("       pantherOS\n", SHELL_LETTER);
    newLine();
    puts("         /\\_/\\", SHELL_LETTER);  
    puts("        ( o.o ) ", SHELL_LETTER);
    puts("         > ^ <", SHELL_LETTER);
    sleep(3000);
    clear_sb();
    setFontSize(DEFAULT_FONT_SIZE);
}


void run_shell(){
    load_shell();
    while(1){
        argument[0] = 0;           // asi la puedo volver a usar
        command[0] = 0; 
        print(P_OS_ID, SHELL_POSID);      // le hize tipo bigotes de pantera
        scanf("%s %s", SHELL_LETTER, command, argument); 
       
        for(int i = 0; i < commands[i].name != NULL ; i++){
            if(strcmp((commands[i].name), command) == 0){
                (*commands[i].func)(argument);       
            }
        }
    }
}


void help(){
    newLine();
    printf(">>>> This is the %s menu \n", HELP_HEADINGS, commands[0].name);
    for(int i = 1; i < commands[i].name != NULL ; i++){
            printf(">> %s : \n", HELP_HEADINGS, commands[i].name);
            printf("      %s \n", SHELL_LETTER, commands[i].description);
    }
}

// no se xq no funciona como yo quiero :(
void divbyzero(char* param){
    int aux = atoi(param);
    int aux2 =  division();
    //falta imprimir los registros
}

void opcode(){
    wrong_opcode();
}

// esta la podria hacer, de momento ya tengo todo solo que no me funciona :( (desps ver si lo metemos en container o no)
void time(){
    run_timeuser();
    set_container_id(container_id);
}

// esta tambn la podria "hacer" solo que falta lo de abrirla en un container y eso 
void registers(){
    do_sys_get_registers();
}

void snake(){
    load_snake();
    set_container_id(container_id);

}

void lettersize(char* param){       // falta que cuando reescriba mantenga los enter; no se porq no lo hace
    int aux = atoi(param);
    if(aux != 0){
        setFontSize(aux);
    }
}

void exit(){
    
}

