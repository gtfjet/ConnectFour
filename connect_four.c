#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void main() {

	int r;
	srand(time(NULL));
	r	= rand();
	printf("r = %d\n");
}