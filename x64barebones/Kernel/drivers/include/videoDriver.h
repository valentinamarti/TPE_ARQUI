#define WHITE ((color_t){255, 255, 255})
#define BLACK ((color_t){0,0,0})
#define RED ((color_t){255,0,0})
#define GREEN ((color_t){0,255,0})
#define SEX ((color_t){69,69,69})
#define SCREENBUFER_SIZE 256
#define BORDER_SIZE 2


//void * malloc();
//void free(void * ptr);
typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} color_t;

typedef struct character{
    uint8_t c;
    color_t color;

} char_t;

typedef struct container {

    uint16_t ID;
    uint8_t * name;

    uint16_t SIZE;

    uint16_t X0;
    uint16_t Y0;

    uint16_t width;
    uint16_t height;

    char_t buffer[SCREENBUFER_SIZE];
    uint16_t buffer_idx;

    uint16_t ACTUAL_X;
    uint16_t ACTUAL_Y;
    
    color_t background_color;
    color_t border_color;


}container_t;


typedef struct container_node{
    container_t container;
    struct container_node * next;
}container_node_t;

struct container_list{
    uint16_t last_index;
    container_node_t * first;
    container_node_t * last;

};

struct container_list initialize_container_list();

uint16_t getContainer(uint8_t * name, uint16_t X0, uint16_t Y0,uint16_t width, uint16_t height);

void putPixel(color_t color, uint64_t x, uint64_t y);

void drawChar(container_t * c,char_t character);

void drawCharInContainer(int ID,char_t character);

void drawString(int ID, uint8_t * string, uint16_t len, color_t * color);

container_t* getContainerByID(int ID);

void drawRectangle(color_t * color,int posx,int posy, int sizex, int sizey);

char inScreenX(uint16_t pixelPos);

char inScreenY(uint16_t pixelPos);

void changeSize(int ID,uint8_t num);

void changeSize(int ID,uint8_t num);

void emptyBuffer(int container_id);

void newLine(container_t * c);

void changeSize(int ID,uint8_t num);

void emptyScreen();
