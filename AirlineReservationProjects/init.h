#pragma once

#include <string.h>

#include "reservation.h"
#include "flight.h"
#include "iterator.h"

/*
CITY_GRAPH�� ����� �ʱ�ȭ�ϰ�,
�������� ������ 24���� ���ÿ� ���� ���� ����� ��θ� �������� 300�� �߰��Ͽ� ��ȯ�Ѵ�. */
CITY_GRAPH* initCityGraph();

/*
LINKED_LIST�� ����� �ʱ�ȭ�ϰ�,
��� ���� ��ο� */
LINKED_LIST* initflightList(CITY_GRAPH* cityGraph, int day);

/*
RESERVATION_RECORD�� ����� �ʱ�ȭ�ϰ�,
�������� ������ 500���� RESERVATION�� �߰��Ͽ� ��ȯ�Ѵ�.*/
RESERVATION_RECORD* initReservationRecord(LINKED_LIST* flightList[], CITY_GRAPH* cityGraph);