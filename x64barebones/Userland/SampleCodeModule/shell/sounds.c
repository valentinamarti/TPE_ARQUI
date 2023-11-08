#include <sounds.h>

extern void do_sys_play_beep(int frec,int millisec);

void playWinnerSound(){
    do_sys_play_beep(330,300); //mu
    do_sys_play_beep(330,800); //chaaaaaa
    do_sys_play_beep(294,300); //chos
    do_sys_play_beep(294,250); //ahora
    do_sys_play_beep(350,300); //nos
    do_sys_play_beep(330,300); //vimos
    do_sys_play_beep(261,200); //a
    do_sys_play_beep(330,300); //ilusio
    do_sys_play_beep(330,700); //naarrr
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
