#include <miniDriverKeyboard.h>

extern char getKey();
extern char getKeyPressed();

static char* codes[] = {
        "ERROR", "Esc","1","2","3","4","5","6","7","8","9","0","-","=","backspace",
        "tab","q","w","e","r","t","y","u","i","o","p","[","]","enter",
        "L Ctrl","a","s","d","f","g","h","j","k","l",";","\'","`",
        "L Shift", "\\", "z","x","c","v","b","n","m",",",".","/","R Shift","NumPad *",
        "L Alt", " ","CapsLock",
        "F1", "F2","F3","F4","F5","F6","F7","F8","F9","F10",
        "Num Lock", "ScrLk", "NumPad 7", "NumPad 8", "NumPad 9", "NumPad -", "NumPad 4"
        ,"NumPad 5","NumPad 6", "NumPad +", "NumPad 1", "NumPad 2", "NumPad 3", "NumPad 0",
        "NumPad ."
};

// char getPressedKeyCode(){
// 	return getKey(); 
// }

// char* getStringFromCode(char code){
//     return codes[code]; //code=getPressedKeyCode();
// }

void keyboard_handle1r(){
    uint8_t key = getKeyPressed();
    if(key <= 0x79){
        ncPrint(codes[key]);   
        ncPrint(" ");
        ncPrintHex(key);
        ncPrint(" ");
    }
    
}



