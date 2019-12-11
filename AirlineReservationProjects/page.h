#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "consoleControl.h"

// EDIT_TEXT 등의 input에 대한 방식을 바꾸도록 한다.

#define BUTTON_CODE 1
#define EDIT_TEXT_CODE 2
#define TEXT_CODE 3
#define COMBO_BOX_CODE 4
#define CHECK_BOX_CODE 5

#define MAX_ROW_OF_VIEW 40
#define MAX_COLUMN_OF_VIEW 10

#define CHANGEABLE 1
#define UNCHANGEABLE 0

#define CHECKED 1
#define UNCHECKED 0

typedef struct view
{
	int code;
	int x;
	int y;
} VIEW;

typedef struct page
{
	VIEW* view[MAX_ROW_OF_VIEW][MAX_COLUMN_OF_VIEW];
	VIEW* currentView;
} PAGE;

typedef struct button
{
	int code;
	int x;
	int y;
	char* text;
	void* (*functionToCall)(void*);
	void* funcInput;
} BUTTON;

typedef struct editText
{
	int code;
	int x;
	int y;
	char* text;
	char* input;
} EDIT_TEXT;

typedef struct text
{
	int code;
	int x;
	int y;
	char* text;
} TEXT;

typedef struct comboBox
{
	int code;
	int x;
	int y;
	char* text;
	char* input;
	char** choice;
} COMBO_BOX;

typedef struct checkBox
{
	int code;
	int x;
	int y;
	int isChecked;
	int isChangeable;
} CHECK_BOX;

// ------ PAGE관련 함수 ------
/*
PAGE 구조체를 만들어 초기화하고 반환한다. */
PAGE* generatePage();

/*
page에 view를 추가한다. */
void addView(PAGE* page, VIEW* view);

/*
page의 row열, column행의 VIEW를 제거하고 메모리를 해제한다. */
VIEW* removeView(PAGE* page, int row, int column);

/*
page를 초기화한다. 
page의 currentView를 초기화하거나, 내부 VIEW들 중 EDIT_TEXT의 입력칸을 지운다*/
void initPage(PAGE* page);

/*
page에 담긴 VIEW들을 각자의 위치에 띄워서 보여준다. */
void showPage(PAGE* page);

/*
direction을 입력받아 page의 currentView를 바꾼다. */
void moveTo(PAGE* page);

/*
화면 최하단에 메세지를 띄운다. */
void showMessage(char* message);

/*
화면 최하단의 메세지를 지운다. */
void deleteMessage();


// ------ BUTTON관련 함수 ------
/*
BUTTON 구조체를 만들어 초기화하고 반환한다. */
BUTTON* generateButton(char* text, void (*functionToCall)(), void* funcInput, int x, int y);

/*
button의 functionToCall 함수 포인터를 호출한다.*/
void* pressButton(BUTTON* button);

/*
button을 콘솔에 표시한다. */
void showButton(BUTTON* button); //헤더에서 지워야함

/*
선택된 button을 콘솔에 표시한다*/
void showActiveButton(BUTTON* button);

/*
button의 메모리를 해제한다. */
void freeButton(BUTTON** button);


// ------ EDIT_TEXT관련 함수 ------
/*
EDIT_TEXT 구조체를 만들어 초기화하고 반환한다. 
input에는 문자열 포인터의 주소값을 넘겨받는다.
해당 문자열 포인터는 입력값을 저장한다. */
EDIT_TEXT* generateEditText(char* text, int x, int y);

/*
문자 c를 입력받아 edit_text의 input 문자열을 변경한다.
이 함수는 백스페이스도 입력받는다. 이 경우, 문자열의 끝부터 하나씩 지운다.
또, showEditText를 호출하여 갱신하고, 문자열의 끝으로 커서를 맞춘다. */
void editText(EDIT_TEXT* editText, char c);
						
/*
editText를 콘솔에 표시한다. */
void showEditText(EDIT_TEXT* editText); //헤더에서 지워야함

/*
선택된 editText를 콘솔에 표시한다. */
void showActiveEditText(EDIT_TEXT* editText);

/*
button의 메모리를 해제한다. */
void freeEditText(EDIT_TEXT** editText);

// ------ TEXT관련 함수 ------
/*
TEXT 구조체를 만들어 초기화하고 반환한다. */
TEXT* generateText(char* text, int x, int y);

/*
text를 콘솔에 표시한다. */
void showText(TEXT* text); //헤더에서 지워야함

/*
text의 메모리를 해제한다. */
void freeText(TEXT** text);

// ------ COMBO_BOX관련 함수 ------
/*
COMBO_BOX 구조체를 만들어 초기화하고 반환한다. 
input에는 문자열 포인터의 주소값을 넘겨받는다.
해당 문자열 포인터는 입력값을 저장한다. 
choice는 선택 목록들을 저장해두는 문자열 포인터의 배열이다.
choice의 끝은 반드시 NULL이어야 한다. */
COMBO_BOX* generateComboBox(char* text, char** choice, int x, int y);

/*
comboBox를 콘솔에 표시한다. */
void showComboBox(COMBO_BOX* comboBox);

/*
선택된 comboBox를 콘솔에 표시한다. */
void showActiveComboBox(COMBO_BOX* comboBox);

/*
comboBox의 목록을 띄우고, 입력를 받아 고를 수 있게한다. */
void openComboBox(COMBO_BOX* comboBox);

/*
text의 메모리를 해제한다. */
void freeComboBox(COMBO_BOX** comboBox);

// ------ CHECK_BOX관련 함수 ------
CHECK_BOX* generateCheckBox(int isChecked, int isChangeable, int x, int y);

void showCheckBox(CHECK_BOX* checkBox);

void showActiveCheckBox(CHECK_BOX* checkBox);

void clickCheckBox(CHECK_BOX* checkBox);