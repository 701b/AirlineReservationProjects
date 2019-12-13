#include "airplane.h"

#define MAX_ROW_OF_FIRST_CLASS_SEATS_OF_BOEING_777 4
#define MAX_ROW_OF_FIRST_CLASS_SEATS_OF_BOEING_737 0
#define MAX_ROW_OF_FIRST_CLASS_SEATS_OF_BOEING_747 2
#define MAX_ROW_OF_FIRST_CLASS_SEATS_OF_AIRBUS_330 0
#define MAX_ROW_OF_FIRST_CLASS_SEATS_OF_AIRBUS_380 4
#define MAX_ROW_OF_FIRST_CLASS_SEATS_OF_AIRBUS_220 0

#define MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_BOEING_777 2
#define MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_BOEING_737 0
#define MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_BOEING_747 3
#define MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_AIRBUS_330 0
#define MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_AIRBUS_380 3
#define MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_AIRBUS_220 0

#define MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_BOEING_777 7
#define MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_BOEING_737 4
#define MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_BOEING_747 6
#define MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_330 6
#define MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_380 6
#define MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_220 0

#define MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_BOEING_777 6
#define MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_BOEING_737 3
#define MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_BOEING_747 8
#define MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_330 4
#define MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_380 16
#define MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_220 0

#define MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_BOEING_777 9
#define MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_BOEING_737 6
#define MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_BOEING_747 10
#define MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_330 8
#define MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_380 10
#define MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_220 5

#define MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_BOEING_777 26
#define MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_BOEING_737 21
#define MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_BOEING_747 30
#define MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_330 30
#define MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_380 30
#define MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_220 26



int** allocateMemoryToSeats(int row, int column)
{
	int** seats;

	if (row != 0)
	{
		seats = malloc(row * sizeof(int*));

		for (int i = 0; i < row; i++)
		{
			seats[i] = calloc(column, sizeof(int));
		}
	}
	else
	{
		seats = NULL;
	}

	return seats;
}

AIRPLANE* generateAirplane(int kindsOfAirplane)
{
	AIRPLANE* airplane = malloc(sizeof(AIRPLANE));

	airplane->kindsOfAirplane = kindsOfAirplane;

	switch (kindsOfAirplane)
	{
		case BOEING_777:
			airplane->firstClass = allocateMemoryToSeats(MAX_ROW_OF_FIRST_CLASS_SEATS_OF_BOEING_777, MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_BOEING_777);
			airplane->businessClass = allocateMemoryToSeats(MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_BOEING_777, MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_BOEING_777);
			airplane->economyClass = allocateMemoryToSeats(MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_BOEING_777, MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_BOEING_777);
			break;
		case BOEING_737:
			airplane->firstClass = allocateMemoryToSeats(MAX_ROW_OF_FIRST_CLASS_SEATS_OF_BOEING_737, MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_BOEING_737);
			airplane->businessClass = allocateMemoryToSeats(MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_BOEING_737, MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_BOEING_737);
			airplane->economyClass = allocateMemoryToSeats(MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_BOEING_737, MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_BOEING_737);
			break;
		case BOEING_747:
			airplane->firstClass = allocateMemoryToSeats(MAX_ROW_OF_FIRST_CLASS_SEATS_OF_BOEING_747, MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_BOEING_747);
			airplane->businessClass = allocateMemoryToSeats(MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_BOEING_747, MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_BOEING_747);
			airplane->economyClass = allocateMemoryToSeats(MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_BOEING_747, MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_BOEING_747);
			break;
		case AIRBUS_330:
			airplane->firstClass = allocateMemoryToSeats(MAX_ROW_OF_FIRST_CLASS_SEATS_OF_AIRBUS_330, MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_AIRBUS_330);
			airplane->businessClass = allocateMemoryToSeats(MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_330, MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_330);
			airplane->economyClass = allocateMemoryToSeats(MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_330, MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_330);
			break;
		case AIRBUS_380:
			airplane->firstClass = allocateMemoryToSeats(MAX_ROW_OF_FIRST_CLASS_SEATS_OF_AIRBUS_380, MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_AIRBUS_380);
			airplane->businessClass = allocateMemoryToSeats(MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_380, MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_380);
			airplane->economyClass = allocateMemoryToSeats(MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_380, MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_380);
			break;
		case AIRBUS_220:
			airplane->firstClass = allocateMemoryToSeats(MAX_ROW_OF_FIRST_CLASS_SEATS_OF_AIRBUS_220, MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_AIRBUS_220);
			airplane->businessClass = allocateMemoryToSeats(MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_220, MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_220);
			airplane->economyClass = allocateMemoryToSeats(MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_220, MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_220);
			break;
	}

	return airplane;
}

char* getStrOfAirplane(AIRPLANE* airplane)
{
	char* str = calloc(5, sizeof(char));

	switch (airplane->kindsOfAirplane)
	{
		case BOEING_737:
			strcpy(str, "B737");
			break;

		case BOEING_747:
			strcpy(str, "B747");
			break;

		case BOEING_777:
			strcpy(str, "B777");
			break;

		case AIRBUS_220:
			strcpy(str, "A220");
			break;

		case AIRBUS_330:
			strcpy(str, "A330");
			break;

		case AIRBUS_380:
			strcpy(str, "A380");
			break;
	}

	return str;
}

char* getStrOfSeatClass(int seatClass)
{
	switch (seatClass)
	{
	case FIRST_CLASS:
		return "일등석";

	case BUSINESS_CLASS:
		return "비즈니스석";

	case ECONOMY_CLASS:
		return "일반석";
	}
}

int getRowOfAirplaneSeat(AIRPLANE* airplane, int seatClass)
{
	switch (airplane->kindsOfAirplane)
	{
	case BOEING_777:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_ROW_OF_FIRST_CLASS_SEATS_OF_BOEING_777;

		case BUSINESS_CLASS:
			return MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_BOEING_777;

		case ECONOMY_CLASS:
			return MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_BOEING_777;
		}
		break;

	case BOEING_737:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_ROW_OF_FIRST_CLASS_SEATS_OF_BOEING_737;

		case BUSINESS_CLASS:
			return MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_BOEING_737;

		case ECONOMY_CLASS:
			return MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_BOEING_737;
		}
		break;

	case BOEING_747:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_ROW_OF_FIRST_CLASS_SEATS_OF_BOEING_747;

		case BUSINESS_CLASS:
			return MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_BOEING_747;

		case ECONOMY_CLASS:
			return MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_BOEING_747;
		}
		break;

	case AIRBUS_330:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_ROW_OF_FIRST_CLASS_SEATS_OF_AIRBUS_330;

		case BUSINESS_CLASS:
			return MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_330;

		case ECONOMY_CLASS:
			return MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_330;
		}
		break;

	case AIRBUS_380:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_ROW_OF_FIRST_CLASS_SEATS_OF_AIRBUS_380;

		case BUSINESS_CLASS:
			return MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_380;

		case ECONOMY_CLASS:
			return MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_380;
		}
		break;

	case AIRBUS_220:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_ROW_OF_FIRST_CLASS_SEATS_OF_AIRBUS_220;

		case BUSINESS_CLASS:
			return MAX_ROW_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_220;

		case ECONOMY_CLASS:
			return MAX_ROW_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_220;
		}
		break;

	default:
		return 0;
	}
}

int getColumnOfAirplaneSeat(AIRPLANE* airplane, int seatClass)
{
	switch (airplane->kindsOfAirplane)
	{
	case BOEING_777:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_BOEING_777;

		case BUSINESS_CLASS:
			return MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_BOEING_777;

		case ECONOMY_CLASS:
			return MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_BOEING_777;
		}
		break;

	case BOEING_737:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_BOEING_737;

		case BUSINESS_CLASS:
			return MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_BOEING_737;

		case ECONOMY_CLASS:
			return MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_BOEING_737;
		}
		break;

	case BOEING_747:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_BOEING_747;

		case BUSINESS_CLASS:
			return MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_BOEING_747;

		case ECONOMY_CLASS:
			return MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_BOEING_747;
		}
		break;

	case AIRBUS_330:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_AIRBUS_330;

		case BUSINESS_CLASS:
			return MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_330;

		case ECONOMY_CLASS:
			return MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_330;
		}
		break;

	case AIRBUS_380:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_AIRBUS_380;

		case BUSINESS_CLASS:
			return MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_380;

		case ECONOMY_CLASS:
			return MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_380;
		}
		break;

	case AIRBUS_220:
		switch (seatClass)
		{
		case FIRST_CLASS:
			return MAX_COLUMN_OF_FIRST_CLASS_SEATS_OF_AIRBUS_220;

		case BUSINESS_CLASS:
			return MAX_COLUMN_OF_BUSINESS_CLASS_SEATS_OF_AIRBUS_220;

		case ECONOMY_CLASS:
			return MAX_COLUMN_OF_ECONOMY_CLASS_SEATS_OF_AIRBUS_220;
		}
		break;

	default:
		return 0;
	}
}

int getNumberOfSeatsOfClass(AIRPLANE* airplane, int seatClass)
{
	int seats = 0;
	int maxRow = getRowOfAirplaneSeat(airplane, seatClass);
	int maxCol = getColumnOfAirplaneSeat(airplane, seatClass);

	for (int row = 0; row < maxRow; row++)
	{
		for (int col = 0; col < maxCol; col++)
		{
			switch (seatClass)
			{
			case FIRST_CLASS:
				if (airplane->firstClass[row][col] == SEAT_AVAILABLE)
				{
					seats++;
				}
				break;

			case BUSINESS_CLASS:
				if (airplane->businessClass[row][col] == SEAT_AVAILABLE)
				{
					seats++;
				}
				break;

			case ECONOMY_CLASS:
				if (airplane->economyClass[row][col] == SEAT_AVAILABLE)
				{
					seats++;
				}
				break;
			}
		}
	}

	return seats;
}

int getSeatAvailable(AIRPLANE* airplane, int seatClass, int row, int column)
{
	switch (seatClass)
	{
	case FIRST_CLASS:
		return airplane->firstClass[row][column];

	case BUSINESS_CLASS:
		return airplane->businessClass[row][column];

	case ECONOMY_CLASS:
		return airplane->economyClass[row][column];
	}
}
