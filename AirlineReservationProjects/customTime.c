#define _CRT_SECURE_NO_WARNINGS

#include "customTime.h"

#define MONTH_TO_DAY 31
#define DAY_TO_HOUR 24
#define HOUR_TO_MINUTE 60

TIME* generateTime(int month, int day, int hour, int minute)
{
	TIME* time = malloc(sizeof(TIME));

	time->month = month;
	time->day = day;
	time->hour = hour;
	time->minute = minute;

	return time;
}

TIME* generateCloneTime(TIME* time)
{
	TIME* cloneTime = malloc(sizeof(TIME));

	cloneTime->month = time->month;
	cloneTime->day = time->day;
	cloneTime->hour = time->hour;
	cloneTime->minute = time->minute;

	return cloneTime;
}

void addToTimeByMinute(TIME* time, int minute)
{
	time->minute += minute;
	time->hour += time->minute / HOUR_TO_MINUTE;
	time->minute %= HOUR_TO_MINUTE;
	time->day += time->hour / DAY_TO_HOUR;
	time->hour %= DAY_TO_HOUR;
	time->month += (time->day - 1) / MONTH_TO_DAY;
	time->day = (time->day - 1) % MONTH_TO_DAY + 1;
}

int compareTime(TIME* time1, TIME* time2)
{
	if (time1->month > time2->month)
	{
		return 1;
	}
	else if (time1->month < time2->month)
	{
		return -1;
	}
	else
	{
		if (time1->day > time2->day)
		{
			return 1;
		}
		else if (time1->day < time2->day)
		{
			return -1;
		}
		else
		{
			if (time1->hour > time2->hour)
			{
				return 1;
			}
			else if (time1->hour < time2->hour)
			{
				return -1;
			}
			else
			{
				if (time1->minute > time2->minute)
				{
					return 1;
				}
				else if (time1->minute < time2->minute)
				{
					return -1;
				}
				else
				{
					return 0;
				}
			}
		}

	}
}

char* timeToStr(TIME* time)
{
	char* result = calloc(16, sizeof(char));
	char hour[3] = "";
	char minute[3] = "";

	sprintf(hour, "%d", time->hour);
	sprintf(minute, "%d", time->minute);

	if (strlen(hour) == 1)
	{
		hour[1] = hour[0];
		hour[0] = '0';
	}

	if (strlen(minute) == 1)
	{
		minute[1] = minute[0];
		minute[0] = '0';
	}

	sprintf(result, "%d¿ù %dÀÏ %s:%s", time->month, time->day, hour, minute);

	return result;
}

int calculateTimeDifference(TIME* time1, TIME* time2)
{
	int minute1 = 0;
	int minute2 = 0;

	minute1 += time1->minute;
	minute1 += time1->hour * HOUR_TO_MINUTE;
	minute1 += time1->day * DAY_TO_HOUR * HOUR_TO_MINUTE;
	minute1 += time1->month * MONTH_TO_DAY * DAY_TO_HOUR * HOUR_TO_MINUTE;

	minute2 += time2->minute;
	minute2 += time2->hour * HOUR_TO_MINUTE;
	minute2 += time2->day * DAY_TO_HOUR * HOUR_TO_MINUTE;
	minute2 += time2->month * MONTH_TO_DAY * DAY_TO_HOUR * HOUR_TO_MINUTE;

	return abs(minute1 - minute2);
}
}
