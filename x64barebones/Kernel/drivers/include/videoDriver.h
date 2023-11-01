#define WHITE ((color_t){255, 255, 255})
#define BLACK ((color_t){0,0,0})

#define SCREENBUFER_SIZE 256
#define BORDER_SIZE 3


//void * malloc();
//void free(void * ptr);
typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} color_t;

void putPixel(color_t color, uint64_t x, uint64_t y);

void drawChar(container_t * c,char_t character);

void drawCharInContainer(int ID,char_t character);

void drawRectangle(color_t color,int posx,int posy, int sizex, int sizey);

char inScreenX(uint16_t pixelPos);

char inScreenY(uint16_t pixelPos);

void changeSize(int ID,uint8_t num);

void changeSize(int ID,uint8_t num);
#endif