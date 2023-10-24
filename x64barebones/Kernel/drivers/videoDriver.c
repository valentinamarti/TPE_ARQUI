//#include <lib.h>
#include <font8x8_basic.h>
#include <stdint.h>
#include <string.h>
//#include <stdarg.h>
#include <videoDriver.h>

#define SCREEN_W VBE_mode_info->width
#define SCREEN_H VBE_mode_info->height
#define SCREENBUFER_SIZE 256

uint8_t SIZE = DEFAULT_SIZE;

uint8_t screenbuffer[SCREENBUFER_SIZE];
uint16_t screenbuffer_idx=0;

struct vbe_mode_info_structure {
    uint16_t attributes;        // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;           // deprecated
    uint8_t window_b;           // deprecated
    uint16_t granularity;       // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;      // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;             // number of bytes per horizontal line
    uint16_t width;             // width in pixels
    uint16_t height;            // height in pixels
    uint8_t w_char;             // unused...
    uint8_t y_char;             // ...
    uint8_t planes;
    uint8_t bpp;                // bits per pixel in this mode
    uint8_t banks;              // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size;          // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer;       // physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size;   // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__ ((packed));





uint64_t ACTUAL_X = 0, ACTUAL_Y = 0;                    // Coordenadas de escritura de caracteres


typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

char inScreenX(uint16_t pixelPos){
    return pixelPos <= SCREEN_W;
}
char inScreenY(uint16_t pixelPos){
    return pixelPos <= SCREEN_H;
}
void changeSize(uint8_t num){
    SIZE= num;
    redrawScreenBuffer(WHITE,0);
}

void addScreenBuffer(uint8_t character){
    if(SCREENBUFER_SIZE== screenbuffer_idx){
        return;
    }
    screenbuffer[screenbuffer_idx++]= character;
}

void redrawScreenBuffer(color_t color,uint16_t offset){
    emptyScreen();
    int aux=screenbuffer_idx;
    screenbuffer_idx=0;
    for(int i=offset; i< aux;i++){
        drawChar(color,screenbuffer[i]);
    }
}

void emptyScreen(){
    for(int y=0; y<SCREEN_H; y++){
        for(int x=0; x<SCREEN_W; x++){
            putPixel(BLACK,x,y);
        }
    }
    ACTUAL_X=0;
    ACTUAL_Y=0;
    return;
}

void newLine(){
    if(inScreenY(ACTUAL_Y + 2 * DEFAULT_CHAR_HEIGHT * SIZE)){
        ACTUAL_Y+= DEFAULT_CHAR_HEIGHT* SIZE;
    }
    else{
        redrawScreenBuffer(WHITE,SCREEN_W/(DEFAULT_CHAR_WIDTH * SIZE));
    }ACTUAL_X=0;

}
void putPixel(color_t color, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;                 // Crea un puntero al framebuffer del struct 
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  color.blue;              // Escribe los colores en el framebuffer
    framebuffer[offset+1]   =  color.green; 
    framebuffer[offset+2]   =  color.red;
}

void drawRectangle(color_t color,int posx,int posy, int sizex, int sizey){
    for(int i=0;i<sizey;i++){
        for(int j=0;j<sizex;j++){
            putPixel(color,posx+i,posy+j);
        }
    }
}

void drawByte(color_t color,uint8_t hexa,uint64_t posx, uint64_t posy){
    for(int i=0; i< 8;i++){ //El 8 es el tamaño del byte
        if(hexa & 1){
            drawRectangle(color,posx + i * SIZE,posy,SIZE,SIZE);
        }
        hexa= hexa>>2;
    }
}

void drawChar(color_t color, char character){
    addScreenBuffer(character);
    char* vector= font[character];
    if(character== '\b'){

    }
    if((! inScreenX(ACTUAL_X + DEFAULT_CHAR_WIDTH * SIZE)) || character=='\n'){
        newLine();
    }
    for(int y=0;y<DEFAULT_CHAR_HEIGHT;y++){
        drawByte(color,vector[y],ACTUAL_X,ACTUAL_Y+y *SIZE);
    }

    ACTUAL_X+= DEFAULT_CHAR_WIDTH * SIZE;

}

// AUXILIARES A BORRAR
void printAsciiTable(int size){
    changeSize(size);
	drawChar(WHITE,'A');

}
// FIN BORRAR