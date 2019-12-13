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
AIRPLANE ����ü�� ����� �ʱ�ȭ�ϰ� ��ȯ�Ѵ�.*/
AIRPLANE* generateAirplane(int kindsOfAirplane);

/*
airplane�� ������ ���ڿ��� ��ȯ�Ѵ�. */
char* getStrOfAirplane(AIRPLANE* airplane);

/*
�¼� ����� ���ڿ��� ��ȯ�Ѵ�. */
char* getStrOfSeatClass(int seatClass);

/*
airplane�� seatClass�� �¼��� ���� ��ȯ�Ѵ�. */
int getRowOfAirplaneSeat(AIRPLANE* airplane, int seatClass);

/*
airplane�� seatClass�� �¼��� ���� ��ȯ�Ѵ�. */
int getColumnOfAirplaneSeat(AIRPLANE* airplane, int seatClass);

/*
airplane�� seatClass�� ���� �¼� ���� ��ȯ�Ѵ�. */
int getNumberOfSeatsOfClass(AIRPLANE* airplane, int seatClass);

/*
airplane�� seatClass�� row�� column���� �¼� ���¸� ��ȯ�Ѵ�. */
int getSeatAvailable(AIRPLANE* airplane, int seatClass, int row, int column);