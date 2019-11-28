#include "airline.h"

// 500 km/h
#define VELOCITY 500.0

#define MONTH_TO_DAY 31
#define DAY_TO_HOUR 24
#define HOUR_TO_MINUTE 60

AIRLINE* generateAirline(CITY* source, CITY* destination, struct tm* departureTime)
{
	AIRLINE* airline = malloc(sizeof(AIRLINE));
	// 단위 : 분
	int elapsedTime = (calculateDistanceBetween(source, destination) / VELOCITY) * HOUR_TO_MINUTE;
	struct tm* arrivalTime = calloc(1, sizeof(struct tm));

	arrivalTime->tm_sec = departureTime->tm_sec;
	arrivalTime->tm_min = departureTime->tm_min + elapsedTime;
	arrivalTime->tm_hour = departureTime->tm_hour;
	arrivalTime->tm_mday = departureTime->tm_mday;
	arrivalTime->tm_mon = departureTime->tm_mon;
	arrivalTime->tm_year = departureTime->tm_year;

	arrivalTime->tm_hour += arrivalTime->tm_min / HOUR_TO_MINUTE;
	arrivalTime->tm_min %= HOUR_TO_MINUTE;
	arrivalTime->tm_mday += arrivalTime->tm_hour / DAY_TO_HOUR;
	arrivalTime->tm_hour %= DAY_TO_HOUR;
	arrivalTime->tm_mon += arrivalTime->tm_mday / MONTH_TO_DAY;
	arrivalTime->tm_mday = (arrivalTime->tm_mday - 1) % MONTH_TO_DAY + 1;

	airline->source = source;
	airline->destination = destination;
	airline->departureTime = departureTime;
	airline->arrivalTime = arrivalTime;

	return airline;
}

void addToAirlineList(LINKED_LIST* airlineList, CITY* source, CITY* destination, struct tm* departureTime)
{
	AIRLINE* airline = generateAirline(source, destination, departureTime);

	if (airlineList == NULL)
	{
		airlineList = generateLinkedList();
	}

	addToList(airlineList, airline);
}

int findFromAirlineList(LINKED_LIST* airlineList, CITY* source, CITY* destination, struct tm* departureTime)
{
	ITERATOR* iterator = generateIterator(airlineList);
	
	for (AIRLINE* airline = getNextData(iterator); airline != NULL; airline = getNextData(airlineList))
	{
		//비교 부분 수정 필요
		if (airline->source == source
			&& airline->destination == destination
			&& airline->departureTime == departureTime)
		{
			return 1;
		}
	}

	return 0;
}
