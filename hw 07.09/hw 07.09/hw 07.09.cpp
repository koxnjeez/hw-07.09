#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h> //окрашивание
#include <conio.h> // configurate input output
using namespace std;

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //уникальный номер окна консоли (дескриптор)

	srand(time(0));
	const int width = 60, height = 20;
	int maze[height][width] = {};

	// коридоры - 0
	// стены - 1
	// монетки - 2
	// враги - 3

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			maze[y][x] = rand() % 4;

			// установка стен
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
				maze[y][x] = 1;
			}

			// определение точки входа и выхода
			if (x == 0 && y == 2 || x == 1 && y == 2 || x == 2 && y == 2 || x == width - 1 && y == height - 3 || x == width - 2 && y == height - 3 || x == width - 3 && y == height - 3) {
				maze[y][x] = 0;
			}

			if (maze[y][x] == 0) {
				SetConsoleTextAttribute(h, 0); // черные
				cout << " ";
			}
			else if (maze[y][x] == 1) {
				SetConsoleTextAttribute(h, 8); // бирюзовые
				cout << "#";
			}
			else if (maze[y][x] == 2) {
				SetConsoleTextAttribute(h, 14); // ярко-желтый
				cout << ".";
			}
			else if (maze[y][x] == 3) {
				SetConsoleTextAttribute(h, 12); // ярко-красный
				cout << "o";
			}
			else {
				cout << maze[y][x];
			}
		}
		cout << endl;
	}

	// установка курсора в любую координату консоли
	COORD position; // координаты гг
	position.X = 0;
	position.Y = 2;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, 13); // розовый
	cout << "o";

	while (true) {
		int code = _getch(); // get character - получение кода нажатой клавиши
		if (code == 224) // если была нажата стрелочка
		{
			code = _getch();
		}

		COORD hallway;
		hallway.X = position.X;
		hallway.Y = position.Y;

		if (code == 77) {
			if (maze[position.Y][position.X + 1] == 1) {
				continue;
			}
			else {
				SetConsoleCursorPosition(h, hallway);
				cout << " ";
				position.X++; // смещение вправо
				SetConsoleCursorPosition(h, position); // установка курсора в новые коорды
				SetConsoleTextAttribute(h, 13); // розовый
				cout << "o";
			}
		}
		else if (code == 75) {
			if (maze[position.Y][position.X - 1] == 1) {
				continue;
			}
			else {
				SetConsoleCursorPosition(h, hallway);
				cout << " ";
				position.X--; // смещение влево
				SetConsoleCursorPosition(h, position); // установка курсора в новые коорды
				SetConsoleTextAttribute(h, 13); // розовый
				cout << "o";
			}
		}
		else if (code == 72) {
			if (maze[position.Y - 1][position.X] == 1) {
				continue;
			}
			else {
				SetConsoleCursorPosition(h, hallway);
				cout << " ";
				position.Y--; // смещение вверх
				SetConsoleCursorPosition(h, position); // установка курсора в новые коорды
				SetConsoleTextAttribute(h, 13); // розовый
				cout << "o";
			}
		}
		else if (code == 80) {
			if (maze[position.Y + 1][position.X] == 1) {
				continue;
			}
			else {
				SetConsoleCursorPosition(h, hallway);
				cout << " ";
				position.Y++; // смещение вверх
				SetConsoleCursorPosition(h, position); // установка курсора в новые коорды
				SetConsoleTextAttribute(h, 13); // розовый
				cout << "o";
			}
		}
	}

	Sleep(50000); // пауза (5 сек)
}