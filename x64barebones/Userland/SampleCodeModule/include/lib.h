#ifndef LIB_H
   
    int scanf(char* fmt, int color, ...);
    void printf(char* string, int color, ...);
    void printChar(char c, int color);
    char getChar(int fd);
    void puts(char* string, int color);
    void set_container_id();
    int abs(int value);
    void newLine();
    void print(char* buff, int color);
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


    int getID();
#endif