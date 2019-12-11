#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
�ð��� ��Ÿ���� ����ü�̴�.
������ �°� ��, ��, �ð�, �и� ����Ѵ�. */
typedef struct time
{
	int month;
	int day;
	int hour;
	int minute;
} TIME;

/*
TIME ����ü�� ����� ���ڸ� �״�� ���� �� ��ȯ�Ѵ�. */
TIME* generateTime(int month, int day, int hour, int minute);

/*
time�� �����Ͽ� ��ȯ�Ѵ�. */
TIME* generateCloneTime(TIME* time);

/*
time�� minute�� ��ŭ ���Ѵ�. */
void addToTimeByMinute(TIME* time, int minute);

/*
�� TIME�� ���Ѵ�.
time1 = time2, 0
time1 > time2, 1
time1 < time2, -1*/
int compareTime(TIME* time1, TIME* time2);

/*
time�� ���ڿ��� ��ȯ�Ѵ�. 
M�� D�� hh:mm*/
char* timeToStr(TIME* time);

/*
time�� ���ڿ��� ��ȯ�Ѵ�. �ð��� �и� ��Ÿ����. 
hh:mm*/
char* timeToShortStr(TIME* time);

/*
�� TIME�� ���� �д����� ��ȯ�Ѵ�. */
int calculateTimeDifference(TIME* time1, TIME* time2);

/*
��¥ ���·� �� ���ڿ��� �ð����� �ٲ۴�. 
yyyy. mm. dd*/
TIME* strToTime(char* str);