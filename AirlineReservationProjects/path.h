#pragma once

#include <time.h>

#include "city.h"
#include "linkedList.h"
#include "airline.h"

/*
����ü PATH�� ���ӵ� AIRLINE�� ���´�.
���� CITY�� �����ؼ� ���� ��츦 ��Ÿ���� ���� �����Ǿ���. */
typedef struct path
{
	LINKED_LIST* airlineList;
} PATH;

/*
����ü PATH�� �����ϰ� ���� ������ �ʱ�ȭ�Ͽ� ��ȯ�Ѵ�. */
PATH* generatePath();

/*
path�� ����ִٸ� �׳� �߰��Ѵ�.
������� �ʰ�, path���� airline�� �������� �������� �߰��� airline�� ������� ����,
�߰��� airline�� ��� �ð��� airline������ airline�� ���� �ð����� ������ ��쿡 �߰��Ѵ�.
�� ���� ���� �߰����� �ʰ� 0�� ��ȯ�Ѵ�. */
int addToPath(PATH* path, AIRLINE* airline);

/*
path�κ��� ó�� AIRLINE�� ������� ��ȯ�Ѵ�. */
CITY* getSource(PATH* path);

/*
path�κ��� ������ AIRLINE�� �������� ��ȯ�Ѵ�. */
CITY* getDestination(PATH* path);

/*
path�κ��� ó�� AIRLINE�� ��� �ð��� ��ȯ�Ѵ�.*/
time_t getDepartureTime(PATH* path);

/*
path�κ��� ������ AIRLINE�� ���� �ð��� ��ȯ�Ѵ�. */
time_t getArrivalTime(PATH* path);

/*
path�κ��� ������ AIRLINE�� ���� �ð� - ó�� AIRLINE�� ��� �ð��� ����Ͽ� ��ȯ�Ѵ�. */
time_t getElapsedTime(PATH* path);

/*
depatureTime���� �ʴ� AIRLINE��κ��� ������� source�̰� �������� destination�� �ǵ���
AIRLINE�� ������ PATH�� ����� ��ȯ�Ѵ�. 
��ΰ� ���ٸ� NULL�� ��ȯ�Ѵ�. */
PATH* findPathForShortestFlightTime(struct tm* departureTime, CITY* source, CITY* destination);