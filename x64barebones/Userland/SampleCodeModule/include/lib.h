#ifndef LIB_H
   
    #include <defs.h>

    int scanf(char* fmt, color_t color, ...);
    void printf(char* string, color_t color, ...);
    void printChar(char c, color_t color);
    char getChar(int fd);
    void puts(char* string, color_t color);
    void set_container_id();
    int abs(int value);
    void newLine();
    void print(char* buff, color_t color);
    void strcopy(char* destination, char* string);
    void itoa(int value, char* buff, int base);
    int strlen(char* string);
    char getCharFromUserspace();
    char getCharFromKernel();
    int atoi(char* value);
    void getTime(int* hrs, int* min, int* sec);
    void toMay(char *str);
    void toMin(char *str);
    int strcmp(char* s1, char* s2);
    int strcmpMinMay(char* s1, char* s2);
    void changeLettersize(int size);
    void sleep(int seconds);
    void clear();
    void setBackground(color_t color);
    void setBorder(color_t color);
    void exitContainer(int container_id);
    int getID();
    void printRectangle(int posx, int posy, int sizex, int sizey, color_t color);
    unsigned int rand();
#endif