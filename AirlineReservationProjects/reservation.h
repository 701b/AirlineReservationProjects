#pragma once

#include <stdlib.h>
#include <time.h>

#include "consoleControl.h"
#include "linkedList.h"
#include "path.h"
#include "flight.h"

#define MAN 1
#define WOMAN 2

#define MAX_SPACE_OF_NAME 26
#define MAX_SPACE_OF_RESERVATION_NUMBER 7

/*
����ü RESERVATION�� ������ ���ϸ�, ������ �̸�, ���� ��ȣ, ��θ� ������.
���� ��ȣ�� �ڵ����� �����ȴ�. */
typedef struct reservation
{
	char* firstName;
	char* lastName;
	int sex;
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
RESERVATION* addToRecord(RESERVATION_RECORD* reservationRecord, const char* firstName, const char* lastName, int sex, PATH* path);

/*
reservation�� reservationRecord���� ã�� �����Ѵ�. 
���������� �������� ��� 1��, �������� ������ ��� 0�� ��ȯ�Ѵ�. */
int removeFromRecord(RESERVATION_RECORD* reservationRecord, RESERVATION* reservation);

/*
reservationRecord�� �迭�� �ٲپ� ��ȯ�Ѵ�. */
LINKED_LIST* listFromRecord(RESERVATION_RECORD* reservationRecord);

/*
reservationRecord�� ���� �� Ʈ���� ���·� ����Ѵ�. */
void printTree(RESERVATION_RECORD* reservationRecord);

/*
reservationRecord�� ���� �� Ʈ���ν��� ���̿� ��� ���� ����� ���ڿ��� ��ȯ�Ѵ�. */
char* printTreeTraversal(RESERVATION_RECORD* reservationRecord);

/*
path�� �����ϰ� ������ ���ڿ��� ��ȯ�Ͽ� ��ȯ�Ѵ�.
�����ȣ �̸� ��  ����� ��߽ð� -- �ҿ� �ð� (������ ��) --> �����ð� ������  �¼���� */
char* reservationToStr(RESERVATION* reservation);