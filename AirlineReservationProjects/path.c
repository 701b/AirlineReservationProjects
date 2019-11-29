#include "path.h"

PATH* generatePath()
{
	PATH* path = malloc(sizeof(PATH));

	path->airlineList = generateLinkedList();

	return path;
}

PATH* generateClonePath(PATH* path)
{
	PATH* clonePath = generatePath();

	ITERATOR* iterator = generateIterator(path->airlineList);

	for (AIRLINE* airline = getNextData(iterator); airline != NULL; airline = getNextData(iterator))
	{
		addToPath(clonePath, airline);
	}

	return clonePath;
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

TIME* getDepartureTime(PATH* path)
{
	AIRLINE* firstAirline = getFirstFromList(path->airlineList);

	return firstAirline->departureTime;
}

TIME* getArrivalTime(PATH* path)
{
	AIRLINE* lastAirline = getLastFromList(path->airlineList);

	return lastAirline->arrivalTime;
}

TIME* getElapsedTime(PATH* path)
{
	TIME* departureTime = getDepartureTime(path);
	TIME* arrivalTime = getArrivalTime(path);

	return calculateTimeDifference(departureTime, arrivalTime);
}

PATH* findPathForShortestFlightTime(LINKED_LIST* airlineList[], TIME* departureTime, CITY* source, CITY* destination)
{
	PATH* path = generatePath();


}

void freePath(PATH* path)
{

	free(path->airlineList);
	free(path);
}
