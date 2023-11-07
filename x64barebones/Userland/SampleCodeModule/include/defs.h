#ifndef DEFS_H

#include <stdint.h>

#define NULL 0
#define WHITE ((color_t){255, 255, 255})
#define BLACK ((color_t){0,0,0})
#define RED ((color_t){255,0,0})
#define GREEN ((color_t){0,255,0})
#define SHELL_BACKGROUND ((color_t){69,69,69})
#define SHELL_LETTER ((color_t){222, 222, 222})
#define SHELL_POSID ((color_t){146, 111, 171})
#define HELP_HEADINGS ((color_t){147, 10, 245})
#define TIME_BACKGROUND ((color_t){25, 21, 28})
#define TIME_BORDER ((color_t){61, 35, 82})
#define SHELL_BACKGROUND ((color_t){69,69,69})
#define SHELL_BACKGROUND ((color_t){69,69,69})

#define SNAKE_LIGHT_COLOR ((color_t){101, 173, 88})
#define SNAKE_DARK_COLOR ((color_t){92, 143, 83})
#define SNAKE_COLOR_1 ((color_t){194, 85, 2})
#define SNAKE_COLOR_2 ((color_t){44, 2, 82})
#define SNAKE_PRICE ((color_t){252, 205, 35})  
#define SNAKE_MENU ((color_t){101, 163, 110}) 
#define SNAKE_MENU_LETTERS ((color_t){245, 245, 171})
#define SNAKE_MENU_SELEC ((color_t){168, 95, 245})

#define REGISTERS_DUMP_BACKGROUND ((color_t){33, 7, 54})
#define REGISTERS_DUMP_LETTER ((color_t){221, 204, 235})
#define REGISTERS_DUMP_REGS ((color_t){166, 62, 250})
#define REGISTERS_DUMP_BORDER ((color_t){43, 8, 71})
#define REGISTERS_DUMP_TITTLE ((color_t){107, 2, 191})
#define ERROR_REGISTERS_DUMP ((color_t){240, 79, 67})


typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} color_t;

#endif