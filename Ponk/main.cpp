#include <string>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

char framebuffer[80][40];

void clearscreen()//codirobat per evitar flickers
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

struct ball
{
	int X;
	int Y;
	int speedX;
	int speedY;
};

struct paddle
{
	int radi;
	int posY;
	int spd;
};

int gameLoop()
{
	ball pilota1;
	pilota1.speedX = 1;
	pilota1.speedY = 1;
	pilota1.X = 10;
	pilota1.Y = 10;

	paddle paddle1;
	paddle paddle2;
	paddle1.radi = 3;
	paddle1.spd = 0;
	paddle1.posY = 20;
	paddle2.radi = 3;
	paddle2.spd = 0;
	paddle2.posY = 20;


	char mapa[80][40];


	for (int i = 0; i<40; i++)
	{
		for (int j = 0; j<80; j++)
		{
			mapa[j][i] = ' ';
		}

	}
	for (int i = 0; i < 80; i++)
	{
		mapa[i][0] = 'X';
		mapa[i][39] = 'X';
	}
	while (1)
	{
		clearscreen();
		for (int i = 0; i<40; i++)
		{
			for (int j = 0; j<80; j++)
			{
				framebuffer[j][i] = mapa[j][i];
			}
		}
		framebuffer[pilota1.X][pilota1.Y] = 'O';
		for (int i = -1 * (paddle1.radi - 1); i < paddle1.radi; i++)
		{
			framebuffer[0][paddle1.posY + i] = 'I';
		}
		for (int i = -1 * (paddle2.radi - 1); i < paddle2.radi; i++)
		{
			framebuffer[79][paddle2.posY + i] = 'I';
		}


		for (int i = 0; i<40; i++)
		{
			for (int j = 0; j<80; j++)
			{
				cout << framebuffer[j][i];
			}
		}

		//codi
		framebuffer[pilota1.X][pilota1.Y] = ' ';
		if (framebuffer[pilota1.X + pilota1.speedX][pilota1.Y] == 'I')
		{
			pilota1.speedX = pilota1.speedX * -1;
			if (pilota1.X>40) {
				pilota1.speedY += paddle2.spd;
			}
			if (pilota1.X<40) {
				pilota1.speedY += paddle1.spd;
			}

		}
		if (pilota1.X == 0)
		{
			return 2;
		}
		if (pilota1.X == 79)
		{
			return 1;
		}
		if (framebuffer[pilota1.X][pilota1.Y + pilota1.speedY] != ' ')
		{
			pilota1.speedY = pilota1.speedY * -1;
		}
		pilota1.X += pilota1.speedX;
		pilota1.Y += pilota1.speedY;



		//inputs

		paddle1.spd = 0;
		paddle2.spd = 0;



		if (1)
		{

			if (GetAsyncKeyState(VK_DOWN))
			{
				if (paddle2.posY + (paddle2.radi)<39)
				{
					paddle2.posY++;
					paddle2.spd = 1;
				}
			}
			if (GetAsyncKeyState(VK_UP))
			{
				if (paddle2.posY - (paddle2.radi)>0)
				{
					paddle2.posY--;
					paddle2.spd = -1;
				}
			}

			if (GetAsyncKeyState('Q'))
			{
				break;
			}

			if (GetAsyncKeyState('S'))
			{
				if (paddle1.posY + (paddle1.radi)<39)
				{
					paddle1.posY++;
					paddle1.spd = 1;
				}
			}
			if (GetAsyncKeyState('W'))
			{
				if (paddle1.posY - (paddle1.radi)>0)
				{
					paddle1.posY--;
					paddle1.spd = -1;
				}
			}

		}


	}

}

int main()
{
	cout << "Launcher by.." << endl;
	cout << "      _             _    ____   ___  _ " << endl;
	cout << "  ___| | __ _ _ __ | | _|___ \\ / _ \\/ |" << endl;
	cout << " / __| |/ _` | '_ \\| |/ / __) | | | | |" << endl;
	cout << "| (__| | (_| | | | |   < / __/| |_| | |" << endl;
	cout << " \\___|_|\\__,_|_| |_|_|\\_\\_____|\\___/|_|" << endl;
	while (1)
	{
		int option;
		cout << "Escull una opcio" << endl << "1) ComenSar" << endl;
		cin >> option;
		int puntuacio1 = 0;
		int puntuacio2 = 0;
		int guanyador;
		if (option == 1)
		{
			while (1) {
				guanyador = gameLoop();
				if (guanyador == 1) {
					puntuacio1++;
				}
				else puntuacio2++;
				cout << puntuacio1 << ' ' << puntuacio2 << endl;
			}
		}
	}
}