#include <timeuser.h>
#include <lib.h>
#include <snake.h>

// Container defines
#define NAME "SNAKE"
#define S_CX0 100     //Constant X0
#define S_CY0 100     //Constant Y0
#define S_WIDTH (MATRIZ_WIDTH * BLOCK_SIZE + 2* OWN_BORDER)
#define S_HEIGHT (MATRIZ_WIDTH * BLOCK_SIZE +2 * OWN_BORDER)
static int container_id;

static char matriz[S_HEIGHT][S_WIDTH];

int prizex=-1;
int prizey=-1;

char cant_players;
snake_t player1;
snake_t player2;

//--------------------------------------------------------------------

void load_snake(){
    container_id = do_sys_new_container(NAME,S_CX0,S_CY0,S_WIDTH,S_HEIGHT); 
    set_container_id(container_id);
    char players=load_snake_menu();
    sleep(1000);
    setBackground(BLACK);
    drawBoard();
    start_snake(players);
    exitContainer(container_id);
}



int load_snake_menu(){
    setBackground(WHITE);
    setFontSize(3);
    int current_player= 1;
    char c= UP_1;
    

    while(c != '\n'){
        
        if(c==UP_1 || c== DOWN_1){
            clear_sb();
            clear();
            if(c== UP_1){
                current_player=1;
            }
            else{
                current_player=2;
            }
            puts("Jugadores:",BLACK);
            puts("1 Jugador",(current_player==1)?GREEN:BLACK);
            puts("2 jugadores",(current_player==2)?GREEN:BLACK);
        }
        c = getCharFromKernel();
    }
    clear();
    return current_player;
}

void drawBoard(){
    char start_flag= 0;
    char color_flag;
    color_t aux;
    for(int y= 0; y< MATRIZ_HEIGHT;y++){
        color_flag= start_flag;
        for(int x=0; x< MATRIZ_WIDTH; x++){
            aux= color_flag ? SNAKE_DARK_COLOR : SNAKE_LIGHT_COLOR;
            matriz[y][x]= color_flag;
            printInMatriz(x,y,aux);
            color_flag= !color_flag;
        }
        start_flag= ! start_flag;
    }
}

void printInMatriz(int x, int y, color_t color){
    printRectangle(S_CX0+(x * BLOCK_SIZE) + OWN_BORDER,S_CY0 + (y * BLOCK_SIZE) + OWN_BORDER,BLOCK_SIZE,BLOCK_SIZE, color);
}


void start_snake(char players){
    cant_players = players;
    player1= (snake_t) {1,NULL,0,0,SNAKE_COLOR_1};
    getBody(&player1,STARTX,STARTY);
    printInMatriz(STARTX,STARTY,SNAKE_COLOR_1);

    if(players==2){
        player2= (snake_t) {2,NULL,0,0,SNAKE_COLOR_2};
        getBody(&player2,STARTX2,STARTY2);
        printInMatriz(STARTX2,STARTY2,SNAKE_COLOR_2);
    }

    
    char lost_flag=1;
    char direc1[]= {0,0};
    char direc2[]= {0,0};

    putPrize();
    while(lost_flag){
        sleep(TICK);
        putDirections(direc1,direc2);
        lost_flag = move(&player1, direc1[0],direc1[1]);
        
        if(gotPrize(&player1)){
            player1.size+=1;
            putPrize();
        }

        if(lost_flag && cant_players==2){
            lost_flag = move(&player2, direc2[0],direc2[1]);
            
            if(gotPrize(&player2)){
                player2.size+=1;
                putPrize();
            }
        }
    }
}

void getBody(snake_t * player,int posx, int posy){
    body_t * aux= (body_t *) smalloc();
    aux->posx= posx;
    aux->posy= posy;
    aux->next= NULL;
    player->size++;

    if(player->size==1){
        player->head= aux;
        return;
    }
    aux->next= player->head-> next;
    player->head->next= aux;
}

void putDirections_aux(char * direc,char c,char up,char down,char left,char right){
    if(c== up){
        direc[0]= 0;
        direc[1]= -1;
    }
    else if(c==down){
        direc[0]= 0;
        direc[1]= 1;
    }
    else if(c== left){
        direc[0]= -1;
        direc[1]= 0;
    }
    else if(c== right){
        direc[0]= 1;
        direc[1]= 0;
    }
}
void putDirections(char * direc1,char * direc2){
    char c1, c2;
    getKeyMove(&c1,&c2);

    putDirections_aux(direc1,c1,UP_1,DOWN_1,LEFT_1,RIGHT_1);
    putDirections_aux(direc2,c2,UP_2,DOWN_2,LEFT_2,RIGHT_2);
}


char move(snake_t * player,int direcX,int direcY){
    body_t * aux= player->head;
    if(aux == NULL){
        return 0;
    }
    if(! in_board(aux->posx + direcX, aux->posy + direcY)){
        return 0;
    }

    if(player->prize_flag){
        getBody(player,aux->posx,aux->posy);

        aux->posx += direcX;
        aux->posy += direcY;
        printInMatriz(aux->posx,aux->posy,player->color);
        player->prize_flag=0;
        return 1;
    }
    while(aux != NULL){
        aux->posx += direcX;
        aux->posy += direcY;
        if(aux->next == NULL){
            printInMatriz(aux->posx- direcX,aux->posy -direcY,matriz[aux->posy - direcY][aux->posx - direcX] ? SNAKE_DARK_COLOR: SNAKE_LIGHT_COLOR);
        }
        else{
            direcX = aux->posx - aux->next->posx - direcX;
            direcY = aux->posy - aux->next->posy - direcY;
        }
        printInMatriz(aux->posx,aux->posy,player->color);
        aux= aux->next;
    }

    
    return getsHit(player);
}

char in_board(int posx,int posy){
    if(posx < 0 || posy < 0){
        return 0;
    }
    if(posx >= MATRIZ_WIDTH || posy >= MATRIZ_HEIGHT){
        return 0;
    }
    return 1;
}

char getsHit_aux(body_t * aux,int posx, int posy){
    while(aux != NULL){
        if(aux->posx == posx && aux->posy== posy){
            return 0;
        }
        aux= aux->next;
    }
    return 1;
}

char getsHit(snake_t * player){
    int posx= player->head->posx;
    int posy= player->head->posy;
    
    body_t * aux= player1.head;
    if(aux== NULL){
        return 1;
    }

    char ret = getsHit_aux(aux->next,posx,posy);
    if(! ret){
        return 0;
    }

    if(cant_players == 2 ){
        aux= player2.head;
        if(aux == NULL){
            return 1;
        }
        ret= getsHit_aux(aux->next,posx,posy);
    }
    return ret;
}

void getKeyMove(char * c1, char * c2){
    for(int i=0; i<TICK; i++){
        char c= getCharFromKernel();
        if(c == UP_1 || c== DOWN_1 || c== LEFT_1 || c==RIGHT_1){ 
            *c1=c;
        }
        if(c == UP_2 || c== DOWN_2 || c== LEFT_2 || c==RIGHT_2){
            *c2=c;
        }
    }
}

void putPrize(){
    prizex= rand() % MATRIZ_WIDTH;
    prizey= rand() % MATRIZ_HEIGHT;
    drawPrize();   
}

void drawPrize(){
    printInMatriz(prizex,prizey,SHELL_POSID);
}

char gotPrize(snake_t * player){
    if(player->head == NULL){
        return 0;
    }
    if(player->head->posx == prizex && player->head->posy == prizey){
        player->prize_flag=1;
        return 1;
    }
    return 0;
}

void exitSnake_aux(body_t * body){
    body_t * aux;
    while(body != NULL){
        aux= body;
        body= body->next;
        sfree(aux);
    }
}

void exitSnake(){
    exitSnake_aux(player1.head);
    if(cant_players == 2){
        exitSnake_aux(player2.head);
    }
}

