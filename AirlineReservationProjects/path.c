#include "path.h"

PATH* generatePath()
{
	PATH* path = malloc(sizeof(PATH));

	path->airlineList = generateLinkedList();

	return path;
}

int addToPath(PATH* path, AIRLINE* airline)
{
	AIRLINE* lastAirline = getLastFromList(path->airlineList);

	if (lastAirline == NULL)
	{
		addToList(path->airlineList, airline);
	}
	else if (lastAirline->destination == airline->source)
	{
		if (lastAirline->arrivalTime <= airline->departureTime)
		{
			addToList(path->airlineList, airline);
		}
	}
	else
	{
		return 0;
	}

	return 1;
}

CITY* getSource(PATH* path)
{
	AIRLINE* firstAirline = (AIRLINE*) getFirstFromList(path->airlineList);
	
	return firstAirline->source;
}

CITY* getDestination(PATH* path)
{
	AIRLINE* lastAirline = (AIRLINE*) getLastFromList(path->airlineList);

	return lastAirline->destination;
}

time_t getDepartureTime(PATH* path)
{
	AIRLINE* firstAirline = getFirstFromList(path->airlineList);

	return firstAirline->departureTime;
}

time_t getArrivalTime(PATH* path)
{
	AIRLINE* lastAirline = getLastFromList(path->airlineList);

	return lastAirline->arrivalTime;
}

time_t getElapsedTime(PATH* path)
{
	time_t departureTime = getDepartureTime(path);
	time_t arrivalTime = getArrivalTime(path);

	return arrivalTime - departureTime;
}

PATH* findPathForShortestFlightTime(time_t departureTime, CITY* source, CITY* destination)
{

}
