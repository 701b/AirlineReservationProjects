#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "consoleControl.h"

// EDIT_TEXT ���� input�� ���� ����� �ٲٵ��� �Ѵ�.

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

// ------ PAGE���� �Լ� ------
/*
PAGE ����ü�� ����� �ʱ�ȭ�ϰ� ��ȯ�Ѵ�. */
PAGE* generatePage();

/*
page�� view�� �߰��Ѵ�. */
void addView(PAGE* page, VIEW* view);

/*
page�� row��, column���� VIEW�� �����ϰ� �޸𸮸� �����Ѵ�. */
VIEW* removeView(PAGE* page, int row, int column);

/*
page�� �ʱ�ȭ�Ѵ�. 
page�� currentView�� �ʱ�ȭ�ϰų�, ���� VIEW�� �� EDIT_TEXT�� �Է�ĭ�� �����*/
void initPage(PAGE* page);

/*
page�� ��� VIEW���� ������ ��ġ�� ����� �����ش�. */
void showPage(PAGE* page);

/*
direction�� �Է¹޾� page�� currentView�� �ٲ۴�. */
void moveTo(PAGE* page);

/*
ȭ�� ���ϴܿ� �޼����� ����. */
void showMessage(char* message);

/*
ȭ�� ���ϴ��� �޼����� �����. */
void deleteMessage();


// ------ BUTTON���� �Լ� ------
/*
BUTTON ����ü�� ����� �ʱ�ȭ�ϰ� ��ȯ�Ѵ�. */
BUTTON* generateButton(char* text, void (*functionToCall)(), void* funcInput, int x, int y);

/*
button�� functionToCall �Լ� �����͸� ȣ���Ѵ�.*/
void* pressButton(BUTTON* button);

/*
button�� �ֿܼ� ǥ���Ѵ�. */
void showButton(BUTTON* button); //������� ��������

/*
���õ� button�� �ֿܼ� ǥ���Ѵ�*/
void showActiveButton(BUTTON* button);

/*
button�� �޸𸮸� �����Ѵ�. */
void freeButton(BUTTON** button);


// ------ EDIT_TEXT���� �Լ� ------
/*
EDIT_TEXT ����ü�� ����� �ʱ�ȭ�ϰ� ��ȯ�Ѵ�. 
input���� ���ڿ� �������� �ּҰ��� �Ѱܹ޴´�.
�ش� ���ڿ� �����ʹ� �Է°��� �����Ѵ�. */
EDIT_TEXT* generateEditText(char* text, int x, int y);

/*
���� c�� �Է¹޾� edit_text�� input ���ڿ��� �����Ѵ�.
�� �Լ��� �齺���̽��� �Է¹޴´�. �� ���, ���ڿ��� ������ �ϳ��� �����.
��, showEditText�� ȣ���Ͽ� �����ϰ�, ���ڿ��� ������ Ŀ���� �����. */
void editText(EDIT_TEXT* editText, char c);
						
/*
editText�� �ֿܼ� ǥ���Ѵ�. */
void showEditText(EDIT_TEXT* editText); //������� ��������

/*
���õ� editText�� �ֿܼ� ǥ���Ѵ�. */
void showActiveEditText(EDIT_TEXT* editText);

/*
button�� �޸𸮸� �����Ѵ�. */
void freeEditText(EDIT_TEXT** editText);

// ------ TEXT���� �Լ� ------
/*
TEXT ����ü�� ����� �ʱ�ȭ�ϰ� ��ȯ�Ѵ�. */
TEXT* generateText(char* text, int x, int y);

/*
text�� �ֿܼ� ǥ���Ѵ�. */
void showText(TEXT* text); //������� ��������

/*
text�� �޸𸮸� �����Ѵ�. */
void freeText(TEXT** text);

// ------ COMBO_BOX���� �Լ� ------
/*
COMBO_BOX ����ü�� ����� �ʱ�ȭ�ϰ� ��ȯ�Ѵ�. 
input���� ���ڿ� �������� �ּҰ��� �Ѱܹ޴´�.
�ش� ���ڿ� �����ʹ� �Է°��� �����Ѵ�. 
choice�� ���� ��ϵ��� �����صδ� ���ڿ� �������� �迭�̴�.
choice�� ���� �ݵ�� NULL�̾�� �Ѵ�. */
COMBO_BOX* generateComboBox(char* text, char** choice, int x, int y);

/*
comboBox�� �ֿܼ� ǥ���Ѵ�. */
void showComboBox(COMBO_BOX* comboBox);

/*
���õ� comboBox�� �ֿܼ� ǥ���Ѵ�. */
void showActiveComboBox(COMBO_BOX* comboBox);

/*
comboBox�� ����� ����, �Է¸� �޾� �� �� �ְ��Ѵ�. */
void openComboBox(COMBO_BOX* comboBox);

/*
text�� �޸𸮸� �����Ѵ�. */
void freeComboBox(COMBO_BOX** comboBox);

// ------ CHECK_BOX���� �Լ� ------
CHECK_BOX* generateCheckBox(int isChecked, int isChangeable, int x, int y);

void showCheckBox(CHECK_BOX* checkBox);

void showActiveCheckBox(CHECK_BOX* checkBox);

void clickCheckBox(CHECK_BOX* checkBox);