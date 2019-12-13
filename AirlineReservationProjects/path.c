#define _CRT_SECURE_NO_WARNINGS

#include "path.h"

#define MAX_WAITING_TIME_OF_TRANSIT 300

#define MAX_SPACE_BETWEEN_CITY_AND_TIME 16
#define MAX_SPACE_BETWEEN_TIME_AND_TIME 30

PATH* generatePath()
{
	PATH* path = malloc(sizeof(PATH));

	path->flightList = generateLinkedList();

	return path;
}

PATH* generateClonePath(PATH* path)
{
	PATH* clonePath = generatePath();

	ITERATOR* iterator = generateIterator(path->flightList);

	for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
	{
		addToPath(clonePath, flight);
	}

	return clonePath;
}

PATH* generateDeepClonePath(PATH* path)
{
	PATH* clonePath = generatePath();

	ITERATOR* iterator = generateIterator(path->flightList);

	for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
	{
		addToPath(clonePath, generateCloneFlight(flight));
	}

	return clonePath;
}

int addToPath(PATH* path, FLIGHT* flight)
{
	FLIGHT* lastFlight = getLastFromList(path->flightList);

	if (lastFlight == NULL)
	{
		addToList(path->flightList, flight);
	}
	else if (lastFlight->destination == flight->source)
	{
		if (compareTime(lastFlight->arrivalTime, flight->departureTime) < 0)
		{
			addToList(path->flightList, flight);
		}
	}
	else
	{
		return 0;
	}

	return 1;
}

FLIGHT* popPath(PATH* path)
{
	FLIGHT* flight = getLastFromList(path->flightList);

	removeFromList(path->flightList, flight);

	return flight;
}

CITY* getSource(PATH* path)
{
	FLIGHT* firstFlight = (FLIGHT*) getFirstFromList(path->flightList);
	
	return firstFlight->source;
}

CITY* getDestination(PATH* path)
{
	FLIGHT* lastFlight = (FLIGHT*) getLastFromList(path->flightList);

	return lastFlight->destination;
}

TIME* getDepartureTime(PATH* path)
{
	FLIGHT* firstFlight = getFirstFromList(path->flightList);

	return firstFlight->departureTime;
}

TIME* getArrivalTime(PATH* path)
{
	FLIGHT* lastFlight = getLastFromList(path->flightList);

	return lastFlight->arrivalTime;
}

TIME* getElapsedTime(PATH* path)
{
	TIME* departureTime = getDepartureTime(path);
	TIME* arrivalTime = getArrivalTime(path);

	return calculateTimeDifference(departureTime, arrivalTime);
}

int getNumberOfTransit(PATH* path)
{
	int number = path->flightList->size - 1;

	if (number <= 0)
	{
		return 0;
	}
	else
	{
		return number;
	}
}

void findPathRecursive(LINKED_LIST* flightList[], TIME* departureTime, LINKED_LIST* pathList, PATH* path, CITY* source, CITY* destination, int seatClass)
{
	LINKED_LIST* flightListFrom = generateLinkedList();
	ITERATOR* iterator;

	if (path->flightList->size != 0 && getArrivalTime(path)->month >= 2)
	{
		popPath(path);
		freeLinkedList(&flightListFrom);
		return;
	}

	if (path->flightList->size != 0 && getDestination(path) == destination)
	{
		addToList(pathList, generateClonePath(path));
		popPath(path);
		freeLinkedList(&flightListFrom);
		return;
	}

	if (path->flightList->size == 0)
	{
		iterator = generateIterator(flightList[departureTime->day - 1]);
	}
	else
	{
		iterator = generateIterator(flightList[getArrivalTime(path)->day - 1]);
	}

	// 갈 수 있는 모든 비행을 한 리스트에 담기
	{
		for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
		{
			if (path->flightList->size == 0)
			{
				if (flight->source == source)
				{
					if (getNumberOfSeatsOfClass(flight->airplane, seatClass) > 0)
					{
						addToList(flightListFrom, flight);
					}
				}
			}
			else
			{
				if (flight->source == getDestination(path) && compareTime(getArrivalTime(path), flight->departureTime) < 0)
				{
					if (getNumberOfSeatsOfClass(flight->airplane, seatClass) > 0)
					{
						addToList(flightListFrom, flight);
					}
				}
			}
		}

		freeIterator(&iterator);

		if (path->flightList->size != 0 && getArrivalTime(path)->hour >= 18 && getArrivalTime(path)->day < 31)
		{
			iterator = generateIterator(flightList[getArrivalTime(path)->day]);

			for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
			{
				if (flight->departureTime->hour <= 6)
				{
					if (path->flightList->size == 0)
					{
						if (flight->source == source)
						{
							if (getNumberOfSeatsOfClass(flight->airplane, seatClass) > 0)
							{
								addToList(flightListFrom, flight);
							}
						}
					}
					else
					{
						if (flight->source == getDestination(path) && compareTime(getArrivalTime(path), flight->departureTime) < 0)
						{
							if (getNumberOfSeatsOfClass(flight->airplane, seatClass) > 0)
							{
								addToList(flightListFrom, flight);
							}
						}
					}
				}
			}

			freeIterator(&iterator);
		}
	}

	iterator = generateIterator(flightListFrom);

	// 다음 도시로 이동
	for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
	{
		// 최대 경유 대기 시간보다 낮은지 검사
		if (path->flightList->size != 0 && calculateTimeDifference(flight->departureTime, getArrivalTime(path)) > MAX_WAITING_TIME_OF_TRANSIT)
		{
			continue;
		}

		// 지나왔던 도시로 가는 비행인지 검사
		{
			ITERATOR* passedPathIterator = generateIterator(path->flightList);
			int isPassedCity = 0;

			for (FLIGHT* passedFlight = getNextData(passedPathIterator); passedFlight != NULL; passedFlight = getNextData(passedPathIterator))
			{
				if (passedFlight->source == flight->destination && path)
				{
					isPassedCity = 1;
					break;
				}
			}

			freeIterator(&passedPathIterator);

			if (isPassedCity)
			{
				continue;
			}
		}

		addToPath(path, flight);
		findPathRecursive(flightList, departureTime, pathList, path, source, destination, seatClass);
	}

	freeLinkedList(&flightListFrom);
	freeIterator(&iterator);

	if (path->flightList->size != 0)
	{
		popPath(path);
	}
}

LINKED_LIST* findAllPath(LINKED_LIST* flightList[], TIME* departureTime, CITY* source, CITY* destination, int seatClass)
{
	LINKED_LIST* flightListAtDepartureDay = flightList[departureTime->day - 1];
	LINKED_LIST* pathList = generateLinkedList();
	PATH* path = generatePath();

	findPathRecursive(flightList, departureTime, pathList, path, source, destination, seatClass);

	freePath(&path);

	if (pathList->size == 0)
	{
		freeLinkedList(&pathList);
		return NULL;
	}

	return pathList;
}

PATH* findPathForShortestFlightTime(LINKED_LIST* flightList[], TIME* departureTime, CITY* source, CITY* destination, int seatClass)
{
	LINKED_LIST* pathList = findAllPath(flightList, departureTime, source, destination, seatClass);
	ITERATOR* iterator;
	PATH* pathForShortestFlightTime = NULL;
	int shortestFlightTime = 0;

	if (pathList == NULL)
	{
		return NULL;
	}

	iterator = generateIterator(pathList);

	for (PATH* path = getNextData(iterator); path != NULL; path = getNextData(iterator))
	{
		if (pathForShortestFlightTime == NULL)
		{
			pathForShortestFlightTime = path;
			shortestFlightTime = calculateTimeDifference(getDepartureTime(path), getArrivalTime(path));
		}
		else
		{
			int flightTime = calculateTimeDifference(getDepartureTime(path), getArrivalTime(path));

			if (flightTime < shortestFlightTime)
			{
				pathForShortestFlightTime = path;
				shortestFlightTime = flightTime;
			}
		}
	}

	removeFromList(pathList, pathForShortestFlightTime);
	freeIterator(&iterator);

	iterator = generateIterator(pathList);

	for (PATH* path = getNextData(iterator); path != NULL; path = getNextData(iterator))
	{
		freePath(&path);
	}

	freeIterator(&iterator);
	freeLinkedList(&pathList);

	return pathForShortestFlightTime;
}

void freePath(PATH** path)
{
	if (*path != NULL)
	{
		freeLinkedList(&((*path)->flightList));
		free(*path);
		*path = NULL;
	}
}

char* pathToStr(PATH* path, char* seatClassStr)
{
	char buffer[200] = "";
	char temp[200] = "";
	int elapsedTime = calculateTimeDifference(getDepartureTime(path), getArrivalTime(path));
	TIME* time = generateTime(1, 0, 0, 0);
	int numberOfTrasit = getNumberOfTransit(path);
	char* departureTime = timeToStr(getDepartureTime(path));
	char* arrivalTime = timeToStr(getArrivalTime(path));
	char* result;

	addToTimeByMinute(time, elapsedTime);

	sprintf(temp, "%c시", getSource(path)->name);
	strcat(buffer, temp);

	for (int j = 0; j < MAX_SPACE_BETWEEN_CITY_AND_TIME - strlen(departureTime); j++)
	{
		strcat(buffer, " ");
	}

	strcat(buffer, departureTime);
	strcat(buffer, " --");

	sprintf(temp, "");

	if (time->day != 0)
	{
		char tempTemp[20] = "";

		sprintf(tempTemp, "%d일 ", time->day);
		strcat(temp, tempTemp);
	}

	if (time->month != 0)
	{
		char tempTemp[20] = "";

		sprintf(tempTemp, "%d시간 ", time->hour);
		strcat(temp, tempTemp);
	}

	if (time->minute != 0)
	{
		char tempTemp[20] = "";

		sprintf(tempTemp, "%d분", time->minute);
		strcat(temp, tempTemp);
	}

	if (numberOfTrasit != 0)
	{
		char tempTemp[20] = "";

		sprintf(tempTemp, " (%d 경유)", numberOfTrasit);
		strcat(temp, tempTemp);
	}

	int lengthOfSpace = MAX_SPACE_BETWEEN_TIME_AND_TIME - strlen(temp);

	for (int j = 0; j < lengthOfSpace / 2; j++)
	{
		strcat(buffer, " ");
	}

	strcat(buffer, temp);

	for (int j = 0; j < lengthOfSpace - (lengthOfSpace / 2); j++)
	{
		strcat(buffer, " ");
	}

	strcat(buffer, "--> ");
	strcat(buffer, arrivalTime);

	for (int j = 0; j < MAX_SPACE_BETWEEN_CITY_AND_TIME - strlen(arrivalTime); j++)
	{
		strcat(buffer, " ");
	}

	sprintf(temp, "%c시", getDestination(path)->name);
	strcat(buffer, temp);
	
	if (seatClassStr != NULL)
	{
		strcat(buffer, "  ");
		strcat(buffer, seatClassStr);
	}

	result = calloc(strlen(buffer) + 1, sizeof(char));
	strcpy(result, buffer);

	free(time);
	free(departureTime);
	free(arrivalTime);

	return result;
}
