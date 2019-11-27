#include "init.h"

#define INITIAL_NUMBER_OF_RESERVATION 500
#define INITIAL_NUMBER_OF_CITY 24
#define INITIAL_NUMBER_OF_DIRECT_PATH 300

#define RANDOM_LENGTH_OF_STR rand() % 15 + 4
#define RANDOM_CHARACTER (rand() % ('z' - 'a')) + 'a'

#define MAX_VALUE_OF_POSITION 3000


char* generateRandomStr(int length)
{
	char* str = calloc(length + 1, sizeof(char));
	char* str_temp = str;

	for (int i = 0; i < length; i++)
	{
		*str_temp++ = RANDOM_CHARACTER;
	}

	return str;
}

RESERVATION_RECORD* initReservationRecord()
{
	RESERVATION_RECORD* record = generateReservationRecord();

	srand(time(NULL));

	for (int i = 0; i < INITIAL_NUMBER_OF_RESERVATION; i++)
	{
		RESERVATION* reservation = generateReservation(generateRandomStr(RANDOM_LENGTH_OF_STR));
	}


}

CITY_GRAPH* initCityGraph()
{
	CITY_GRAPH* cityGraph = generateCityGraph();
	char* name;
	int x, y;

	srand(time(NULL));

	// 정해진 개수의 CITY 생성
	for (int i = 0; i < INITIAL_NUMBER_OF_CITY; i++)
	{
		ITERATOR* iterator = generateIterator(cityGraph->cityList);

		name = generateRandomStr(RANDOM_LENGTH_OF_STR);
		x = rand() % MAX_VALUE_OF_POSITION;
		y = rand() % MAX_VALUE_OF_POSITION;

		for (CITY* city = getNextData(iterator); city != NULL; city = getNextData(iterator))
		{
			// 이름이 같은 것이 있는 경우 다시 생성
			if (!strcmp(city->name, name))
			{
				i--;
				continue;
			}

			// 위치가 같은 것이 있는 경우 다시 생성
			if (city->x == x && city->y == y)
			{
				i--;
				continue;
			}
		}

		addToCityGraph(cityGraph, name, x, y);
	}

	for (int i = 0; i < INITIAL_NUMBER_OF_DIRECT_PATH)
}

void initAirlineList()
{

}

