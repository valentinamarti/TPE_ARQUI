#include <shell.h>
#include <stdint.h>
#include <lib.h>
#include <timeuser.h>

#define WHITE 0         // es mentira, no esta definido ningun color todavia 
#define P_OS_ID ">^< > "
#define BUFFER_SHELL_SIZE 50
#define NULL 0
#define DEFAULT_FONT_SIZE 1

static char *regsName[] = {"RAX", "RBX", "RDX" "RSI", "RDI", "RBP", "RSP", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15", "RIP"};

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


static command_t commands[] = {  {"help", help, " "},
                            {"divbyzero", divbyzero, "divide el numero que recibe como argumento por cero"},
                            {"opcode", opcode, "ni idea que hace este"}, 
                            {"time", time, "deslpiega la hora del sistema (zona horaria ARG)"},
                            {"registers", registers, "imprime los valores de los registros capturados al hacer shift+alt+R"},
                            {"snake",snake, "juego snake el cual como argumento recibe la cantidad de jugadores; por default un jugador"}, 
                            {"lettersize", lettersize, "cambia la dimension de las letras con el numero que recibe como argumento"},    // esta recibe un cahr* que tiene q 
                            {"exit", exit, "sale del programa"}  
                              };                               // psar a int para invocar a la fun changeLettersize


void load_shell(){
    set_container_id();
    setFontSize(3);
    /*newLine();
    print("   pantherOS\n", WHITE);
    newLine();
    puts("     /\\_/\\", WHITE);  
    puts("    ( o.o ) ", WHITE);
    puts("     > ^ <", WHITE);
    sleep(1500);
    clear_sb();
    */
    // aca quiero una funcion para borrar del buffer del video driver lo del pantheros
    setFontSize(DEFAULT_FONT_SIZE);
    //clear();
}


void run_shell(){
    load_shell();
    while(1){
        argument[0] = 0;           // asi la puedo volver a usar
        command[0] = 0; 
        print(P_OS_ID, WHITE);      // le hize tipo bigotes de pantera
        scanf("%s %s", WHITE, command, argument); 
       
        for(int i = 0; i < commands[i].name != NULL ; i++){
            if(strcmp((commands[i].name), command) == 0){
                (*commands[i].func)(argument);       
            }
        }
    }
}


void help(){
    newLine();
    for(int i = 0; i < commands[i].name != NULL ; i++){
        if(strcmp((commands[i].name), "help") != 0){
            printf(">> %s <>\n   %s \n", WHITE, commands[i].name, commands[i].description);    
        }   
    }
}

// no se xq no funciona como yo quiero :(
void divbyzero(char* param){
    int aux = atoi(param);
    int aux2 =  division();
    //falta imprimir los registros
}

void opcode(){

}

// esta la podria hacer, de momento ya tengo todo solo que no me funciona :( (desps ver si lo metemos en container o no)
void time(){
    run_timeuser();
}
// esta tambn la podria "hacer" solo que falta lo de abrirla en un container y eso 
void registers(){
    uint64_t registers[17];
    do_sys_get_registers(&registers);
    for(int i = 0; i < 17; i++){
        printf(" %s <> %s \n", WHITE, regsName[i], registers[i]);
    }
}

void snake(){

}

void lettersize(char* param){       // falta que cuando reescriba mantenga los enter; no se porq no lo hace
    int aux = atoi(param);
    if(aux != 0){
        setFontSize(aux);
    }
}

void exit(){
    
}

