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
         while (1) // �ߺ����� ���� ���� ���� ������ while���� �ݺ��Ѵ�  
         {
            int num = (rand() % (N*N)) + 1; // 1���� N*N������ �� �� �� ���� �����Ѵ� 
            if (sel_user[num - 1] == 0) // ���� ���ڿ� �ش��ϴ� �迭�� ���� 0�̶�� ���� �ѹ��� ���õ��� �ʾҴٴ� �ǹ� 
            {
               p_user[i][j] = num; //�����ǿ� ���ڸ� ä���ִ´� 
               sel_user[num - 1] = 1; // ���� ���ڿ� �ش��ϴ� �迭�� ���� 1�� ä��� = ���ڰ� ���õǾ��ٴ� �ǹ��̴� 
               break; // �ݺ����� �������´�  
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
	
	system("cls"); // ȭ���� �����  
	int i, j_user, j_comp;
	printf("<<<user>>>                      <<<computer>>>\n");
	for (i=0; i<N; i++) { // ����ڿ� ��ǻ���� �������� ������ ����ϱ� ���ؼ� i���� �����Ǿ� ���� �� j���� ���� �����ϵ��� �Ѵ�  
		for (j_user=0; j_user<N; j_user++) 
			printf("%2d   ", p_user[i][j_user]); 
		printf("|"); 
		for (j_comp=0; j_comp<N; j_comp++)
			printf("%2d   ", p_comp[i][j_comp]);
		printf("\n");
		}
		printf("����� ���� %d���Դϴ�.       ��ǻ�� ���� %d���Դϴ�.\n", bingo_status_user, bingo_status_comp); 
}


int get_number_byMe(int N, int *number_status) {
	
	int n;
	while (1) { // �ߺ����� �ʰ� ������ �ʰ����� �ʴ� ���ڸ� �Է��� ������ while���� �ݺ��Ѵ�  
		
		printf("���ڸ� �Է��ϼ��� >> ");
		scanf("%d", &n);
		
		if (n > N*N)
			printf("������ �ʰ��Ͽ����ϴ�.\n");
		else if (number_status[n-1] == 1) 
			printf("�ߺ��Ǿ����ϴ�.\n");
		else {
			
			number_status[n-1] = 1;	// �ߺ����� ���� ���� �ԷµǾ����� 1�� �����Ѵ�  
			break;
			
		}
		
	}
	return n;
}

int get_number_byComp(int N, int *number_status) {
	
	int n;
	while (1) {
		
		n = (rand()%(N*N)) +1; //1���� N*N������ �� �߿��� ���Ƿ� �����Ѵ�  
		
		if (n > N*N)
			printf("������ �ʰ��Ͽ����ϴ�.\n");
		else if (number_status[n-1] == 1)
			continue;
		else {
			printf("��ǻ�Ͱ� �Է��� ���� >> %d\n", n);
			system("pause"); //��ǻ�Ͱ� ���ڸ� �Է��� ���� ���� ���ؼ� ȭ���� �����Ѵ�  
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
			
			if (p_user[i][j] == num) // ������� �����ǿ��� �Է¹��� ���� ���� ���� �ִ� ĭ�� -1�� �ٲ۴�  
				p_user[i][j] = -1;
			if (p_comp[i][j] == num) // ��ǻ���� �����ǿ��� �Է¹��� ���� ���� ���� �ִ� ĭ�� -1�� �ٲ۴�  
				p_comp[i][j] = -1;
		}
	}
	
}

int count_bingo(int **p, int N) {
	
	int i, j;
	int sum=0; // ĭ ���� ���� ���� ����ϴ� ������ 0���� �ʱ�ȭ �Ѵ�  
	int result;
	int bingo_num=0;
	
	result = -1*N; // -1�� ����� ���� N����ŭ ���ϸ� �� -1*N�� �ȴ�  
	
	for (i=0; i<N; i++) { //���� ����  
		sum=0;
		for (j=0; j<N; j++) 
			sum = sum + p[i][j]; // ���� �� ���� ���� ���Ѵ�  
		if (sum==result) // ������ �հ� ������� ������ ������ ������ 1�� �����Ѵ�  
			bingo_num++; 
	}
	
		
	for (i=0; i<N; i++) { // ���� ����  
		sum=0;
		for (j=0; j<N; j++)
			sum = sum + p[j][i];
		if (sum==result)
			bingo_num++;
	}
	
	sum=0;
	for (i=0; i<N; i++) { // ���� ��ܿ��� ������ �ϴ����� ���� �밢�� ����  
		sum = sum + p[i][i];
		if (sum==result)
			bingo_num++;		
	}
	
	sum=0;
	for (i=0; i<N; i++) { // ������ ��ܿ��� ���� �ϴ����� ���� �밢�� ����  
		sum = sum + p[i][N-1-i];
		if (sum==result)
			bingo_num++;
	}
	return bingo_num;
	
}

int main() {
	
	int N; // ǥ�� ũ�⸦ �Է¹���
	int **p_user, **p_comp; // ����ڿ� ��ǻ���� �������� �ּҸ� ����Ű�� ���������� ���� 
	int *sel_user, *sel_comp; // ����ڿ� ��ǻ���� �����ǿ� ä������ ���� ������ �ߺ� ���θ� üũ�ϱ� ���� ������ �迭�� ���� ������ ���� 
	int *number_status; // ���� ���� ���� �� ���� �ߺ��� üũ�ϱ� ���� �迭�� ������ 
	int bingo; // �̱�� �� �ʿ��� ������ ����
	int turn=0; // ����ڿ� ��ǻ���� ������ ���� �� ���°
	int bingo_status_user=0, bingo_status_comp=0; // ����ڿ� ��ǻ���� ���� ���� ���� 
	int input_num; // ����ڿ� ��ǻ�ͷκ��� �Է¹��� ���� 
	int i; 
	
	printf("���� �Է��ϼ��� >> ");
	scanf("%d", &N);
	
	printf("�̱�� �� �ʿ��� ������ ������ �Է��ϼ��� >> ");
	scanf("%d", &bingo);
	
	p_user = (int**)malloc(N*sizeof(int*)); // ���� ���� �����Ҵ� 
	p_comp = (int**)malloc(N*sizeof(int*));
	
	for (i=0; i<N; i++) { //����ڿ� ��ǻ���� �������� ���� ���� �����Ҵ� 
		
		p_user[i] = (int*)malloc(N*sizeof(int));
		p_comp[i] = (int*)malloc(N*sizeof(int));
	} 
	
	sel_user = (int*)malloc((N*N)*sizeof(int)); // ����ڿ� ��ǻ���� �ߺ��� üũ�ϱ� ���� �迭 �����Ҵ� 
	sel_comp = (int*)malloc((N*N)*sizeof(int));
	number_status = (int*)malloc((N*N)*sizeof(int));
	
	for (i=0; i<N*N; i++) { // ĭ ���� ��� ���� 0���� �ʱ�ȭ 
		
		sel_user[i]=0;
		sel_comp[i]=0;
		number_status[i]=0;
		
	}
	
	initiate_bingo(p_user, p_comp, sel_user, sel_comp, N); // �������� �������ڷ� ä���ִ´� 
	
	while ((bingo_status_user < bingo) && (bingo_status_comp < bingo)) { // ����ڿ� ��ǻ���� ���� ������ bingo���� ���� ���� 
		
		print_bingo(p_user, p_comp, N, bingo_status_user, bingo_status_comp); // ������ ����ϱ� 
		if (turn%2==0) { //turn�� ¦���� ���� ������� �����̴� 
			
			input_num = get_number_byMe(N, number_status); // ����ڿ��� ���ڸ� �Է¹޴´� 
			process_bingo(p_user, p_comp, input_num, N); // ���õ� ���ڰ� �ִ� ĭ�� ���� -1�� �ٲ۴� 
			bingo_status_user = count_bingo(p_user, N); // ������� ������ ������ ���� 
			bingo_status_comp = count_bingo(p_comp, N); // ��ǻ���� ������ ������ ���� 
			
		}
		
		else {   // turn�� Ȧ���� ���� ��ǻ���� �����̴� 
		
			input_num = get_number_byComp(N, number_status);
			process_bingo(p_user, p_comp, input_num, N);
			bingo_status_user = count_bingo(p_user, N);
			bingo_status_comp = count_bingo(p_comp, N);	
		}
		turn++;
			
	}
	
	print_bingo(p_user, p_comp, N, bingo_status_user, bingo_status_comp); // ���� ������ �������� ����Ѵ� 
	printf("==================================================\n"); 
	
	if (bingo_status_user > bingo_status_comp) // ������� ���� ������ ��ǻ���� ���� �������� ������ ����ڰ� �̱�� 
		printf("����ڰ� �̰���ϴ�.\n");
		
	else if (bingo_status_user < bingo_status_comp) // ��ǻ���� ���� ������ ������� ���� �������� ������ ��ǻ�Ͱ� �̱�� 
		printf("��ǻ�Ͱ� �̰���ϴ�.\n");
		
	else
		printf("�����ϴ�.\n"); // ���� ������ ���� 
		
	
	for (i=0; i<N; i++) // ���� �޸� �ݳ� 
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
