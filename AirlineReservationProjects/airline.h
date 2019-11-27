#pragma once

#include <time.h>

#include "linkedList.h"
#include "city.h"

typedef struct airline
{
	CITY* source;
	CITY* destination;
	time_t departureTime;
	time_t arrivalTime;
} AIRLINE;

AIRLINE* generateAirline(CITY* source, CITY* destination, time_t departureTime);

void addToAirlineList(AIRLINE* airline);