
// control Constants


#define UP_1 1
#define DOWN_1 4
#define LEFT_1 2
#define RIGHT_1 3

#define UP_2 'w'
#define DOWN_2 's'
#define LEFT_2 'a'
#define RIGHT_2 'd'

// Snake constants

#define BLOCK_SIZE 32       // In pixels
#define MATRIZ_HEIGHT 20    // BLOCKS
#define MATRIZ_WIDTH  20    // BLOCKS
#define OWN_BORDER 5
#define STARTX 5
#define STARTY 5

#define STARTX2 10
#define STARTY2 10

#define NORMAL_SIZE 3
#define GAME_OVER_SIZE 5
#define ERROR -2

#define TICK 250           // Time of each frame move


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
    color_t color;
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

void getKeyMove(char * c1, char * c2);

char gotPrize(snake_t * player);

void drawPrize();

void putPrize();

char getsHit(snake_t * player);

void putDirections(char * direc1,char * direc2);

void exitSnake();

void printPoints();

void gameOver();

void redrawSnake();

void drawBody(body_t * body,color_t color);

void drawBoard();