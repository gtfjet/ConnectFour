#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int map[12][13];
int height[7];

void draw_board() {
	int i, j, x;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info = {0};
    info.cbSize       = sizeof(info);
    info.dwFontSize.Y = 36;
    info.FontWeight   = FW_NORMAL;
    wcscpy(info.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(h, FALSE, &info);
	SetConsoleTextAttribute(h,240);//10);
	system("cls");
	printf("~~Connect Four~~\n\n\n");
	for (i=0; i<6; i++) {
		for (j=0; j<7; j++) {
			x = map[5-i+3][j+3];
			printf("|");
			//SetConsoleTextAttribute(h,x*(12-3*x));
			SetConsoleTextAttribute(h,4.5*x*x-10.5*x+255);
			printf("%c",254);
			SetConsoleTextAttribute(h,240);//10);
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

int move_computer() {
	int i, c, bad, n;
	bad = 1;
	c = -1;
	n = 0;
	
	// can I win?
	for (i=0; i<7; i++) {
		if (height[i]!=6) {
			map[height[i]+3][i+3] = 2;
			height[i]++;
			if (check_win(i, 2)) {
				c = i;
			}
			height[i]--;
			map[height[i]+3][i+3] = 0;
		}
	} 
	
	// can you win?
	if (c==-1) {
		for (i=0; i<7; i++) {
			if (height[i]!=6) {
				map[height[i]+3][i+3] = 1;
				height[i]++;
				if (check_win(i, 1)) {
					c = i;
				}
				height[i]--;
				map[height[i]+3][i+3] = 0;
			}
		}
	}
	
	if (c==-1) {
		while(bad==1 && n<100) {
			bad = 0;  // hope for the best
			
			// make random move
			c = rand() % 7;
			while (height[c]==6) {
				c = rand() % 7;
			}
			map[height[c]+3][c+3] = 2;
			height[c]++;
		
			// could you win?
			for (i=0; i<7; i++) {
				if (height[i]!=6) {
					map[height[i]+3][i+3] = 1;
					height[i]++;
					if (check_win(i, 1)) {
						bad = 1;
					}
					height[i]--;
					map[height[i]+3][i+3] = 0;
					
					if (bad==1) {
						break;
					}
				}
			}
			
			// undo move
			height[c]--;
			map[height[c]+3][c+3] = 0;
			
			n++;
		}
	}
	
	// make move!
	map[height[c]+3][c+3] = 2;
	height[c]++;
	return c;
}

void main() {
	int i, c, u;
	srand(time(NULL));
	draw_board();
	printf("\n");
	for (i=0; i<21; i++) {
		printf("Player: ");
		scanf("%d", &u);
		while (u<1 || u>7 || height[u-1]==6) {
			printf("bad input value\n");
			printf("Player: ");
			scanf("%d", &u);
		}
		u--;  // switch to zero based
		map[height[u]+3][u+3] = 1;
		height[u]++;
		draw_board();
		if (check_win(u, 1)) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),249);
			printf("Player wins!\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
			system("pause");
			return;
		}
		c = move_computer();
		draw_board();
		printf("Computer: %d\n",c+1);
		if (check_win(c, 2)) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),252);
			printf("Computer wins!\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
			system("pause");
			return;
		}
	}
	printf("Draw!\n");
	system("pause");
	return;
}






/*	
	// check vertically
	if (map[y-1][x] == b && map[y-2][x] == b && height[u]!=6) {
		c = u;
		
 	// check horizontally 
	} else if (map[y][x-2] == b && map[y][x-1] == b && u < 6 && map[y][x+1] == 0 && height[u+1]==height[u]) {
		c = u+1;
 	} else if (map[y][x-2] == b && map[y][x-1] == b && u > 2 && map[y][x-3] == 0 && height[u-3]==height[u]) {
		c = u-3;
	} else if (map[y][x-1] == b && map[y][x+1] == b && u < 5 && map[y][x+2] == 0 && height[u+2]==height[u]) {
		c = u+2;
	} else if (map[y][x-1] == b && map[y][x+1] == b && u > 1 && map[y][x-2] == 0 && height[u-2]==height[u]) {
		c = u-2;
	} else if (map[y][x+1] == b && map[y][x+2] == b && u < 4 && map[y][x+3] == 0 && height[u+3]==height[u]) {
		c = u+3;
	} else if (map[y][x+1] == b && map[y][x+2] == b && u > 0 && map[y][x-1] == 0 && height[u+1]==height[u]) {
		c = u-1; 
	
	//} else if (map[y][x-1] == b && map[y][x+1] == b && map[y][x+2] == b) {
	//} else if (map[y][x+1] == b && map[y][x+2] == b && map[y][x+3] == b) {

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
		return 1; */