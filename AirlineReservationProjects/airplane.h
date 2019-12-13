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

/*
AIRPLANE 구조체를 만들어 초기화하고 반환한다.*/
AIRPLANE* generateAirplane(int kindsOfAirplane);

/*
airplane의 기종을 문자열로 반환한다. */
char* getStrOfAirplane(AIRPLANE* airplane);

/*
좌석 등급을 문자열로 반환한다. */
char* getStrOfSeatClass(int seatClass);

/*
airplane의 seatClass의 좌석의 행을 반환한다. */
int getRowOfAirplaneSeat(AIRPLANE* airplane, int seatClass);

/*
airplane의 seatClass의 좌석의 열을 반환한다. */
int getColumnOfAirplaneSeat(AIRPLANE* airplane, int seatClass);

/*
airplane의 seatClass의 남은 좌석 수를 반환한다. */
int getNumberOfSeatsOfClass(AIRPLANE* airplane, int seatClass);

/*
airplane의 seatClass의 row행 column열의 좌석 상태를 반환한다. */
int getSeatAvailable(AIRPLANE* airplane, int seatClass, int row, int column);