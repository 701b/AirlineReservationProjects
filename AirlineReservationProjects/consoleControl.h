#include <Windows.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PINK 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_PINK 13
#define LIGHT_YELLOW 14
#define LIGHT_WHITE 15

/*
콘솔창에서 커서를 x행 y열로 이동시킨다. */
void gotoxy(int x, int y);

/*
콘솔창에서 새로 출력되는 문자열의 색을 변경한다. */
void changeColor(short textColor, short backgroundColor);