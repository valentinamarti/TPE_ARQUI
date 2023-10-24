#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H 

typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} color_t;

void putPixel(color_t color, uint64_t x, uint64_t y);

void drawChar(color_t color, char character);

void drawRectangle(color_t color,int posx,int posy, int sizex, int sizey);

char inScreen(uint16_t pixelPos);

void changeSize(uint8_t num);
// A BORRAR
void printAsciiTable(int size);
// FIN BORRAR
#define RED ((color_t){255, 0, 0})
#define WHITE ((color_t){255, 255, 255})

#endif