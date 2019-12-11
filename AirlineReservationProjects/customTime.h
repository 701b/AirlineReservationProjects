#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
시간을 나타내는 구조체이다.
목적에 맞게 월, 일, 시간, 분만 사용한다. */
typedef struct time
{
	int month;
	int day;
	int hour;
	int minute;
} TIME;

/*
TIME 구조체를 만들고 인자를 그대로 넣은 후 반환한다. */
TIME* generateTime(int month, int day, int hour, int minute);

/*
time을 복제하여 반환한다. */
TIME* generateCloneTime(TIME* time);

/*
time에 minute분 만큼 더한다. */
void addToTimeByMinute(TIME* time, int minute);

/*
두 TIME을 비교한다.
time1 = time2, 0
time1 > time2, 1
time1 < time2, -1*/
int compareTime(TIME* time1, TIME* time2);

/*
time을 문자열로 변환한다. 
M월 D일 hh:mm*/
char* timeToStr(TIME* time);

/*
time을 문자열로 반환한다. 시간과 분만 나타낸다. 
hh:mm*/
char* timeToShortStr(TIME* time);

/*
두 TIME의 차를 분단위로 반환한다. */
int calculateTimeDifference(TIME* time1, TIME* time2);

/*
날짜 형태로 된 문자열을 시간으로 바꾼다. 
yyyy. mm. dd*/
TIME* strToTime(char* str);