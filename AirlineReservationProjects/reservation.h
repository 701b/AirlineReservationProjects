#pragma once

#include <stdlib.h>
#include <time.h>

#include "linkedList.h"
#include "path.h"
#include "airline.h"

#define BLACK 0
#define RED 1

typedef struct reservation
{
	char* name;
	int reservationNumber;
	PATH* path;
} RESERVATION;

typedef struct rbtnode
{
	struct reservation* reservation;
	int color;
	struct rbtnode* parent;
	struct rbtnode* left;
	struct rbtnode* right;
} RBT_NODE;

typedef struct reservationRecord
{
	RBT_NODE* root;
	RBT_NODE* nil;
} RESERVATION_RECORD;

RESERVATION* generateReservation(const char* name);
RESERVATION_RECORD* generateReservationRecord();

void addToRecord(RESERVATION_RECORD* reservationRecord, RESERVATION* reservation);
void removeFromRecord(RESERVATION_RECORD* reservationRecord, RESERVATION* reservation);
RESERVATION** arrayFromRecord(RESERVATION_RECORD* reservationRecord);

