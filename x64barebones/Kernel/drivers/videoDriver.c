//#include <video.h>
//#include <lib.h>
#include <font.h>
#include <stdint.h>
#include <string.h>
//#include <stdarg.h>

#define RGB_SIZE 3
#define MAX_RESOLUTION (64 * 128)   /* Longitud del buffer de caracteres */
#define MSG_BUFFER_EXCEEDED "Buffer de video excedido, la pantalla ha sido limpiada\n"

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

typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} color_t;



uint64_t _X = 0, _Y = 0;                    // Coordenadas de escritura de caracteres
//Color _fontColor = DEFAULT_COLOR;         // Color de fuente
uint8_t _charWidth = DEFAULT_CHAR_WIDTH;    // Ancho en pixeles de un caracter
uint8_t _charHeight = DEFAULT_CHAR_HEIGHT;  // Altura en pixeles de un caracter
char _charBuffer[MAX_RESOLUTION];           // Buffer de caracteres
uint16_t _bufferIdx = 0;                    // Posicion de indice del buffer

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

void putPixel(color_t color, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;                 // Crea un puntero al framebuffer del struct 
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  color.blue;              // Escribe los colores en el framebuffer
    framebuffer[offset+1]   =  color.green; 
    framebuffer[offset+2]   =  color.red;
}


void drawChar(color_t color, char caracter){


    
}