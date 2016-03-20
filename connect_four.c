#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int map[12][13];
int height[7];
int win, loss, draw;
int total[7];

void draw_board() {
	int i, j, x;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	printf("~~Connect Four~~\n\n");
	SetConsoleTextAttribute(h,249);
	printf("%d",win);
	SetConsoleTextAttribute(h,240);
	printf("/");
	SetConsoleTextAttribute(h,252);
	printf("%d",loss);	
	SetConsoleTextAttribute(h,240);
	printf("/");
	SetConsoleTextAttribute(h,250);
	printf("%d\n\n",draw);
	SetConsoleTextAttribute(h,240);
		
	for (i=0; i<6; i++) {
		for (j=0; j<7; j++) {
			x = map[5-i+3][j+3];
			printf("|");
			SetConsoleTextAttribute(h,4.5*x*x-10.5*x+255);
			printf("%c",254);
			SetConsoleTextAttribute(h,240);
		}
		printf("|\n");
	}
	printf("\n|1|2|3|4|5|6|7|\n\n");
}

int check_win(int u, int b) {
	int x = u+3;
	int y = height[u]-1+3;
	
	// check vertically
	if (map[y-1][x] == b && map[y-2][x] == b && map[y-3][x] == b) {
		return 1; 
		
	// check horizontally 
	} else if (map[y][x-3] == b && map[y][x-2] == b && map[y][x-1] == b) {
		return 1;
	} else if (map[y][x-2] == b && map[y][x-1] == b && map[y][x+1] == b) {
		return 1;
	} else if (map[y][x-1] == b && map[y][x+1] == b && map[y][x+2] == b) {
		return 1;
	} else if (map[y][x+1] == b && map[y][x+2] == b && map[y][x+3] == b) {
		return 1;
	
	// check diagonally 
	} else if (map[y-3][x-3] == b && map[y-2][x-2] == b && map[y-1][x-1] == b) {
		return 1;
	} else if (map[y-2][x-2] == b && map[y-1][x-1] == b && map[y+1][x+1] == b) {
		return 1;
	} else if (map[y-1][x-1] == b && map[y+1][x+1] == b && map[y+2][x+2] == b) {
		return 1;
	} else if (map[y+1][x+1] == b && map[y+2][x+2] == b && map[y+3][x+3] == b) {
		return 1;
	} else if (map[y+3][x-3] == b && map[y+2][x-2] == b && map[y+1][x-1] == b) {
		return 1;
	} else if (map[y+2][x-2] == b && map[y+1][x-1] == b && map[y-1][x+1] == b) {
		return 1;
	} else if (map[y+1][x-1] == b && map[y-1][x+1] == b && map[y-2][x+2] == b) {
		return 1;
	} else if (map[y-1][x+1] == b && map[y-2][x+2] == b && map[y-3][x+3] == b) {
		return 1;

	// otherwise.. 
	} else {
		return 0;
	}
}

// zero based get max's index
int get_max() {
	int i, c, max;
	c = -1;
	max = 0;
	for (i=0; i<7; i++) {
		if (height[i]!=6) {
			if (c==-1 || total[i]>max)
			{
				max = total[i];
				c = i;
			}
		}
	}
	if (total[0]==0 && total[1]==0 && total[2]==0 && total[3]==0 && total[4]==0 && total[5]==0 && total[6]==0) {
		// pick random
		c = rand() % 7;
		while (height[c]==6) {
			c = rand() % 7;
		}
	}
	return c;
}

void count_wins(int n, int r) {
	int i, b;
	b = n%2 + 1;
	
	if (n < 7) {
		for (i=0; i<7; i++) {
			if (height[i]!=6) {
				map[height[i]+3][i+3] = b;  //b to i
				height[i]++;
				if (check_win(i, b)) {
					if (b==1) {
						total[r] += -1;   //if player won
					} else {
						total[r] += 1;   //if computer won
					}
				} else {
					count_wins(n+1, r);  //recusive
				}
				height[i]--;
				map[height[i]+3][i+3] = 0;	//b from i
			}
		}
	}
}

int move_computer() {
	int i, c;
	for (i=0; i<7; i++) {
		if (height[i]!=6) {
			map[height[i]+3][i+3] = 2;  //comp to i
			height[i]++;
			if (check_win(i, 2)) {
				return i;
			}
			height[i]--;
			map[height[i]+3][i+3] = 0;	//comp from i
		}
	} 	
	memset(total, 0, sizeof total);
	for (i=0; i<7; i++) {
		if (height[i]!=6) {
			map[height[i]+3][i+3] = 2;  //comp to i
			height[i]++;
			count_wins(0,i);
			height[i]--;
			map[height[i]+3][i+3] = 0;	//comp from i
		}
	}
	c = get_max();			
	map[height[c]+3][c+3] = 2;  //comp to c
	height[c]++;
	return c;
}

int move_player() {
	int u;
	printf("Player: ");
	scanf("%d", &u);
	getchar();
	while (u<1 || u>7 || height[u-1]==6) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),247);
		printf("bad input value\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
		printf("Player: ");
		scanf("%d", &u);
		getchar();
	}
	u--;  // switch to zero based
	map[height[u]+3][u+3] = 1;
	height[u]++;
	return u;
}

void main() {
	int i, c, u, n;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT size = {0,0,17,17};
	COORD coord = {18,18};
	CONSOLE_FONT_INFOEX info = {0};
	info.cbSize = sizeof(info);
    info.dwFontSize.Y = 36;
    info.FontWeight = FW_NORMAL;
    wcscpy(info.FaceName, L"Lucida Console");
	SetConsoleWindowInfo(h, TRUE, &size);
	SetConsoleScreenBufferSize(h, coord);
    SetCurrentConsoleFontEx(h, FALSE, &info);
	SetConsoleTextAttribute(h,240);
	srand(time(NULL));
	n = 0;

	while(1) {
		memset(map, 0, sizeof map);
		memset(height, 0, sizeof height);
		draw_board();
		printf("\n");
		
		for (i=0; i<21; i++) {
			if (n%2 == 0) {
				u = move_player();
				draw_board();
				if (check_win(u, 1)) {
					win++;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),249);
					printf("Player wins!\n");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
					break;
				}
			}
			c = move_computer();
			draw_board();
			//printf("%d,%d,%d,%d,%d,%d,%d\n",total[0],total[1],total[2],total[3],total[4],total[5],total[6]);
			printf("Computer: %d\n",c+1);
			if (check_win(c, 2)) {
				loss++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),252);
				printf("Computer wins!\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
				break;
			}
			if (n%2 == 1) {
				u = move_player();
				draw_board();
				if (check_win(u, 1)) {
					win++;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),249);
					printf("Player wins!\n");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
					break;
				}
			}
			if (i==20) {
				draw++;
				(GetStdHandle(STD_OUTPUT_HANDLE),250);
				printf("Draw!\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
			}
		}
		n++;
		getchar();
	}
}
