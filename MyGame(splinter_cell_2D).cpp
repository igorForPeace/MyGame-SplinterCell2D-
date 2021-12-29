// игра на подобии 2д стелс экшн
// Цель игры - дойти до точки координат {1 , 1}


#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

COORD enemy_1,enemy_2, enemy_3, enemy_4, enemy_5, enemy_6, enemy_7, enemy_8, enemy_9;
COORD spy;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
enum colors { WHITE = 7, GRAY = 8, RED = 4, GREEN = 10, BLUE = 3, PURPLE = 13, GOLD = 6 };
enum map_object {
	HALL, WALL, WALL_2, CORNER_WALL_1, CORNER_WALL_2, CORNER_WALL_3, CORNER_WALL_4,
	HORIZONTAL_WALL, LIGHT, ENEMY, KEY, SWITCH, SWITCH_2, SWITCH_3, SWITCH_4, SWITCH_5, DOOR, DOOR_2, DOOR_3, DOOR_4, SPY, EXIT
};
    // DOOR - синяя дверь, открывает проход в большой зал первой половины игры
	// DOOR_2  - зеленная дверь, открывает проход во вторую часть карты
	// DOOR_3 - промежуточная фиолетовая дверь
	// DOOR_4 - золотая дверь в верхней комнате

const int P = 5;
const int T = 3;
char arr_left_right[P][T] =
{
		{' ','*',' '},
		{'*','*','*'},
		{'*','*','*'},
		{'*','*','*'},
		{' ','*',' '}
};

const int N = 3;
const int M = 7;
char arr_up[N][M] =
{
	{ '*','*','*','*','*','*','*' },
	{ ' ','*','*','*','*','*',' ' },
	{ ' ',' ','*','*','*',' ',' ' }

};

char arr_down[N][M] =
	{
		{ ' ',' ','*','*','*',' ',' ' },
		{ ' ','*','*','*','*','*',' ' },
		{ '*','*','*','*','*','*','*' },
	};

void ConsoleCursorVisible(bool show, short size)   // функция убирает курсор из консоли
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

// создаем отдельный поток для движения врагов

void DoWork(int **arrmap) 
{
	
	// создаем координаты для врагов
	COORD enemy_1 = { 110, 29 };   // враг маленькой комнаты с выключателем света
	SetConsoleCursorPosition(hStdOut, enemy_1);
	SetConsoleTextAttribute(hStdOut, RED);
	cout << (char)2;

	COORD light_left_enemy_1 = { 107,27 };// Координаты для отображения зоны видимости первого врага 
          								  // в движении на лево
	COORD light_left_off_enemy_1 = { 107,27 }; // Координаты для затирание зоны видимости при движении влево

	COORD light_up_enemy_1 = { 87,26 };  // координаты луча света при движении вверх

	COORD light_up_off_enemy_1 = { 87,26 }; // затирание луча света при движении вверх

	COORD light_right_enemy_1 = { 91,24 }; // область света при движении на право

	COORD light_right_off_enemy_1 = { 91,24 }; // Затирание луча света при движении в право

	COORD light_down_enemy_1 = { 107,27 }; // луч света при движении вниз

	COORD light_down_off_enemy_1 = { 107,27 };// затирание луча света вниз
	
	SetConsoleCursorPosition(hStdOut, light_left_enemy_1);
	SetConsoleTextAttribute(hStdOut, WHITE);
	for (int i = 0; i < P; i++)
	{
		for (int j = 0; j < T; j++)
		{
			
			cout << arr_left_right[i][j];
			arrmap[light_left_enemy_1.Y][light_left_enemy_1.X+j] = LIGHT;

		}
		light_left_enemy_1.Y += 1;
		SetConsoleCursorPosition(hStdOut, light_left_enemy_1);
		SetConsoleTextAttribute(hStdOut, WHITE);
	}
	
	// враги первой большой комнаты (низ карты)
	COORD enemy_2 = { 73,30 };      
	SetConsoleCursorPosition(hStdOut, enemy_2);
	SetConsoleTextAttribute(hStdOut, RED);
	cout << (char)2;

	COORD light_left_enemy_2 = { 70,28 };
	COORD light_left_off_enemy_2 = { 70,28 };

	COORD light_up_enemy_2 = { 53,27 };
	COORD light_up_off_enemy_2 = { 53,27 };

	COORD light_right_enemy_2 = { 57,17 }; 
	COORD light_right_off_enemy_2 = { 57,17 };

	COORD light_down_enemy_2 = { 70,20 };
	COORD light_down_off_enemy_2 = { 70,20 };

	SetConsoleCursorPosition(hStdOut, light_left_enemy_2);
	SetConsoleTextAttribute(hStdOut, WHITE);
	for (int i = 0; i < P; i++)
	{
		for (int j = 0; j < T; j++)
		{
			
			cout << arr_left_right[i][j];
			arrmap[light_left_enemy_2.Y][light_left_enemy_2.X + j] = LIGHT;

		}
		light_left_enemy_2.Y += 1;
		SetConsoleCursorPosition(hStdOut, light_left_enemy_2);
		SetConsoleTextAttribute(hStdOut, WHITE);
	}

	COORD enemy_3 = { 56, 19 };
	SetConsoleCursorPosition(hStdOut, enemy_3);
	SetConsoleTextAttribute(hStdOut, RED);
	cout << (char)2;

	COORD light_right_enemy_3 = { 57,17 };
	COORD light_right_off_enemy_3 = { 57,17 };

	COORD light_down_enemy_3 = { 70,20 };
	COORD light_down_off_enemy_3 = { 70,20 };

	COORD light_left_enemy_3 = { 70,28 };
	COORD light_left_off_enemy_3 = { 70,28 };

	COORD light_up_enemy_3 = { 53,27 };
	COORD light_up_off_enemy_3 = { 53,27 };

	SetConsoleCursorPosition(hStdOut, light_right_enemy_3);
	SetConsoleTextAttribute(hStdOut, WHITE);
	for (int i = 0; i < P; i++)
	{
		for (int j = 0; j < T; j++)
		{
			cout << arr_left_right[i][j];
			arrmap[light_right_enemy_3.Y][light_right_enemy_3.X + j] = LIGHT;
		}
		light_right_enemy_3.Y += 1;
		SetConsoleCursorPosition(hStdOut, light_right_enemy_3);
		SetConsoleTextAttribute(hStdOut, WHITE);
	}

	COORD enemy_4 = { 39 , 19 };
	SetConsoleCursorPosition(hStdOut, enemy_4);
	SetConsoleTextAttribute(hStdOut, RED);
	cout << (char)2;

	COORD light_down_enemy_4 = { 36,20 };
	COORD light_down_off_enemy_4 = { 36,20 };

	COORD light_left_enemy_4 = {36, 28};
	COORD light_left_off_enemy_4 = {36, 28};

	COORD light_up_enemy_4 = { 20,27 };
	COORD light_up_off_enemy_4 = { 20,27 };

	COORD light_right_enemy_4 = { 24,17 };
	COORD light_right_off_enemy_4 = { 24,17 };

	SetConsoleCursorPosition(hStdOut, light_down_enemy_4);
	SetConsoleTextAttribute(hStdOut, WHITE);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << arr_down[i][j];
			arrmap[light_down_enemy_4.Y][light_down_enemy_4.X + j] = LIGHT;
		}
		light_down_enemy_4.Y += 1;
		SetConsoleCursorPosition(hStdOut, light_down_enemy_4);
		SetConsoleTextAttribute(hStdOut, WHITE);
	}
	light_down_enemy_4.Y -= 3;

	COORD enemy_5 = { 23,30 };
	SetConsoleCursorPosition(hStdOut, enemy_5);
	SetConsoleTextAttribute(hStdOut, RED);
	cout << (char)2;

	COORD light_up_enemy_5 = { 20,27 };
	COORD light_up_off_enemy_5 = { 20,27 };

	COORD light_right_enemy_5 = { 24,17 };
	COORD light_right_off_enemy_5 = { 24,17 };

	COORD light_down_enemy_5 = { 36,20 };
	COORD light_down_off_enemy_5 = { 36,20 };

	COORD light_left_enemy_5 = { 36, 28 };
	COORD light_left_off_enemy_5 = { 36, 28 };

	SetConsoleCursorPosition(hStdOut, light_up_enemy_5);
	SetConsoleTextAttribute(hStdOut, WHITE);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << arr_up[i][j];
			arrmap[light_up_enemy_5.Y][light_up_enemy_5.X + j] = LIGHT;
		}
		light_up_enemy_5.Y += 1;
		SetConsoleCursorPosition(hStdOut, light_up_enemy_5);
	}
	
	// враги верхней комнаты

	COORD enemy_6 = { 22, 12 };
	SetConsoleCursorPosition(hStdOut, enemy_6);
	SetConsoleTextAttribute(hStdOut, RED);
	cout << (char)2;

	COORD enemy_7 = { 22,3 };
	SetConsoleCursorPosition(hStdOut, enemy_7);
	SetConsoleTextAttribute(hStdOut, RED);
	cout << (char)2;

	COORD enemy_8 = { 63,3 };
	SetConsoleCursorPosition(hStdOut, enemy_8);
	SetConsoleTextAttribute(hStdOut, RED);
	cout << (char)2;

	COORD enemy_9 = { 63,12 };
	SetConsoleCursorPosition(hStdOut, enemy_9);
	SetConsoleTextAttribute(hStdOut, RED);
	cout << (char)2;

	while (true)
	{
		
		// Задаем алгоритм движения для первого врага
		if (enemy_1.Y == 29)  // движение влево
		{
			
			SetConsoleCursorPosition(hStdOut, light_left_off_enemy_1);

			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << " ";
					arrmap[light_left_off_enemy_1.Y][light_left_off_enemy_1.X + j] = HALL;
				}
				light_left_off_enemy_1.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_left_off_enemy_1);
			}

			light_left_off_enemy_1.Y -= 5;
			light_left_off_enemy_1.X -= 1;
				
			enemy_1.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_1);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_1.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_1);
			cout << " ";
			enemy_1.X -= 1;
			
			light_left_enemy_1.X -= 1;
			light_left_enemy_1.Y -= 5;
			SetConsoleCursorPosition(hStdOut, light_left_enemy_1);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << arr_left_right[i][j];
					arrmap[light_left_enemy_1.Y][light_left_enemy_1.X + j] = LIGHT;
				}
				light_left_enemy_1.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_left_enemy_1);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}

			Sleep(100);
			
			if (enemy_1.X == 90 && enemy_1.Y == 29)
			{
				SetConsoleCursorPosition(hStdOut, light_left_off_enemy_1);

				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << " ";
						arrmap[light_left_off_enemy_1.Y][light_left_off_enemy_1.X + j] = HALL;
					}
					light_left_off_enemy_1.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_left_off_enemy_1);
				}
				light_left_off_enemy_1.Y -= 5;
				light_left_off_enemy_1.X -= 1;

				SetConsoleCursorPosition(hStdOut, light_up_enemy_1);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << arr_up[i][j];
						arrmap[light_up_enemy_1.Y][light_up_enemy_1.X + j] = LIGHT;
					}
					light_up_enemy_1.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_up_enemy_1);
				}
				light_left_enemy_1 = { 107,27 };
				light_left_off_enemy_1 = { 107,27 };
				
			}	
		}
		if (enemy_1.X == 90)   // движение вверх
		{
			
			SetConsoleCursorPosition(hStdOut, light_up_off_enemy_1);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << " ";
					arrmap[light_up_off_enemy_1.Y][light_up_off_enemy_1.X + j] = HALL;
				}
				light_up_off_enemy_1.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_up_off_enemy_1);
			}
			
			enemy_1.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_1);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_1.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_1);
			cout << " ";
			enemy_1.Y -= 1;
			
			light_up_enemy_1.Y -= 4;
			SetConsoleCursorPosition(hStdOut, light_up_enemy_1);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << arr_up[i][j];
					arrmap[light_up_enemy_1.Y][light_up_enemy_1.X + j] = LIGHT;
				}
				light_up_enemy_1.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_up_enemy_1);
			}
			light_up_off_enemy_1.Y -= 4;
			SetConsoleCursorPosition(hStdOut, light_up_off_enemy_1);

			Sleep(100);

			if (enemy_1.X == 90 && enemy_1.Y == 26)
			{
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << " ";
						arrmap[light_up_off_enemy_1.Y][light_up_off_enemy_1.X + j] = HALL;
					}
					light_up_off_enemy_1.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_up_off_enemy_1);
				}

				
				SetConsoleCursorPosition(hStdOut, light_right_enemy_1);
				SetConsoleTextAttribute(hStdOut, WHITE);
				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{

						cout << arr_left_right[i][j];
						arrmap[light_right_enemy_1.Y][light_right_enemy_1.X + j] = LIGHT;
					}
					light_right_enemy_1.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_right_enemy_1);
					SetConsoleTextAttribute(hStdOut, WHITE);
				}
			}
		}
		if (enemy_1.Y == 26)  // движение вправо
		{
			SetConsoleCursorPosition(hStdOut, light_right_off_enemy_1);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << " ";
					arrmap[light_right_off_enemy_1.Y][light_right_off_enemy_1.X + j] = HALL;
				}
				light_right_off_enemy_1.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_right_off_enemy_1);
			}
			light_right_off_enemy_1.Y -= 5;
			light_right_off_enemy_1.X += 1;


			enemy_1.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_1);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_1.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_1);
			cout << " ";
			enemy_1.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_1);
			

			light_right_enemy_1.Y -= 5;
			light_right_enemy_1.X += 1;
			SetConsoleCursorPosition(hStdOut, light_right_enemy_1);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << arr_left_right[i][j];
					arrmap[light_right_enemy_1.Y][light_right_enemy_1.X + j] = LIGHT;
				}
				light_right_enemy_1.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_right_enemy_1);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}

			Sleep(100);

			if (enemy_1.X == 110 && enemy_1.Y == 26)
			{
				SetConsoleCursorPosition(hStdOut, light_right_off_enemy_1);
				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << " ";
						arrmap[light_right_off_enemy_1.Y][light_right_off_enemy_1.X + j] = HALL;
					}
					light_right_off_enemy_1.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_right_off_enemy_1);
				}
				light_right_off_enemy_1.Y += 5;
				light_right_off_enemy_1.X += 1;

				SetConsoleCursorPosition(hStdOut, light_down_enemy_1);
				SetConsoleTextAttribute(hStdOut, WHITE);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << arr_down[i][j];
						arrmap[light_down_enemy_1.Y][light_down_enemy_1.X + j] = LIGHT;
					}
					light_down_enemy_1.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_down_enemy_1);
					SetConsoleTextAttribute(hStdOut, WHITE);
				}
				light_down_enemy_1.Y -= 3;

				light_right_enemy_1 = { 91,24 };
				light_right_off_enemy_1 = { 91,24 };
			}
			
		}
		if (enemy_1.X == 110)  // движение вниз
		{
			
			SetConsoleCursorPosition(hStdOut, light_down_off_enemy_1);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << " ";
					arrmap[light_down_off_enemy_1.Y][light_down_off_enemy_1.X + j] = HALL;
				}
				light_down_off_enemy_1.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_down_off_enemy_1);
			}
			light_down_off_enemy_1.Y -= 3;
			

			enemy_1.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_1);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_1.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_1);
			cout << " ";
			enemy_1.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_1);

			light_down_enemy_1.Y += 1;
			SetConsoleCursorPosition(hStdOut, light_down_enemy_1);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << arr_down[i][j];
					arrmap[light_down_enemy_1.Y][light_down_enemy_1.X + j] = LIGHT;
				}
				light_down_enemy_1.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_down_enemy_1);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}
			light_down_enemy_1.Y -= 3;
			Sleep(100);

			if (enemy_1.X == 110 && enemy_1.Y == 29)
			{
				light_down_off_enemy_1.Y += 3;
				SetConsoleCursorPosition(hStdOut, light_down_off_enemy_1);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << " ";
						arrmap[light_down_off_enemy_1.Y][light_down_off_enemy_1.X + j] = HALL;
					}
					light_down_off_enemy_1.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_down_off_enemy_1);
				}

				SetConsoleCursorPosition(hStdOut, light_left_enemy_1);
				SetConsoleTextAttribute(hStdOut, WHITE);

				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << arr_left_right[i][j];
						arrmap[light_left_enemy_1.Y][light_left_enemy_1.X + j] = LIGHT;
					}
					light_left_enemy_1.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_left_enemy_1);
				}
				light_down_enemy_1 = { 107,27 };
				light_down_off_enemy_1 = { 107,27 };
			}

		}

		// алгоритм движения для второго врага
		if (enemy_2.Y == 30)  // движение второго врага налево
		{
			SetConsoleCursorPosition(hStdOut, light_left_off_enemy_2);

			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << " ";
					arrmap[light_left_off_enemy_2.Y][light_left_off_enemy_2.X + j] = HALL;
				}
				light_left_off_enemy_2.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_left_off_enemy_2);
			}

			light_left_off_enemy_2.Y -= 5;
			light_left_off_enemy_2.X -= 1;

			enemy_2.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_2.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);
			cout << " ";
			enemy_2.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);

			light_left_enemy_2.X -= 1;
			light_left_enemy_2.Y -= 5;
			SetConsoleCursorPosition(hStdOut, light_left_enemy_2);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << arr_left_right[i][j];
					arrmap[light_left_enemy_2.Y][light_left_enemy_2.X + j] = LIGHT;
				}
				light_left_enemy_2.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_left_enemy_2);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}

			Sleep(100);

			if (enemy_2.X == 56 && enemy_2.Y == 30)
			{
				SetConsoleCursorPosition(hStdOut, light_left_off_enemy_2);

				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << " ";
						arrmap[light_left_off_enemy_2.Y][light_left_off_enemy_2.X + j] = HALL;
					}
					light_left_off_enemy_2.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_left_off_enemy_2);
				}
				light_left_off_enemy_2.Y -= 5;
				light_left_off_enemy_2.X -= 1;

				SetConsoleCursorPosition(hStdOut, light_up_enemy_2);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << arr_up[i][j];
						arrmap[light_up_enemy_2.Y][light_up_enemy_2.X + j] = LIGHT;
					}
					light_up_enemy_2.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_up_enemy_2);
				}
				 light_left_enemy_2 = { 70,28 };
				 light_left_off_enemy_2 = { 70,28 };

			}
		}
		if (enemy_2.X == 56) //движение ВТОРОГО врага вверх
		{
			SetConsoleCursorPosition(hStdOut, light_up_off_enemy_2);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << " ";
					arrmap[light_up_off_enemy_2.Y][light_up_off_enemy_2.X + j] = HALL;
				}
				light_up_off_enemy_2.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_up_off_enemy_2);
			}

			enemy_2.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_2.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);
			cout << " ";
			enemy_2.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);

			light_up_enemy_2.Y -= 4;
			SetConsoleCursorPosition(hStdOut, light_up_enemy_2);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << arr_up[i][j];
					arrmap[light_up_enemy_2.Y][light_up_enemy_2.X + j] = LIGHT;
				}
				light_up_enemy_2.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_up_enemy_2);
			}
			light_up_off_enemy_2.Y -= 4;
			SetConsoleCursorPosition(hStdOut, light_up_off_enemy_2);

			Sleep(100);

			if (enemy_2.X == 56 && enemy_2.Y == 19)
			{
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << " ";
						arrmap[light_up_off_enemy_2.Y][light_up_off_enemy_2.X + j] = HALL;
					}
					light_up_off_enemy_2.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_up_off_enemy_2);
				}


				SetConsoleCursorPosition(hStdOut, light_right_enemy_2);
				SetConsoleTextAttribute(hStdOut, WHITE);
				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{

						cout << arr_left_right[i][j];
						arrmap[light_right_enemy_2.Y][light_right_enemy_2.X + j] = LIGHT;
					}
					light_right_enemy_2.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_right_enemy_2);
					SetConsoleTextAttribute(hStdOut, WHITE);
				}
				light_up_enemy_2 = { 53,27 };
				light_up_off_enemy_2 = { 53,27 };
			}
		}
		if (enemy_2.Y == 19)  // движение второго врага вправо
		{
			SetConsoleCursorPosition(hStdOut, light_right_off_enemy_2);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << " ";
					arrmap[light_right_off_enemy_2.Y][light_right_off_enemy_2.X + j] = HALL;
				}
				light_right_off_enemy_2.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_right_off_enemy_2);
			}
			light_right_off_enemy_2.Y -= 5;
			light_right_off_enemy_2.X += 1;

			enemy_2.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_2.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);
			cout << " ";
			enemy_2.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);

			light_right_enemy_2.Y -= 5;
			light_right_enemy_2.X += 1;
			SetConsoleCursorPosition(hStdOut, light_right_enemy_2);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << arr_left_right[i][j];
					arrmap[light_right_enemy_2.Y][light_right_enemy_2.X + j] = LIGHT;
				}
				light_right_enemy_2.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_right_enemy_2);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}

			Sleep(100);

			if (enemy_2.X == 73 && enemy_2.Y == 19)
			{
				SetConsoleCursorPosition(hStdOut, light_right_off_enemy_2);
				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << " ";
						arrmap[light_right_off_enemy_2.Y][light_right_off_enemy_2.X + j] = HALL;
					}
					light_right_off_enemy_2.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_right_off_enemy_2);
				}
				light_right_off_enemy_2.Y += 5;
				light_right_off_enemy_2.X += 1;

				SetConsoleCursorPosition(hStdOut, light_down_enemy_2);
				SetConsoleTextAttribute(hStdOut, WHITE);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << arr_down[i][j];
						arrmap[light_down_enemy_2.Y][light_down_enemy_2.X + j] = LIGHT;
					}
					light_down_enemy_2.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_down_enemy_2);
					SetConsoleTextAttribute(hStdOut, WHITE);
				}
				light_down_enemy_2.Y -= 3;

				light_right_enemy_2 = { 57,17 };
				light_right_off_enemy_2 = { 57,17 };
			}

		}
		if (enemy_2.X == 73)  // движение второго врага вниз
		{
			
			SetConsoleCursorPosition(hStdOut, light_down_off_enemy_2);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << " ";
					arrmap[light_down_off_enemy_2.Y][light_down_off_enemy_2.X + j] = HALL;
				}
				light_down_off_enemy_2.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_down_off_enemy_2);
			}
			light_down_off_enemy_2.Y -= 2;

			enemy_2.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_2.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);
			cout << " ";
			enemy_2.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_2);

			light_down_enemy_2.Y += 1;
			SetConsoleCursorPosition(hStdOut, light_down_enemy_2);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << arr_down[i][j];
					arrmap[light_down_enemy_2.Y][light_down_enemy_2.X + j] = LIGHT;
				}
				light_down_enemy_2.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_down_enemy_2);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}
			light_down_enemy_2.Y -= 3;

			Sleep(100);

			if (enemy_2.X == 73 && enemy_2.Y == 30)
			{

				SetConsoleCursorPosition(hStdOut, light_down_off_enemy_2);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << " ";
						arrmap[light_down_off_enemy_2.Y][light_down_off_enemy_2.X + j] = HALL;
					}
					light_down_off_enemy_2.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_down_off_enemy_2);
				}

				SetConsoleCursorPosition(hStdOut, light_left_enemy_2);
				SetConsoleTextAttribute(hStdOut, WHITE);

				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << arr_left_right[i][j];
						arrmap[light_left_enemy_2.Y][light_left_enemy_2.X + j] = LIGHT;
					}
					light_left_enemy_2.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_left_enemy_2);
				}
				light_down_enemy_2 = { 70,20 };
				light_down_off_enemy_2 = { 70,20 };
			}
		}

		// Движение третьего врага 
		
		if (enemy_3.Y == 19)  //  движение вправо
		{
			SetConsoleCursorPosition(hStdOut, light_right_off_enemy_3);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << " ";
					arrmap[light_right_off_enemy_3.Y][light_right_off_enemy_3.X + j] = HALL;
				}
				light_right_off_enemy_3.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_right_off_enemy_3);
			}
			light_right_off_enemy_3.Y -= 5;
			light_right_off_enemy_3.X += 1;


			enemy_3.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_3.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);
			cout << " ";
			enemy_3.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);

			light_right_enemy_3.Y -= 5;
			light_right_enemy_3.X += 1;
			SetConsoleCursorPosition(hStdOut, light_right_enemy_3);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << arr_left_right[i][j];
					arrmap[light_right_enemy_3.Y][light_right_enemy_3.X + j] = LIGHT;
				}
				light_right_enemy_3.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_right_enemy_3);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}

			Sleep(100);

			if (enemy_3.X == 73 && enemy_3.Y == 19)
			{
				SetConsoleCursorPosition(hStdOut, light_right_off_enemy_3);
				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << " ";
						arrmap[light_right_off_enemy_3.Y][light_right_off_enemy_3.X + j] = HALL;
					}
					light_right_off_enemy_3.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_right_off_enemy_3);
				}
				light_right_off_enemy_3.Y += 5;
				light_right_off_enemy_3.X += 1;

				SetConsoleCursorPosition(hStdOut, light_down_enemy_3);
				SetConsoleTextAttribute(hStdOut, WHITE);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << arr_down[i][j];
						arrmap[light_down_enemy_3.Y][light_down_enemy_3.X + j] = LIGHT;
					}
					light_down_enemy_3.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_down_enemy_3);
					SetConsoleTextAttribute(hStdOut, WHITE);
				}
				light_down_enemy_3.Y -= 3;

				light_right_enemy_3 = { 57,17 };
				light_right_off_enemy_3 = { 57,17 };
			}
		}
		if (enemy_3.X == 73)  // движение вниз для третьего врага
		{
			SetConsoleCursorPosition(hStdOut, light_down_off_enemy_3);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << " ";
					arrmap[light_down_off_enemy_3.Y][light_down_off_enemy_3.X + j] = HALL;
				}
				light_down_off_enemy_3.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_down_off_enemy_3);
			}
			light_down_off_enemy_3.Y -= 2;

			enemy_3.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_3.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);
			cout << " ";
			enemy_3.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);

			light_down_enemy_3.Y += 1;
			SetConsoleCursorPosition(hStdOut, light_down_enemy_3);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << arr_down[i][j];
					arrmap[light_down_enemy_3.Y][light_down_enemy_3.X + j] = LIGHT;
				}
				light_down_enemy_3.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_down_enemy_3);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}
			light_down_enemy_3.Y -= 3;

			Sleep(100);

			if (enemy_3.X == 73 && enemy_3.Y == 30)
			{
				
				SetConsoleCursorPosition(hStdOut, light_down_off_enemy_3);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << " ";
						arrmap[light_down_off_enemy_3.Y][light_down_off_enemy_3.X + j] = HALL;
					}
					light_down_off_enemy_3.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_down_off_enemy_3);
				}

				SetConsoleCursorPosition(hStdOut, light_left_enemy_3);
				SetConsoleTextAttribute(hStdOut, WHITE);

				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << arr_left_right[i][j];
						arrmap[light_left_enemy_3.Y][light_left_enemy_3.X + j] = LIGHT;
					}
					light_left_enemy_3.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_left_enemy_3);
				}
				light_down_enemy_3 = { 70,20 };
				light_down_off_enemy_3 = { 70,20 };
			}
		}
		if (enemy_3.Y == 30)  // движение влево для третьего врага
		{
			SetConsoleCursorPosition(hStdOut, light_left_off_enemy_3);

			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << " ";
					arrmap[light_left_off_enemy_3.Y][light_left_off_enemy_3.X + j] = HALL;
				}
				light_left_off_enemy_3.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_left_off_enemy_3);
			}

			light_left_off_enemy_3.Y -= 5;
			light_left_off_enemy_3.X -= 1;

			enemy_3.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_3.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);
			cout << " ";
			enemy_3.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);

			light_left_enemy_3.X -= 1;
			light_left_enemy_3.Y -= 5;
			SetConsoleCursorPosition(hStdOut, light_left_enemy_3);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << arr_left_right[i][j];
					arrmap[light_left_enemy_3.Y][light_left_enemy_3.X + j] = LIGHT;
				}
				light_left_enemy_3.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_left_enemy_3);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}

			Sleep(100);

			if (enemy_3.X == 56 && enemy_3.Y == 30)
			{
				SetConsoleCursorPosition(hStdOut, light_left_off_enemy_3);

				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << " ";
						arrmap[light_left_off_enemy_3.Y][light_left_off_enemy_3.X + j] = HALL;
					}
					light_left_off_enemy_3.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_left_off_enemy_3);
				}
				light_left_off_enemy_3.Y -= 5;
				light_left_off_enemy_3.X -= 1;

				SetConsoleCursorPosition(hStdOut, light_up_enemy_3);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << arr_up[i][j];
						arrmap[light_up_enemy_3.Y][light_up_enemy_3.X + j] = LIGHT;
					}
					light_up_enemy_3.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_up_enemy_3);
				}
				light_left_enemy_3 = { 70,28 };
				light_left_off_enemy_3 = { 70,28 };

			}
		}
		if (enemy_3.X == 56)  // движение третьего врага вверх
		{
			SetConsoleCursorPosition(hStdOut, light_up_off_enemy_3);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << " ";
					arrmap[light_up_off_enemy_3.Y][light_up_off_enemy_3.X + j] = HALL;
				}
				light_up_off_enemy_3.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_up_off_enemy_3);
			}

			enemy_3.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_3.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);
			cout << " ";
			enemy_3.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_3);

			light_up_enemy_3.Y -= 4;
			SetConsoleCursorPosition(hStdOut, light_up_enemy_3);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << arr_up[i][j];
					arrmap[light_up_enemy_3.Y][light_up_enemy_3.X + j] = LIGHT;
				}
				light_up_enemy_3.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_up_enemy_3);
			}
			light_up_off_enemy_3.Y -= 4;
			SetConsoleCursorPosition(hStdOut, light_up_off_enemy_3);

			Sleep(100);

			if (enemy_3.X == 56 && enemy_3.Y == 19)
			{
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << " ";
						arrmap[light_up_off_enemy_3.Y][light_up_off_enemy_3.X + j] = HALL;
					}
					light_up_off_enemy_3.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_up_off_enemy_3);
				}


				SetConsoleCursorPosition(hStdOut, light_right_enemy_3);
				SetConsoleTextAttribute(hStdOut, WHITE);
				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{

						cout << arr_left_right[i][j];
						arrmap[light_right_enemy_3.Y][light_right_enemy_3.X + j] = LIGHT;
					}
					light_right_enemy_3.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_right_enemy_3);
					SetConsoleTextAttribute(hStdOut, WHITE);
				}
				light_up_enemy_3 = { 53,27 };
				light_up_off_enemy_3 = { 53,27 };
			}
		}
		// Движение четвертого врага

		if (enemy_4.X == 39)  // движение четвертого врага вниз
		{
			SetConsoleCursorPosition(hStdOut, light_down_off_enemy_4);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << " ";
					arrmap[light_down_off_enemy_4.Y][light_down_off_enemy_4.X + j] = HALL;
				}
				light_down_off_enemy_4.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_down_off_enemy_4);
			}
			light_down_off_enemy_4.Y -= 2;

			enemy_4.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_4.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);
			cout << " ";
			enemy_4.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);

			light_down_enemy_4.Y += 1;
			SetConsoleCursorPosition(hStdOut, light_down_enemy_4);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << arr_down[i][j];
					arrmap[light_down_enemy_4.Y][light_down_enemy_4.X + j] = LIGHT;
				}
				light_down_enemy_4.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_down_enemy_4);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}
			light_down_enemy_4.Y -= 3;
			
			Sleep(100);

			if (enemy_4.X == 39 && enemy_4.Y == 30)
			{

				SetConsoleCursorPosition(hStdOut, light_down_off_enemy_4);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << " ";
						arrmap[light_down_off_enemy_4.Y][light_down_off_enemy_4.X + j] = HALL;
					}
					light_down_off_enemy_4.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_down_off_enemy_4);
				}

				SetConsoleCursorPosition(hStdOut, light_left_enemy_4);
				SetConsoleTextAttribute(hStdOut, WHITE);

				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << arr_left_right[i][j];
						arrmap[light_left_enemy_4.Y][light_left_enemy_4.X + j] = LIGHT;
					}
					light_left_enemy_4.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_left_enemy_4);
				}
				light_down_enemy_4 = { 36,20 };
				light_down_off_enemy_4 = { 36,20 };
			}
		}
		if (enemy_4.Y == 30)  //движение четвертого врага влево
		{
			SetConsoleCursorPosition(hStdOut, light_left_off_enemy_4);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << " ";
					arrmap[light_left_off_enemy_4.Y][light_left_off_enemy_4.X + j] = HALL;
				}
				light_left_off_enemy_4.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_left_off_enemy_4);
			}
			light_left_off_enemy_4.Y -= 5;
			light_left_off_enemy_4.X -= 1;

			enemy_4.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_4.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);
			cout << " ";
			enemy_4.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);

			light_left_enemy_4.X -= 1;
			light_left_enemy_4.Y -= 5;
			SetConsoleCursorPosition(hStdOut, light_left_enemy_4);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << arr_left_right[i][j];
					arrmap[light_left_enemy_4.Y][light_left_enemy_4.X + j] = LIGHT;
				}
				light_left_enemy_4.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_left_enemy_4);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}

			Sleep(100);
			
			if (enemy_4.X == 23 && enemy_4.Y == 30)
			{
				SetConsoleCursorPosition(hStdOut, light_left_off_enemy_4);

				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << " ";
						arrmap[light_left_off_enemy_4.Y][light_left_off_enemy_4.X + j] = HALL;
					}
					light_left_off_enemy_4.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_left_off_enemy_4);
				}
				light_left_off_enemy_4.Y -= 5;
				light_left_off_enemy_4.X -= 1;

				SetConsoleCursorPosition(hStdOut, light_up_enemy_4);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << arr_up[i][j];
						arrmap[light_up_enemy_4.Y][light_up_enemy_4.X + j] = LIGHT;
					}
					light_up_enemy_4.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_up_enemy_4);
				}
				light_left_enemy_4 = { 36, 28 };
				light_left_off_enemy_4 = { 36, 28 };

			}
		}
		if (enemy_4.X == 23)  // движение четвертого врага вверх
		{
			SetConsoleCursorPosition(hStdOut, light_up_off_enemy_4);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << " ";
					arrmap[light_up_off_enemy_4.Y][light_up_off_enemy_4.X + j] = HALL;
				}
				light_up_off_enemy_4.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_up_off_enemy_4);
			}

			enemy_4.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_4.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);
			cout << " ";
			enemy_4.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);

			light_up_enemy_4.Y -= 4;
			SetConsoleCursorPosition(hStdOut, light_up_enemy_4);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << arr_up[i][j];
					arrmap[light_up_enemy_4.Y][light_up_enemy_4.X + j] = LIGHT;
				}
				light_up_enemy_4.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_up_enemy_4);
			}
			light_up_off_enemy_4.Y -= 4;
			SetConsoleCursorPosition(hStdOut, light_up_off_enemy_4);

			Sleep(100);

			if (enemy_4.X == 23 && enemy_4.Y == 19)
			{
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << " ";
						arrmap[light_up_off_enemy_4.Y][light_up_off_enemy_4.X + j] = HALL;
					}
					light_up_off_enemy_4.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_up_off_enemy_4);
				}


				SetConsoleCursorPosition(hStdOut, light_right_enemy_4);
				SetConsoleTextAttribute(hStdOut, WHITE);
				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{

						cout << arr_left_right[i][j];
						arrmap[light_right_enemy_4.Y][light_right_enemy_4.X + j] = LIGHT;
					}
					light_right_enemy_4.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_right_enemy_4);
					SetConsoleTextAttribute(hStdOut, WHITE);
				}
				light_up_enemy_4 = { 20,27 };
				light_up_off_enemy_4 = { 20,27 };
			}
		}
		if (enemy_4.Y == 19)  // движение четвертого врага вправо
		{
			SetConsoleCursorPosition(hStdOut, light_right_off_enemy_4);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << " ";
					arrmap[light_right_off_enemy_4.Y][light_right_off_enemy_4.X + j] = HALL;
				}
				light_right_off_enemy_4.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_right_off_enemy_4);
			}
			light_right_off_enemy_4.Y -= 5;
			light_right_off_enemy_4.X += 1;

			enemy_4.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_4.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);
			cout << " ";
			enemy_4.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_4);

			light_right_enemy_4.Y -= 5;
			light_right_enemy_4.X += 1;
			SetConsoleCursorPosition(hStdOut, light_right_enemy_4);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << arr_left_right[i][j];
					arrmap[light_right_enemy_4.Y][light_right_enemy_4.X + j] = LIGHT;
				}
				light_right_enemy_4.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_right_enemy_4);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}

			Sleep(100);

			if (enemy_4.X == 39 && enemy_4.Y == 19)
			{
				SetConsoleCursorPosition(hStdOut, light_right_off_enemy_4);
				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << " ";
						arrmap[light_right_off_enemy_4.Y][light_right_off_enemy_4.X + j] = HALL;
					}
					light_right_off_enemy_4.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_right_off_enemy_4);
				}
				light_right_off_enemy_4.Y += 5;
				light_right_off_enemy_4.X += 1;

				SetConsoleCursorPosition(hStdOut, light_down_enemy_4);
				SetConsoleTextAttribute(hStdOut, WHITE);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << arr_down[i][j];
						arrmap[light_down_enemy_4.Y][light_down_enemy_4.X + j] = LIGHT;
					}
					light_down_enemy_4.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_down_enemy_4);
					SetConsoleTextAttribute(hStdOut, WHITE);
				}
				light_down_enemy_4.Y -= 3;

				light_right_enemy_4 = { 24,17 };
				light_right_off_enemy_4 = { 24,17 };
			}

		}

		// алгоритм движения для пятого врага
		if (enemy_5.X == 23)   // движение пятого врага вверх
		{
			SetConsoleCursorPosition(hStdOut, light_up_off_enemy_5);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << " ";
					arrmap[light_up_off_enemy_5.Y][light_up_off_enemy_5.X + j] = HALL;
				}
				light_up_off_enemy_5.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_up_off_enemy_5);
			}

			enemy_5.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_5.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);
			cout << " ";
			enemy_5.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);

			light_up_enemy_5.Y -= 4;
			SetConsoleCursorPosition(hStdOut, light_up_enemy_5);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << arr_up[i][j];
					arrmap[light_up_enemy_5.Y][light_up_enemy_5.X + j] = LIGHT;
				}
				light_up_enemy_5.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_up_enemy_5);
			}
			light_up_off_enemy_5.Y -= 4;
			SetConsoleCursorPosition(hStdOut, light_up_off_enemy_5);

			Sleep(100);

			if (enemy_5.X == 23 && enemy_5.Y == 19)
			{
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << " ";
						arrmap[light_up_off_enemy_5.Y][light_up_off_enemy_5.X + j] = HALL;
					}
					light_up_off_enemy_5.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_up_off_enemy_5);
				}


				SetConsoleCursorPosition(hStdOut, light_right_enemy_5);
				SetConsoleTextAttribute(hStdOut, WHITE);
				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{

						cout << arr_left_right[i][j];
						arrmap[light_right_enemy_5.Y][light_right_enemy_5.X + j] = LIGHT;
					}
					light_right_enemy_5.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_right_enemy_5);
					SetConsoleTextAttribute(hStdOut, WHITE);
				}
				light_up_enemy_5 = { 20,27 };
				light_up_off_enemy_5 = { 20,27 };
			}
		}
		if (enemy_5.Y == 19)  // движение пятого врага вправо
		{
			SetConsoleCursorPosition(hStdOut, light_right_off_enemy_5);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << " ";
					arrmap[light_right_off_enemy_5.Y][light_right_off_enemy_5.X + j] = HALL;
				}
				light_right_off_enemy_5.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_right_off_enemy_5);
			}
			light_right_off_enemy_5.Y -= 5;
			light_right_off_enemy_5.X += 1;

			enemy_5.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_5.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);
			cout << " ";
			enemy_5.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);

			light_right_enemy_5.Y -= 5;
			light_right_enemy_5.X += 1;
			SetConsoleCursorPosition(hStdOut, light_right_enemy_5);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << arr_left_right[i][j];
					arrmap[light_right_enemy_5.Y][light_right_enemy_5.X + j] = LIGHT;
				}
				light_right_enemy_5.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_right_enemy_5);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}

			Sleep(100);

			if (enemy_5.X == 39 && enemy_5.Y == 19)
			{
				SetConsoleCursorPosition(hStdOut, light_right_off_enemy_5);
				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << " ";
						arrmap[light_right_off_enemy_5.Y][light_right_off_enemy_5.X + j] = HALL;
					}
					light_right_off_enemy_5.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_right_off_enemy_5);
				}
				light_right_off_enemy_5.Y += 5;
				light_right_off_enemy_5.X += 1;

				SetConsoleCursorPosition(hStdOut, light_down_enemy_5);
				SetConsoleTextAttribute(hStdOut, WHITE);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << arr_down[i][j];
						arrmap[light_down_enemy_5.Y][light_down_enemy_5.X + j] = LIGHT;
					}
					light_down_enemy_5.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_down_enemy_5);
					SetConsoleTextAttribute(hStdOut, WHITE);
				}
				light_down_enemy_5.Y -= 3;

				light_right_enemy_5 = { 24,17 };
				light_right_off_enemy_5 = { 24,17 };
			}
		}
		if (enemy_5.X == 39)  // движение пятого врага вниз
		{
			SetConsoleCursorPosition(hStdOut, light_down_off_enemy_5);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << " ";
					arrmap[light_down_off_enemy_5.Y][light_down_off_enemy_5.X + j] = HALL;
				}
				light_down_off_enemy_5.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_down_off_enemy_5);
			}
			light_down_off_enemy_5.Y -= 2;

			enemy_5.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_5.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);
			cout << " ";
			enemy_5.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);

			light_down_enemy_5.Y += 1;
			SetConsoleCursorPosition(hStdOut, light_down_enemy_5);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					cout << arr_down[i][j];
					arrmap[light_down_enemy_5.Y][light_down_enemy_5.X + j] = LIGHT;
				}
				light_down_enemy_5.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_down_enemy_5);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}
			light_down_enemy_5.Y -= 3;

			Sleep(100);

			if (enemy_5.X == 39 && enemy_5.Y == 30)
			{

				SetConsoleCursorPosition(hStdOut, light_down_off_enemy_5);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << " ";
						arrmap[light_down_off_enemy_5.Y][light_down_off_enemy_5.X + j] = HALL;
					}
					light_down_off_enemy_5.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_down_off_enemy_5);
				}

				SetConsoleCursorPosition(hStdOut, light_left_enemy_5);
				SetConsoleTextAttribute(hStdOut, WHITE);

				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << arr_left_right[i][j];
						arrmap[light_left_enemy_5.Y][light_left_enemy_5.X + j] = LIGHT;
					}
					light_left_enemy_5.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_left_enemy_5);
				}
				light_down_enemy_5 = { 36,20 };
				light_down_off_enemy_5 = { 36,20 };
			}
		}
		if (enemy_5.Y == 30)  // движение пятого врага влево
		{
			SetConsoleCursorPosition(hStdOut, light_left_off_enemy_5);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << " ";
					arrmap[light_left_off_enemy_5.Y][light_left_off_enemy_5.X + j] = HALL;
				}
				light_left_off_enemy_5.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_left_off_enemy_5);
			}
			light_left_off_enemy_5.Y -= 5;
			light_left_off_enemy_5.X -= 1;

			enemy_5.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_5.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);
			cout << " ";
			enemy_5.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_5);

			light_left_enemy_5.X -= 1;
			light_left_enemy_5.Y -= 5;
			SetConsoleCursorPosition(hStdOut, light_left_enemy_5);
			SetConsoleTextAttribute(hStdOut, WHITE);
			for (int i = 0; i < P; i++)
			{
				for (int j = 0; j < T; j++)
				{
					cout << arr_left_right[i][j];
					arrmap[light_left_enemy_5.Y][light_left_enemy_5.X + j] = LIGHT;
				}
				light_left_enemy_5.Y += 1;
				SetConsoleCursorPosition(hStdOut, light_left_enemy_5);
				SetConsoleTextAttribute(hStdOut, WHITE);
			}

			Sleep(100);

			if (enemy_5.X == 23 && enemy_5.Y == 30)
			{
				SetConsoleCursorPosition(hStdOut, light_left_off_enemy_5);

				for (int i = 0; i < P; i++)
				{
					for (int j = 0; j < T; j++)
					{
						cout << " ";
						arrmap[light_left_off_enemy_5.Y][light_left_off_enemy_5.X + j] = HALL;
					}
					light_left_off_enemy_5.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_left_off_enemy_5);
				}
				light_left_off_enemy_5.Y -= 5;
				light_left_off_enemy_5.X -= 1;

				SetConsoleCursorPosition(hStdOut, light_up_enemy_5);
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						cout << arr_up[i][j];
						arrmap[light_up_enemy_5.Y][light_up_enemy_5.X + j] = LIGHT;
					}
					light_up_enemy_5.Y += 1;
					SetConsoleCursorPosition(hStdOut, light_up_enemy_5);
				}
				light_left_enemy_5 = { 36, 28 };
				light_left_off_enemy_5 = { 36, 28 };

			}
		}
		
		// алгоритм движения для шестого врага
		if (enemy_6.Y == 12)
		{
			enemy_6.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_6.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			cout << " ";
			enemy_6.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			Sleep(100);
		}
		if (enemy_6.X == 63)
		{
			enemy_6.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_6.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			cout << " ";
			enemy_6.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			Sleep(100);
		}
		if (enemy_6.Y == 3)
		{
			enemy_6.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_6.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			cout << " ";
			enemy_6.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			Sleep(100);
		}
		if (enemy_6.X == 22)
		{
			enemy_6.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_6.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			cout << " ";
			enemy_6.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_6);
			Sleep(100);
		}

		// алгоритм движения седьмого врага
		if (enemy_7.X == 22)
		{
			enemy_7.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_7.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			cout << " ";
			enemy_7.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			Sleep(100);
		}
		if (enemy_7.Y == 12)
		{
			enemy_7.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_7.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			cout << " ";
			enemy_7.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			Sleep(100);
		}
		if (enemy_7.X == 63)
		{
			enemy_7.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_7.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			cout << " ";
			enemy_7.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			Sleep(100);
		}
		if (enemy_7.Y == 3)
		{
			enemy_7.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_7.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			cout << " ";
			enemy_7.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_7);
			Sleep(100);
		}

		// алгоритм движения восьмого врага врага
		if (enemy_8.Y == 3)
		{
			enemy_8.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_8.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			cout << " ";
			enemy_8.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			Sleep(100);
		}
		if (enemy_8.X == 22)
		{
			enemy_8.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_8.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			cout << " ";
			enemy_8.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			Sleep(100);
		}
		if (enemy_8.Y == 12)
		{
			enemy_8.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_8.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			cout << " ";
			enemy_8.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			Sleep(100);
		}
		if (enemy_8.X == 63)
		{
			enemy_8.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_8.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			cout << " ";
			enemy_8.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_8);
			Sleep(100);
		}

		// алгоритм движения девятого врага
		if (enemy_9.X == 63)
		{
			enemy_9.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_9.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			cout << " ";
			enemy_9.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			Sleep(100);
		}
		if (enemy_9.Y == 3)
		{
			enemy_9.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_9.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			cout << " ";
			enemy_9.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			Sleep(100);
		}
		if (enemy_9.X == 22)
		{
			enemy_9.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_9.Y -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			cout << " ";
			enemy_9.Y += 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			Sleep(100);
		}
		if (enemy_9.Y == 12)
		{
			enemy_9.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			SetConsoleTextAttribute(hStdOut, RED);
			cout << (char)2;
			enemy_9.X -= 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			cout << " ";
			enemy_9.X += 1;
			SetConsoleCursorPosition(hStdOut, enemy_9);
			Sleep(100);
		}
	}
}

//функция для отрисовки карты

void init_show_array(int** ptrmap, int N, int P)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < P; j++)
		{
			if (i == 0 || j == 0 || i == N - 1 || j == P - 1)
			{
				ptrmap[i][j] = WALL;
			}
			if (j == 85 && i >= 19 && i <= 20)
			{
				ptrmap[i][j] = DOOR;
			}
			if (i > 20 && j == 115)
			{
				ptrmap[i][j] = WALL;
			}
			if ((i == 21 && j >= 110 && j <= 115) || (i == 21 && j >= 85 && j < 108))
			{
				ptrmap[i][j] = WALL;
			}
			if ((j == 85 && i > 21) || (i == 18 && j >= 85 && j <= 92) || (i == 18 && j >= 100))
			{
				ptrmap[i][j] = WALL;
			}
			if ((j == 85 && i >= 12 && i < 19) || (i == 12 && j >= 85 && j <= 105) || (j == 106 && i >= 12 && i < 19))
			{
				ptrmap[i][j] = WALL;
			}
			if ((j > 85 && j < 106) && (i > 12 && i < 18))  // свет в комнате
			{
				ptrmap[i][j] = LIGHT;
			}
			if ((j >= 93 && j < 100) && (i >= 18 && i < 21))  // свет между комнатой и коридором
			{
				ptrmap[i][j] = LIGHT;
			}
			if ((i == 21 && j >= 79 && j <= 84) || (j == 79 && i > 21 && i <= 30))
			{
				ptrmap[i][j] = WALL;
			}
			if (j == 67 && i > 21 && i < 28)          // отрисовка правой тонкой стенки большой комнаты
			{
				ptrmap[i][j] = WALL_2;
			}
			if (j == 67 && i == 22)
			{
				ptrmap[i][j] = CORNER_WALL_1;
			}
			if (j == 67 && i == 27)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if ((i == 22 && j >= 62 && j < 67) || (i == 27 && j >= 62 && j < 67))
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if ((i == 20 && j == 49) || (i == 20 && j == 46))  // создание небольших перегородок (верхняя)
			{
				ptrmap[i][j] = WALL_2;
			}
			if (i == 19 && j == 49)
			{
				ptrmap[i][j] = CORNER_WALL_1;
			}
			if (i == 19 && j == 46)
			{
				ptrmap[i][j] = CORNER_WALL_3;
			}
			if ((i == 19 && j > 46 && j < 49) || (i == 21 && j > 46 && j < 49))
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 21 && j == 49)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if (i == 21 && j == 46)
			{
				ptrmap[i][j] = CORNER_WALL_4;
			}
			if ((i == 28 && j == 49) || (i == 28 && j == 46))  // создание небольших перегородок (нижняя)
			{
				ptrmap[i][j] = WALL_2;
			}
			if (i == 27 && j == 49)
			{
				ptrmap[i][j] = CORNER_WALL_1;
			}
			if (i == 27 && j == 46)
			{
				ptrmap[i][j] = CORNER_WALL_3;
			}
			if ((i == 27 && j > 46 && j < 49) || (i == 29 && j > 46 && j < 49))
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 29 && j == 49)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if (i == 29 && j == 46)
			{
				ptrmap[i][j] = CORNER_WALL_4;
			}
			if ((i == 24 && j == 49) || (i == 24 && j == 46))  // создание небольших перегородок (средняя)
			{
				ptrmap[i][j] = WALL_2;
			}
			if (i == 23 && j == 49)
			{
				ptrmap[i][j] = CORNER_WALL_1;
			}
			if (i == 23 && j == 46)
			{
				ptrmap[i][j] = CORNER_WALL_3;
			}
			if ((i == 23 && j > 46 && j < 49) || (i == 25 && j > 46 && j < 49))
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 25 && j == 49)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if (i == 25 && j == 46)
			{
				ptrmap[i][j] = CORNER_WALL_4;
			}
			if (i == 22 && j <= 33 && j >= 29)      // создание левой тонкой стены большой комнаты  
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 22 && j == 28)
			{
				ptrmap[i][j] = CORNER_WALL_3;
			}
			if (j == 28 && i > 22 && i <= 27)
			{
				ptrmap[i][j] = WALL_2;
			}
			if (j == 28 && i == 27)
			{
				ptrmap[i][j] = CORNER_WALL_4;
			}
			if (i == 27 && j <= 33 && j >= 29)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (j == 17 && i >= 19 && i <= 30)
			{
				ptrmap[i][j] = WALL;
			}
			if (i == 30 && j < 17 && j >= 12)
			{
				ptrmap[i][j] = WALL;
			}
			if (j == 11 && i <= 30 && i >= 15)
			{
				ptrmap[i][j] = WALL;
			}
			if (i == 15 && j > 11 && j <= 84)  // горизонтальная длинная стена между верхним и нижним уровнем
			{
				ptrmap[i][j] = WALL;
			}
			if ((i == 15 && j >= 1 && j <= 4) || (i == 15 && j >= 7 && j <= 10))
			{
				ptrmap[i][j] = WALL;
			}
			if (i == 15 && j >= 5 && j <= 6)
			{
				ptrmap[i][j] = DOOR_2;
			}
			if ((i == 30 && j == 80) || (i == 30 && j == 84))
			{
				ptrmap[i][j] = WALL;
			}
			if (i == 30 && j > 80 && j < 84)
			{
				ptrmap[i][j] = DOOR_3;
			}
			if (i == 12 && j == 11)   // создание маленьких блоков большой верхней комнаты (левые)
			{
				ptrmap[i][j] = CORNER_WALL_4;
			}
			if (i == 12 && j == 17)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if (i == 12 && j > 11 && j < 17)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 3 && j == 11)
			{
				ptrmap[i][j] = CORNER_WALL_3;
			}
			if (i == 3 && j == 17)
			{
				ptrmap[i][j] = CORNER_WALL_1;
			}
			if (i == 3 && j > 11 && j < 17)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if ((i == 4 && j == 11) || (i == 4 && j == 17) || (i == 11 && j == 11) || (i == 11 && j == 17))
			{
				ptrmap[i][j] = WALL_2;
			}
			if (i == 6 && j == 11)
			{
				ptrmap[i][j] = CORNER_WALL_4;
			}
			if (i == 6 && j == 17)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if (i == 6 && j > 11 && j < 17)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 9 && j == 11)
			{
				ptrmap[i][j] = CORNER_WALL_3;
			}
			if (i == 9 && j == 17)
			{
				ptrmap[i][j] = CORNER_WALL_1;
			}
			if (i == 9 && j > 11 && j < 17)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if ((i == 10 && j == 11) || (i == 10 && j == 17))
			{
				ptrmap[i][j] = WALL_2;
			}
			if ((i == 5 && j == 11) || (i == 5 && j == 17))
			{
				ptrmap[i][j] = WALL_2;
			}
			// Маленькие блоки верхней комнаты (правые)
			if (i == 12 && j == 68)
			{
				ptrmap[i][j] = CORNER_WALL_4;
			}
			if (i == 12 && j == 74)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if (i == 12 && j > 68 && j < 74)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 3 && j == 68)
			{
				ptrmap[i][j] = CORNER_WALL_3;
			}
			if (i == 3 && j == 74)
			{
				ptrmap[i][j] = CORNER_WALL_1;
			}
			if (i == 3 && j > 68 && j < 74)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if ((i == 4 && j == 68) || (i == 4 && j == 74) || (i == 11 && j == 68) || (i == 11 && j == 74))
			{
				ptrmap[i][j] = WALL_2;
			}
			if (i == 6 && j == 68)
			{
				ptrmap[i][j] = CORNER_WALL_4;
			}
			if (i == 6 && j == 74)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if (i == 6 && j > 68 && j < 74)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 9 && j == 68)
			{
				ptrmap[i][j] = CORNER_WALL_3;
			}
			if (i == 9 && j == 74)
			{
				ptrmap[i][j] = CORNER_WALL_1;
			}
			if (i == 9 && j > 68 && j < 74)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if ((i == 10 && j == 68) || (i == 10 && j == 74))
			{
				ptrmap[i][j] = WALL_2;
			}
			if ((i == 5 && j == 68) || (i == 5 && j == 74))
			{
				ptrmap[i][j] = WALL_2;
			}
			// создание в большой верхней комнате центральные блоки
			if (i == 9 && j > 27 && j < 40)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 9 && j == 27)
			{
				ptrmap[i][j] = CORNER_WALL_4;
			}
			if (i == 9 && j == 40)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if (i == 9 && j == 58)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if (i == 9 && j > 45 && j < 58)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 9 && j == 45)
			{
				ptrmap[i][j] = CORNER_WALL_4;
			}
			if (i == 6 && j > 27 && j < 40)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 6 && j == 27)
			{
				ptrmap[i][j] = CORNER_WALL_3;
			}
			if (i == 6 && j == 40)
			{
				ptrmap[i][j] = CORNER_WALL_1;
			}
			if (i == 6 && j == 58)
			{
				ptrmap[i][j] = CORNER_WALL_1;
			}
			if (i == 6 && j > 45 && j < 58)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			if (i == 6 && j == 45)
			{
				ptrmap[i][j] = CORNER_WALL_3;
			}
			if ((i > 6 && i < 9 && j == 40) || (i > 6 && i < 9 && j == 45))
			{
				ptrmap[i][j] = WALL_2;
			}
			if (j == 5 && i > 0 && i < 2)
			{
				ptrmap[i][j] = WALL_2;
			}
			if (i == 2 && j == 5)
			{
				ptrmap[i][j] = CORNER_WALL_2;
			}
			if (i == 2 && j > 1 && j < 5)
			{
				ptrmap[i][j] = DOOR_4;
			}
			if (i == 2 && j == 1)
			{
				ptrmap[i][j] = HORIZONTAL_WALL;
			}
			// Установка выключателя света для маленькой верхней комнаты
			if (i == 33 && j == 114)
			{
				ptrmap[i][j] = SWITCH;
			}
			// установка открытия двери в большой зал
			if (i == 13 && j == 105)
			{
				ptrmap[i][j] = SWITCH_2;
			}
			// установка открывателя фиолетовой двери
			if (i == 29 && j == 14)
			{
				ptrmap[i][j] = SWITCH_3;
			}
			// установка выключателя для зеленной двери
			if (i == 22 && j == 82)
			{
				ptrmap[i][j] = SWITCH_4;
			}
			// установка выключателя для желтой двери
			if (i == 8 && j == 46)
			{
				ptrmap[i][j] = SWITCH_5;
			}


			if (ptrmap[i][j] == WALL)
			{
				SetConsoleTextAttribute(hStdOut, GRAY);
				cout << (char)178;
			}
			else if (ptrmap[i][j] == DOOR)
			{
				SetConsoleTextAttribute(hStdOut, BLUE);
				cout << (char)186;
			}
			else if (ptrmap[i][j] == LIGHT)
			{
				SetConsoleTextAttribute(hStdOut, WHITE);
				cout << (char)176;
			}
			else if (ptrmap[i][j] == WALL_2)
			{
				SetConsoleTextAttribute(hStdOut, GRAY);
				cout << (char)186;
			}
			else if (ptrmap[i][j] == CORNER_WALL_1)
			{
				SetConsoleTextAttribute(hStdOut, GRAY);
				cout << (char)187;
			}
			else if (ptrmap[i][j] == HORIZONTAL_WALL)
			{
				SetConsoleTextAttribute(hStdOut, GRAY);
				cout << (char)205;
			}
			else if (ptrmap[i][j] == CORNER_WALL_2)
			{
				SetConsoleTextAttribute(hStdOut, GRAY);
				cout << (char)188;
			}
			else if (ptrmap[i][j] == CORNER_WALL_3)
			{
				SetConsoleTextAttribute(hStdOut, GRAY);
				cout << (char)201;
			}
			else if (ptrmap[i][j] == CORNER_WALL_4)
			{
				SetConsoleTextAttribute(hStdOut, GRAY);
				cout << (char)200;
			}
			else if (ptrmap[i][j] == DOOR_2)
			{
				SetConsoleTextAttribute(hStdOut, GREEN);
				cout << (char)205;
			}
			else if (ptrmap[i][j] == DOOR_3)
			{
				SetConsoleTextAttribute(hStdOut, PURPLE);
				cout << (char)205;
			}
			else if (ptrmap[i][j] == DOOR_4)
			{
				SetConsoleTextAttribute(hStdOut, GOLD);
				cout << (char)205;
			}
			else if (ptrmap[i][j] == SWITCH)
			{
				SetConsoleTextAttribute(hStdOut, WHITE);
				cout << (char)15;
			}
			else if (ptrmap[i][j] == SWITCH_2)
			{
				SetConsoleTextAttribute(hStdOut, BLUE);
				cout << (char)15;
			}
			else if (ptrmap[i][j] == SWITCH_3)
			{
				SetConsoleTextAttribute(hStdOut, PURPLE);
				cout << (char)15;
			}
			else if (ptrmap[i][j] == SWITCH_4)
			{
				SetConsoleTextAttribute(hStdOut, GREEN);
				cout << (char)15;
			}
			else if (ptrmap[i][j] == SWITCH_5)
			{
				SetConsoleTextAttribute(hStdOut, GOLD);
				cout << (char)15;
			}

			else
			{
				ptrmap[i][j] = HALL;
				cout << " ";
			}
		}
		cout << endl;
	}
}

int main()
{
	//HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(L"Splinter Cell");
	system("mode con cols=140 lines=45");
	ConsoleCursorVisible(false, 100);
	int HEIGHT = 35;
	int WIDTH = 120;
	int** ptrmap = new int *[HEIGHT];
	for (int i = 0; i < HEIGHT; i++)
	{
		ptrmap[i] = new int[WIDTH];
	}
 
	enum direction { DOWN = 80, UP = 72, LEFT = 75, RIGHT = 77,FUNCTION = 102, ATTACK = 113 };

	init_show_array(ptrmap, HEIGHT, WIDTH);
	thread th(DoWork, ptrmap);

	COORD spy = { 117, 33 };
	SetConsoleCursorPosition(hStdOut, spy);
	SetConsoleTextAttribute(hStdOut, GREEN);
	cout << (char)2;
	ptrmap[33][117] = SPY;

	while (true)
	{
		if (_kbhit())
		{
			int direct = _getch();
			if (direct == 224)
			{
				direct = _getch();
			}
			SetConsoleCursorPosition(hStdOut, spy);
			cout << " ";
			
			int offsetX = 0;
			int offsetY = 0;

			switch (direct)
			{
			case UP:
				offsetY -= 1;
				break;
			case DOWN:
				offsetY += 1;
				break;
			case RIGHT:
				offsetX += 1;
				break;
			case LEFT:
				offsetX -= 1;
				break;
			case FUNCTION:
				if ((ptrmap[spy.Y + 1][spy.X] == SWITCH) || (ptrmap[spy.Y][spy.X + 1] == SWITCH))
				{
					int i, j;
					COORD cursorPos;
					
					for ( i = 0; i < HEIGHT; i++)
					{
						for ( j = 0; j < WIDTH; j++)
						{
							if (ptrmap[i][j] == LIGHT)
							{
								ptrmap[i][j] = HALL;
								cursorPos.Y = i;
								cursorPos.X = j;
								SetConsoleCursorPosition(hStdOut, cursorPos);
								cout << " ";
							}
						}
					}
				}
				if ((ptrmap[spy.Y - 1][spy.X] == SWITCH_2) || (ptrmap[spy.Y][spy.X + 1] == SWITCH_2))
				{
					int i, j;
					COORD cursorPos;
					for ( i = 0; i < HEIGHT; i++)
					{
						for ( j = 0; j < WIDTH; j++)
						{
							if (ptrmap[i][j] == DOOR)
							{
								ptrmap[i][j] = HALL;
								cursorPos.Y = i;
								cursorPos.X = j;
								SetConsoleCursorPosition(hStdOut, cursorPos);
								cout << " ";
								SetConsoleCursorPosition(hStdOut, spy);
								SetConsoleTextAttribute(hStdOut, GREEN);
								cout << (char)2;
								Sleep(250);
							}
						}
					}
				}
				if ((ptrmap[spy.Y + 1][spy.X] == SWITCH_3) || (ptrmap[spy.Y][spy.X + 1] == SWITCH_3)||
					(ptrmap[spy.Y][spy.X - 1] == SWITCH_3))
				{
					int i, j;
					COORD cursorPos;
					for (int i = 0; i < HEIGHT; i++)
					{
						for (int j = 0; j < WIDTH; j++) 
						{
							if (ptrmap[i][j] == DOOR_3)
							{
								ptrmap[i][j] = HALL;
								cursorPos.Y = i;
								cursorPos.X = j;
								SetConsoleCursorPosition(hStdOut, cursorPos);
								cout << " ";
								SetConsoleCursorPosition(hStdOut, spy);
								SetConsoleTextAttribute(hStdOut, GREEN);
								cout << (char)2;
								Sleep(250);
							}
						}
					}
				}
				if ((ptrmap[spy.Y - 1][spy.X] == SWITCH_4) || (ptrmap[spy.Y][spy.X + 1] == SWITCH_4) ||
					(ptrmap[spy.Y][spy.X - 1] == SWITCH_4))
				{
					int i, j;
					COORD cursorPos;
					for (int i = 0; i < HEIGHT; i++)
					{
						for (int j = 0; j < WIDTH; j++)
						{
							if (ptrmap[i][j] == DOOR_2)
							{
								ptrmap[i][j] = HALL;
								cursorPos.Y = i;
								cursorPos.X = j;
								SetConsoleCursorPosition(hStdOut, cursorPos);
								cout << " ";
								SetConsoleCursorPosition(hStdOut, spy);
								SetConsoleTextAttribute(hStdOut, GREEN);
								cout << (char)2;
								Sleep(250);
							}
						}
					}

				}
				if ((ptrmap[spy.Y + 1][spy.X] == SWITCH_5) || (ptrmap[spy.Y][spy.X - 1] == SWITCH_5))
				{
					int i, j;
					COORD cursorPos;
					for (i = 0; i < HEIGHT; i++)
					{
						for (j = 0; j < WIDTH; j++)
						{
							if (ptrmap[i][j] == DOOR_4)
							{
								ptrmap[i][j] = HALL;
								cursorPos.Y = i;
								cursorPos.X = j;
								SetConsoleCursorPosition(hStdOut, cursorPos);
								cout << " ";
								SetConsoleCursorPosition(hStdOut, spy);
								SetConsoleTextAttribute(hStdOut, GREEN);
								cout << (char)2;
								Sleep(250);
							}
						}
					}
				}
				else
				{
					SetConsoleCursorPosition(hStdOut, spy);
					SetConsoleTextAttribute(hStdOut, GREEN);
					cout << (char)2;
					continue;
				}
				break;
			}
			if ((ptrmap[spy.Y + offsetY][spy.X + offsetX] != WALL)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != DOOR)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != DOOR_2)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != DOOR_3)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != DOOR_4)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != SWITCH)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != SWITCH_2)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != SWITCH_3) &&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != SWITCH_4) &&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != SWITCH_5) &&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != WALL_2)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != CORNER_WALL_1)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != CORNER_WALL_2)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != CORNER_WALL_3)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != CORNER_WALL_4)&&
				(ptrmap[spy.Y + offsetY][spy.X + offsetX] != HORIZONTAL_WALL))
			{
				spy.X += offsetX;
				spy.Y += offsetY;
			}
			if (spy.X==1&&spy.Y==1)
			{
				MessageBox(NULL, TEXT("Вы прошли уровень!"), TEXT("Сообщение!"), MB_OK);
				break;
			}
			if (ptrmap[spy.Y][spy.X] == LIGHT)
			{
				MessageBox(NULL, TEXT("Вы проиграли, вас заметили!"), TEXT("Сообщение!"), MB_OK);
				break;
			}
			ptrmap[spy.Y][spy.X] = SPY;
			SetConsoleCursorPosition(hStdOut, spy);
			SetConsoleTextAttribute(hStdOut, GREEN);
			cout << (char)2;
			ptrmap[spy.Y - offsetY][spy.X - offsetX] = HALL;
		}
		else
		{
		
		}
	}
	th.join();
	for (int i = 0; i < HEIGHT; i++)
	{
		delete[]ptrmap[i];
	}
	delete[]ptrmap;
	return 0;
}