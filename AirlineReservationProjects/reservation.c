#include "reservation.h"

#define BLACK 0
#define RED 1

RBT_NODE* generateRBTNode(RESERVATION* reservation)
{
	RBT_NODE* rbtNode = malloc(sizeof(RBT_NODE));

	rbtNode->reservation = reservation;
	rbtNode->color = BLACK;
	rbtNode->parent = NULL;
	rbtNode->left = NULL;
	rbtNode->right = NULL;

	return rbtNode;
}

RESERVATION* generateReservation(RESERVATION_RECORD* reservationRecord, const char* name, PATH* path)
{
	RESERVATION* reservation = malloc(sizeof(RESERVATION));

	reservation->name = name;
	reservation->path = path;
	// 1 부터 차례대로 reservation Number로 설정
	reservation->reservationNumber = reservationRecord->nextReservationNumber++;

	return reservation;
}

RESERVATION_RECORD* generateReservationRecord()
{
	RESERVATION_RECORD* reservationRecord = malloc(sizeof(RESERVATION_RECORD));

	reservationRecord->root = NULL;
	reservationRecord->nil = generateRBTNode(NULL);
	reservationRecord->nextReservationNumber = 1;

	return reservationRecord;
}

void addToRecord(RESERVATION_RECORD* reservationRecord, const char* name, PATH* path)
{
	RBT_NODE* rbtNode = generateRBTNode(generateReservation(reservationRecord, name, path));


}

int removeFromRecord(RESERVATION_RECORD* reservationRecord, RESERVATION* reservation)
{

}

RESERVATION** arrayFromRecord(RESERVATION_RECORD* reservationRecord)
{

}