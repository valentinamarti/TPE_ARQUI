#define WHITE ((color_t){255, 255, 255})
#define BLACK ((color_t){0,0,0})

typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} color_t;

// uint32_t colorToHexa(color_t color){
//     uint32_t ret= color.red;
//     ret= ret << 4;
//     ret+= color.green;
//     ret= ret<< 4;
//     ret+= color.blue;
//     return ret;
// }



void putPixel(color_t color, uint64_t x, uint64_t y);

void drawChar(color_t color, char character);

void drawRectangle(color_t color,int posx,int posy, int sizex, int sizey);

char inScreen(uint16_t pixelPos);

void changeSize(uint8_t num);
// A BORRAR
void printAsciiTable(int size);
// FIN BORRAR

#endif