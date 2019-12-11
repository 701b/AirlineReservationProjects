#pragma once

#include <stdlib.h>
#include <time.h>

#include "linkedList.h"
#include "path.h"
#include "flight.h"

/*
����ü RESERVATION�� ������ ���ϸ�, ������ �̸�, ���� ��ȣ, ��θ� ������.
���� ��ȣ�� �ڵ����� �����ȴ�. */
typedef struct reservation
{
	char* name;
	int reservationNumber;
	PATH* path;
} RESERVATION;

/*
���� �� Ʈ��(RESERVATION_RECORD)�� ���Ǵ� ����̴�. */
typedef struct rbtnode
{
	struct reservation* reservation;
	int color;
	struct rbtnode* parent;
	struct rbtnode* left;
	struct rbtnode* right;
} RBT_NODE;

/*
����ü RESERVATION_RECORD�� ���� �� Ʈ����, root��带 ���´�.
nextReservationNumber�� ���� RESERVATION�� �߰��� �� 1���� ���ʴ�� �����ϱ� ���� ����Ǿ���.*/
typedef struct reservationRecord
{
	RBT_NODE* root;
	int nextReservationNumber;
} RESERVATION_RECORD;

/*
����ü RESERVATION_RECORD�� �����ϰ� ���� ������ �ʱ�ȭ�Ͽ� ��ȯ�Ѵ�. */
RESERVATION_RECORD* generateReservationRecord();

/*
name, path�� �̿��Ͽ� RESERVATION�� �����ϰ�, �װ��� reservationRecord�� �߰��Ѵ�. 
������� RESERVATION�� ��ȯ�Ѵ�. */
void addToRecord(RESERVATION_RECORD* reservationRecord, const char* name, PATH* path);

/*
reservation�� reservationRecord���� ã�� �����Ѵ�. 
���������� �������� ��� 1��, �������� ������ ��� 0�� ��ȯ�Ѵ�. */
int removeFromRecord(RESERVATION_RECORD* reservationRecord, RESERVATION* reservation);

/*
reservationRecord�� �迭�� �ٲپ� ��ȯ�Ѵ�. */
RESERVATION** arrayFromRecord(RESERVATION_RECORD* reservationRecord);

/*
reservationRecord�� ���� �� Ʈ���� ���·� ����Ѵ�. */
void printTree(RESERVATION_RECORD* reservationRecord);