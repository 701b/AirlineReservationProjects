#include <stdlib.h>

#define SEAT_AVAILABLE 0
#define NO_SEAT 1

#define BOEING_777 0
#define BOEING_737 1
#define BOEING_747 2
#define AIRBUS_330 3
#define AIRBUS_380 4
#define AIRBUS_220 5  

#define FIRST_CLASS 0
#define BUSINESS_CLASS 1
#define ECONOMY_CLASS 2


typedef struct airplane
{
	int kindsOfAirplane;
	int** firstClass;
	int** businessClass;
	int** economyClass;
} AIRPLANE;

AIRPLANE* generateAirplane(int kindsOfAirplane);

int getSeatsOfClass(AIRPLANE* airplane, int seatClass);

char* getStrOfAirplane(AIRPLANE* airplane);

int getRowOfAirplaneSeat(AIRPLANE* airplane, int seatClass);

int getColumnOfAirplaneSeat(AIRPLANE* airplane, int seatClass);