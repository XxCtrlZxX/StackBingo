#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;

#define HEIGHT 6
#define WIDTH 10
#define WINCOUNT 4

int board[HEIGHT][WIDTH];

void gotoxy(short x, short y) { // 좌표 이동
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printBoard();
void clearBoard();
int win();		// 몇픽이 승리 했는지 알려줌
bool win_Judge(int x, int y);

class XY {
public:
	int x;
	int y;
	bool flag;
	void set(int x_, int y_, bool flag_) {
		x = x_;
		y = y_;
		flag = flag_;
	}
};

XY H, V, LD, RD;

int main()
{
	int input = 0, count = 1, winner = 0;
	std::string name[3];
	
	system("mode con cols=50 lines=15");
	
	cout << "닉네임을 적어주세요" << endl;
	cout << "1픽 : "; cin >> name[1];
	cout << "2픽 : "; cin >> name[2];
	
	while (true) {
		system("cls");
		printBoard();
//		cout << endl << endl;
		gotoxy(0, HEIGHT + 3);
		if (winner != 0) {
			cout << "축하합니다! " << winner << "픽(" << name[winner] << ") 승!" << endl;
			cout << "계속 하시겠습니까? (y/n) ";
			char ch; cin >> ch;
			if (ch == 'y' || ch == 'Y') {
				clearBoard();
				count = 1;
				winner = 0;
				continue;
			}
			else if (ch == 'n' || ch == 'N') {
				cout << "\n게임을 종료합니다" << endl;
				break;
			}
			else
				break;
		}
		cout << "(" << count << "턴)" << endl;
		bool flag = count % 2 == 1 ? true : false;
		if (flag)
			cout << "1픽(" << name[1] << ") 차례 ○>> ";
		else
			cout << "2픽(" << name[2] << ") 차례 ●>> ";
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
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			if (board[y][x] != 0)
				if (win_Judge(x, y)) {
					// TODO : 빙고 된 부분 빨간색으로 칠하는 함수
					return board[y][x];
				}
	return 0;
}

//*****************//
bool win_Judge(int x, int y) {

	H.set(x, y, true);
	V.set(x, y, true);
	LD.set(x, y, true);
	RD.set(x, y, true);

	int cnt = 0;
	while (H.flag || V.flag || LD.flag || RD.flag) {

		cnt++;

		// horizontal
		if (H.x + 1 < WIDTH) {
			if (board[H.y][H.x + 1] == board[H.y][H.x])
				H.x++;
			else
				H.flag = false;
		}
		else
			H.flag = false;

		// vertical
		if (V.y + 1 < HEIGHT) {
			if (board[V.y + 1][V.x] == board[V.y][V.x])
				V.y++;
			else
				V.flag = false;
		}
		else
			V.flag = false;

		// diagnal Left Down
		if (LD.x > 0 && LD.y + 1 < HEIGHT) {
			if (board[LD.y + 1][LD.x - 1] == board[LD.y][LD.x]) {
				LD.x--;
				LD.y++;
			}
			else
				LD.flag = false;
		}
		else
			LD.flag = false;

		// diagnal Right Down
		if (RD.x > 0 && RD.y + 1 < HEIGHT) {
			if (board[RD.y + 1][RD.x + 1] == board[RD.y][RD.x]) {
				RD.x++;
				RD.y++;
			}
			else
				RD.flag = false;
		}
		else
			RD.flag = false;
	}

	if (cnt == WINCOUNT)
		return true;

	return false;
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
				cout << "○";//◎
				break;
			case 2:
				cout << "●";
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