#define _CRT_SECURE_NO_WARNINGS

#include "userInterface.h"

#define DAY_OF_MONTH 31

#define MAX_NUMBER_OF_RESULT 25

#define MAX_SPACE_BETWEEN_CITY_AND_TIME 16
#define MAX_SPACE_BETWEEN_TIME_AND_TIME 30

#define STARTING_POINT_OF_SEARCH_LIST 6

char* cityChoice[27] = { "a ��", "b ��", "c ��", "d ��", "e ��", "f ��", "g ��",
							"h ��", "i ��", "j ��", "k ��", "l ��", "m ��", "n ��",
							"o ��", "p ��", "q ��", "r ��", "s ��", "t ��", "u ��",
							"v ��", "w ��", "x ��", "y ��", "z ��", NULL };
char* dateChoice[32] = { "2019. 01. 01", "2019. 01. 02", "2019. 01. 03",
						"2019. 01. 04", "2019. 01. 05", "2019. 01. 06",
						"2019. 01. 07", "2019. 01. 08", "2019. 01. 09",
						"2019. 01. 10", "2019. 01. 11", "2019. 01. 12",
						"2019. 01. 13", "2019. 01. 14", "2019. 01. 15",
						"2019. 01. 16", "2019. 01. 17", "2019. 01. 18",
						"2019. 01. 19", "2019. 01. 20", "2019. 01. 21",
						"2019. 01. 22", "2019. 01. 23", "2019. 01. 24",
						"2019. 01. 25", "2019. 01. 26", "2019. 01. 27",
						"2019. 01. 28", "2019. 01. 29", "2019. 01. 30",
						"2019. 01. 31", NULL };
char* classChoice[4] = { "�ϵ", "����Ͻ���", "�Ϲݼ�", NULL };
char* sexChoice[3] = { "����", "����", NULL };

CITY_GRAPH* cityGraph;
LINKED_LIST* flightList[DAY_OF_MONTH];
RESERVATION_RECORD* record;

PAGE* currentPage;

PAGE* mainPage;
PAGE* reservationListPage;
PAGE* reservationDetailPage;
PAGE* flightInformationPage;
PAGE* enteringMemberInformationPage;
PAGE* seatSelectionPage;
PAGE* checkingAllInformationPage;

COMBO_BOX* sourceComboBox;
COMBO_BOX* destinationComboBox;
COMBO_BOX* departureDateComboBox;
COMBO_BOX* seatClassComboBox;
EDIT_TEXT* lastNameEditText;
EDIT_TEXT* firstNameEditText;
COMBO_BOX* sexComboBox;

int seatClass;
PATH* selectedPath;
RESERVATION* reservationTemp;

LINKED_LIST* searchResultList;
int pageNumberOfSearchResult;
int pageNumberOfReservationList;

BUTTON* selectPathButtons[MAX_NUMBER_OF_RESULT];
BUTTON* selectReservationButtons[MAX_NUMBER_OF_RESULT];
CHECK_BOX* seatsCheckBox[MAX_ROW_OF_CHECK_BOX_SET][MAX_COLUMN_OF_CHECK_BOX_SET];

ITERATOR* flightForSeatSelectionIterator;
BUTTON* seatSelectionButton;

//-- mainPage���� ���̴� �Լ��� ���� �Լ�
void* goToFlightInformation(void* ptr);
void* goToReservationList(void* ptr);
void* searchPaths(void* ptr);
void* nextResult(void* ptr);
void* previousResult(void* ptr);
void showSearchResults();
void freeSearchResultList();
void sortSearchResultList();

//-- reservationListPage���� ���̴� �Լ��� ���� �Լ�
void showReservationList();
void clearReservationList();
void* cancleReservationList(void* ptr);
void* nextReservationList(void* ptr);
void* previousReservationList(void* ptr);
void* goToReservationDetail(void* ptr);

//-- reservationDetailPage���� ���̴� �Լ��� ���� �Լ�
void showReservationDetail();
void clearReservationDetail();
void* deleteReservation(void* ptr);
void* cancleReservationDetail(void* ptr);

//-- flightInformationPage���� ���̴� �Լ��� ���� �Լ�
void* cancleFlightInformation(void* ptr);
void* goToEnteringMemberInformation(void* ptr);
void showFlightInformation();
void clearFlightInformation();

//-- enteringMemberInformationPage���� ���̴� �Լ��� ���� �Լ�
void* goToSeatSelection(void* ptr);
void* cancleEnteringMemberInformation(void* ptr);

//-- seatSelectionPage���� ���̴� �Լ��� ���� �Լ�
void* goToCheckingAllInformation(void* ptr);
void showSeatSelection();
void clearSeatSelection();
void* selectSeat(void* ptr);
void* cancleSeatSelection(void* ptr);

//-- checkingAllInformationPage���� ���̴� �Լ��� ���� �Լ�
void showCheckingAllInformation();
void clearCheckingAllInformation();
void* reservateFlight(void* ptr);
void* cancleCheckingAllInformation(void* ptr);






void init()
{
	system("mode con cols=140 lines=40");

	printf("�ʱ�ȭ��..  �� �� �ð��� �ɸ��ϴ�.\n");

	changeColor(LIGHT_WHITE, BLACK);

	printf("���� 26���� �׷����� �߰� �� �ܹ��� ��� 100�� ������..");

	cityGraph = initCityGraph();

	printf(" �Ϸ�\n");

	printf("���� �װ� ���� ���� ������..");

	for (int i = 0; i < DAY_OF_MONTH; i++)
	{
		flightList[i] = initflightList(cityGraph, i + 1);
	}

	printf(" �Ϸ�\n");

	printf("�ʱ� ���� 500�� ������..");

	record = initReservationRecord(flightList, cityGraph);

	printf(" �Ϸ�\n");

	printf("Page ������..");

	// mainPage ����
	{
		mainPage = generatePage();
		sourceComboBox = generateComboBox("�����", cityChoice, 1, 1);
		destinationComboBox = generateComboBox("������", cityChoice, 21, 1);
		departureDateComboBox = generateComboBox("��� ��¥", dateChoice, 41, 1);
		seatClassComboBox = generateComboBox("�¼� ���", classChoice, 61, 1);

		addView(mainPage, sourceComboBox);
		addView(mainPage, destinationComboBox);
		addView(mainPage, departureDateComboBox);
		addView(mainPage, seatClassComboBox);
		addView(mainPage, generateButton("�װ��� �˻�", searchPaths, NULL, 81, 1));
		addView(mainPage, generateButton("���� ������", previousResult, NULL, 50, 4));
		addView(mainPage, generateButton("���� ������", nextResult, NULL, 70, 4));
		addView(mainPage, generateButton("���� ��� ����", goToReservationList, NULL, 101, 1));

		for (int i = 0; i < MAX_NUMBER_OF_RESULT; i++)
		{
			selectPathButtons[i] = generateButton("����", goToFlightInformation, NULL, 1, i + STARTING_POINT_OF_SEARCH_LIST);
		}
	}
	
	// reservationListPage ����
	{
		reservationListPage = generatePage();

		addView(reservationListPage, generateText("���� ���� Ȯ��", 1, 1));
		addView(reservationListPage, generateButton("���� ������", previousReservationList, NULL, 50, 4));
		addView(reservationListPage, generateButton("���� ������", nextReservationList, NULL, 70, 4));
		addView(reservationListPage, generateButton("�ڷ�", cancleReservationList, NULL, 60, 35));

		for (int i = 0; i < MAX_NUMBER_OF_RESULT; i++)
		{
			selectReservationButtons[i] = generateButton("����", goToReservationDetail, NULL, 1, i + STARTING_POINT_OF_SEARCH_LIST);
		}
	}

	// reservationDetailPage ����
	{
		reservationDetailPage = generatePage();
		addView(reservationDetailPage, generateText("���� ���� Ȯ��", 1, 1));
		addView(reservationDetailPage, generateText("-- ���� ���� --", 8, 7));
		addView(reservationDetailPage, generateButton("����", deleteReservation, NULL, 50, 35));
		addView(reservationDetailPage, generateButton("�ڷ�", cancleReservationDetail, NULL, 70, 35));
	}
	
	// flightInformationPage ����
	{
		flightInformationPage = generatePage();
		addView(flightInformationPage, generateText("����� ���� Ȯ��-��-��-��", 1, 1));
		addView(flightInformationPage, generateButton("�����ϱ�", goToEnteringMemberInformation, NULL, 50, 35));
		addView(flightInformationPage, generateButton("�ڷ�", cancleFlightInformation, NULL, 70, 35));
	}

	// enteringMemberInformationPage ����
	{
		enteringMemberInformationPage = generatePage();
		lastNameEditText = generateEditText("��", 5, 3);
		firstNameEditText = generateEditText("�̸�", 25, 3);
		sexComboBox = generateComboBox("�°� ����", sexChoice, 45, 3);

		addView(enteringMemberInformationPage, generateText("��-��ȸ�� ���� �Է�-��-��", 1, 1));
		addView(enteringMemberInformationPage, lastNameEditText);
		addView(enteringMemberInformationPage, firstNameEditText);
		addView(enteringMemberInformationPage, sexComboBox);
		addView(enteringMemberInformationPage, generateButton("���", goToSeatSelection, NULL, 50, 35));
		addView(enteringMemberInformationPage, generateButton("�ڷ�", cancleEnteringMemberInformation, NULL, 70, 35));
	}

	// seatSelectionPage ����
	{
		seatSelectionPage = generatePage();
		seatSelectionButton = generateButton("���� �Ϸ�", selectSeat, NULL, 30, 35);
		addView(seatSelectionPage, generateText("��-��-���¼� ����-��", 1, 1));
		addView(seatSelectionPage, seatSelectionButton);
		addView(seatSelectionPage, generateButton("�ڷ�", cancleSeatSelection, NULL, 60, 35));
	}

	// checkingAllInformationPage ����
	{
		checkingAllInformationPage = generatePage();
		addView(checkingAllInformationPage, generateText("��-��-��-������ Ȯ�� �� ���� �Ϸ�", 1, 1));
		addView(checkingAllInformationPage, generateText("-- ���� ���� --", 8, 7));
		addView(checkingAllInformationPage, generateButton("�����ϱ�", reservateFlight, NULL, 50, 35));
		addView(checkingAllInformationPage, generateButton("�ڷ�", cancleCheckingAllInformation, NULL, 70, 35));
	}

	printf(" �Ϸ�\n");
}

void run()
{
	init();

	currentPage = mainPage;
	initPage(currentPage);
	showPage(currentPage);

	// ���� ����
	while (1)
	{
		char c = getch();

		switch (c)
		{
			case 13:
				if (currentPage->currentView->code == BUTTON_CODE)
				{
					pressButton(currentPage->currentView, NULL);
				}
				else if (currentPage->currentView->code == COMBO_BOX_CODE)
				{
					openComboBox(currentPage->currentView);
					showPage(currentPage);
				}
				else if (currentPage->currentView->code == CHECK_BOX_CODE)
				{
					clickCheckBox(currentPage->currentView);
				}
				break;

			case -32:
				moveTo(currentPage);
				break;

			default:
				if (currentPage->currentView->code == EDIT_TEXT_CODE)
				{
					editText(currentPage->currentView, c);
				}
		}
	}
}


void* goToFlightInformation(void* ptr)
{
	PATH* path = ptr;
	selectedPath = path;

	currentPage = flightInformationPage;
	showFlightInformation();
	initPage(flightInformationPage);
	showPage(currentPage);
}

void showSearchResults()
{
	if (searchResultList == NULL)
	{
		for (int i = STARTING_POINT_OF_SEARCH_LIST; i < MAX_NUMBER_OF_RESULT + STARTING_POINT_OF_SEARCH_LIST; i++)
		{
			removeView(mainPage, i, 0);
			TEXT* text = removeView(mainPage, i, 1);

			selectPathButtons[i - STARTING_POINT_OF_SEARCH_LIST]->funcInput = NULL;
			freeText(&text);
		}

		showPage(mainPage);
		deleteMessage();
		showMessage("�˻��� ��ΰ� �����ϴ�. ");
		return;
	}

	ITERATOR* iterator = generateIterator(searchResultList);

	for (int i = 0; i < pageNumberOfSearchResult; i++)
	{
		for (int j = 0; j < MAX_NUMBER_OF_RESULT; j++)
		{
			getNextData(iterator);

			// ���� ������ ���� �������� �Ѿ
			if (hasNextData(iterator) == 0)
			{
				pageNumberOfSearchResult--;
				i = -1;
				freeIterator(&iterator);
				iterator = generateIterator(searchResultList);
				break;
			}
		}
	}

	for (int i = STARTING_POINT_OF_SEARCH_LIST; i < MAX_NUMBER_OF_RESULT + STARTING_POINT_OF_SEARCH_LIST; i++)
	{
		PATH* path = getNextData(iterator);

		if (path == NULL)
		{
			removeView(mainPage, i, 0);
			TEXT* text = removeView(mainPage, i, 1);

			selectPathButtons[i - STARTING_POINT_OF_SEARCH_LIST]->funcInput = NULL;
			freeText(&text);
			continue;
		}

		removeView(mainPage, i, 0);
		TEXT* text = removeView(mainPage, i, 1);
		addView(mainPage, selectPathButtons[i - STARTING_POINT_OF_SEARCH_LIST]);
		addView(mainPage, generateText(pathToStr(path, NULL), 15, i));

		selectPathButtons[i - STARTING_POINT_OF_SEARCH_LIST]->funcInput = path;

		freeText(&text);
	}

	showPage(mainPage);

	freeIterator(&iterator);
}

void freeSearchResultList()
{
	if (searchResultList != NULL)
	{
		ITERATOR* iterator = generateIterator(searchResultList);

		for (PATH* path = getNextData(iterator); path != NULL; path = getNextData(iterator))
		{
			freePath(&path);
		}

		freeIterator(&iterator);
		freeLinkedList(&searchResultList);
	}
}

void sortSearchResultList()
{
	LINKED_LIST* searchResultListTemp = generateLinkedList();

	while (searchResultList->size != 0)
	{
		PATH* targetPath = NULL;
		ITERATOR* iterator = generateIterator(searchResultList);

		for (PATH* path = getNextData(iterator); path != NULL; path = getNextData(iterator))
		{
			if (targetPath == NULL)
			{
				targetPath = path;
				continue;
			}
			else
			{
				int flightTime = calculateTimeDifference(getArrivalTime(path), getDepartureTime(path));
				int targetFlightTime = calculateTimeDifference(getArrivalTime(targetPath), getDepartureTime(targetPath));

				if (flightTime < targetFlightTime)
				{
					targetPath = path;
					continue;
				}
				else if (flightTime == targetFlightTime)
				{
					if (compareTime(getDepartureTime(path), getDepartureTime(targetPath)) < 0)
					{
						targetPath = path;
						continue;
					}
				}
			}
		}

		removeFromList(searchResultList, targetPath);
		addToList(searchResultListTemp, targetPath);
		freeIterator(&iterator);
	}

	freeSearchResultList();
	searchResultList = searchResultListTemp;
}

void* searchPaths(void* ptr)
{
	if (strlen(sourceComboBox->input) == 0
		|| strlen(destinationComboBox->input) == 0
		|| strlen(departureDateComboBox->input) == 0
		|| strlen(seatClassComboBox->input) == 0)
	{
		deleteMessage();
		showMessage("����ִ� �׸��� �ֽ��ϴ�.");
		return;
	}

	if (!strcmp(sourceComboBox->input, destinationComboBox->input))
	{
		deleteMessage();
		showMessage("������� �������� �����ϴ�.");
		return;
	}

	CITY* source = findCityByChar(cityGraph, sourceComboBox->input[0]);
	CITY* destination = findCityByChar(cityGraph, destinationComboBox->input[0]);
	TIME* departureDate = strToTime(departureDateComboBox->input);

	if (!strcmp(seatClassComboBox->input, "�ϵ"))
	{
		seatClass = FIRST_CLASS;
	}
	else if (!strcmp(seatClassComboBox->input, "����Ͻ���"))
	{
		seatClass = BUSINESS_CLASS;
	}
	else
	{
		seatClass = ECONOMY_CLASS;
	}

	deleteMessage();
	showMessage("�˻���.. �ð��� �� �ɸ� �� �ֽ��ϴ�.");

	freeSearchResultList();
	searchResultList = findAllPath(flightList, departureDate, source, destination, seatClass);
	pageNumberOfSearchResult = 0;
	if (searchResultList != NULL)
	{
		sortSearchResultList();
	}

	showSearchResults();

	free(departureDate);
}

void* nextResult(void* ptr)
{
	pageNumberOfSearchResult++;

	showSearchResults();
}

void* previousResult(void* ptr)
{
	if (pageNumberOfSearchResult > 0)
	{
		pageNumberOfSearchResult--;
		showSearchResults();
	}
}

void showReservationDetail()
{
	char sexStr[5] = "";

	switch (reservationTemp->sex)
	{
	case MAN:
		strcat(sexStr, "����");
		break;

	case WOMAN:
		strcat(sexStr, "����");
		break;
	}

	char* firstNameViewStr = calloc(strlen(reservationTemp->firstName) + 1 + 8, sizeof(char));
	char* lastNameViewStr = calloc(strlen(reservationTemp->lastName) + 1 + 8, sizeof(char));
	char* sexViewStr = calloc(strlen(sexStr) + 1 + 8, sizeof(char));

	sprintf(lastNameViewStr, "��    : %s", reservationTemp->lastName);
	sprintf(firstNameViewStr, "�� �� : %s", reservationTemp->firstName);
	sprintf(sexViewStr, "�� �� : %s", sexStr);

	addView(reservationDetailPage, generateText(lastNameViewStr, 5, 3));
	addView(reservationDetailPage, generateText(firstNameViewStr, 5, 4));
	addView(reservationDetailPage, generateText(sexViewStr, 5, 5));
	addView(reservationDetailPage, generateText(reservationToStr(reservationTemp), 5, 8));

	{
		ITERATOR* iterator = generateIterator(reservationTemp->path->flightList);
		int line = 10;
		FLIGHT* previousFlight = NULL;

		for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator), line++)
		{
			addView(reservationDetailPage, generateText(flightToStr(flight, previousFlight, -1), 2, line));
			previousFlight = flight;
		}

		freeIterator(&iterator);
	}
}

void clearReservationDetail()
{
	for (int i = 3; i < 7; i++)
	{
		TEXT* text = removeView(reservationDetailPage, i, 0);

		freeText(&text);
	}

	for (int i = 8; i < 35; i++)
	{
		TEXT* text = removeView(reservationDetailPage, i, 0);

		freeText(&text);
	}
}

void* deleteReservation(void* ptr)
{
	removeFromRecord(record, reservationTemp);

	free(reservationTemp->firstName);
	free(reservationTemp->lastName);

	{
		ITERATOR* iterator = generateIterator(reservationTemp->path->flightList);

		for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
		{
			freeFlight(&flight);
		}

		freeIterator(&iterator);
		freePath(&(reservationTemp->path));
		free(reservationTemp);
	}

	clearReservationList();
	showReservationList();
	cancleReservationDetail(NULL);
}

void* cancleReservationDetail(void* ptr)
{
	clearReservationDetail();
	currentPage = reservationListPage;
	showPage(currentPage);
}

void showReservationList()
{
	LINKED_LIST* reservationList = listFromRecord(record);
	ITERATOR* iterator = generateIterator(reservationList);

	for (int i = 0; i < pageNumberOfReservationList; i++)
	{
		for (int j = 0; j < MAX_NUMBER_OF_RESULT; j++)
		{
			getNextData(iterator);

			// ���� ������ ���� �������� �Ѿ
			if (hasNextData(iterator) == 0)
			{
				pageNumberOfReservationList--;
				i = -1;
				freeIterator(&iterator);
				iterator = generateIterator(reservationList);
				break;
			}
		}
	}

	for (int i = STARTING_POINT_OF_SEARCH_LIST; i < MAX_NUMBER_OF_RESULT + STARTING_POINT_OF_SEARCH_LIST; i++)
	{
		RESERVATION* reservation = getNextData(iterator);

		if (reservation == NULL)
		{
			continue;
		}

		addView(reservationListPage, selectReservationButtons[i - STARTING_POINT_OF_SEARCH_LIST]);
		addView(reservationListPage, generateText(reservationToStr(reservation, NULL), 15, i));

		selectReservationButtons[i - STARTING_POINT_OF_SEARCH_LIST]->funcInput = reservation;
	}

	addView(reservationListPage, generateText(printTreeTraversal(record), 100, 1));

	showPage(currentPage);
	freeIterator(&iterator);
	freeLinkedList(&reservationList);
}

void clearReservationList()
{
	TEXT* text = removeView(reservationListPage, 1, 1);
	freeText(&text);

	for (int i = STARTING_POINT_OF_SEARCH_LIST; i < MAX_NUMBER_OF_RESULT + STARTING_POINT_OF_SEARCH_LIST; i++)
	{
		removeView(reservationListPage, i, 0);
		text = removeView(reservationListPage, i, 1);

		selectReservationButtons[i - STARTING_POINT_OF_SEARCH_LIST]->funcInput = NULL;
		freeText(&text);
	}
}


void* nextReservationList(void* ptr)
{
	pageNumberOfReservationList++;

	clearReservationList();
	showReservationList();
}

void* previousReservationList(void* ptr)
{
	if (pageNumberOfReservationList > 0)
	{
		pageNumberOfReservationList--;
		clearReservationList();
		showReservationList();
	}
}

void* goToReservationDetail(void* ptr)
{
	RESERVATION* reservation = ptr;
	reservationTemp = reservation;

	currentPage = reservationDetailPage;
	showReservationDetail();
	initPage(currentPage);
	showPage(currentPage);
}

void* cancleReservationList(void* ptr)
{
	clearReservationList();
	pageNumberOfReservationList = 0;
	currentPage = mainPage;
	showPage(currentPage);
}

void* cancleFlightInformation(void* ptr)
{
	clearFlightInformation();
	currentPage = mainPage;
	showPage(currentPage);
}

void* goToEnteringMemberInformation(void* ptr)
{
	currentPage = enteringMemberInformationPage;
	initPage(currentPage);
	showPage(currentPage);
}

void showFlightInformation()
{
	addView(flightInformationPage, generateText(pathToStr(selectedPath, seatClassComboBox->input), 5, 3));

	{
		ITERATOR* iterator = generateIterator(selectedPath->flightList);
		int line = 5;
		FLIGHT* previousFlight = NULL;

		for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator), line++)
		{
			addView(flightInformationPage, generateText(flightToStr(flight, previousFlight, seatClass), 2, line));
			previousFlight = flight;
		}

		freeIterator(&iterator);
	}
}

void clearFlightInformation()
{
	for (int i = 3; i < 35; i++)
	{
		TEXT* text = removeView(flightInformationPage, i, 0);

		freeText(&text);
	}
}



void showSeatSelection()
{
	FLIGHT* flight = getNextData(flightForSeatSelectionIterator);
	char* strOfAirplane = getStrOfAirplane(flight->airplane);
	char* textOfAirplaneInformation = calloc(strlen(strOfAirplane) + 8, sizeof(char));

	addView(seatSelectionPage, generateText(flightToStr(flight, NULL, seatClass), 35, 1));

	sprintf(textOfAirplaneInformation, "���� : %s", strOfAirplane);

	addView(seatSelectionPage, generateText(textOfAirplaneInformation, 1, 3));

	for (int col = 0; col < getColumnOfAirplaneSeat(flight->airplane, seatClass); col++)
	{
		char* seatNumber = calloc(3, sizeof(char));

		if (col + 1 < 10)
		{
			seatNumber[0] = ' ';
			seatNumber[1] = '0' + col + 1;
		}
		else
		{
			seatNumber[0] = '0' + ((col + 1) / 10);
			seatNumber[1] = '0' + ((col + 1) % 10);
		}

		addView(seatSelectionPage, generateText(seatNumber, 28, col + 4));
	}

	char* seatAlphabet = calloc(91, sizeof(char));

	for (int row = 0; row < getRowOfAirplaneSeat(flight->airplane, seatClass); row++)
	{
		seatAlphabet[row * 3] = 'A' + row;
		seatAlphabet[row * 3 + 1] = ' ';
		seatAlphabet[row * 3 + 2] = ' ';
	}

	addView(seatSelectionPage, generateText(seatAlphabet, 30, 3));

	for (int row = 0; row < getRowOfAirplaneSeat(flight->airplane, seatClass); row++)
	{
		for (int col = 0; col < getColumnOfAirplaneSeat(flight->airplane, seatClass); col++)
		{
			int seatAvailable = getSeatAvailable(flight->airplane, seatClass, row, col);

			if (seatAvailable == NO_SEAT)
			{
				addView(seatSelectionPage, generateCheckBox(CHECKED, UNCHANGEABLE, seatsCheckBox, 1, GRAY, row * 3 + 30, col + 4));
			}
			else
			{
				seatsCheckBox[row][col] = generateCheckBox(UNCHECKED, CHANGEABLE, seatsCheckBox, 1, LIGHT_WHITE, row * 3 + 30, col + 4);
				addView(seatSelectionPage, seatsCheckBox[row][col]);
			}
		}
	}

	seatSelectionButton->funcInput = flight;
}

void showCheckingAllInformation()
{
	char* lastName = lastNameEditText->input;
	char* firstName = firstNameEditText->input;
	char* sexStr = sexComboBox->input;

	char* lastNameClone = calloc(strlen(lastName) + 1, sizeof(char));
	char* firstNameClone = calloc(strlen(firstName) + 1, sizeof(char));
	int sex;

	strcpy(lastNameClone, lastName);
	strcpy(firstNameClone, firstName);

	if (!strcmp(sexStr, "����"))
	{
		sex = MAN;
	}
	else
	{
		sex = WOMAN;
	}

	reservationTemp = addToRecord(record, firstNameClone, lastNameClone, sex, generateDeepClonePath(selectedPath));

	{
		char* firstNameViewStr = calloc(strlen(firstNameClone) + 1 + 8, sizeof(char));
		char* lastNameViewStr = calloc(strlen(lastNameClone) + 1 + 8, sizeof(char));
		char* sexViewStr = calloc(strlen(sexStr) + 1 + 8, sizeof(char));

		sprintf(lastNameViewStr, "��    : %s", lastNameClone);
		sprintf(firstNameViewStr, "�� �� : %s", firstNameClone);
		sprintf(sexViewStr, "�� �� : %s", sexStr);

		addView(checkingAllInformationPage, generateText(lastNameViewStr, 5, 3));
		addView(checkingAllInformationPage, generateText(firstNameViewStr, 5, 4));
		addView(checkingAllInformationPage, generateText(sexViewStr, 5, 5));
		addView(checkingAllInformationPage, generateText(reservationToStr(reservationTemp), 5, 8));

		{
			ITERATOR* iterator = generateIterator(reservationTemp->path->flightList);
			int line = 10;
			FLIGHT* previousFlight = NULL;

			for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator), line++)
			{
				addView(checkingAllInformationPage, generateText(flightToStr(flight, previousFlight, -1), 2, line));
				previousFlight = flight;
			}

			freeIterator(&iterator);
		}
	}
}

void* goToCheckingAllInformation(void* ptr)
{
	currentPage = checkingAllInformationPage;
	showCheckingAllInformation();
	initPage(currentPage);
	showPage(currentPage);
}

void clearSeatSelection()
{
	TEXT* text = removeView(seatSelectionPage, 2, 0);
	freeText(&text);
	text = removeView(seatSelectionPage, 1, 1);
	freeText(&text);
	text = removeView(seatSelectionPage, 3, 0);
	freeText(&text);
	text = removeView(seatSelectionPage, 3, 1);
	freeText(&text);

	for (int row = 4; row < 4 + MAX_COLUMN_OF_CHECK_BOX_SET; row++)
	{
		for (int col = 0; col < MAX_ROW_OF_CHECK_BOX_SET + 2; col++)
		{
			VIEW* view = removeView(seatSelectionPage, row, col);

			if (view != NULL)
			{
				if (view->code == CHECK_BOX_CODE)
				{
					CHECK_BOX* checkBox = view;
					free(checkBox);
				}
				else if (view->code == TEXT_CODE)
				{
					freeText(&view);
				}
			}
		}
	}

	for (int row = 0; row < MAX_ROW_OF_CHECK_BOX_SET; row++)
	{
		for (int col = 0; col < MAX_COLUMN_OF_CHECK_BOX_SET; col++)
		{
			seatsCheckBox[row][col] = NULL;
		}
	}
}

void* selectSeat(void* ptr)
{
	FLIGHT* flight = ptr;
	int isChecked = 0;

	for (int row = 0; row < getRowOfAirplaneSeat(flight->airplane, seatClass); row++)
	{
		for (int col = 0; col < getColumnOfAirplaneSeat(flight->airplane, seatClass); col++)
		{
			if (seatsCheckBox[row][col] != NULL)
			{
				if (seatsCheckBox[row][col]->isChecked == CHECKED)
				{
					setSeat(flight, seatClass, row, col, SEAT_AVAILABLE);
					isChecked = 1;
					break;
				}
			}
		}
	}

	if (isChecked == 0)
	{
		deleteMessage();
		showMessage("�¼��� �����ؾ� �մϴ�.");
		return;
	}

	if (hasNextData(flightForSeatSelectionIterator))
	{
		clearSeatSelection();
		showSeatSelection();
		showPage(currentPage);
	}
	else
	{
		clearSeatSelection();
		goToCheckingAllInformation(NULL);
	}
}

void* goToSeatSelection(void* ptr)
{
	if (strlen(lastNameEditText->input) != 0 && strlen(firstNameEditText->input) != 0 && strlen(sexComboBox->input) != 0)
	{
		freeIterator(&flightForSeatSelectionIterator);
		flightForSeatSelectionIterator = generateIterator(selectedPath->flightList);
	}

	showSeatSelection();

	currentPage = seatSelectionPage;
	initPage(currentPage);
	showPage(currentPage);
}

void* cancleEnteringMemberInformation(void* ptr)
{
	currentPage = flightInformationPage;
	showPage(currentPage);
}

void clearCheckingAllInformation()
{
	for (int i = 3; i < 7; i++)
	{
		TEXT* text = removeView(checkingAllInformationPage, i, 0);

		freeText(&text);
	}

	for (int i = 8; i < 35; i++)
	{
		TEXT* text = removeView(checkingAllInformationPage, i, 0);

		freeText(&text);
	}
}

void* reservateFlight(void* ptr)
{
	ITERATOR* iterator = generateIterator(reservationTemp->path->flightList);

	for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
	{
		setSeat(flight, flight->seatClass, flight->seatRowNumber, flight->seatColumnNumber, NO_SEAT);
	}

	freeIterator(&iterator);

	clearFlightInformation();
	clearSeatSelection();
	clearCheckingAllInformation();

	currentPage = mainPage;
	showPage(currentPage);
}

void* cancleCheckingAllInformation(void* ptr)
{
	clearCheckingAllInformation();
	removeFromRecord(record, reservationTemp);
	goToSeatSelection(NULL);
	currentPage = seatSelectionPage;

	free(reservationTemp->firstName);
	free(reservationTemp->lastName);

	{
		ITERATOR* iterator = generateIterator(reservationTemp->path->flightList);

		for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
		{
			freeFlight(&flight);
		}

		freeIterator(&iterator);
		freePath(&(reservationTemp->path));
		free(reservationTemp);
	}

	record->nextReservationNumber--;
}

void* cancleSeatSelection(void* ptr)
{
	clearSeatSelection();

	currentPage = enteringMemberInformationPage;
	showPage(currentPage);
}

void* goToReservationList(void* ptr)
{
	currentPage = reservationListPage;
	initPage(currentPage);
	showReservationList();
}