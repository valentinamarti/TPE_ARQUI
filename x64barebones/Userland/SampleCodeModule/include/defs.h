#ifndef DEFS_H

#include <stdint.h>
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


typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} color_t;

#endif