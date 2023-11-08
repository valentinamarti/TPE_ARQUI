#include <timeuser.h>
#include <lib.h>
#include <snake.h>
#include <sounds.h>

// Container defines
#define S_NAME "SNAKE"
#define S_CX0 100     //Constant X0
#define S_CY0 100     //Constant Y0
#define S_WIDTH (MATRIZ_WIDTH * BLOCK_SIZE + 2* OWN_BORDER)
#define S_HEIGHT (MATRIZ_WIDTH * BLOCK_SIZE +2 * OWN_BORDER)

// Container Points Board defines

#define P_NAME "POINTS BOARD"
#define P_CX0 S_CX0 + S_WIDTH       //Constant X0
#define P_CY0 S_CY0                 //Constant Y0
#define P_WIDTH 250
#define P_HEIGHT 300


static int container_id;
static int container_id_points;

static char matriz[S_HEIGHT][S_WIDTH];

int prizex=-1;
int prizey=-1;

char cant_players;
snake_t player1;
snake_t player2;

//--------------------------------------------------------------------

void load_snake(){
    container_id = do_sys_new_container(S_NAME,S_CX0,S_CY0,S_WIDTH,S_HEIGHT); 
    container_id_points = do_sys_new_container(P_NAME,P_CX0,P_CY0,P_WIDTH,P_HEIGHT);
    set_container_id(container_id);
    setBorder(BLACK);
    char players=load_snake_menu();
    sleep(1000);
    setBackground(SNAKE_MENU);
    drawBoard();
    start_snake(players);
    gameOver();
    exitSnake();
}



int load_snake_menu(){
    setBackground(SNAKE_MENU);
    setFontSize(NORMAL_SIZE);
    int current_player= 1;
    char c= UP_1;
    

    while(c != '\n'){
        if(c==UP_1 || c== DOWN_1){
            clear_sb();
            if(c== UP_1){
                current_player=1;
            }
            else{
                current_player=2;
            }
            puts("Jugadores:\n",SNAKE_MENU_LETTERS);
            puts("1 Jugador",(current_player==1)?SNAKE_MENU_SELEC:SNAKE_MENU_LETTERS);
            puts("2 jugadores",(current_player==2)?SNAKE_MENU_SELEC:SNAKE_MENU_LETTERS);
        }
        c = getCharFromKernel();
    }
    clear_sb();
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
        if(do_sys_was_redraw(container_id)){
            redrawSnake();
        }
        sleep(TICK);
        putDirections(direc1,direc2);
        
        if(direc1[0]== ERROR || direc2[0]== ERROR){
            lost_flag=0;
        }
        else{
            lost_flag = move(&player1, direc1[0],direc1[1]);
        }

        if(gotPrize(&player1)){
            player1.size++;
            putPrize();
            printPoints();
        }

        if(lost_flag && cant_players==2){
            lost_flag = move(&player2, direc2[0],direc2[1]);
            
            if(gotPrize(&player2)){
                player2.size++;
                putPrize();
                printPoints();
            }
        }
    }
}

void getBody(snake_t * player,int posx, int posy){
    body_t * aux= (body_t *) smalloc();
    aux->posx= posx;
    aux->posy= posy;
    aux->next= NULL;

    if(player->size==0){
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
    if(c1 == ERROR || c2 == ERROR ){
        direc1[0]= ERROR;
        direc2[0]= ERROR;
        return;
    }
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
        drawBody(aux,player->color);
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

        if(c== ESCAPE){
            *c1= ERROR;
            *c2= ERROR;
        }
        if(c == UP_1 || c== DOWN_1 || c== LEFT_1 || c==RIGHT_1){ 
            *c1=c;
        }
        if(c == UP_2 || c== DOWN_2 || c== LEFT_2 || c==RIGHT_2){
            *c2=c;
        }
    }
}

void putPrize(){
    char flag=1;

    while(flag){
        prizex= rand() % MATRIZ_WIDTH;
        prizey= rand() % MATRIZ_HEIGHT;
        
        if(getsHit_aux(player1.head,prizex,prizey)){
            flag=0;
        }

        if(cant_players==2 && getsHit_aux(player2.head,prizex,prizey)){
            flag=0;
        }

    }
    drawPrize();   
}

void drawPrize(){
    printInMatriz(prizex,prizey,SHELL_POSID);
}

void drawBody(body_t * body,color_t color){
    printInMatriz(body->posx,body->posy,color);
}

void drawSnake(snake_t * snake){
    if(snake== NULL){
        return;
    }
    
    body_t * body= snake->head;

    while(body != NULL){
        drawBody(body,snake->color);
        body= body->next;
    }
}
char gotPrize(snake_t * player){
    if(player->head == NULL){
        return 0;
    }
    if(player->head->posx == prizex && player->head->posy == prizey){
        player->prize_flag=1;
        playEatsSound();
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
    exitContainer(container_id_points);
    exitContainer(container_id);
}

void redrawSnake(){
    drawBoard();
    drawPrize();
    drawSnake(&player1);
    drawSnake(&player2);
}

void printPoints(){
    set_container_id(container_id_points);
    setBackground(SNAKE_MENU);
    setBorder(BLACK);
    clear_sb();

    puts("Puntajes:",SNAKE_MENU_LETTERS);
    printf("P1: %d\n",SNAKE_GO_POINTS,(int) player1.size);

    if(cant_players==2){
        printf("P2: %d\n",SNAKE_GO_POINTS,(int) player2.size);
    }
    set_container_id(container_id);
}

void gameOver(){
    clear_sb();
    setBackground(SNAKE_GO_BACK);
    setFontSize(GAME_OVER_SIZE);
    puts("GAME OVER", SNAKE_GO_TITLE);
    puts("Puntajes:",SHELL_LETTER);
    printf("P1: %d\n",SNAKE_GO_POINTS,(int) player1.size);
    printf("P2: %d\n",SNAKE_GO_POINTS,(int) player2.size);
    playLoserSound();
    print("\nApreta ESC para salir del juego",SNAKE_GO_ESC);
    char c;
    while(c = getCharFromKernel()!= ESCAPE){}   
}