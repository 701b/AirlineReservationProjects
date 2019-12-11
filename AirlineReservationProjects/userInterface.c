#define _CRT_SECURE_NO_WARNINGS

#include "userInterface.h"

#define DAY_OF_MONTH 31

#define MAX_NUMBER_OF_RESULT 25

#define MAX_SPACE_BETWEEN_CITY_AND_TIME 16
#define MAX_SPACE_BETWEEN_TIME_AND_TIME 30

#define STARTING_POINT_OF_SEARCH_LIST 6

char* cityChoice[27] = { "a 시", "b 시", "c 시", "d 시", "e 시", "f 시", "g 시",
							"h 시", "i 시", "j 시", "k 시", "l 시", "m 시", "n 시",
							"o 시", "p 시", "q 시", "r 시", "s 시", "t 시", "u 시",
							"v 시", "w 시", "x 시", "y 시", "z 시", NULL };
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
char* classChoice[4] = { "일등석", "비즈니스석", "일반석", NULL };
char* sexChoice[3] = { "남성", "여성", NULL };

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

			// 끝을 만나면 이전 페이지로 넘어감
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

	if (!strcmp(seatClassComboBox->input, "일등석"))
	{
		seatClass = FIRST_CLASS;
	}
	else if (!strcmp(seatClassComboBox->input, "비즈니스석"))
	{
		seatClass = BUSINESS_CLASS;
	}
	else
	{
		seatClass = ECONOMY_CLASS;
	}

	deleteMessage();
	showMessage("검색중..");
	
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

//-- flightInformationPage의 버튼에 사용될 함수
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

//-- enteringMemberInformationPage의 버튼에 사용될 함수
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

			sprintf(textOfAirplaneInformation, "기종 : %s", strOfAirplane);

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

//-- seatSelectionPage의 버튼에 사용될 함수 --
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

	// mainPage 제작
	{
		mainPage = generatePage();
		sourceComboBox = generateComboBox("출발지", cityChoice, 1, 1);
		destinationComboBox = generateComboBox("도착지", cityChoice, 21, 1);
		departureDateComboBox = generateComboBox("출발 날짜", dateChoice, 41, 1);
		seatClassComboBox = generateComboBox("좌석 등급", classChoice, 61, 1);

		addView(mainPage, sourceComboBox);
		addView(mainPage, destinationComboBox);
		addView(mainPage, departureDateComboBox);
		addView(mainPage, seatClassComboBox);
		addView(mainPage, generateButton("항공권 검색", searchPaths, NULL, 81, 1));
		addView(mainPage, generateButton("이전 페이지", previousResult, NULL, 30, 4));
		addView(mainPage, generateButton("다음 페이지", nextResult, NULL, 50, 4));

		for (int i = 0; i < MAX_NUMBER_OF_RESULT; i++)
		{
			selectButtons[i] = generateButton("선택", goToFlightInformation, NULL, 1, i + STARTING_POINT_OF_SEARCH_LIST);
		}
	}

	// flightInformationPage 제작
	{
		flightInformationPage = generatePage();
		addView(flightInformationPage, generateText("①운항 정보 확인-②-③-④", 1, 1));
		reservationButton = generateButton("예약하기", goToEnteringMemberInformation, NULL, 30, 35);
		addView(flightInformationPage, reservationButton);
		addView(flightInformationPage, generateButton("뒤로", cancleFlightInformation, NULL, 50, 35));
	}

	// enteringMemberInformationPage 제작
	{
		enteringMemberInformationPage = generatePage();
		lastNameEditText = generateEditText("성", 5, 3);
		firstNameEditText = generateEditText("이름", 25, 3);
		sexComboBox = generateComboBox("승객 구분", sexChoice, 45, 3);

		addView(enteringMemberInformationPage, generateText("①-②회원 정보 입력-③-④", 1, 1));
		addView(enteringMemberInformationPage, lastNameEditText);
		addView(enteringMemberInformationPage, firstNameEditText);
		addView(enteringMemberInformationPage, sexComboBox);
		addView(enteringMemberInformationPage, generateButton("계속", goToSeatSelection, NULL, 30, 35));
		addView(enteringMemberInformationPage, generateButton("뒤로", cancleEnteringMemberInformation, NULL, 50, 35));
	}

	// seatSelectionPage 제작
	{
		seatSelectionPage = generatePage();
		addView(seatSelectionPage, generateText("①-②-③좌석 선택-④", 1, 1));
		addView(seatSelectionPage, generateButton("선택 완료", goToCheckingAllInformation, NULL, 30, 35));
		addView(seatSelectionPage, generateButton("뒤로", cancleSeatSelection, NULL, 50, 35));
	}

	// checkingAllInformationPage 제작
	{
		checkingAllInformation = generatePage();
		addView(checkingAllInformation, generateText("①-②-③-④정보 확인 및 예약 완료", 1, 1));
	}
}

void showMain()
{
	init();

	//addView(mainPage, generateButton("button", showSelect, 1, 1));
	//addView(mainPage, generateButton("button", showSelect, 20, 1));
	//addView(mainPage, generateButton("button", showSelect, 1, 2));
	//addView(mainPage, generateText("항공권 검색", 0, 0));
	//addView(mainPage, generateText("text", 1, 6));

	/*for (int i = 0; i < DAY_OF_MONTH; i++)
	{
		ITERATOR* iterator = generateIterator(flightList[i]);

		for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
		{
			char* departureTime = timeToStr(flight->departureTime);
			char* arrivalTime = timeToStr(flight->arrivalTime);

			printf("출발지 : %c, 도착지 : %c, ", flight->source->name, flight->destination->name);
			printf("출발 시간 : %s, ", departureTime);
			printf("도착 시간 : %s\n", arrivalTime);

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

