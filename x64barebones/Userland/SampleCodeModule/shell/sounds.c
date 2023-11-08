#include <sounds.h>

extern void do_sys_play_beep(int frec,int millisec);

void playWinnerSound(){
    do_sys_play_beep(330,300);
    do_sys_play_beep(330,800);
    do_sys_play_beep(294,300);
    do_sys_play_beep(294,500);
    do_sys_play_beep(350,300);
    do_sys_play_beep(330,300);
    do_sys_play_beep(330,100);
    do_sys_play_beep(330,100);
    do_sys_play_beep(261,100);
    do_sys_play_beep(330,300);
    do_sys_play_beep(330,500);
}

void playLoserSound(){
    do_sys_play_beep(880,3);
    do_sys_play_beep(780,3);
    do_sys_play_beep(660,3);
    do_sys_play_beep(585,6);
    do_sys_play_beep(780,3);
    do_sys_play_beep(520,6);
}
