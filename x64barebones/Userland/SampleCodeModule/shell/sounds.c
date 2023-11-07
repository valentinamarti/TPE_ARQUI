#include <sounds.h>

extern void do_sys_play_beep(int frec,int millisec);

void playWinnerSound(){
    do_sys_play_beep(330,1000);
    do_sys_play_beep(330,2000);
    do_sys_play_beep(294,500);
    do_sys_play_beep(294,1000);
    do_sys_play_beep(660,3);
    do_sys_play_beep(780,6);
}

void playLoserSound(){
    do_sys_play_beep(880,3);
    do_sys_play_beep(780,3);
    do_sys_play_beep(660,3);
    do_sys_play_beep(585,6);
    do_sys_play_beep(780,3);
    do_sys_play_beep(520,6);
}
