//#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int map[12][13];
int height[7];

void draw_board() {
	int i, j, x;
	system("cls");
	printf("~~~~Connect Four~~~~\nPlayer 1 = o\nPlayer 2 = x\n\n\n");
	for (i=0; i<6; i++) {
		for (j=0; j<7; j++) {
			x = map[5-i+3][j+3];
			printf("|%c",-35*x*x + 114*x + 32);  //ascii conversion
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


void main() {
	int i, c, u, b;
	srand(12);
	draw_board();
	
	for (i=0; i<42; i++) {
		b = i % 2 + 1;
		printf("Player %d: ",b);
		scanf("%d", &u);
		while (u<1 || u>7 || height[u-1]==6) {
			printf("bad input value\n");
			printf("Player %d: ",b);
			scanf("%d", &u);
		}
		
		u--;  // switch to zero based
		map[height[u]+3][u+3] = b;
		height[u]++;
		draw_board();
		
		if (check_win(u, b)) {
			printf("Player %d wins!\n", b);
			system("pause");
			return;
		}
	}
	printf("Draw!\n");
	system("pause");
	return;
}





/* 	
	for (i=0; i<10; i++) {
		c = rand() % 7;
		printf("c = %d\n",c+1);
		map[height[c]][c] = 2;
		height[c]++;
	} 
	draw_board(); 
*/


/*
	h = height[u]-1;
	
	// check vertically
	if (height[u] >= 4 && map[h-1][u] == 2 && map[h-2][u] == 2 && map[h-3][u] == 2) {
		return 1; 
		
	// check horizontally 
	} else if (u==0 && map[h][1] == 2 && map[h][2] == 2 && map[h][3] == 2) {
		return 1;  
	} else if (u==1 && map[h][0] == 2 && map[h][2] == 2 && map[h][3] == 2) {
		return 1;
	} else if (u==1 && map[h][2] == 2 && map[h][3] == 2 && map[h][4] == 2) {
		return 1;
	} else if (u==2 && map[h][0] == 2 && map[h][1] == 2 && map[h][3] == 2) {
		return 1;
	} else if (u==2 && map[h][1] == 2 && map[h][3] == 2 && map[h][4] == 2) {
		return 1;
	} else if (u==2 && map[h][3] == 2 && map[h][4] == 2 && map[h][5] == 2) {
		return 1;
	} else if (u==3 && map[h][0] == 2 && map[h][1] == 2 && map[h][2] == 2) {
		return 1;
	} else if (u==3 && map[h][1] == 2 && map[h][2] == 2 && map[h][4] == 2) {
		return 1;
	} else if (u==3 && map[h][2] == 2 && map[h][4] == 2 && map[h][5] == 2) {
		return 1;
	} else if (u==3 && map[h][4] == 2 && map[h][5] == 2 && map[h][6] == 2) {
		return 1;
	} else if (u==4 && map[h][1] == 2 && map[h][2] == 2 && map[h][3] == 2) {
		return 1;
	} else if (u==4 && map[h][2] == 2 && map[h][3] == 2 && map[h][5] == 2) {
		return 1;
	} else if (u==4 && map[h][3] == 2 && map[h][5] == 2 && map[h][6] == 2) {
		return 1;
	} else if (u==5 && map[h][2] == 2 && map[h][3] == 2 && map[h][4] == 2) {
		return 1;
	} else if (u==5 && map[h][3] == 2 && map[h][4] == 2 && map[h][6] == 2) {
		return 1;
	} else if (u==6 && map[h][3] == 2 && map[h][4] == 2 && map[h][5] == 2) {
		return 1;
	} else {
		return 0;
	}
*/
