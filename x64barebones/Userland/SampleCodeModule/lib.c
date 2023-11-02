#include <lib.h>
#include <stdarg.h>
// #include <def.h>

#define STDOUT 1	// para imprimir en pantalla el fd 
#define WHITE  0
#define MAX_CHARS 150
#define BUFFER_SHELL_SIZE 50
#define BUFFER_KERNEL 0
#define BUFFER_USERSPACE 1

// Container defines
#define NAME "SHELL"
#define CX0 10  //Constant X0
#define CY0 10  //Constant Y0
#define WIDTH 400
#define HEIGHT 500


#define isupper(c) ((c >= 'A') && (c <= 'Z'))
#define islower(c) ((c >= 'a') && (c <= 'z'))
#define tolower(c) (c + ('a' - 'A'))
#define toupper(c) (c - ('a' - 'A'))

extern void do_sys_write(char* buffer, int longitud, int fd, int color, int container_id);
extern void do_sys_new_line(int container_id);
extern void do_sys_get_time(int* hrs, int* min, int* sec);
extern void do_sys_read(char* buffer, int longitud, int fd);
//extern int do_sys_new_container(char * name, int X0, int Y0,int width, int height, int *container_id);

static int container_id;

// ESTA FUNCION SI O SI LLAMARLA AL PRINCIPIO, PARA QUE CARGUE EL CONTAINER
void set_container_id(){
    do_sys_new_container(NAME,CX0,CY0,WIDTH,HEIGHT, &container_id); 
    print(container_id+ '0',WHITE);
}

int getID(){
    return container_id;
}

//falta agregar float 
void printf(char* string, int color, ...){
    va_list v;
    char buffer[MAX_CHARS] = {0};
    char buffAux[25] = {0};         // buffer auxiliar para cuando transformo el arg con otra funcion que requiere de un buffer
    int i = 0, j = 0;               // con i recorro el string y con j el buffer
    va_start(v, color);

    while(string && string[i]){     // mientras string existe y no es un puntero nulo
                                    // mientras string[i] no es el carácter nulo 
        if(string[i] == '%'){
            i++; 
            switch(string[i]){
                // convierte a char 
                case 'c':{
                    buffer[j] = va_arg(v, int);
                    j++;
                    break;
                }
                // convierte a decimal
                case 'd':{
                    itoa(va_arg(v, int), buffAux, 10);
                    strcopy(&buffer[j], buffAux);
                    j += strlen(buffAux);
                    break;
                }
                // convierte a string
                case 's':{
                    char* str = va_arg(v, char*);
                    strcopy(&buffer[j], str);
                    j += strlen(str);
                    break;
                }
                // convierte a hexa
                case 'x':{
                    itoa(va_arg(v, int), buffAux, 16);
                    strcopy(&buffer[j], buffAux);
                    j += strlen(buffAux);
                    break; 
                }
            }
        }else if(string[i] == '\n'){
            buffer[j] = 0;
            print(buffer, color);
            newLine();  
            j = 0;         
        }else{
            buffer[j++] = string[i];            // si no es nada especial, copio el string normal en el buffer a devolver
        }
        i++; 
    }
    buffer[j] = 0;      // asi le indico que aca terminamos 
    print(buffer, color);
    va_end(v);
}

void printChar(char c, int color){
    char buff = c; 
    do_sys_write(&buff, 1, STDOUT, color, container_id);
}

void putChar(char c, int color){
    printChar(c, color);
    newLine();
}

char getChar(int fd){
    char buffer[1] = {0};
    do_sys_read(buffer, 1, fd);
    return buffer[0];
}


char getCharFromKernel(){
    return getChar(BUFFER_KERNEL);
}

char getCharFromUserspace(){
    return getChar(BUFFER_USERSPACE);
}

void puts(char* string, int color){
    print(string, color);
    newLine();
}

int strlen(char* string) {
    int aux = 0;
    while(string[aux] != 0){
        aux++;
    }
    return aux;
}

void itoa(int value, char* buff, int base){
    int i = 0;
    int val = abs(value);       // tomo el valor absoluto para no mandarme un moco con los signos

    if(val == 0){
        buff[i] = '0';
    }

    while(val != 0){
        int resto = val % base; 
        if(resto < 10){
            buff[i++] = resto + '0';
        }else{                          // con esto vemos si es hexa
            buff[i++] = resto + 'A' - 10;   
        }
        val /= base; 
    }

    if (value < 0 && base == 10) {      // si es base 10, le pongo el signo menos 
        buff[i++] = '-';
    }
    int dim = i;        // me guardo dim del numero
    
    int j = 0; 
    i -= 1;  
    char aux;
    while(j < i){
        aux = buff[j];
        buff[j] = buff[i];
        buff[i] = aux; 
        j++;
        i--;
    }
    buff[dim] = 0;

}

int atoi(char* value){
    int aux = 0;
    for (int i = 0; value[i] != '\0'; ++i){
        if(value[i] >= '0' && value[i] <= '9'){
             aux = aux * 10 + value[i] - '0';
        }
    }    
    return aux;
}

void strcopy(char* destination, char* string){
    if(destination == 0){
        return; 
    }
    int i;
    for(i  = 0; string[i] != '\0'; i++){
        destination[i] = string[i];
    }
    destination[i] = '\0';
}

void print(char* buff, int color){
    int len = strlen(buff);
    do_sys_write(buff, len, STDOUT, color, container_id);
}

void newLine(){
    printChar('\n', WHITE);        
}

int abs(int value){
	if(value < 0){
        return -value;
    }
    return value; 
}

int strcmp(char* s1, char* s2){         // devuelve 0 si son igulaes, 1 sino 
    int i = 0; 
     while (s1[i] && s2[i]){    
        if(s1[i] !=  s2[i]){
            return 1; 
        }
        i++;
    }
    if(s1[i] || s2[i]){
    return 1;       
    }
    return 0;
}

int strcmpMinMay(char* s1, char* s2){
    char* s1Aux;    // lo hago en auxiliares para no perder el original
    char* s2Aux;
    strcopy(s1Aux, s1);    
    strcopy(s2Aux, s2);
    toMin(s1Aux);
    toMin(s2Aux);
    return strcmp(s1Aux, s2Aux);
}

void toMin(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (isupper(str[i])) {
            str[i] = tolower(str[i]);
        }
    }
}

void toMay(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (islower(str[i])) {
            str[i] = toupper(str[i]);
        }
    }
}

void setFontSize(int size){
    do_sys_set_font_size(size, container_id);
}

void clear(){
    do_sys_clear(container_id);
}
 
int scanf(char* fmt, int color, ...){
    va_list v;
    va_start(v, color);

    char c;
    char buffer[MAX_CHARS];             // este va a ser el buffer auxiliar; aca guardo todo lo que obtengo 
    int i = 0;                          // este va a ser mi indice

    while ((c = getCharFromKernel()) != '\n' && i < BUFFER_SHELL_SIZE - 1){
        if(c == '\b' && i > 0){
            buffer[i--] = ' ';              // esto desps se pisa
            // aca elimino la letra, todavia no se como lo hace mati
            // a completar
        }else if(c != '\b' && c != 0){
            buffer[i++] = c; 
            printChar(c, color);
        }
    }
    newLine();
    // en esta parte se analiza que lo ingresado cumpla con el formato, 
    // y se van guardando los datos ingresados

    buffer[i] = 0;          // marco el final de lo recolectado
    int params = 0; 
    i = 0;                     // reinicializo el indice  
    int j = 0;                 // inicializo el indice para recorrer el formato

    while(fmt[j] != 0 && buffer[i] != 0 && i < MAX_CHARS){
        if(fmt[j] == '%'){
            j++; 
            switch(fmt[j]){
                // convierte a char 
                case 'c':{
                    *(char*) va_arg(v, char *) = buffer[i];
                    i++; 
                    params++;
                    break;
                }
                // convierte a decimal
                case 'd':{
                    int aux = wordlen(&buffer[i]);
                    buffer[i+aux] = 0; 
                    *(int*) va_arg(v, int *) = atoi(&buffer[i]);
                    buffer[i+aux] = ' ';
                    i += aux; 
                    params++;
                    break;
                }
                // convierte a string
                case 's':{
                    int aux = wordlen(&buffer[i]);
                    buffer[i+aux] = 0; 
                    strcopy((char *) va_arg(v, char *), &buffer[i]);
                    buffer[i+aux] = ' ';
                    i += aux;   
                    params++;
                    break;
                }
            } 
        } else if (fmt[j] == buffer[i]){
            i++; 
        } else{
            print("ERROR", WHITE);
        }
        j++;
    }

    va_end(v);
    return params;
}

int wordlen(char* s){
    int aux = 0;
    while(s[aux] != 0 && s[aux] != ' '){
        aux++;
    }
    return aux;
}

void clear_sb(){
    do_sys_clear_sb(container_id);
}


