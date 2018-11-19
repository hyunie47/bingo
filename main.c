#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void initiate_bingo(int **p_user, int **p_comp, int *sel_user, int *sel_comp, int N)
{
   int i, j;
   srand(time(NULL));  

   for (i = 0; i < N; i++)
   {
      for (j = 0; j < N; j++)
      {
         while (1) // 중복되지 않은 수를 뽑을 때까지 while문을 반복한다  
         {
            int num = (rand() % (N*N)) + 1; // 1부터 N*N까지의 수 중 한 개를 선택한다 
            if (sel_user[num - 1] == 0) // 뽑은 숫자에 해당하는 배열의 값이 0이라면 수가 한번도 선택되지 않았다는 의미 
            {
               p_user[i][j] = num; //빙고판에 숫자를 채워넣는다 
               sel_user[num - 1] = 1; // 뽑은 숫자에 해당하는 배열의 값을 1로 채운다 = 숫자가 선택되었다는 의미이다 
               break; // 반복문을 빠져나온다  
            }
         }
      }
   }

   for (i = 0; i < N; i++)
   {
      for (j = 0; j < N; j++)
      {
         while (1)
         {
            int num = (rand() % (N*N)) + 1;
            if (sel_comp[num - 1] == 0)
            {
               p_comp[i][j] = num;
               sel_comp[num - 1] = 1;
               break;
            }
         }
      }
   }
}

void print_bingo(int **p_user, int **p_comp, int N, int bingo_status_user, int bingo_status_comp) {
	
	system("cls"); // 화면을 지운다  
	int i, j_user, j_comp;
	printf("<<<user>>>                      <<<computer>>>\n");
	for (i=0; i<N; i++) { // 사용자와 컴퓨터의 빙고판을 나란히 출력하기 위해서 i값이 고정되어 있을 때 j값이 각각 증가하도록 한다  
		for (j_user=0; j_user<N; j_user++) 
			printf("%2d   ", p_user[i][j_user]); 
		printf("|"); 
		for (j_comp=0; j_comp<N; j_comp++)
			printf("%2d   ", p_comp[i][j_comp]);
		printf("\n");
		}
		printf("사용자 빙고 %d개입니다.       컴퓨터 빙고 %d개입니다.\n", bingo_status_user, bingo_status_comp); 
}


int get_number_byMe(int N, int *number_status) {
	
	int n;
	while (1) { // 중복되지 않고 범위를 초과하지 않는 숫자를 입력할 때까지 while문을 반복한다  
		
		printf("숫자를 입력하세요 >> ");
		scanf("%d", &n);
		
		if (n > N*N)
			printf("범위를 초과하였습니다.\n");
		else if (number_status[n-1] == 1) 
			printf("중복되었습니다.\n");
		else {
			
			number_status[n-1] = 1;	// 중복되지 않은 수가 입력되었으면 1로 변경한다  
			break;
			
		}
		
	}
	return n;
}

int get_number_byComp(int N, int *number_status) {
	
	int n;
	while (1) {
		
		n = (rand()%(N*N)) +1; //1부터 N*N까지의 수 중에서 임의로 선택한다  
		
		if (n > N*N)
			printf("범위를 초과하였습니다.\n");
		else if (number_status[n-1] == 1)
			continue;
		else {
			printf("컴퓨터가 입력한 숫자 >> %d\n", n);
			system("pause"); //컴퓨터가 숫자를 입력한 수를 보기 위해서 화면을 정지한다  
			number_status[n-1] = 1;
			break;
			
		}
	}
	return n;
}

void process_bingo(int **p_user, int **p_comp, int num, int N) {
	
	int i, j;
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			
			if (p_user[i][j] == num) // 사용자의 빙고판에서 입력받은 수와 같은 수가 있는 칸을 -1로 바꾼다  
				p_user[i][j] = -1;
			if (p_comp[i][j] == num) // 컴퓨터의 빙고판에서 입력받은 수와 같은 수가 있는 칸을 -1로 바꾼다  
				p_comp[i][j] = -1;
		}
	}
	
}

int count_bingo(int **p, int N) {
	
	int i, j;
	int sum=0; // 칸 안의 수의 합을 계산하는 변수를 0으로 초기화 한다  
	int result;
	int bingo_num=0;
	
	result = -1*N; // -1로 변경된 수를 N개만큼 더하면 총 -1*N이 된다  
	
	for (i=0; i<N; i++) { //가로 빙고  
		sum=0;
		for (j=0; j<N; j++) 
			sum = sum + p[i][j]; // 가로 한 줄의 합을 구한다  
		if (sum==result) // 숫자의 합과 결과값이 같으면 빙고의 개수가 1개 증가한다  
			bingo_num++; 
	}
	
		
	for (i=0; i<N; i++) { // 세로 빙고  
		sum=0;
		for (j=0; j<N; j++)
			sum = sum + p[j][i];
		if (sum==result)
			bingo_num++;
	}
	
	sum=0;
	for (i=0; i<N; i++) { // 왼쪽 상단에서 오른쪽 하단으로 가는 대각선 빙고  
		sum = sum + p[i][i];
		if (sum==result)
			bingo_num++;		
	}
	
	sum=0;
	for (i=0; i<N; i++) { // 오른쪽 상단에서 왼쪽 하단으로 가는 대각선 빙고  
		sum = sum + p[i][N-1-i];
		if (sum==result)
			bingo_num++;
	}
	return bingo_num;
	
}

int main() {
	
	int N; // 표의 크기를 입력받음
	int **p_user, **p_comp; // 사용자와 컴퓨터의 빙고판의 주소를 가리키는 이중포인터 선언 
	int *sel_user, *sel_comp; // 사용자와 컴퓨터의 빙고판에 채워넣을 랜덤 숫자의 중복 여부를 체크하기 위한 일차원 배열에 대한 포인터 선언 
	int *number_status; // 빙고 게임 진행 중 숫자 중복을 체크하기 위한 배열의 포인터 
	int bingo; // 이기는 데 필요한 빙고의 개수
	int turn=0; // 사용자와 컴퓨터의 순서를 정할 때 몇번째
	int bingo_status_user=0, bingo_status_comp=0; // 사용자와 컴퓨터의 현재 빙고 개수 
	int input_num; // 사용자와 컴퓨터로부터 입력받은 숫자 
	int i; 
	
	printf("수를 입력하세요 >> ");
	scanf("%d", &N);
	
	printf("이기는 데 필요한 빙고의 개수를 입력하세요 >> ");
	scanf("%d", &bingo);
	
	p_user = (int**)malloc(N*sizeof(int*)); // 세로 방향 동적할당 
	p_comp = (int**)malloc(N*sizeof(int*));
	
	for (i=0; i<N; i++) { //사용자와 컴퓨터의 빙고판의 가로 방향 동적할당 
		
		p_user[i] = (int*)malloc(N*sizeof(int));
		p_comp[i] = (int*)malloc(N*sizeof(int));
	} 
	
	sel_user = (int*)malloc((N*N)*sizeof(int)); // 사용자와 컴퓨터의 중복을 체크하기 위한 배열 동적할당 
	sel_comp = (int*)malloc((N*N)*sizeof(int));
	number_status = (int*)malloc((N*N)*sizeof(int));
	
	for (i=0; i<N*N; i++) { // 칸 안의 모든 수를 0으로 초기화 
		
		sel_user[i]=0;
		sel_comp[i]=0;
		number_status[i]=0;
		
	}
	
	initiate_bingo(p_user, p_comp, sel_user, sel_comp, N); // 빙고판을 랜덤숫자로 채워넣는다 
	
	while ((bingo_status_user < bingo) && (bingo_status_comp < bingo)) { // 사용자와 컴퓨터의 빙고 개수가 bingo보다 작은 동안 
		
		print_bingo(p_user, p_comp, N, bingo_status_user, bingo_status_comp); // 빙고판 출력하기 
		if (turn%2==0) { //turn이 짝수일 때는 사용자의 차례이다 
			
			input_num = get_number_byMe(N, number_status); // 사용자에게 숫자를 입력받는다 
			process_bingo(p_user, p_comp, input_num, N); // 선택된 숫자가 있는 칸의 수를 -1로 바꾼다 
			bingo_status_user = count_bingo(p_user, N); // 사용자의 빙고의 개수를 센다 
			bingo_status_comp = count_bingo(p_comp, N); // 컴퓨터의 빙고의 개수를 센다 
			
		}
		
		else {   // turn이 홀수일 때는 컴퓨터의 차례이다 
		
			input_num = get_number_byComp(N, number_status);
			process_bingo(p_user, p_comp, input_num, N);
			bingo_status_user = count_bingo(p_user, N);
			bingo_status_comp = count_bingo(p_comp, N);	
		}
		turn++;
			
	}
	
	print_bingo(p_user, p_comp, N, bingo_status_user, bingo_status_comp); // 최종 상태의 빙고판을 출력한다 
	printf("==================================================\n"); 
	
	if (bingo_status_user > bingo_status_comp) // 사용자의 빙고 개수가 컴퓨터의 빙고 개수보다 많으면 사용자가 이긴다 
		printf("사용자가 이겼습니다.\n");
		
	else if (bingo_status_user < bingo_status_comp) // 컴퓨터의 빙고 개수가 사용자의 빙고 개수보다 많으면 컴퓨터가 이긴다 
		printf("컴퓨터가 이겼습니다.\n");
		
	else
		printf("비겼습니다.\n"); // 빙고 개수가 같다 
		
	
	for (i=0; i<N; i++) // 동적 메모리 반납 
	{
		free(p_comp[i]);
		free(p_user[i]);
	}
	
	free(p_comp);
	free(p_user);
	free(sel_comp);
	free(sel_user);
	free(number_status);
	
	return 0;
		

	
	 
	
}
