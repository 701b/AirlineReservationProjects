#define _CRT_SECURE_NO_WARNINGS

#include "flight.h"

// 500 km/h
#define VELOCITY 500.0

#define MONTH_TO_DAY 31
#define DAY_TO_HOUR 24
#define HOUR_TO_MINUTE 60

#define MAX_SPACE_BETWEEN_TIME_AND_TIME 20

FLIGHT* generateFlight(CITY* source, CITY* destination, TIME* departureTime, AIRPLANE* airplane)
{
	FLIGHT* flight = malloc(sizeof(FLIGHT));
	// 단위 : 분
	int elapsedTime = (calculateDistanceBetween(source, destination) / VELOCITY) * HOUR_TO_MINUTE;
	TIME* arrivalTime = generateCloneTime(departureTime);

	addToTimeByMinute(arrivalTime, elapsedTime);

	flight->source = source;
	flight->destination = destination;
	flight->departureTime = departureTime;
	flight->arrivalTime = arrivalTime;
	flight->airplane = airplane;
	flight->seatColumnNumber = -1;
	flight->seatRowNumber = -1;

	return flight;
}

FLIGHT* generateCloneFlight(FLIGHT* flight)
{
	FLIGHT* cloneFlight = generateFlight(flight->source, flight->destination, generateCloneTime(flight->departureTime), flight->airplane);

	cloneFlight->seatClass = flight->seatClass;
	cloneFlight->seatRowNumber = flight->seatRowNumber;
	cloneFlight->seatColumnNumber = flight->seatColumnNumber;

	return cloneFlight;
}

void addToFlightList(LINKED_LIST* flightList, CITY* source, CITY* destination, TIME* departureTime, AIRPLANE* airplane)
{
	FLIGHT* flight = generateFlight(source, destination, departureTime, airplane);

	if (flightList == NULL)
	{
		flightList = generateLinkedList();
	}

	addToList(flightList, flight);
}

int findFromFlightList(LINKED_LIST* flightList, CITY* source, CITY* destination, TIME* departureTime)
{
	ITERATOR* iterator = generateIterator(flightList);
	
	for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(flightList))
	{
		if (flight->source == source
			&& flight->destination == destination
			&& compareTime(flight->departureTime, departureTime) == 0)
		{
			return 1;
		}
	}

	return 0;
}

void setSeat(FLIGHT* flight, int seatClass, int seatRowNumber, int seatColumnNumber, int seatStatus)
{
	flight->seatClass = seatClass;
	flight->seatRowNumber = seatRowNumber;
	flight->seatColumnNumber = seatColumnNumber;

	switch (seatClass)
	{
		case FIRST_CLASS:
			flight->airplane->firstClass[seatRowNumber][seatColumnNumber] = seatStatus;
			break;

		case BUSINESS_CLASS:
			flight->airplane->businessClass[seatRowNumber][seatColumnNumber] = seatStatus;
			break;

		case ECONOMY_CLASS:
			flight->airplane->economyClass[seatRowNumber][seatColumnNumber] = seatStatus;
			break;
	}
}

char* flightToStr(FLIGHT* flight, FLIGHT* previousFlight, int seatClass)
{
	char buffer[100] = "";
	char temp[100] = "";
	char tempTemp[100] = "";
	char* departureTime = timeToShortStr(flight->departureTime);
	char* arrivalTime = timeToShortStr(flight->arrivalTime);
	char sourceName = flight->source->name;
	char destinationName = flight->destination->name;
	TIME* elapsedTime = generateTime(0, 0, 0, 0);
	int lengthOfSpace;
	int seats = getNumberOfSeatsOfClass(flight->airplane, seatClass);
	char* result;

	addToTimeByMinute(elapsedTime, calculateTimeDifference(flight->departureTime, flight->arrivalTime));

	sprintf(buffer, "%c시 %s", sourceName, departureTime);

	if (previousFlight != NULL && flight->departureTime->day != previousFlight->arrivalTime->day)
	{
		strcat(buffer, "(+1) --");
	}
	else
	{
		strcat(buffer, "     --");
	}

	if (elapsedTime->hour != 0)
	{
		sprintf(temp, "%d시간 ", elapsedTime->hour);
	}

	if (elapsedTime->minute != 0)
	{
		sprintf(tempTemp, "%d분", elapsedTime->minute);
		strcat(temp, tempTemp);
	}

	lengthOfSpace = MAX_SPACE_BETWEEN_TIME_AND_TIME - strlen(temp);

	for (int j = 0; j < lengthOfSpace / 2; j++)
	{
		strcat(buffer, " ");
	}

	strcat(buffer, temp);

	for (int j = 0; j < lengthOfSpace - (lengthOfSpace / 2); j++)
	{
		strcat(buffer, " ");
	}

	sprintf(temp, "--> %c시 %s", destinationName, arrivalTime);
	strcat(buffer, temp);

	if (flight->departureTime->day != flight->arrivalTime->day)
	{
		strcat(buffer, "(+1)");
	}
	else
	{
		strcat(buffer, "    ");
	}

	if (seatClass != -1)
	{
		sprintf(temp, " 잔여 %d석", seats);
		strcat(buffer, temp);
	}
	else
	{
		sprintf(temp, " %s %d%c", getStrOfSeatClass(flight->seatClass), flight->seatColumnNumber + 1, 'A' + flight->seatRowNumber);
		strcat(buffer, temp);
	}

	result = calloc(sizeof(buffer) + 1, sizeof(char));
	strcpy(result, buffer);

	free(departureTime);
	free(arrivalTime);
	free(elapsedTime);
	
	return result;
}

void freeFlight(FLIGHT** flight)
{
	if (*flight != NULL)
	{
		free((*flight)->departureTime);
		free((*flight)->arrivalTime);
		free(*flight);
		*flight = NULL;
	}
}
