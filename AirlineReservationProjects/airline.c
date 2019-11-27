#include "airline.h"

// 500 km/h
#define VELOCITY 500

#define HOUR_TO_MINUTE 60
#define MINUTE_TO_SECOND 60

static LINKED_LIST* airlineList;

AIRLINE* generateAirline(CITY* source, CITY* destination, time_t departureTime)
{
	AIRLINE* airline = malloc(sizeof(AIRLINE));
	// ´ÜÀ§ : ÃÊ
	int elapsedTime = calculateDistanceBetween(source, destination) / VELOCITY * HOUR_TO_MINUTE * MINUTE_TO_SECOND;

	airline->source = source;
	airline->destination = destination;
	airline->departureTime = departureTime;
	airline->arrivalTime = departureTime + elapsedTime;

	return airline;
}

void addToAirlineList(AIRLINE* airline)
{
	if (airlineList == NULL)
	{
		airlineList = generateLinkedList();
	}

	addToList(airlineList, airline);
}
