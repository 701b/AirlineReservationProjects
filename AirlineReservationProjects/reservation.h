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
구조체 RESERVATION은 예약을 뜻하며, 예약자 이름, 예약 번호, 경로를 가진다.
예약 번호는 자동으로 생성된다. */
typedef struct reservation
{
	char* firstName;
	char* lastName;
	int sex;
	int reservationNumber;
	PATH* path;
} RESERVATION;

/*
레드 블랙 트리(RESERVATION_RECORD)에 사용되는 노드이다. */
typedef struct rbtnode
{
	struct reservation* reservation;
	int color;
	struct rbtnode* parent;
	struct rbtnode* left;
	struct rbtnode* right;
} RBT_NODE;

/*
구조체 RESERVATION_RECORD는 레드 블랙 트리로, root노드를 갖는다.
nextReservationNumber은 새로 RESERVATION이 추가될 때 1부터 차례대로 지정하기 위해 선언되었다.*/
typedef struct reservationRecord
{
	RBT_NODE* root;
	int nextReservationNumber;
} RESERVATION_RECORD;

/*
구조체 RESERVATION_RECORD를 생성하고 내부 변수를 초기화하여 반환한다. */
RESERVATION_RECORD* generateReservationRecord();

/*
name, path를 이용하여 RESERVATION을 생성하고, 그것을 reservationRecord에 추가한다. 
만들어진 RESERVATION도 반환한다. */
RESERVATION* addToRecord(RESERVATION_RECORD* reservationRecord, const char* firstName, const char* lastName, int sex, PATH* path);

/*
reservation을 reservationRecord에서 찾아 제거한다. 
성공적으로 제거했을 경우 1을, 제거하지 못했을 경우 0을 반환한다. */
int removeFromRecord(RESERVATION_RECORD* reservationRecord, RESERVATION* reservation);

/*
reservationRecord를 배열로 바꾸어 반환한다. */
LINKED_LIST* listFromRecord(RESERVATION_RECORD* reservationRecord);

/*
reservationRecord를 레드 블랙 트리의 형태로 출력한다. */
void printTree(RESERVATION_RECORD* reservationRecord);

/*
reservationRecord의 레드 블랙 트리로써의 높이와 노드 수를 출력한 문자열을 반환한다. */
char* printTreeTraversal(RESERVATION_RECORD* reservationRecord);

/*
path를 간략하게 한줄의 문자열로 변환하여 반환한다.
예약번호 이름 성  출발지 출발시간 -- 소요 시간 (경유지 수) --> 도착시간 도착지  좌석등급 */
char* reservationToStr(RESERVATION* reservation);