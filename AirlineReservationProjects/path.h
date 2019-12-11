#pragma once

#include <time.h>

#include "city.h"
#include "linkedList.h"
#include "flight.h"
#include "customTime.h"

/*
����ü PATH�� ���ӵ� FLIGHT�� ���´�.
���� CITY�� �����ؼ� ���� ��츦 ��Ÿ���� ���� �����Ǿ���. */
typedef struct path
{
	LINKED_LIST* flightList;
} PATH;

/*
����ü PATH�� �����ϰ� ���� ������ �ʱ�ȭ�Ͽ� ��ȯ�Ѵ�. */
PATH* generatePath();


/*
path�� �����Ͽ� ��ȯ�Ѵ�. */
PATH* generateClonePath(PATH* path);

/*
path�� ����ִٸ� �׳� �߰��Ѵ�.
������� �ʰ�, path���� flight�� �������� �������� �߰��� flight�� ������� ����,
�߰��� flight�� ��� �ð��� flight������ flight�� ���� �ð����� ������ ��쿡 �߰��Ѵ�.
�� ���� ���� �߰����� �ʰ� 0�� ��ȯ�Ѵ�. */
int addToPath(PATH* path, FLIGHT* flight);

/*
path���� ���� ������ FLIGHT�� ������. */
FLIGHT* popPath(PATH* path);

/*
path�κ��� ó�� FLIGHT�� ������� ��ȯ�Ѵ�. */
CITY* getSource(PATH* path);

/*
path�κ��� ������ FLIGHT�� �������� ��ȯ�Ѵ�. */
CITY* getDestination(PATH* path);

/*
path�κ��� ó�� FLIGHT�� ��� �ð��� ��ȯ�Ѵ�.*/
TIME* getDepartureTime(PATH* path);

/*
path�κ��� ������ FLIGHT�� ���� �ð��� ��ȯ�Ѵ�. */
TIME* getArrivalTime(PATH* path);

/*
path�κ��� ������ FLIGHT�� ���� �ð� - ó�� FLIGHT�� ��� �ð��� ����Ͽ� ��ȯ�Ѵ�. */
TIME* getElapsedTime(PATH* path);

/*
�������� ���� ��ȯ�Ѵ�. (�����, �������� ������ ��ġ�� ������ ��)*/
int getNumberOfTransit(PATH* path);

/*
departureTime�� ����ϴ� source�κ��� destination������ ��� ��θ� ã�� ��ȯ�Ѵ�. 
��� ��ε� �� ã�� ���, NULL�� ��ȯ�Ѵ�. */
LINKED_LIST* findAllPath(LINKED_LIST* flightList[], TIME* departureTime, CITY* source, CITY* destination, int seatClass);

/*
depatureTime���� �ʴ� FLIGHT��κ��� ������� source�̰� �������� destination�� �ǵ���
FLIGHT�� ������ PATH�� ����� ��ȯ�Ѵ�. 
��ΰ� ���ٸ� NULL�� ��ȯ�Ѵ�. */
PATH* findPathForShortestFlightTime(LINKED_LIST* flightList[], TIME* departureTime, CITY* source, CITY* destination);

/*
path�� �޸𸮸� �����Ѵ�. */
void freePath(PATH** path);

/*
path�� �����ϰ� ���ڿ��� ��ȯ�Ͽ� ��ȯ�Ѵ�. 
����� ��߽ð� -- �ҿ� �ð� (������ ��) --> �����ð� ������ �¼����
seatClassStr�� NULL�̸� �¼������ ǥ�õ��� �ʴ´�. */
char* pathToStr(PATH* path, char* seatClassStr);