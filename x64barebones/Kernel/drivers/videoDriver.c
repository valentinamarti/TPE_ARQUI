#include <stdlib.h>	
#include <fonts.h>
#include <stdint.h>
#include <string.h>
#include <videoDriver.h>

#define SCREEN_W VBE_mode_info->width
#define SCREEN_H VBE_mode_info->height

uint64_t ACTUAL_X = 0, ACTUAL_Y = 0;                    // Coordenadas de escritura de caracteres
uint64_t SIZE = 2;

char_t screenbuffer[SCREENBUFER_SIZE];
uint16_t screenbuffer_idx=0;

struct container_list c_list;
char c_list_flag=0;

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


typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;



char inScreenX(uint16_t pixelPos){
    return pixelPos <= SCREEN_W;
}
char inScreenY(uint16_t pixelPos){
    return pixelPos <= SCREEN_H;
}

void emptyScreen(){
    for(int y=0; y<SCREEN_H; y++){
        for(int x=0; x<SCREEN_W; x++){
            putPixel(BLACK,x,y);
        }
    }
    ACTUAL_X=0;
    ACTUAL_Y=0;
    return;
}

void emptyBuffer(int container_id){
    container_t * c=getContainerByID(container_id);
    c->buffer_idx=0;
    c->ACTUAL_X= c->X0;
    c->ACTUAL_Y= c->Y0;
}

void putPixel(color_t color, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;                 // Crea un puntero al framebuffer del struct 
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  color.blue;              // Escribe los colores en el framebuffer
    framebuffer[offset+1]   =  color.green; 
    framebuffer[offset+2]   =  color.red;
}

void drawRectangle(color_t * color,int posx,int posy, int sizex, int sizey){
    for(int i=0;i<sizey;i++){
        for(int j=0;j<sizex;j++){
            putPixel(*color,posx+j,posy+i);
        }
    }
}

void drawHorizontalLine(color_t color, int posx,int posy,int width, int size){
    
    if(! inScreenX(posx) && !inScreenX(posx+width) && !inScreenY(posy)){
        return;
    }
    for(int x= posx; x + size <= posx + width;x+= size){
        drawRectangle(&color,x,posy,size,size);
    }
}

void drawVerticalLine(color_t color, int posx,int posy,int height, int size){

    if(! inScreenX(posx) && !inScreenY(posy+height) && !inScreenY(posy)){
        return;
    }
    for(int y= posy; y + size <= posy + height;y+= size){
        drawRectangle(&color,posx,y,size,size);
    }
}

void drawByte(color_t color,uint16_t SIZE,uint8_t hexa,uint64_t posx, uint64_t posy){
    for(int i=8; i>0;i--){ //El 8 es el tamaño del byte
        if(hexa & 1){
            drawRectangle(&color,posx + i * SIZE,posy,SIZE,SIZE);
        }
        hexa= hexa>>2;
    }
}

//---------------------CONTAINER FUNCTIONS----------------------------

uint16_t getContainer(uint8_t * name, uint16_t X0, uint16_t Y0,uint16_t width, uint16_t height){
    if(! c_list_flag){
        c_list= initialize_container_list();
        c_list_flag=1;
    }

    if(X0< 0 || Y0<0 || width<=0 || height<=0 ){
        return -1;
    }
    
    if((X0+width> SCREEN_W) || (Y0+height)> SCREEN_H){        
        return -1;
    }

    container_node_t * node= (container_node_t * ) malloc(sizeof(container_node_t));
    if((uint64_t)node == -1){
        drawChar(NULL, (char_t){'e',RED});
    }
    node->next=NULL;
    //Initialize node
    node->container.ID= c_list.last_index++;
    node->container.name= name;
    node->container.SIZE = DEFAULT_SIZE;
    node->container.redraw_flag=0;
    node->container.X0=X0+ BORDER_SIZE;
    node->container.ACTUAL_X= X0;
    node->container.Y0=Y0 + BORDER_SIZE;
    node->container.ACTUAL_Y=Y0 ;
    node->container.width= width - BORDER_SIZE;
    node->container.height= height - BORDER_SIZE;
    node->container.buffer_idx=0;
    node->container.background_color= SHELL_BACKGROUND;
    node->container.border_color= RED;         //Hacer funcion color random
    
    appendContainer(node);
    return node->container.ID;
}

void drawContainerBorder(container_t * c){
    int y = c->Y0;
    int x;
    
    if(y  <= c->Y0 + c->height){
        drawHorizontalLine(c->border_color,c->X0 - BORDER_SIZE,y - BORDER_SIZE,c->width + 2* BORDER_SIZE,BORDER_SIZE);
    }
    
    y=c->Y0 + c->height;

    if(y > c->Y0){
        drawHorizontalLine(c->border_color,c->X0 - BORDER_SIZE,y,c->width + 2 * BORDER_SIZE,BORDER_SIZE);
    }

    x= c->X0;

    if(x <= c->X0 + c->width){
        drawVerticalLine(c->border_color,x - BORDER_SIZE,c->Y0 - BORDER_SIZE,c->height + BORDER_SIZE,BORDER_SIZE);
    }
    x=c->X0 + c->width ;
    if(x> c->X0){
        drawVerticalLine(c->border_color,x,c->Y0 - BORDER_SIZE,c->height + BORDER_SIZE,BORDER_SIZE);
    }

}
void emptyContainerByID(int ID){
    emptyContainer(getContainerByID(ID));
}

void emptyContainer(container_t * c){
    drawRectangle(&(c->background_color),c->X0,c->Y0,c->width,c->height);
    c->ACTUAL_X=c->X0;
    c->ACTUAL_Y=c->Y0;
    return;
}

void appendContainer(container_node_t * node){
    drawContainerBorder(&(node->container));
    emptyContainer(&(node->container));
    if(c_list.first == NULL){
        c_list.first=node;
        c_list.last= node;
        return;
    }

    c_list.last->next= node;
    c_list.last= node;
}

void popContainer(container_t* c){

    if(c_list.first == NULL){
        return;
    }

    if(c_list.first->container.ID == c->ID){
        c_list.first= c_list.first->next;
        return;
    }

    container_node_t * node= c_list.first;
    while(node->next != NULL){
        if(node->next->container.ID == c->ID){
            node->next= node->next->next;
            c_list.last= node;
            return;
        }
        node= node->next;
    }
    return;
    
}

struct container_list initialize_container_list(){
    return (struct container_list) {1,NULL,NULL};
}

container_t* getContainerByID(int ID){
    container_node_t* node = c_list.first;

    while(node != NULL){
        if(node->container.ID == ID){
            return &(node->container);
        }
        node= node->next;
    }
    return NULL;
}


void drawCharInContainer(int ID,char_t character){
    container_t * c= getContainerByID(ID);
    
    drawChar(c,character);

}


char inContainerX(container_t * c,uint16_t pixelPos){
    return pixelPos <= (c->X0+c->width);
}
char inContainerY(container_t * c,uint16_t pixelPos){
    return pixelPos <= (c->Y0+c->height);
}

void addContainerBuffer(container_t * c, char_t character){
    if(SCREENBUFER_SIZE== c->buffer_idx){
        return;
    }
    c->buffer[c->buffer_idx++]= character;
}


void redrawContainerBuffer(container_t * c, uint16_t offset){
    emptyContainer(c);
    int aux=c->buffer_idx;
    c->buffer_idx=0;
    for(int i=offset; i< aux;i++){
        drawChar(c,c->buffer[i]);
    }
}


void exitContainer(int ID){
    container_t * c=getContainerByID(ID);
    // arreglar pop container
    popContainer(c);

    drawRectangle(&BLACK,c->X0 - BORDER_SIZE,c->Y0 - BORDER_SIZE, c->width + 2 * BORDER_SIZE,c->height + 2 * BORDER_SIZE);

    free(c);
    redrawCList();
}


void redrawCList(){
    container_node_t * node= c_list.first;

    while(node != NULL){
        drawContainerBorder(&(node->container));
        redrawContainerBuffer(&(node->container),0);
        node->container.redraw_flag=1;
        node= node->next;
    }
    return;
}

void changeBackgroundColor(int ID, color_t* color){
    container_t * c= getContainerByID(ID);
    c->background_color= *color;
    redrawContainerBuffer(c,0);
}

void changeBorderColor(int ID, color_t* color){
    container_t * c= getContainerByID(ID);
    c->border_color= *color;
    drawContainerBorder(c);
}

char wasRedraw(int ID){
    container_t * c= getContainerByID(ID);
    char ret= c->redraw_flag;
    c->redraw_flag=0;
    return ret;
}

int getCurrentID(){
    return c_list.last->container.ID;
}

//---------------------CHARACTER FUNCTIONS----------------------------

void drawChar(container_t * c, char_t character){
    
    if(character.c == '\b'){
        backspace(c);
        return;
    }
    addContainerBuffer(c,character);
    char* vector= font[character.c];
    
    if((! inContainerX(c,c->ACTUAL_X + DEFAULT_CHAR_WIDTH * c->SIZE)) || character.c=='\n'){
        newLine(c);
    }
    if(character.c != '\n'){
        for(int y=0;y<DEFAULT_CHAR_HEIGHT;y++){
            drawByte(character.color,c->SIZE,vector[y],c->ACTUAL_X,c->ACTUAL_Y+y *c->SIZE);
        }
        c->ACTUAL_X+= DEFAULT_CHAR_WIDTH * c->SIZE;
    }
}

void backspace(container_t * c){
    if(c->buffer_idx>0){
        c->buffer_idx-=1;
    }
    if(c->ACTUAL_X == c->X0){
        c->ACTUAL_Y-= DEFAULT_CHAR_HEIGHT * c->SIZE;
        int aux= (c->width) / (DEFAULT_CHAR_WIDTH * c->SIZE);  // Aca lo que hago es restar la diferencia
        c->ACTUAL_X= c->X0 + c->width  -((c->width ) - aux * DEFAULT_CHAR_WIDTH * c->SIZE);            // Por si justo no llega a completar el char
    }
    c->ACTUAL_X-= DEFAULT_CHAR_WIDTH * c->SIZE;
    drawRectangle(&(c->background_color),c->ACTUAL_X,c->ACTUAL_Y,DEFAULT_CHAR_WIDTH * c->SIZE,DEFAULT_CHAR_HEIGHT * c->SIZE);
    return;
}

void newLine(container_t * c){
    
    if(inContainerY(c,c->ACTUAL_Y + 2 * DEFAULT_CHAR_HEIGHT * c->SIZE)){
        c->ACTUAL_Y+= DEFAULT_CHAR_HEIGHT* c->SIZE;
    }
    else{
        int i;
        for(i=0;i< (c->width /(DEFAULT_CHAR_WIDTH * c->SIZE ));i++){
            if(c->buffer[i].c == '\n'){
                redrawContainerBuffer(c,++i);
                return;
            }
        }
        redrawContainerBuffer(c,i);
    }
    
    c->ACTUAL_X=c->X0;
}

void changeSize(int ID,uint8_t num){
    container_t * c= getContainerByID(ID);
    c->SIZE= num;
    redrawContainerBuffer(c,0);
}

void drawString(int ID, uint8_t * string, uint16_t len, color_t * color){
    container_t * c = getContainerByID(ID);
    for(int i=0; i< len; i++){
        drawChar(c,(char_t){string[i],*color});
    }

}

void drawStringNull(int ID, uint8_t * string, color_t * color){
    container_t * c = getContainerByID(ID);
    for(int i=0; string[i] != 0; i++){
        drawChar(c,(char_t){string[i],*color});
    }
}

//me la hago aux
void drawCharNC(char_t character){
    addBuffer(character);
    char* vector= font[character.c];
    if(character.c != '\n'){
        for(int y=0;y<DEFAULT_CHAR_HEIGHT;y++){
            drawByte(character.color,SIZE,vector[y],ACTUAL_X,ACTUAL_Y+y *SIZE);
        }
        ACTUAL_X+= DEFAULT_CHAR_WIDTH * SIZE;
    }
}


void addBuffer(char_t character){
    if(SCREENBUFER_SIZE== screenbuffer_idx){
        return;
    }
    screenbuffer[screenbuffer_idx++]= character;
}
