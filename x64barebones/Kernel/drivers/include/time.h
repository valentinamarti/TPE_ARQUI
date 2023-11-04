#ifndef _TIME_DRIVER_H_
#define _TIME_DRIVER_H_

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void sleep(int xmillis);
int seconds();
int minutes();
int hours();
void getCurrentCpuTime();
int changeFormat(int num);

#endif
