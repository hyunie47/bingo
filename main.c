#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void initiate_bingo() {
	
	int N; //1부터 N*N까지의 수  
	int i, j; //빙고판에서 i는 가로줄, j는 세로줄 
	
	scanf("%d", &N);
	printf("Enter a number>>");
	
	int bingo_board_me[N][N]; //나의 빙고판 선언
	int bingo_board_comp[N][N]; //컴퓨터의 빙고판 선언 
	
	int sel_me[N*N]; //sel은 배열된 N*N개의 수를 배열해놓고 그 중 하나를 고름 
	int sel_comp[N*N];  
	 
}
