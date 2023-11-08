#include <sounds.h>

extern void do_sys_play_beep(int frec,int millisec);

void playWinnerSound(){
    do_sys_play_beep(330,300); 
    do_sys_play_beep(330,800); 
    do_sys_play_beep(294,300); 
    do_sys_play_beep(294,250); 
    do_sys_play_beep(350,300); 
    do_sys_play_beep(330,300); 
    do_sys_play_beep(261,200); 
    do_sys_play_beep(330,300); 
    do_sys_play_beep(330,700); 
}

void playLoserSound(){
    do_sys_play_beep(100,500);
    do_sys_play_beep(70,600);
    do_sys_play_beep(40,1500);

}

void playEatsSound(){
    do_sys_play_beep(600,100);
    do_sys_play_beep(400,100);
}
