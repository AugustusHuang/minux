#ifndef _CLOCK_H_
#define _CLOCK_H_

typedef struct clock_time *clock_time;
struct clock_time {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int dayofweek;
	int nano;
};

#define CLOCK_MON 1
#define CLOCK_TUE 2
#define CLOCK_WEN 3
#define CLOCK_THU 4
#define CLOCK_FRI 5
#define CLOCK_SAT 6
#define CLOCK_SUN 7


#endif
