#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;

#define HEIGHT 6
#define WIDTH 10
#define WINCOUNT 4

int board[HEIGHT][WIDTH];

void gotoxy(short x, short y) { // ��ǥ �̵�
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void printBoard();
void clearBoard();
int win();	// ������ �¸� �ߴ��� �˷���

int main()
{
	int input = 0, count = 1, winner = 0;
	std::string name[3];

	cout << "�г����� �����ּ���" << endl;
	cout << "1�� : "; cin >> name[1];
	cout << "2�� : "; cin >> name[2];
	
	system("mode con cols=50 lines=15");
	while (true) {
		system("cls");
		printBoard();
//		cout << endl << endl;
		gotoxy(0, HEIGHT + 3);
		if (winner != 0) {
			cout << "�����մϴ�! " << winner << "��(" << name[winner] << ") ��!" << endl;
			cout << "��� �Ͻðڽ��ϱ�? (y/n) ";
			char ch; cin >> ch;
			if (ch == 'y' || ch == 'Y') {
				clearBoard();
				count = 1;
				winner = 0;
				continue;
			}
			else if (ch == 'n' || ch == 'N') {
				cout << "������ �����մϴ�" << endl;
				break;
			}
			else
				break;
		}
		cout << "(" << count << "��)" << endl;
		bool flag = count % 2 == 1 ? true : false;
		if (flag)
			cout << "1��(" << name[1] << ") ���� ��>> ";
		else
			cout << "2��(" << name[2] << ") ���� ��>> ";
		cin >> input;
		if (!(input >= 0 && input <= WIDTH - 1)) continue;

		int h = 0;
		while (board[h][input] == 0) {
			h++;
			if (h >= HEIGHT) break;
		}

		if (h == 0) continue;
		board[h - 1][input] = flag ? 1 : 2;

		winner = win();

		count++;
	}
}

int win() {
	bool horizontal = false;
	bool vertical = true;
	bool diagnalLeftDown = true;	// diagnal : �밢��
	bool diagnalRightDown = true;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (board[y][x] != 0) 
			{
				if (x + WINCOUNT - 1 <= WIDTH && board[y][x] == board[y][x + 1] && board[y][x] == board[y][x + 2] && board[y][x] == board[y][x + 3])
					horizontal = true;
				for (int i = 1; i < WINCOUNT; i++)
				{
					if (y + WINCOUNT - 1 >= HEIGHT || board[y][x] != board[y + i][x])
						vertical = false;
					if (x - WINCOUNT <= 0 || y + WINCOUNT - 1 >= HEIGHT || board[y][x] != board[y + i][x - i])
						diagnalLeftDown = false;
					if (x + WINCOUNT - 1 >= WIDTH || y + WINCOUNT - 1 >= HEIGHT || board[y][x] != board[y + i][x + i])
						diagnalRightDown = false;
				}
				if (horizontal || vertical || diagnalLeftDown || diagnalRightDown)
					return board[y][x];
			}
		}
	}
	return 0;
}

void printBoard() {
	for (int i = 0; i < WIDTH; i++)
		cout << setw(2) << i;
	for (int i = 0; i < HEIGHT; i++) {
		cout << endl;
		for (int j = 0; j < WIDTH; j++) {
			switch (board[i][j]) {
			case 0:
				cout << "  ";
				break;
			case 1:
				cout << "��";//��
				break;
			case 2:
				cout << "��";
				break;
			}
		}
	}
}

void clearBoard() {
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			board[i][j] = 0;
}