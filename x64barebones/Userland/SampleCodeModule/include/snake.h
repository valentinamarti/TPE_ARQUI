
// control Constants

#define UP_ARROW 'u'
#define DOWN_ARROw 'd'

// Snake constants

#define BLOCK_SIZE 32       // In pixels
#define MATRIZ_HEIGHT 20    // BLOCKS
#define MATRIZ_WIDTH  20    // BLOCKS
#define OWN_BORDER 5
#define STARTX 5
#define STARTY 5


#define TICK 1000           // Time of each frame move

#define UP_1 'w'
#define DOWN_1 's'
#define LEFT_1 'a'
#define RIGHT_1 'd'

typedef struct body_struct{     //One body by block
    uint16_t posx;
    uint16_t posy;
    struct body_struct * next;
}body_t;


typedef struct snake_struct{
    uint8_t player;
    body_t * head;
    uint16_t size;
    uint8_t prize_flag;
}snake_t;

extern void * smalloc();
extern void  sfree(void * ptr);

void load_snake();

int load_snake_menu();

char in_board(int posx,int posy);

char move(snake_t * player,int direcX,int direcY);

void getBody(snake_t * player,int posx, int posy);

void printInMatriz(int x, int y, color_t color);

void start_snake(char players);

char getKeyMove();

char gotPrize(snake_t * player);

void drawPrize();

void putPrize();

char getsHit();