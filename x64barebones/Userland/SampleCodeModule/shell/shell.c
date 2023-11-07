#include <shell.h>
#include <stdint.h>
#include <lib.h>
#include <sounds.h>
#include <snake.h>
#include <timeuser.h>
       
#define P_OS_ID ">^< "
#define BUFFER_SHELL_SIZE 150
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
void clear_shell();

static char command[BUFFER_SHELL_SIZE] = {0};
static char argument[BUFFER_SHELL_SIZE] = {0};
static int container_id; 


static command_t commands[] = {  {"help", help, " "},
                            {"divbyzero", divbyzero, "does 7 dividied by zero"},
                            {"opcode", opcode, "simulates a wrong opcode exception"}, 
                            {"time", time, "displays the hour (time ARG)"},
                            {"registers", registers, "prints the registers that were captures by the shift+alt+R hot key; if no registeres were captured it prints an error message"},
                            {"snake",snake, "play the snake game"}, 
                            {"lettersize", lettersize, "it changes the size of the letter to the number passed as a paramter (it is advised numbers between 1 and 5)"},    // esta recibe un cahr* que tiene q 
                            {"clear", clear_shell, "clear the shell"}  
                              };                             


void load_shell(){
    int aux = do_sys_new_container(NAME,CX0,CY0,WIDTH,HEIGHT); 
    container_id = aux;
    set_container_id(container_id);

    setBorder(SHELL_BACKGROUND);
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
    playWinnerSound();
    while(1){
        argument[0] = 0;           
        command[0] = 0; 
        print(P_OS_ID, SHELL_POSID);      
        scanf("%s %s", SHELL_LETTER, command, argument); 
       
        int found = 0; 
        for(int i = 0; i < commands[i].name != NULL ; i++){
            if(strcmp((commands[i].name), command) == 0){
                (*commands[i].func)(argument);   
                found = 1;    
            }
        }
        if(found == 0){
            printf("Error command %s not found\n", SHELL_LETTER, command);
        }
    }
}


void help(){
    newLine(container_id);
    printf(">>>> This is the %s menu\n", HELP_HEADINGS, commands[0].name);
    for(int i = 1; i < 8 ; i++){
            printf("   >> %s : ", HELP_HEADINGS, commands[i].name);
            printf(" %s \n", SHELL_LETTER, commands[i].description);
    }
}

void divbyzero(){
    division();
}

void opcode(){
    wrong_opcode();
}

void time(){
    run_timeuser();
    set_container_id(container_id);
}

void registers(){
    run_regsuser();
    set_container_id(container_id);
}

void snake(){
    load_snake();
    set_container_id(container_id);

}

void lettersize(char* param){     
    int aux = atoi(param);
    if(aux != 0){
        setFontSize(aux);
    }
}

void clear_shell(){
    clear_sb();
    setFontSize(DEFAULT_FONT_SIZE);
}

