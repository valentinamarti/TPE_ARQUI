#include <miniDriverKeyboard.h>

extern char getKeyPressed();
void getKeyValue(uint8_t key);
void saveCharToBuffer(char c);
char getNextCharFromBuffer();

#define MAX_VALUE_FOR_KEY 0x79
#define L_SHIFT_PUSH_KEY_VALUE 0x2A
#define R_SHIFT_PUSH_KEY_VALUE 0x36
#define ALT_KEY_PUSH_VALUE 0x38
#define L_SHIFT_RELEASE_KEY_VALUE 0xAA
#define R_SHIFT_RELEASE_KEY_VALUE 0xB6
#define CAPS_LOCK_KEY_VALUE 0x3A
#define BUFFER_SIZE 250

// En video driver deberiamos agregar que si encontramos tal caracter especial 
// como por ejemplo '\t' tenemos que hacer tal cosa y etc


static unsigned char* keyboard[] = {   
    // Para usar esto, nos falta ver de donde salio; asi ponemos la documentacion necesaria para justificar 
        0, 27, "1", "2", "3", "4", '5', '6', '7', '8', '9', '0', '-', '=', '\b', /*del*/ 
        '\t', /*tab*/ 'q', 'w', 'e', 'r',  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    /*enter*/ 
        0,  /*29-control */ 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
        0,  /*l shift*/ '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,  /*r shift*/
        '*', /*numpad **/ 0,    /* Alt */ ' ',    /* Space bar */ 0,    /* Caps lock */ 
        0,    /* 59 - F1 key ... > */ 0, 0, 0, 0, 0, 0, 0, 0, 0,    /* < ... F10 */
        0,    /* 69 - Num lock*/
        0,    /* Scroll Lock */
        0,    /* Home key */
        0,    /* Up Arrow */
        0,    /* Page Up */
        '-',
        0,    /* Left Arrow */
        0,
        0,    /* Right Arrow */
        '+',
        0,    /* 79 - End key*/
        0,    /* Down Arrow */
        0,    /* Page Down */
        0,    /* Insert Key */
        0,    /* Delete Key */
        0, 0, 0,
        0,    /* F11 Key */
        0,    /* F12 Key */
        0,    /* All other keys are undefined */
};

static unsigned char* keyboard_shift[] = {
        0, 27, '!', '\"', '#', 0 /*shift+4*/, '%', '&', '/', '(', ')', '=', '?', '`', '\b', /*del*/
        '\t', /*tab*/ 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /*enter*/
        0,  /*29-control*/ 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\'', '>', 
        0, /*l shift*/ '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0, /*r shift*/
        '*', /*numpad **/ 0,    /* Alt */ ' ',   /* Space bar */ 0,    /* Caps lock */  
        0,    /* 59 - F1 key ... > */  0, 0, 0, 0, 0, 0, 0, 0, 0,    /* < ... F10 */
        0,    /* 69 - Num lock*/
        0,    /* Scroll Lock */
        0,    /* Home key */
        0,    /* Up Arrow */
        0,    /* Page Up */
        '-',  /*numpad -*/
        0,    /* Left Arrow */
        0,
        0,    /* Right Arrow */
        '+',  /*numpad +*/
        0,    /* 79 - End key*/
        0,    /* Down Arrow */
        0,    /* Page Down */
        0,    /* Insert Key */
        0,    /* Delete Key */
        0, 0, '>',
        0,    /* F11 Key */
        0,    /* F12 Key */
        0,    /* All other keys are undefined */
};

static char buffer[BUFFER_SIZE] = {0};
static int first = 0;                   // points to the first element of the buffer
static int last = 0;                    // points to the last element added
static int elems = 0; 

char shiftFlag = 0;                     // if 1 we use keyboard_shift
char capsLockFlag = 0;                  // if 1 we use keyboard_shift 
char altFlag = 0; 


void keyboard_handler(){
    uint8_t key = getKeyPressed();
   
    if(key <= MAX_VALUE_FOR_KEY){
        getKeyValue(key);                       // ver si desps le cambio el nombre
    }else if(key ==  L_SHIFT_RELEASE_KEY_VALUE || key == R_SHIFT_RELEASE_KEY_VALUE){
        shiftFlag = 0;         
    }
}

void getKeyValue(uint8_t key){
    if(key == L_SHIFT_PUSH_KEY_VALUE || key == R_SHIFT_PUSH_KEY_VALUE){
        shiftFlag = 1; 
        return;
    }else if(key == CAPS_LOCK_KEY_VALUE){
        capsLockFlag = ~(capsLockFlag | 0xFE);          // niego el caps, si estaba prendido lo apago y viceversa
        return; 
    }else if(key == ALT_KEY_PUSH_VALUE){
        altFlag = 1; 
        return; 
    }
    unsigned char c = 0; 
    if(capsLockFlag == 1 && ((key >= 0x10 && key <= 0x19)  || (key >= 0x1E && key <= 0x26) || (key >= 0x2C && key <= 0x32))){
             c = keyboard_shift[key];
    }else if(shiftFlag == 1){
        c = keyboard_shift[key];
    }else{
        c = keyboard[key];
    }
    if(c != 0){
        // ncPrintChar(c);              // si quiero que funcione que se escriban en la pantalla, hay q descomentar esto 
        saveCharToBuffer(c);
    }
}

void saveCharToBuffer(char c){
    if (elems == BUFFER_SIZE){
            return;             // osea llegue al limite no hago nada
        }
    if(first == BUFFER_SIZE){   // si llego al final, vuelvo al principio
        first = 0; 
    } 
    if(last == BUFFER_SIZE){
        last = 0; 
    }
    buffer[last++] = c;
    elems++;
}

char getNextCharFromBuffer(){
    if(elems <= 0){
        return 0;          // if there are no elements, return null?
    }
    char aux = buffer[first++];
    elems--; 
    return aux; 
}

