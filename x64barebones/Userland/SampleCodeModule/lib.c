#include <lib.h>
#include <stdarg.h>
// #include <def.h>

#define STDOUT 1	// para imprimir en pantalla el fd 
#define MAX_CHARS 150
#define BUFFER_SHELL_SIZE 150
#define BUFFER_KERNEL 0
#define BUFFER_USERSPACE 1


#define UP_1 1
#define DOWN_1 4
#define LEFT_1 2
#define RIGHT_1 3


#define isupper(c) ((c >= 'A') && (c <= 'Z'))
#define islower(c) ((c >= 'a') && (c <= 'z'))
#define tolower(c) (c + ('a' - 'A'))
#define toupper(c) (c - ('a' - 'A'))

extern void do_sys_write(char* buffer, int longitud, int fd, color_t* color, int container_id);
extern void do_sys_new_line(int container_id);
extern void do_sys_get_time(int* hrs, int* min, int* sec);
extern void do_sys_read(char* buffer, int longitud, int fd);
extern int do_sys_new_container(char * name, int X0, int Y0,int width, int height);
extern void do_sys_draw_rectangle(int posx, int posy, int sizex, int sizey, color_t * color, int container_id);
extern void do_sys_clear(int container_id);
extern void do_sys_exit_container(int container_id);
extern void do_sys_set_background(color_t* color, int container_id);
extern void do_sys_set_border(color_t* color, int container_id);
extern void do_sys_clear_sb(int container_id);
extern void do_sys_set_font_size(int size, int container_id);

static int container_id;
unsigned int seed = 1234; // Initial seed value

// ESTA FUNCION SI O SI LLAMARLA AL PRINCIPIO, PARA QUE CARGUE EL CONTAINER
void set_container_id(int id){
    container_id = id;
}

int getID(){
    return container_id;
}


unsigned int rand(){
    seed = (1103515245 * seed + 12345) & 0x7FFFFFFF; // LCG formula
    return seed;
}

//falta agregar float 
void printf(char* string, color_t color, ...){
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

void printChar(char c, color_t color){
    char buff = c; 
    do_sys_write(&buff, 1, STDOUT, &color, container_id);
}

void putChar(char c, color_t color){
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

void puts(char* string, color_t color){
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
        buff[i++] = '0';
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

void print(char* buff, color_t color){
    int len = strlen(buff);
    do_sys_write(buff, len, STDOUT, &color, container_id);
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
    char s1Aux[MAX_CHARS] = {0};
    char s2Aux[MAX_CHARS] = {0};
    strcopy(s1Aux, s1);    
    strcopy(s2Aux, s2);
    toMin(s1Aux);
    toMin(s2Aux);
    int aux = strcmp(s1Aux, s2Aux);
    return aux; 
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
 
int scanf(char* fmt, color_t color, ...){
    va_list v;
    va_start(v, color);

    char c;
    char buffer[MAX_CHARS];            
    int i = 0;                         

    while ((c = getCharFromKernel()) != '\n' && i < BUFFER_SHELL_SIZE - 1){
        if(c != UP_1 && c != DOWN_1 && c != LEFT_1 && c != RIGHT_1){
            if(c == '\b' && i > 0){
                buffer[i--] = ' ';
                printChar(c, color);
            }else if(c != '\b' && c != 0){
                    buffer[i++] = c; 
                    printChar(c, color);
            }
        }
    }
    newLine();

    buffer[i] = 0;          
    int params = 0; 
    i = 0;                     
    int j = 0;                 

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
            print("ERROR", color);
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

void setBackground(color_t color){
    do_sys_set_background(&color, container_id);
}

void setBorder(color_t color){
    do_sys_set_border(&color, container_id);
}

void exitContainer(int container_id){
    do_sys_exit_container(container_id);
}

void printRectangle(int posx, int posy, int sizex, int sizey, color_t color){
    do_sys_draw_rectangle(posx,posy,sizex,sizey,&color,container_id);
}
