#include <sounds.h>

void playWinnerSound(){
    do_sys_play_beep(390,3);
    do_sys_play_beep(520,3);
    do_sys_play_beep(660,3);
    do_sys_play_beep(780,6);
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
