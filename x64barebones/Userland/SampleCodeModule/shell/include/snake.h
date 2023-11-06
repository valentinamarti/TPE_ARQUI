
// control Constants

#define UP_ARROW 'u'
#define DOWN_ARROw 'd'

// Snake constants

#define BLOCK_SIZE 16       // In pixels
#define MATRIZ_HEIGHT 20    // BLOCKS
#define MATRIZ_WIDTH  20    // BLOCKS




typedef struct body_struct{     //One body by block
    int posx;
    int posy;
    struct body_struct * next;
}body_t;


typedef struct snake_struct{
    char player;
    body_t * head;
    body_t * tail;
    int size;
}snake_t;

void load_snake();

int load_snake_menu();