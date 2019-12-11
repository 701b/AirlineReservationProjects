#define _CRT_SECURE_NO_WARNINGS

#include "page.h"

#define BACK_SPACE 8

#define UP 72
#define LEFT 75
#define DOWN 80
#define RIGHT 77

#define EDIT_TEXT_INPUT_MESSAGE "::"
#define COMBO_BOX_INPUT_MESSAGE "▼"

#define MAX_LENGTH_OF_INPUT_TEXT 15
#define MAX_LINE_OF_COMBO_BOX 5

PAGE* generatePage()
{ 
	PAGE* page = malloc(sizeof(PAGE));

	page->currentView = NULL;

	for (int i = 0; i < MAX_ROW_OF_VIEW; i++)
	{
		for (int j = 0; j < MAX_COLUMN_OF_VIEW; j++)
		{
			page->view[i][j] = NULL;
		}
	}

	return page;
}

void addView(PAGE* page, VIEW* view)
{
	for (int i = 0; i < MAX_COLUMN_OF_VIEW; i++)
	{
		VIEW* viewToCompare = page->view[view->y][i];

		if (viewToCompare == NULL)
		{
			page->view[view->y][i] = view;
			break;
		}

		if (view->x < viewToCompare->x)
		{
			for (int j = MAX_COLUMN_OF_VIEW; j > i; j--)
			{
				page->view[view->y][j] = page->view[view->y][j - 1];
			}

			page->view[view->y][i] = view;
			break;
		}
		else if (view->x == viewToCompare->x)
		{
			printf("Error : view가 겹침.");
			exit(0);
		}
	}
}

VIEW* removeView(PAGE* page, int row, int column)
{
	VIEW* view = page->view[row][column];

	page->view[row][column] = NULL;

	return view;
}

void initPage(PAGE* page)
{
	int isCurrentViewInitiated = 0;

	for (int row = 0; row < MAX_ROW_OF_VIEW; row++)
	{
		for (int column = 0; column < MAX_COLUMN_OF_VIEW; column++)
		{
			VIEW* view = page->view[row][column];

			if (view != NULL)
			{
				if (!isCurrentViewInitiated && view->code != TEXT_CODE)
				{
					isCurrentViewInitiated = 1;
					page->currentView = view;
				}

				if (view->code == EDIT_TEXT_CODE || view->code == COMBO_BOX_CODE)
				{
					char* str = ((EDIT_TEXT*)view)->input;

					for (int i = 0; str[i] != '\0'; i++)
					{
						str[i] = '\0';
					}
				}
			}
		}
	}
}

void showPage(PAGE* page)
{
	system("cls");

	for (int row = 0; row < MAX_ROW_OF_VIEW; row++)
	{
		for (int column = 0; column < MAX_COLUMN_OF_VIEW; column++)
		{
			VIEW* view = page->view[row][column];

			if (view == NULL)
			{
				break;
			}

			switch (view->code)
			{
				case BUTTON_CODE:
					showButton(view);
					break;

				case EDIT_TEXT_CODE:
					showEditText(view);
					break;

				case TEXT_CODE:
					showText(view);
					break;

				case COMBO_BOX_CODE:
					showComboBox(view);
					break;

				case CHECK_BOX_CODE:
					showCheckBox(view);
					break;
			}
		}
	}

	switch (page->currentView->code)
	{
		case BUTTON_CODE:
			showActiveButton(page->currentView);
			break;

		case EDIT_TEXT_CODE:
			showActiveEditText(page->currentView);
			break;

		case COMBO_BOX_CODE:
			showActiveComboBox(page->currentView);
			break;

		case CHECK_BOX_CODE:
			showActiveCheckBox(page->currentView);
			break;
	}
}

void moveTo(PAGE* page)
{
	VIEW* currentView = page->currentView;
	char direction = getch();
	int currentRow = currentView->y;
	int currentColumn;
	int row;
	int column;

	for (int col = 0; col < MAX_COLUMN_OF_VIEW && page->view[currentRow][col] != NULL; col++)
	{
		if (currentView == page->view[currentRow][col])
		{
			currentColumn = col;
			break;
		}
	}

	row = currentRow;
	column = currentColumn;

	switch (currentView->code)
	{
		case BUTTON_CODE:
			showButton(currentView);
			break;

		case EDIT_TEXT_CODE:
			showEditText(currentView);
			break;

		case COMBO_BOX_CODE:
			showComboBox(currentView);
			break;

		case CHECK_BOX_CODE:
			showCheckBox(currentView);
			break;
	}

	do
	{
		switch (direction)
		{
			case LEFT:
				if (column == 0)
				{
					page->currentView = currentView;
					break;
				}

				page->currentView = page->view[row][column - 1];
				column -= 1;
				break;

			case RIGHT:
				if (column == MAX_COLUMN_OF_VIEW - 1)
				{
					page->currentView = currentView;
					break;
				}

				page->currentView = page->view[row][column + 1];
				column += 1;
				break;

			case UP:
				if (row == 0)
				{
					page->currentView = currentView;
					break;
				}

				page->currentView = page->view[row - 1][0];
				row -= 1;
				break;

			case DOWN:
				if (row == MAX_ROW_OF_VIEW - 1)
				{
					page->currentView = currentView;
					break;
				}

				page->currentView = page->view[row + 1][0];
				row += 1;
				break;
		}
	} while (page->currentView == NULL 
			|| (page->currentView->code != BUTTON_CODE && page->currentView->code != EDIT_TEXT_CODE && page->currentView->code != COMBO_BOX_CODE && page->currentView->code != CHECK_BOX_CODE));

	switch (page->currentView->code)
	{
		case BUTTON_CODE:
			showActiveButton(page->currentView);
			break;

		case EDIT_TEXT_CODE:
			showActiveEditText(page->currentView);
			break;

		case COMBO_BOX_CODE:
			showActiveComboBox(page->currentView);
			break;

		case CHECK_BOX_CODE:
			showActiveCheckBox(page->currentView);
			break;
	}
}

void showMessage(char* message)
{
	gotoxy(0, 39);
	printf("%s", message);
}

void deleteMessage()
{
	gotoxy(0, 39);
	printf("                                                                                                   ");
}

BUTTON* generateButton(char* text, void(*functionToCall)(), void* funcInput, int x, int y)
{
	BUTTON* button = malloc(sizeof(BUTTON));

	button->code = BUTTON_CODE;
	button->text = text;
	button->functionToCall = functionToCall;
	button->funcInput = funcInput;
	button->x = x;
	button->y = y;

	return button;
}

void* pressButton(BUTTON* button)
{
	return button->functionToCall(button->funcInput);
}

void showButton(BUTTON* button)
{
	gotoxy(button->x, button->y);
	printf("< %s >", button->text);
}

void showActiveButton(BUTTON* button)
{
	changeColor(BLACK, LIGHT_WHITE);
	showButton(button);
	changeColor(LIGHT_WHITE, BLACK);

	deleteMessage();
	showMessage("방향키를 통해 이동할 수 있습니다. 엔터를 눌러 상호작용할 수 있습니다.");
}

void freeButton(BUTTON** button)
{
	if (*button != NULL)
	{
		free((*button)->text);
		free(*button);
		*button = NULL;
	}
}

EDIT_TEXT* generateEditText(char* text, int x, int y)
{
	EDIT_TEXT* editText = malloc(sizeof(EDIT_TEXT));

	editText->code = EDIT_TEXT_CODE;
	editText->input = calloc(MAX_LENGTH_OF_INPUT_TEXT + 1, sizeof(char));
	editText->text = text;
	editText->x = x;
	editText->y = y;

	return editText;
}

void editText(EDIT_TEXT* editText, char c)
{
	changeColor(BLACK, LIGHT_WHITE);
	gotoxy(editText->x + strlen(EDIT_TEXT_INPUT_MESSAGE), editText->y + 1);

	if (c == BACK_SPACE)
	{
		editText->input[strlen(editText->input) - 1] = '\0';
	}
	else if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || (c <= '9' && c >= '0'))
	{
		if (strlen(editText->input) < MAX_LENGTH_OF_INPUT_TEXT)
		{
			editText->input[strlen(editText->input)] = c;
		}
	}

	printf("%s ", editText->input);
	changeColor(LIGHT_WHITE, BLACK);

	gotoxy(editText->x + strlen(EDIT_TEXT_INPUT_MESSAGE) + strlen(editText->input), editText->y + 1);
}

void showEditText(EDIT_TEXT* editText)
{
	gotoxy(editText->x, editText->y);
	printf("-- %s ", editText->text);

	for (int i = 0; i < MAX_LENGTH_OF_INPUT_TEXT + strlen(EDIT_TEXT_INPUT_MESSAGE) - 4 - strlen(editText->text); i++)
	{
		printf("-");
	}

	gotoxy(editText->x, editText->y + 1);
	printf(EDIT_TEXT_INPUT_MESSAGE);
	printf("%s", editText->input);

	for (int i = 0; i < MAX_LENGTH_OF_INPUT_TEXT - strlen(editText->input); i++)
	{
		printf(" ");
	}
}

void showActiveEditText(EDIT_TEXT* editText)
{
	gotoxy(editText->x, editText->y);
	printf("-- %s ", editText->text);

	for (int i = 0; i < MAX_LENGTH_OF_INPUT_TEXT + strlen(EDIT_TEXT_INPUT_MESSAGE) - 4 - strlen(editText->text); i++)
	{
		printf("-");
	}

	changeColor(BLACK, LIGHT_WHITE);
	gotoxy(editText->x, editText->y + 1);
	printf(EDIT_TEXT_INPUT_MESSAGE);
	printf("%s", editText->input);

	for (int i = 0; i < MAX_LENGTH_OF_INPUT_TEXT - strlen(editText->input); i++)
	{
		printf(" ");
	}
	changeColor(LIGHT_WHITE, BLACK);

	deleteMessage();
	showMessage("방향키를 통해 이동할 수 있습니다. 문자를 입력할 수 있습니다.");

	gotoxy(editText->x + strlen(EDIT_TEXT_INPUT_MESSAGE) + strlen(editText->input), editText->y + 1);
}

void freeEditText(EDIT_TEXT** editText)
{
	if (*editText != NULL)
	{
		free((*editText)->text);
		free(*editText);
		*editText = NULL;
	}
}

TEXT* generateText(char* text, int x, int y)
{
	TEXT* text_ = malloc(sizeof(TEXT));

	text_->code = TEXT_CODE;
	text_->text = text;
	text_->x = x;
	text_->y = y;

	return text_;
}

void showText(TEXT* text)
{
	gotoxy(text->x, text->y);
	printf("%s", text->text);
}

void freeText(TEXT** text)
{
	if (*text != NULL)
	{
		free((*text)->text);
		free(*text);
		*text = NULL;
	}
}

COMBO_BOX* generateComboBox(char* text, char** choice, int x, int y)
{
	COMBO_BOX* comboBox = malloc(sizeof(COMBO_BOX));

	comboBox->code = COMBO_BOX_CODE;
	comboBox->input = calloc(MAX_LENGTH_OF_INPUT_TEXT + 1, sizeof(char));
	comboBox->text = text;
	comboBox->choice = choice;
	comboBox->x = x;
	comboBox->y = y;

	return comboBox;
}

void showComboBox(COMBO_BOX* comboBox)
{
	gotoxy(comboBox->x, comboBox->y);
	printf("-- %s ", comboBox->text);

	for (int i = 0; i < MAX_LENGTH_OF_INPUT_TEXT + strlen(COMBO_BOX_INPUT_MESSAGE) - 4 - strlen(comboBox->text); i++)
	{
		printf("-");
	}

	gotoxy(comboBox->x, comboBox->y + 1);
	printf(COMBO_BOX_INPUT_MESSAGE);
	printf("%s", comboBox->input);

	for (int i = 0; i < MAX_LENGTH_OF_INPUT_TEXT - strlen(comboBox->input); i++)
	{
		printf(" ");
	}
}

void showActiveComboBox(COMBO_BOX* comboBox)
{
	gotoxy(comboBox->x, comboBox->y);
	printf("-- %s ", comboBox->text);

	for (int i = 0; i < MAX_LENGTH_OF_INPUT_TEXT + strlen(COMBO_BOX_INPUT_MESSAGE) - 4 - strlen(comboBox->text); i++)
	{
		printf("-");
	}

	changeColor(BLACK, LIGHT_WHITE);
	gotoxy(comboBox->x, comboBox->y + 1);
	printf(COMBO_BOX_INPUT_MESSAGE);
	printf("%s", comboBox->input);

	for (int i = 0; i < MAX_LENGTH_OF_INPUT_TEXT - strlen(comboBox->input); i++)
	{
		printf(" ");
	}
	changeColor(LIGHT_WHITE, BLACK);

	deleteMessage();
	showMessage("방향키를 통해 이동할 수 있습니다. 엔터를 눌러 목록을 확인할 수 있습니다.");

	gotoxy(comboBox->x + strlen(COMBO_BOX_INPUT_MESSAGE) + strlen(comboBox->input), comboBox->y + 1);
}

void openComboBox(COMBO_BOX* comboBox)
{
	int standardPoint = 0;
	int endPoint = 0;
	int selectedNumber = 0;

	for (endPoint = 0; comboBox->choice[endPoint] != NULL; endPoint++);

	while (1)
	{
		for (int i = 0; i < MAX_LINE_OF_COMBO_BOX && comboBox->choice[i] != NULL; i++)
		{
			gotoxy(comboBox->x, comboBox->y + 2 + i);
			printf("|%s", comboBox->choice[standardPoint + i]);

			for (int j = 0; j < MAX_LENGTH_OF_INPUT_TEXT - strlen(comboBox->choice[standardPoint + i]); j++)
			{
				printf(" ");
			}
		}

		changeColor(BLACK, LIGHT_WHITE);
		gotoxy(comboBox->x, comboBox->y + 2 + selectedNumber - standardPoint);
		printf("|%s", comboBox->choice[selectedNumber]);
		for (int j = 0; j < MAX_LENGTH_OF_INPUT_TEXT - strlen(comboBox->choice[selectedNumber]); j++)
		{
			printf(" ");
		}
		changeColor(LIGHT_WHITE, BLACK);

		char c = getch();

		if (c == -32)
		{
			c = getch();

			if (c == UP)
			{
				if (selectedNumber > 0)
				{
					selectedNumber--;

					if (standardPoint > 0 && standardPoint > selectedNumber)
					{
						standardPoint--;
					}
				}
			}
			else if (c == DOWN)
			{
				if (selectedNumber < endPoint - 1)
				{
					selectedNumber++;

					if (standardPoint < endPoint - MAX_LINE_OF_COMBO_BOX && selectedNumber - standardPoint >= MAX_LINE_OF_COMBO_BOX)
					{
						standardPoint++;
					}
				}
			}
		}
		else if (c == 13)
		{
			char* str = comboBox->input;

			for (int i = 0; str[i] != '\0'; i++)
			{
				str[i] = '\0';
			}

			strcpy(comboBox->input, comboBox->choice[selectedNumber]);
			break;
		}
	}
}

void freeComboBox(COMBO_BOX** comboBox)
{
	if (comboBox != NULL)
	{
		free((*comboBox)->text);
		free(*comboBox);
		*comboBox = NULL;
	}
}

CHECK_BOX* generateCheckBox(int isChecked, int isChangeable, int x, int y)
{
	CHECK_BOX* checkBox = malloc(sizeof(CHECK_BOX));

	checkBox->code = CHECK_BOX_CODE;
	checkBox->isChecked = isChecked;
	checkBox->isChangeable = isChangeable;
	checkBox->x = x;
	checkBox->y = y;

	return checkBox;
}

void showCheckBox(CHECK_BOX* checkBox)
{
	gotoxy(checkBox->x, checkBox->y);
	if (checkBox->isChecked == CHECKED)
	{
		printf("■");
	}
	else
	{
		printf("□");
	}
}

void showActiveCheckBox(CHECK_BOX* checkBox)
{
	gotoxy(checkBox->x, checkBox->y);
	changeColor(BLACK, LIGHT_WHITE);
	if (checkBox->isChecked == CHECKED)
	{
		printf("□");
	}
	else
	{
		printf("■");
	}
	changeColor(LIGHT_WHITE, BLACK);

	showMessage("방향키를 통해 이동할 수 있습니다. 엔터를 눌러 상호작용할 수 있습니다. □ : 선택 안됨, ■ : 선택됨");
}

void clickCheckBox(CHECK_BOX* checkBox)
{
	if (checkBox->isChangeable == CHANGEABLE)
	{
		if (checkBox->isChecked == CHECKED)
		{
			checkBox->isChecked = UNCHECKED;
		}
		else
		{
			checkBox->isChecked = CHECKED;
		}
	}

	showActiveCheckBox(checkBox);
}
