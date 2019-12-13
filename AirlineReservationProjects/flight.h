#pragma once

#include "linkedList.h"
#include "city.h"
#include "iterator.h"
#include "customTime.h"
#include "airplane.h"

/*
����ü FLIGHT�� �װ��� ���� ������ ������, �����, ������, ��߽ð�, �����ð��� ������.
flightList�� �߰��� �ʿ��� ���, addToflightList�Լ��� ����� �߰��Ѵ�. */
typedef struct flight
{
	CITY* source;
	CITY* destination;
	TIME* departureTime;
	TIME* arrivalTime;
	AIRPLANE* airplane;
	int seatClass;
	int seatRowNumber;
	int seatColumnNumber;
} FLIGHT;

/*
���ڷ� �����, ������, ��߽ð��� �޴´�.
�����ð��� �����, ������ ������ �Ÿ��� ���� �ӵ��� ���� ���� ��� �ð��� ���Ͽ� ���Ѵ�.*/
FLIGHT* generateFlight(CITY* source, CITY* destination, TIME* departureTime, AIRPLANE* airplane);

/*
flight�� �����Ͽ� ��ȯ�Ѵ�. ������ ���� �� ���δ�. */
FLIGHT* generateCloneFlight(FLIGHT* flight);

/*
���� ���� flightList�� FLIGHT�� �߰��Ѵ�. */
void addToFlightList(LINKED_LIST* flightList, CITY* source, CITY* destination, TIME* departureTime, AIRPLANE* airplane);

/*
flightList�� ���� �����, ������, ��߽ð��� ���� ���� �ִ��� ã�´�.
ã�´ٸ� 1��, �� ã�´ٸ� 0�� ��ȯ�Ѵ�. */
int findFromFlightList(LINKED_LIST* flightList, CITY* source, CITY* destination, TIME* departureTime);

/*
�¼��� �����ϰ�, �ش� �װ����� ���� �¼��� ���¸� seatStatus�� �ٲ۴� */
void setSeat(FLIGHT* flight, int seatClass, int seatRowNumber, int seatColumnNumber, int seatStatus);

/*
flight�� ���� ������ ���ڿ��� ��ȯ�Ѵ�.
previousFlight�� ��¥�� �Ѿ���� ǥ���ϱ� ���ؼ� ���δ�.
seatClass�� �̿��Ͽ� Ư�� �¼������ �ܿ� �¼��� ǥ���Ѵ�.
seatClass�� -1�� ���� �¼���ȣ�� ǥ���Ѵ�. */
char* flightToStr(FLIGHT* flight, FLIGHT* previousFlight, int seatClass);

/*
flight�� �޸𸮸� �����Ѵ�. */
void freeFlight(FLIGHT** flight);