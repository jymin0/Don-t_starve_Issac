// #include
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

// #define
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // 선택(스페이스바)

#define WALL '1'
#define DOORWALL '#'
#define PLAYER '2'
#define WATER '3'
#define FOOD '4'
#define DOOR '*'
#define MEDICKIT '+'

#define EAST 0
#define WAST 1
#define SOUTH 2
#define NORTH 3
#define MAPNUMBER 4
#define DOOROPEN 5

#define MAPSIZE 10

// setting
enum {
	black,
	blue,
	green,
	cyan,
	red,
	purple,
	brown,
	lightgray,
	darkgray,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightpurple,
	yellow,
	white
};
char maps[MAPSIZE][60][60];
char defaultmap[60][60] = {
	// 0: 빈공간, 1: 벽, *; 문, #: 벽(문o), @: 벽(문x), +:표시선
	// 게임 내 공간 [2][2]~[29][29], 정중앙 [15][15]
	{"0000000000000#***#0000000000000"},
	{"0111111111111#@@@#1111111111110"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"##000000000000000000000000000##"},
	{"*@000000000000000000000000000@*"},
	{"*@000000000000000000000000000@*"},
	{"*@000000000000000000000000000@*"},
	{"##000000000000000000000000000##"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0111111111111#@@@#1111111111110"},
	{"0000000000000#***#0000000000000"},
};
int infomap[MAPSIZE][6];
int reset[MAPSIZE][6];

int pX = 0;
int pY = 0;
int pHealth = 10;
int pFood = 10;
int pWater = 10;

// funcions list
void init();
void gotoxy(int, int);
void setColor(int, int);
void titleDraw();
int menuDraw();
int keyControl();
void infoDraw(); 
void randomObjectMaking(char, char*);
void creatmap();
void drawMap(int);
int mobile(char);
int move(int, int, int, int);
void drawUI(int pX, int pY, int pHealth, int pFood, int pWater);
void drawStart();

// main function
int main()
{
	srand(time(NULL));
	int menuCode = -1;
	int j;
	char string2[30] = { '-','-','-','-','-','-','-','-','-','-','-','B','y','e',' ','B','y','e','-','-','-','-','-','-','-','-','-','-','-','-' };
	init();
	while (1)
	{
		titleDraw();
		menuCode = menuDraw();
		if (menuCode == 0)
		{
			creatmap();
			Sleep(500);
			system("cls");
			for (int x = 0; x < MAPSIZE; x++)
			{
				printf("\n%d\n", x);
				printf("EAST= %d, ", infomap[x][EAST]);
				printf("WAST= %d, ", infomap[x][WAST]);
				printf("SOUTH= %d, ", infomap[x][SOUTH]);
				printf("NORTH= %d, ", infomap[x][NORTH]);
			}
			_getch();
	
			drawMap(0);
			drawStart();
			setColor(white, black);
			gotoxy(28, 10);
			Sleep(300);
			int mKey;
			int playing = 1;
			int mappos = 0;
			int cHealth = 0;
			int cFood = 0;
			int cWater = 0;
			int i;
			char string[10] = { 'G','A','M','E',' ','O','V','E','R'};
			while (playing)
			{
				mKey = keyControl();
				switch (mKey)
				{
				case UP:
					mappos = move(PLAYER, mappos, 0, -1);
					cFood++;
					cWater++;
					break;
				case DOWN:
					mappos = move(PLAYER, mappos, 0, 1);
					cFood++;
					cWater++;
					break;
				case RIGHT:
					mappos = move(PLAYER, mappos, 1, 0);
					cFood++;
					cWater++;
					break;
				case LEFT:
					mappos = move(PLAYER, mappos, -1, 0);
					cFood++;
					cWater++;
					break;
				case SUBMIT:
					playing = 0;
				}
				if (cFood % 15 == 0)
				{
					if (pFood > 0){
						if (pWater > 0) {
							pFood -= 1;
							if (pHealth < 10) {
								pHealth += 1;
							}
						}
						else if (pWater == 0) {
							pFood -= 1;
						}
					}
					else if (pFood == 0) {
						pHealth -= 1;
					}
				}
				if(cWater % 10 == 0)
				{
					if (pWater > 0) {
						pWater -= 1;
					}
					else if (pWater == 0) {
						pHealth -= 1;
					}
				}
				drawUI(pX, pY, pHealth, pFood, pWater);
				if (pHealth == 0)
				{   
					Sleep(200);
					setColor(white, black);
					gotoxy(27, 10);
					for (i = 0; i < 9; i++) 
					{
						printf("%c", string[i]);
						Sleep(250);
					}
					gotoxy(27, 10);
					for (i = 0; i < 9; i++)
					{
						printf(" ");
						Sleep(150);
					}
					Sleep(300);
					playing = 0;
				}
			}
		}
		else if (menuCode == 1)
		{
			infoDraw();
		}
		else if (menuCode == 2)
		{
			break;
		}
		menuCode = -1;
		system("cls");
	}
	gotoxy(12, 16);
	for (j = 0; j < 29; j++)
	{
		printf("%c", string2[j]);
		Sleep(150);
	}
	return _getch();
}

// function seting
void init()
{
	system("mode con cols=104 lines=40 | title survival game");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	for (int x = 0; x < MAPSIZE; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			reset[x][y] = -1;
		}
	}
}
void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
void setColor(int forground, int background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}
void titleDraw()
{
	setColor(white, black);
	printf("\n\n\n"); // 맨위에 4칸 개행
	printf("                                                              \n");
	printf("   ■■■■■■■    ■■■■■■■  ■   ■■■■■■  ■    \n");
	printf("               ■          ■        ■   ■        ■  ■    \n");
	printf("               ■         ■■       ■   ■ ●  ● ■  ■    \n");
	printf(" ■■■■■■■■■      ■  ■      ■   ■        ■  ■    \n");
	printf("         ■             ■    ■     ■   ■        ■  ■■  \n");
	printf("   ■■■■■■■      ■      ■    ■   ■        ■  ■    \n");
	printf("         ■    ■     ■        ■   ■   ■        ■  ■    \n");
	printf("   ■■■■    ■    ■          ■  ■   ■        ■  ■    \n");
	printf("   ■    ■    ■   ■            ■ ■   ■   ▼   ■  ■    \n");
	printf("   ■■■■■■■  ■              ■■   ■■■■■■  ■    \n");
	printf("                                                              \n");
}
int menuDraw()
{
	int x = 24;
	int y = 12;
	gotoxy(x - 2, y); // -2 한 이유는 > 를 출력해야하기 때문에  
	printf("☞ 게임시작");
	gotoxy(x, y + 1);
	printf(" 게임정보");
	gotoxy(x, y + 2);
	printf("   종료  ");
	while (1) { // 무한반복  
		int n = keyControl(); // 키보드 이벤트를 키값으로 받아오기  
		switch (n) {
		case UP: { // 입력된 키의 값이 UP인경우 (w) 
			if (y > 12) { // y는 12~14까지만 이동  
				gotoxy(x - 2, y); // x-2 하는 이유는 ">"를 두칸 이전에 출력하기위해  
				printf(" "); // 원래 위치를 지우고  
				gotoxy(x - 2, --y); // 새로 이동한 위치로 이동하여  
				printf("☞"); // 다시 그리기  
			}
			break;
		}

		case DOWN: { // 입력된 키의 값이 DOWN인경우 (s) 
			if (y < 14) { // 최대 14  
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf("☞");
			}
			break;
		}

		case SUBMIT: {
			return y - 12; // 스페이스바(선택)되었을 경우 y-12
			// y 시작 위치가 12였으므로 y-12 를 하면 0, 1, 2 세 숫자를 받을 수 있다. 
		}
		}
	}
}
int keyControl() {
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 'a' || temp == 'A')
	{
		return LEFT;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D')
	{
		return RIGHT;
	}
	else if (temp == ' ')
	{ // 스페이스바(공백)이 선택 버튼  
		return SUBMIT;
	}
}
void infoDraw()
{
	system("cls"); // 화면 모두 지우기  
	printf("\n\n");
	printf("                        [ 조작법 ]\n\n");
	printf("                      이동: W, A, S, D\n");
	printf("                      선택: 스페이스바\n\n\n\n\n");
	printf("              개발자: jyoh5005, yandusty, jymin0\n");
	printf("         스페이스바를 누르면 메인화면으로 이동합니다.");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}
void creatmap()
{
	srand(rand());
	int index = 0, moveMap = 0;
	memcpy(infomap, reset, sizeof(reset));
	memcpy(maps[index], defaultmap, sizeof(defaultmap));
	// 초기 맵 설정
	pX = 20;
	pY = 20;
	maps[0][20][20] = PLAYER;
	infomap[0][MAPNUMBER] = 0;

	for (index = 1; index < MAPSIZE; index++)
	{
		int mapNumber, find = 1;
		memcpy(maps[index], defaultmap, sizeof(defaultmap));
		infomap[index][MAPNUMBER] = index;
		mapNumber = rand() % index;
		while (find)
		{
			moveMap = rand() % 4;
			if (infomap[mapNumber][moveMap] != -1)
			{
				mapNumber = infomap[mapNumber][moveMap];
				continue;
			}
			else
			{
				find = 0;
				infomap[mapNumber][moveMap] = index;
				//infomap[mapNumber][1] += (1 << 3 * moveMap);
				if (moveMap == EAST)
				{
					infomap[index][WAST] = mapNumber;
					//infomap[index][1] += (1 << 3 * WAST);
				}
				if (moveMap == WAST)
				{
					infomap[index][EAST] = mapNumber;
					//infomap[index][1] += (1 << 3 * EAST);
				}
				if (moveMap == SOUTH)
				{
					infomap[index][NORTH] = mapNumber;
					//infomap[index][1] += (1 << 3 * NORTH);
				}
				if (moveMap == NORTH)
				{
					infomap[index][SOUTH] = mapNumber;
					//infomap[index][1] += (1 << 3 * SOUTH);
				}
			}
		}

		int i, fooditem = 0, wateritem = 0;
		fooditem = rand() % 9, wateritem = rand() % 9;
		for (i = 0; i < fooditem; i++)
		{
			randomObjectMaking(FOOD, (char*)maps[index]);
		}
		for (i = 0; i < fooditem; i++)
		{
			randomObjectMaking(WATER, (char*)maps[index]);
		}
	}
	//char* changePoint = (char*)&maps + index * 32 * 32;



}
void randomObjectMaking(char object, char* map)
{
	int posx, posy;
	while (1)
	{
		srand(rand());
		posx = 2 + rand() % 28;
		posy = 2 + rand() % 28;
		char* p = map + posx * 32;
		if (p[posy] == '0')
			p[posy] = object;
		break;
	}
}
void drawMap(int pos)
{
	system("cls");
	int h, w;
	char temp;
	for (h = 0; h < 32; h++)
	{
		for (w = 0; w < 32; w++)
		{
			gotoxy(2 * h, w);
			temp = maps[pos][h][w];
			if (temp == '0' || temp == NULL)
			{
				setColor(black, black);
				printf("  ");
			}
			else if (temp == '1')
			{
				setColor(white, white);
				printf("  ");
			}
			else if (temp == PLAYER)
			{
				//플레이어 X,Y 위치 저장
				setColor(cyan, black);
				printf("@@");
			}
			else if (temp == WATER)
			{
				setColor(black, cyan);
				printf("WW");
			}
			else if (temp == FOOD)
			{
				setColor(black, lightgreen);
				printf("FF");
			}
			else
			{
				setColor(white, white);
				printf("  ");
			}
		}
		setColor(black, black);
	}
	setColor(red, red);
	gotoxy(60, 36);
	printf(" ");
	setColor(green, green);
	if (infomap[pos][EAST] != -1)
	{
		gotoxy(62, 36);
		printf(" ");
	}
	if (infomap[pos][WAST] != -1)
	{
		gotoxy(58, 36);
		printf(" ");
	}
	if (infomap[pos][SOUTH] != -1)
	{
		gotoxy(60, 38);
		printf(" ");
	}
	if (infomap[pos][NORTH] != -1)
	{
		gotoxy(60, 34);
		printf(" ");
	}
	setColor(white, black);
	gotoxy(60, 2);
	printf("pos=%2d ", pos);
	
	gotoxy(62, 3);
	printf("EAST=%d ", infomap[pos][EAST]);
	gotoxy(62, 4);
	printf("WAST=%d ", infomap[pos][WAST]);
	gotoxy(62, 5);
	printf("SOUTH=%d ", infomap[pos][SOUTH]);
	gotoxy(62, 6);
	printf("NORTH=%d ", infomap[pos][NORTH]);
	
}
int mobile(char object)
{
	switch (object)
	{
	case WALL:
	case DOORWALL:
	case PLAYER:
		return 0;
	case FOOD:
	case WATER:
	case MEDICKIT:
		return 3;
	case '*':
		return 2;
	default:
		return 1;
	}
}
int move(int moveObject, int mappos, int x, int y)
{
	gotoxy(34, 34);
	printf("%d, %d", pX, pY);
	char object = maps[mappos][pX + x][pY + y];
	int t = mobile(object);
	if (t == 1)
	{
		//maps[mappos][pX + x][pY + y] == object;
		maps[mappos][pX][pY] = '0';

		setColor(white, black);
		gotoxy(2*pX, pY);
		printf("  ");

		setColor(cyan, black);
		gotoxy(2*(pX + x), pY + y);
		printf("@@");
		pX += x;
		pY += y;
		return mappos;
	}
	else if (t == 2)
	{
		int newmappos;
		int moveNewMap = 0;
		if (pY + y == 30) // SOUTH
		{
			newmappos = infomap[mappos][SOUTH];
			if (newmappos != -1)
			{
				maps[mappos][pX][pY] = '0';
				pX = 14, pY = 28;
				moveNewMap = 1;
			}
			else
				return mappos;
		}
		if (pY + y == 0) // NORTH
		{
			newmappos = infomap[mappos][NORTH];
			if (newmappos != -1)
			{
				maps[mappos][pX][pY] = '0';
				pX = 14, pY = 2;
				moveNewMap = 1;
			}
			else
				return mappos;
		}
		if (pX + x == 31) // EAST
		{
			newmappos = infomap[mappos][EAST];
			if (newmappos != -1)
			{
				maps[mappos][pX][pY] = '0';
				pX = 2, pY = 15;
				moveNewMap = 1;
			}
			else
				return mappos;
		}
		if (pX + x == 0) // WAST
		{
			newmappos = infomap[mappos][WAST];
			if (newmappos != -1)
			{
				maps[mappos][pX][pY] = '0';
				pX = 28, pY = 15;
				moveNewMap = 1;
			}
			else
				return mappos;
		}
		if (moveNewMap == 1)
		{
			maps[newmappos][pX][pY] = PLAYER;
			drawMap(newmappos);
			return newmappos;
		}
	}
	else if (t == 3)
	{
		maps[mappos][pX + x][pY + y] = '0';
		if (object == WATER)
		{
			pWater = 10;
		}
		else if (object == FOOD)
		{
			pFood = 10;
		}
		else if (object == MEDICKIT)
			pHealth += 2;
		setColor(white, black);
		gotoxy(2 * pX, pY);
		printf("  ");

		setColor(cyan, black);
		gotoxy(2 * (pX + x), pY + y);
		printf("@@");
		pX += x;
		pY += y;
	}
	return mappos;


}
void drawUI(int pX, int pY, int pHealth, int pFood, int pWater)
{
	int i;
	setColor(red, black);
	gotoxy(34, 30);
	printf(" H P  〔");
	for (i = 0; i < pHealth; i++) {
		printf("♥");
	}
	for (i = 0; i < 10 - pHealth; i++) {
		printf("♡");
	}
	printf("〕");

	setColor(brown, black);
	gotoxy(34, 31);
	printf("Hunger〔");
	for (i = 0; i < pFood; i++) {
		printf("♣");
	}
	for (i = 0; i < 10 - pFood; i++) {
		printf("♧");
	}
	printf("〕");

	setColor(blue, black);
	gotoxy(34, 32);
	printf("Water 〔");
	for (i = 0; i < pWater; i++) {
		printf("●");
	}
	for (i = 0; i < 10 - pWater; i++) {
		printf("○");
	}
	printf("〕");
}

void drawStart()
{
	int i;
	char string_s[10] = {'=','=','S','T','A','R','T','=','=' };
	setColor(white, black);
	gotoxy(31, 10);
	printf("%c", string_s[4]);
	for (i = 3; i >= 0; i--)
	{
		gotoxy(31 - (4 - i), 10);
		printf("%c", string_s[i]);
		gotoxy(31 + (6 - i - 2), 10);
		printf("%c", string_s[8 - i]);
		Sleep(500);
	}
	for (i = 0; i <= 3; i++)
	{
		gotoxy(27+i, 10);
		printf(" ");
		gotoxy(35 - i, 10);
		printf(" ");
		Sleep(300);
	}
	gotoxy(31, 10);
	printf(" ");
}