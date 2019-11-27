#include "reservation.h"

static int nextReservationNumber;

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

RESERVATION* generateReservation(const char* name)
{
	RESERVATION* reservation = malloc(sizeof(RESERVATION));

	reservation->name = name;
	reservation->path = generatePath();
	// 1 부터 차례대로 reservation Number로 설정
	reservation->reservationNumber = ++nextReservationNumber;

	return reservation;
}

RESERVATION_RECORD* generateReservationRecord()
{
	RESERVATION_RECORD* reservationRecord = malloc(sizeof(RESERVATION_RECORD));

	reservationRecord->root = NULL;
	reservationRecord->nil = generateRBTNode(NULL);

	return reservationRecord;
}

void addToRecord(RESERVATION_RECORD* reservationRecord, RESERVATION* reservation)
{
	RBT_NODE* rbtNode = generateRBTNode(reservation);


}

void removeFromRecord(RESERVATION_RECORD* reservationRecord, RESERVATION* reservation)
{

}

RESERVATION** arrayFromRecord(RESERVATION_RECORD* reservationRecord)
{

}