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
PAGE* flightInformationPage;
PAGE* enteringMemberInformationPage;
PAGE* seatSelectionPage;
PAGE* checkingAllInformation;

COMBO_BOX* sourceComboBox;
COMBO_BOX* destinationComboBox;
COMBO_BOX* departureDateComboBox;
COMBO_BOX* seatClassComboBox;
EDIT_TEXT* lastNameEditText;
EDIT_TEXT* firstNameEditText;
COMBO_BOX* sexComboBox;

int seatClass;
PATH* selectedPath;

LINKED_LIST* searchResultList;
int pageNumberOfSearchResult;

BUTTON* selectButtons[MAX_NUMBER_OF_RESULT];
BUTTON* reservationButton;

void* goToFlightInformation(void* ptr)
{
	PATH* path = ptr;
	selectedPath = path;

	currentPage = flightInformationPage;
	addView(flightInformationPage, generateText(pathToStr(path, seatClassComboBox->input), 5, 3));

	{
		ITERATOR* iterator = generateIterator(path->flightList);
		int line = 5;
		FLIGHT* previousFlight = NULL;

		for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator), line++)
		{
			addView(flightInformationPage, generateText(flightToStr(flight, previousFlight, seatClass), 2, line));
			previousFlight = flight;
		}

		freeIterator(&iterator);
	}

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

			selectButtons[i - STARTING_POINT_OF_SEARCH_LIST]->funcInput = NULL;
			freeText(&text);
		}

		showPage(mainPage);
		return;
	}

	ITERATOR* iterator = generateIterator(searchResultList);

	for (int i = 0; i < pageNumberOfSearchResult; i++)
	{
		for (int j = 0; j < MAX_NUMBER_OF_RESULT; j++)
		{
			PATH* path = getNextData(iterator);

			// ���� ������ ���� �������� �Ѿ
			if (path == NULL)
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

			selectButtons[i - STARTING_POINT_OF_SEARCH_LIST]->funcInput = NULL;
			freeText(&text);
			continue;
		}

		removeView(mainPage, i, 0);
		TEXT* text = removeView(mainPage, i, 1);
		addView(mainPage, selectButtons[i - STARTING_POINT_OF_SEARCH_LIST]);
		addView(mainPage, generateText(pathToStr(path, NULL), 15, i));

		selectButtons[i - STARTING_POINT_OF_SEARCH_LIST]->funcInput = path;

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
		return;
	}

	if (!strcmp(sourceComboBox->input, destinationComboBox->input))
	{
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
	showMessage("�˻���..");
	
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

//-- flightInformationPage�� ��ư�� ���� �Լ�
void* cancleFlightInformation(void* ptr)
{
	for (int i = 3; i < 35; i++)
	{
		TEXT* text = removeView(flightInformationPage, i, 0);

		freeText(&text);
	}

	currentPage = mainPage;
	showPage(currentPage);
}

void* goToEnteringMemberInformation(void* ptr)
{
	currentPage = enteringMemberInformationPage;
	initPage(currentPage);
	showPage(currentPage);
}

//-- enteringMemberInformationPage�� ��ư�� ���� �Լ�
void* goToSeatSelection(void* ptr)
{
	if (strlen(lastNameEditText->input) != 0 && strlen(firstNameEditText->input) != 0 && strlen(sexComboBox->input) != 0)
	{
		ITERATOR* iterator = generateIterator(selectedPath->flightList);

		for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
		{
			int** seats;
			char* strOfAirplane = getStrOfAirplane(flight->airplane);
			char* textOfAirplaneInformation = calloc(strlen(strOfAirplane) + 8, sizeof(char));

			sprintf(textOfAirplaneInformation, "���� : %s", strOfAirplane);

			addView(seatSelectionPage, generateText(textOfAirplaneInformation, 1, 3));

			switch (seatClass)
			{
				case FIRST_CLASS:
					seats = flight->airplane->firstClass;
					break;

				case BUSINESS_CLASS:
					seats = flight->airplane->businessClass;
					break;

				case ECONOMY_CLASS:
					seats = flight->airplane->economyClass;
					break;
			}

			
		}

		freeIterator(iterator);
	}
}

void* cancleEnteringMemberInformation(void* ptr)
{
	currentPage = flightInformationPage;
	showPage(currentPage);
}

//-- seatSelectionPage�� ��ư�� ���� �Լ� --
void* goToCheckingAllInformation(void* ptr)
{

}

void* cancleSeatSelection(void* ptr)
{

}

void init()
{
	system("mode con cols=120 lines=40");

	changeColor(LIGHT_WHITE, BLACK);

	cityGraph = initCityGraph();

	for (int i = 0; i < DAY_OF_MONTH; i++)
	{
		flightList[i] = initflightList(cityGraph, i + 1);
	}

	record = initReservationRecord(flightList, cityGraph);

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
		addView(mainPage, generateButton("���� ������", previousResult, NULL, 30, 4));
		addView(mainPage, generateButton("���� ������", nextResult, NULL, 50, 4));

		for (int i = 0; i < MAX_NUMBER_OF_RESULT; i++)
		{
			selectButtons[i] = generateButton("����", goToFlightInformation, NULL, 1, i + STARTING_POINT_OF_SEARCH_LIST);
		}
	}

	// flightInformationPage ����
	{
		flightInformationPage = generatePage();
		addView(flightInformationPage, generateText("����� ���� Ȯ��-��-��-��", 1, 1));
		reservationButton = generateButton("�����ϱ�", goToEnteringMemberInformation, NULL, 30, 35);
		addView(flightInformationPage, reservationButton);
		addView(flightInformationPage, generateButton("�ڷ�", cancleFlightInformation, NULL, 50, 35));
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
		addView(enteringMemberInformationPage, generateButton("���", goToSeatSelection, NULL, 30, 35));
		addView(enteringMemberInformationPage, generateButton("�ڷ�", cancleEnteringMemberInformation, NULL, 50, 35));
	}

	// seatSelectionPage ����
	{
		seatSelectionPage = generatePage();
		addView(seatSelectionPage, generateText("��-��-���¼� ����-��", 1, 1));
		addView(seatSelectionPage, generateButton("���� �Ϸ�", goToCheckingAllInformation, NULL, 30, 35));
		addView(seatSelectionPage, generateButton("�ڷ�", cancleSeatSelection, NULL, 50, 35));
	}

	// checkingAllInformationPage ����
	{
		checkingAllInformation = generatePage();
		addView(checkingAllInformation, generateText("��-��-��-������ Ȯ�� �� ���� �Ϸ�", 1, 1));
	}
}

void showMain()
{
	init();

	//addView(mainPage, generateButton("button", showSelect, 1, 1));
	//addView(mainPage, generateButton("button", showSelect, 20, 1));
	//addView(mainPage, generateButton("button", showSelect, 1, 2));
	//addView(mainPage, generateText("�װ��� �˻�", 0, 0));
	//addView(mainPage, generateText("text", 1, 6));

	/*for (int i = 0; i < DAY_OF_MONTH; i++)
	{
		ITERATOR* iterator = generateIterator(flightList[i]);

		for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
		{
			char* departureTime = timeToStr(flight->departureTime);
			char* arrivalTime = timeToStr(flight->arrivalTime);

			printf("����� : %c, ������ : %c, ", flight->source->name, flight->destination->name);
			printf("��� �ð� : %s, ", departureTime);
			printf("���� �ð� : %s\n", arrivalTime);

			free(departureTime);
			free(arrivalTime);
		}

		freeIterator(&iterator);
	}

	getch();*/

	initPage(mainPage);
	showPage(mainPage);

	currentPage = mainPage;

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

