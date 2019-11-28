#pragma once

#include <stdlib.h>
#include <time.h>

#include "linkedList.h"
#include "path.h"
#include "airline.h"

/*
구조체 RESERVATION은 예약을 뜻하며, 예약자 이름, 예약 번호, 경로를 가진다.
예약 번호는 자동으로 생성된다. */
typedef struct reservation
{
	char* name;
	int reservationNumber;
	PATH* path;
} RESERVATION;

/*
레드 블랙 트리(RESERVATION_RECORD에 사용되는 노드이다. */
typedef struct rbtnode
{
	struct reservation* reservation;
	int color;
	struct rbtnode* parent;
	struct rbtnode* left;
	struct rbtnode* right;
} RBT_NODE;

/*
구조체 RESERVATION_RECORD는 레드 블랙 트리로, root노드와 nil노드를 갖는다.
nextReservationNumber은 새로 RESERVATION이 추가될 때 1부터 차례대로 지정하기 위해 선언되었다.*/
typedef struct reservationRecord
{
	RBT_NODE* root;
	RBT_NODE* nil;
	int nextReservationNumber;
} RESERVATION_RECORD;

/*
구조체 RESERVATION_RECORD를 생성하고 내부 변수를 초기화하여 반환한다. */
RESERVATION_RECORD* generateReservationRecord();

/*
name, path를 이용하여 RESERVATION을 생성하고, 그것을 reservationRecord에 추가한다. */
void addToRecord(RESERVATION_RECORD* reservationRecord, const char* name, PATH* path);

/*
reservation을 reservationRecord에서 찾아 제거한다. 
성공적으로 제거했을 경우 1을, 제거하지 못했을 경우 0을 반환한다. */
int removeFromRecord(RESERVATION_RECORD* reservationRecord, RESERVATION* reservation);

/*
reservationRecord를 배열로 바꾸어 반환한다. */
RESERVATION** arrayFromRecord(RESERVATION_RECORD* reservationRecord);

