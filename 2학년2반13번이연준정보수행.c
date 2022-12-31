/*=============================================================================
			�ۼ��� : �����а� 2�г� 2�� 13�� �̿��� 
		���α׷��� : ���ܾ� ���� ���� �� ȿ���� �м� 
	�Է����� ����
	1. ���� �� �� ���� : ��� ���ڰ� ���� �빮�ڷθ� �̷��������
								test_.txt (_:��ȣ, 1���� ���� (1<=_<=n))
	2. ���� ���� ���� : ��� ���ڰ� ���� �빮�� Ȥ�� �������� �̷��������
								collet_.txt (_:��ȣ, 1���� ���� (1<=_<=n))
	3. �ܾ� ���� ���� : ��� ���ڰ� ���� �빮�ڷ� �Ǿ��־���ϸ�,
						���ͷ� ���еǾ���
						realword.txt 
=============================================================================*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h> 

#define MaxWord 68				//���� ������ �ܾ��� �ִ� ���ڼ� : 68 
#define MaxSten 2<<10			//���� �˻��� ������ �ִ� ���ڼ� : 2048 (����) 
#define testcount 8				//test ������ ��

// �Լ� 
// 1. �⺻ 
void explain();					// ���α׷� ����
int selexplain();				// ���� ����
void prexplain();				// ���� ���α׷� ����
void spexplain();				// ��ġ�� ��� �˰��� ���� 
// ������ ���������� ��� �ִ��� �˻� : ������ � ������ ���� �� �˷��ְ� ����
int chFile();
// ���α׷� ����, ȿ���� �м�, ���� ���� 
int selmode();

// 2. ���ܾ� ����
// 2.0 ���ܾ� ���� ��������
int Iswordin(char plword[]);	//���� �˻��� �ܾ �������Ͽ� �ִ��� Ȯ�� 
int len(char text[]);			//�ܾ� ���̸� ���� �Լ�, ���̽��� len(a) 
void clear(int max);			//������ �ܾ�ִ� ������ \0���� �ʱ�ȭ 
void slycing(int a, int b);		//���ڿ� �����̽�, ���̽��� tmp[1, 3]�� slycing(1, 3)���� ��ü! 

// 2.1 ���α׷�1 (�� ���� Ȯ��)
void Fileopen_simple(int i);	// ���α׷�1 ���� ���� ����  
void enter_simple();			// ���α׷�1 �ܾ ���� ���ִ� �Լ� 
void Simbrute(int j);			// ���α׷�1�� main �Լ� 

// 2.2 ���α׷�2 (�ܾ ���� �� ���� �ܾ �ٸ� �ܾ�� �˻�) 
void Fileopen_check(int i);		// ���α׷�2 ���� ���� ���� 
void enter_check();				// ���α׷�2 �ܾ ���� ���ִ� �Լ� 
void Chkbrute(int j);			// ���α׷�2�� main �Լ� 

//3. ���� ȿ���� �м�
//3.0 ���� ȿ���� �м��� main �Լ�
void analysis(); 
//3.1 �ɸ��ð� ���� 
void time_check(int i);
// ��ġ�ϴ� ���ڼ� ���� 
void Fileopen_wcheck(int i);	// ��ġ�ϴ� ���� �� ���� ���� ���� ���� �Լ� 
void count_wcheck();			// ��ġ�ϴ� ���� �� ���� 
void Wordcheck(int i, int set);			// ��ġ�� �ϴ� ���ڼ� ������ main �Լ� 

//4. �м� �ð�ȭ 
void chart();					// ǥ�� �ð�ȭ 

//5. �м� ���
void anresult(); 
 
// ���� �� �� ���ڿ��� ������ ����, MaxSten��ŭ�� ���� ���� 
char pltext[MaxSten];
// ���� ���Ͽ� �ִ� ���� �� �� ���ڿ��� �ܾ �ӽ������� �����ϴ� �뵵
char tmp[MaxWord];

// ���α׷�2���� �ܾ �ӽ������� �ִ� ����ü 
struct Pointer {
	char first[MaxWord];		// ù ��° �ܾ� 
	int fircnt;					// ù ��° �ܾ��� ���ڼ� 
	char second[MaxWord];		// �� ��° �ܾ� 
	int seccnt;					// �� ��° �ܾ��� ���ڼ�
} p;

// ���� ���� 
char rlstr[MaxSten+1];			// ��Ȯ�� ���� ��� �ִ� ���ڿ� 
struct real{
	int wcnt;					// ���� �ܾ��� �� 
	int rmat;					// ���� ������ �� 
} real;

// ���α׷�1 ���� 
char sistrb[MaxSten+1];			// �ܼ� ����(���α׷�1) ��� �ִ� ���ڿ�
// ���α׷�1 ����� �ܾ��� ��, ��ġ�ϴ� ������ �� ���� 
struct bsim{
	int wcnt;					// ���� �� Ƚ�� (�˻� ��� �ܾ��� ��) 
	int match;					// ��ġ�ϴ� ������ ��
} bsim;

// ���α׷�2 ���� 
char chstrb[MaxSten+1];			// �ٽ� Ȯ���ϴ� ����(���α׷�2) ��� �ִ� ���ڿ�
// ���α׷�2 ����� �ܾ��� ��, ��ġ�ϴ� ������ �� ���� 
struct bchk{
	int wcnt;					// ���� �� Ƚ�� (�˻� ��� �ܾ��� ��) 
	int match;					// ��ġ�ϴ� ������ ��
} bchk;

// �м� ��� �ִ� ��
struct result{
	float time1b[10];			// ���α׷�1 �����ϴµ� �ɸ� �ð� 
	float time2b[10];			// ���α׷�2 �����ϴµ� �ɸ� �ð�
	float match1b[10];			// ���α׷�1�� ��ġ��(��ġ�ϴ� ���ڼ�*100/��ü ���ڼ�) 
	float match2b[10];			// ���α׷�2�� ��ġ��(��ġ�ϴ� ���ڼ�*100/��ü ���ڼ�)
	int restr[10];				// �� ������ ��ü ���ڼ�  
} result;


// ���� 
//Word : �ܾ� ���� ����, Plain : ���� �� �� ����
FILE *Word = NULL, *Plain = NULL;
// ���α׷�1 �ܾ� ���� ��� ���� ���� 
FILE *Result_Simple = NULL;
// ���α׷�2 �ܾ� ���� ��� ���� ���� 
FILE *Result_check = NULL;
FILE *Collect = NULL;			// ���� ���� ���� 

int main()
{ 
	int i;
	srand((unsigned)time(NULL));
	
	printf("=============================================================\n"); 
	printf("              2213 �̿��� ������ �м� ���α׷�\n");
	printf("             ���ܾ� ���� ���� �� ȿ���� �м�\n");
	printf("=============================================================\n"); 
	
	if(chFile())
	{
		fflush(stdin);
		printf("�����Ͻ÷��� enter Ű�� �Է��ϼ���.\n");
		getchar();
		return 1;
	}
	
	// ����, �м�, ���� ���� 
	i = selmode();
	
	while(i != 2)
	{
		switch(i) {
			// ���� 
			case 1:
				explain();
				i = selmode();
				break;
			// ���� 
			case 3:
				fflush(stdin);
				printf("���α׷��� �����մϴ�. �����Ͻ÷��� enter Ű�� �Է��ϼ���.\n");
				getchar();
				return 0;
		}
	}
	 
	printf("\n");
	
	// �м�
	analysis();
	
	// �м� ��� ���� Ȥ�� ���� ���� 
	printf("==========================================\n");
	printf("  [1] ������ �м� ��� ����  [2] �����ϱ�\n>>> ");
	scanf("%d", &i);
	
	while((i!=1)&&(i!=2)) {
		while (getchar() != '\n');	// ���� �Է½� ���ѷ��� ���� �� ������ 
		printf("\n 1, 2 �� �ϳ��� �Է����ּ���\n");
		printf("==========================================\n");
		printf("   [1] ������ �м� ǥ ����  [2] �����ϱ�\n>>> ");
		scanf("%d", &i);
	}
	
	// �м� ��� ���� 
	if(i == 1) chart();
	
	anresult();
	
	// ���� 
	fflush(stdin);
	printf("���α׷��� �����մϴ�. �����Ͻ÷��� enter Ű�� �Է��ϼ���.\n");
	getchar();
	return 0;
}

// �м� ��� 
void anresult()
{
	printf("============================================ ��� �м� =============================================\n ");
	printf(" �ܾ �� ���� Ȯ���ϸ� ���⸦ ����(���α׷�1)�� ���� ���� �ܾ ����� ���� �ܾ �ٽ� �˻�\n");
	printf(" �ϸ� ���⸦ ����(���α׷�2)�� �ͺ��� �׻� �� ���� �ð��� �ɷȴ�. ������, �ɸ� �ð��� ���̰�\n");
	printf(" ������ ���� ����� �����δ� ��Ÿ���� �ʾҴ�. �̴� ���� ���� ��ü�� ã�ƺ��� brute-force �����\n");
	printf(" Ư���� �������Ͽ� �˸´� �ܾ �����ϸ� ���� ������, �������� ������ ���� �ɸ��� �����̴�.\n");
	printf("----------------------------------------------------------------------------------------------------\n");
	printf(" ��ġ���� ��쵵 ����������, �ܾ �� ���� Ȯ���ϴµ� �˸��� �ܾ�θ� Ȯ���ߴٸ� ��ġ���� ��������.\n");
	printf(" ������ �ܾ �ѹ��� Ȯ��(���α׷�1)�� ���� ���� �ܾ ����� �ٽ� Ȯ��(���α׷�2)�� ��� �Ѵ�\n");
	printf(" ��Ȯ���� 95%%�� ������ ������ ����, �� ���� �ܾ ���� ���������� ����ϰ�,\n");
	printf(" ���� �˰����� ���� �� �����Ѵٸ� �� ȿ������ ���ܾ� ���⸦ ������ �� ���� ������ ���δ�.\n");
	printf("====================================================================================================\n\n");
}

// ���ܾ� ���� ����� ǥ�� ��Ÿ�� 
void chart()
{
	int i;
	
	HANDLE ghOutput;
	ghOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	system("cls");
	
	// ���ڼ��� ���� �ɸ� �ð� 
	printf("�� ���α׷��� ���� ���ڼ� ��ȭ�� ���� �ɸ� �ð�(��)\n");
	printf("=============");
	for(i=0; i<testcount; i++) printf("=============");
	printf("\n|   ���ڼ�  |"); 
	for(i=0; i<testcount; i++) printf("    %4d    |", result.restr[i]);
	printf("\n| ���α׷�1 |"); 
	for(i=0; i<testcount; i++) printf(" %10.6llf |", result.time1b[i]);
	printf("\n| ���α׷�2 |");
	for(i=0; i<testcount; i++) printf(" %10.6llf |", result.time2b[i]);
	printf("\n| ����(2-1) |");
	for(i=0; i<testcount; i++) {	
		if(result.time2b[i] - result.time1b[i] < 0.0) {
			SetConsoleTextAttribute(ghOutput, 4);
		} else if(result.time2b[i] - result.time1b[i] == 0.0) {
			SetConsoleTextAttribute(ghOutput, 7);
		} else {
			SetConsoleTextAttribute(ghOutput, 11);
		}
		printf(" %10.6llf |", result.time2b[i] - result.time1b[i]);
		SetConsoleTextAttribute(ghOutput, 7);
	}
	printf("\n=============");
	for(i=0; i<testcount; i++) printf("=============");
	
	// ���ڼ��� ���� ��ġ�� 
	printf("\n\n�� ���α׷��� ���� ���ڼ� ��ȭ�� ���� ��ġ��(%%)\n");
	printf("=============");
	for(i=0; i<testcount; i++) printf("=============");
	printf("\n|   ���ڼ�  |"); 
	for(i=0; i<testcount; i++) printf("    %4d    |", result.restr[i]);
	printf("\n| ���α׷�1 |"); 
	for(i=0; i<testcount; i++) printf(" %10.6llf |", result.match1b[i]);
	printf("\n| ���α׷�2 |");
	for(i=0; i<testcount; i++) printf(" %10.6llf |", result.match2b[i]);
	printf("\n| ����(2-1) |");
	for(i=0; i<testcount; i++) {	
		if(result.match2b[i] - result.match1b[i] < 0.0) {
			SetConsoleTextAttribute(ghOutput, 4);
		} else if(result.match2b[i] - result.match1b[i] == 0.0) {
			SetConsoleTextAttribute(ghOutput, 7);
		} else {
			SetConsoleTextAttribute(ghOutput, 11);
		}
		printf(" %10.6llf |", result.match2b[i] - result.match1b[i]);
		SetConsoleTextAttribute(ghOutput, 7);
	}
	printf("\n=============");
	for(i=0; i<testcount; i++) printf("=============");
	printf("\n");
}

// ���� ������ ��, ���α׷� ����, ��ġ�� ��� ����, ���� ���� �Է� ����ó�� 
int selexplain()
{
	int i = 0;
	while(!((i>=1) && (i<=3))) {
		while (getchar() != '\n');	// ���� �Է½� ���ѷ��� ���� �� ������ 
		printf("\n 1, 2, 3 �� �ϳ��� �Է����ּ���\n");
		printf("==========================================================================================\n");
		printf("  [1] ���α׷�1, 2�� ���� �߰� ����  [2] �ܾ� ��ġ�� �м� �˰��� ����  [3] ���� ������\n>>> ");
		scanf("%d", &i);
	}
	return i; 
}

// �⺻���� ���α׷� ���� 
void explain()
{
	int i = 0;
	system("cls");	//�ܼ� ȭ�� ����� ���� 
	
	printf("\n====================================== ���α׷� ���� ======================================\n");
	printf(" �� ���α׷��� ���� ������ ���⸦ �����ϰ� �ɸ��ð�, ��Ȯ���� �м��ϴ� ���α׷��Դϴ�.\n");
	printf(" ���� ������ ���µ� �� 2���� ���α׷��� ����մϴ�.\n");
	printf(" �� ���α׷����� ����ϴ� ���� ������ �� ���� ������ �Ϻο� 2022�� ���� ���� �Ϻ��Դϴ�.\n");
	printf(" ���� ������ ��ó�� https://blog.daum.net/edrjang/7968274��\n");
	printf(" https://www.wordfrequency.info/samples.asp�� ù��° �׸��� 4��° ���� �Դϴ�.\n");
	printf("======================================== ���� ���� =======================================\n");
	printf(" realword.txt : ���� ����\n");
	printf(" result_simple.txt : ���α׷�1 ��� ����, result_check.txt : ���α׷�2 ��� ����\n");
	printf(" test1.txt, test2.txt,,,,, : ���� �� �� ���� ����\n");
	printf(" collect1.txt, collect2.txt,,,,, : ���� ���� �� ���� ����\n");
	printf("\n - ���α׷�1 : �ܾ� �˻縦 �� ���� �մϴ�.\n");
	printf(" - ���α׷�2 : �ܾ ���ٸ� ���� 2���� �ܾ �ٽ� �˻��մϴ�.\n");
	printf("==================================== ��ġ�� ��� ��� ====================================\n");
	printf(" ������ ��ġ���� ���α׷��� ���� ���� �� ����� ���� ���� ������ ��������\n");
	printf(" (��ġ�ϴ� ���� ��/ ��ü ���ڼ�) * 100 ���� ����߽��ϴ�.\n");
	printf("==========================================================================================\n");
	printf("  [1] ���α׷�1, 2�� ���� �߰� ����  [2] �ܾ� ��ġ�� �м� �˰��� ����  [3] ���� ������\n>>> ");
	scanf("%d", &i);

	if(!((i>=1)&&(i<=3))) i = selexplain();

	while(1)
	{		
		if(i == 3) {
			system("cls");	//���� ������ �ܼ�ȭ�� �����
			return;
		} else if(i == 1) {
			i = 0;
			// ���α׷� ���� 
			prexplain();
		} else if(i == 2){
			i = 0;
			// ��ġ�� �м� ���� 
			spexplain();
		}
		
		while (getchar() != '\n');	// ���� �Է½� ���ѷ��� ���� �� ������ 
		printf("  [1] ���α׷�1, 2�� ���� �߰� ����  [2] �ܾ� ��ġ�� �м� �˰��� ����  [3] ���� ������\n>>> ");
		scanf("%d", &i);
		
		if(!((i>=1)&&(i<=3))) i = selexplain();
	}
} 

// ���α׷� ���� 
void prexplain()
{
	HANDLE ghOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");	//�ܼ� ȭ�� ����� ����
	printf("\n============================================= ���α׷�1 ���� =============================================\n");
	printf(" 1. ���� �� �� ���Ͽ���2040���� ���ڷ� ������ ������ �н��ϴ�.\n");
	printf(" 2. �տ��� ���� ���� �� ���� �߰��ϸ� �ܾ ���� ���Ͽ� �ִ��� Ȯ���մϴ�.\n");
	printf(" 3. ���� �������Ͽ� �ܾ �ִٸ� �ܾ ���� ����(�ܾ�, �ܾ��� ���� ��)�� �����ϰ� 2.�� ��� �ݺ��մϴ�.\n");
	printf(" 4. ��ü ������ �� ������ ��, �ܾ �ִٸ� ���� �� �ܾ� �������� 2.�� ������ �ݺ��մϴ�.\n");
	printf("	 ���� �ܾ ���ٸ� ���� �ܾ���� 2.�� ������ �ݺ��մϴ�.\n");
	printf("-------------------------------------------------- ���� --------------------------------------------------\n");
	printf(" ���� ���� : COMES TO MIND WHEN\n");
	printf(" INPUT : COMESTOMINDWHEN\n");
	printf("\n ó�� ����\n");
	printf(" 1.2. C, ,, : �������Ͽ� ���� => �׳� �Ѿ\n");
	printf("   3. COMES : �������Ͽ� ���� => COMES ����, ���� �� 5 ����\n");
	printf("   3. COMEST : �������Ͽ� ���� => COMEST ����, ���� �� 6 ����\n");
	printf("   3. COMESTO : �������Ͽ� ���� => ���� �ܾ COMEST�� ����\n");
	printf("   4. �ܾ� ������ COMESTOMIN�� �� ��° O ���� �ٽ� �˻��� (2.3. ���� �ݺ�)\n");
	printf("   4. => OMIN�� ���� �ܾ�� ����, OMIND���� D���� �ٽ� �˻������� D, DW, ,,, : ���� ���Ͽ� ����\n");
	printf("   4. D�� �Ѿ�� WHEN ���� �˻� ����(2.3. ���� �ݺ�)\n");
	printf("==========================================================================================================\n");
	
	printf("\n============================================= ���α׷�2 ���� =============================================\n");
	printf(" 1. ���� �� �� ���Ͽ���2040���� ���ڷ� ������ ������ �н��ϴ�.\n");
	printf(" 2. �տ��� ���� ���� �� ���� �߰��ϸ� �ܾ ���� ���Ͽ� �ִ��� Ȯ���մϴ�.\n");
	printf(" 3. ���� �������Ͽ� �ܾ �ִٸ� �ܾ ���� ����(�ܾ�, �ܾ��� ���� ��)�� �����ϰ� 2.�� ��� �ݺ��մϴ�.\n");
	printf(" 4. ��ü ������ �� ������ ��, �ܾ �ִٸ� ���� �� �ܾ� �������� 2.�� ������ �ݺ��մϴ�.\n");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("	 ���� �ܾ ���ٸ� ���� 2���� �ܾ �ٽ� �˻��Ͽ� �ٸ� �ܾ ���� �ܾ�� �����մϴ�.\n");
	printf("	 ���� �ٽ� 2.�� ������ ���ư��ϴ�.\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("-------------------------------------------------- ���� --------------------------------------------------\n");
	printf(" ���� ���� : COMES TO MIND WHEN\n");
	printf(" INPUT : COMESTOMINDWHEN\n");
	printf("\n ó�� ����\n");
	printf(" 1.2. C, ,, : �������Ͽ� ���� => �׳� �Ѿ\n");
	printf("   3. COMES : �������Ͽ� ���� => COMES ����, ���� �� 5 ����\n");
	printf("   3. COMEST : �������Ͽ� ���� => COMEST ����, ���� �� 6 ����\n");
	printf("   3. COMESTO : �������Ͽ� ���� => ���� �ܾ COMEST�� ����\n");
	printf("   4. �ܾ� ������ COMESTOMIN�� �� ��° O ���� �ٽ� �˻��� (2.3. ���� �ݺ�)\n");
	printf("   4. => OMIN�� ���� �ܾ�� ����, OMIND���� D���� �ٽ� �˻������� D, DW, ,,, : ���� ���Ͽ� ����\n");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("   4. D ���� �� �ܾ���� �ٽ� �˻� ���� : OMIN, COMEST => COMEST ���� �ٽ� �˻�\n");
	printf("   4. COMES : ���� ���Ͽ� ����, COMEST : ���� ���Ͽ� ������ ������ ����� => COMES�� �����ܾ�� ����\n");
	printf("   4. COMES ������ TOMIN��T ���� �ٽð˻�(2.3. ���� �ݺ�)\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("==========================================================================================================\n");
} 

// ���� ��ġ�� �м� �˰��� ���� 
void spexplain()
{
	HANDLE ghOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");	//�ܼ� ȭ�� ����� ����
	printf("\n===================================== ���� ��ġ�� �м� �˰��� ====================================\n");
	printf(" ���� ���� ����� ���α׷��� ���� ���Ⱑ �� ������ ���ڸ� 1���� ���ϸ� ��ġ���� �м��մϴ�.\n");
	printf(" ��ġ�� �м� ���α׷������� ���� ���� ����� ���� �� ���忡�� ��ġ�ϴ� ������ ���� �����մϴ�.\n");
	printf(" ���ڰ� ���� ��ġ���� ���� ���� ���α׷��� ���⸦ ������ ��, �߸� ���ų� ���� ���� ����Դϴ�.\n");
	printf(" ��, �� ���� ���� ������ ���� Ȥ�� ������ ������ ���ڿ� ������ �ִ� ����Դϴ�.\n");
	printf("\n ��ġ���� �ʴ� ���ڰ� ��Ÿ���� ���\n");
	printf(" 1. ���� ���� ������ ���ڰ� ������ ��쿡�� ���� ������ �ε����� 1 ������ŵ�ϴ�.\n");
	printf("    �̸� ���� ���� ���� ����� ������ ������ �������� �����ϰ� ���߰� �ٽ� �˻��մϴ�.\n");
	printf(" 2. ���� �� ������ ���ڰ� ������ ��쿡�� ���� �� ������ �ε����� 1 ������ŵ�ϴ�.\n");
	printf("    �̸� ���� ���� ���� ����� ������ ������ �������� �����ϰ� ���߰� �ٽ� �˻��մϴ�.\n");
	printf("-------------------------------------------------- ���� --------------------------------------------------\n");
	printf(" ���� ���� ���� : ES_TO :(_:����)\n");
	printf(" ����� ����    : EST_O :(_:����)\n");
	printf("\n ó�� ����(�� ������ �ε��� ��ġ�� ���ڸ� ����մϴ�:COME���� �ε����� 0�̶�� C ���)\n\n");
	printf(" 1. ���� ���� ���� : ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("E");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("                             2. ���� ���� ���� : E");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("S\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" 1. ����� ����    : ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("E");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("                             2. ����� ����    : E");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("S\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("   => ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("E���� ��ġ");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" => ��ġ�ϴ� ���� ��+1                   => ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("S���� ��ġ");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" => ��ġ�ϴ� ���� ��+1\n\n"); 
	
	printf(" 3. ���� ���� ���� : ES");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("_\n");
	SetConsoleTextAttribute(ghOutput, 7);	
	printf(" 3. ����� ����    : ES");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("T\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("   => ");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("���� ����ġ");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(", ���� ���� ������ ����:���� => ���� ���� ���� �ε���+1\n");
	printf("   => ���� ���� ���� : ES_T\n\n");
	
	printf(" 4. ���� ���� ���� : ES_");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("T\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" 4. ����� ����    :  ES");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("T\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("   => ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("T���� ��ġ");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" => ��ġ�ϴ� ���� ��+1\n\n");
	
	printf(" 5. ���� ���� ���� : ES_T");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("O\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" 5. ����� ����    :  EST");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("_\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("   => ");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("���� ����ġ");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(", ���� �� ������ ����:���� => ���� �� ���� �ε���+1\n");
	printf("   => ���� �� ���� : ES_T_O\n\n");
	
	printf(" 6. ���� ���� ���� : ES_T");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("O\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" 6. ����� ����    : EST_");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("O\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("   => ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("O���� ��ġ");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" => ��ġ�ϴ� ���� ��+1\n\n");
	printf("==========================================================================================================\n");
}

// �ʿ��� ������ �����ϴ� �� Ȯ�� 
int chFile()
{
	int i = 1;
	int j;
	char te[] = "test";				// ���� �� �� ������ ����κ� �̸� 
	char co[] = "collect";			// ���� ���� ������ ����κ� �̸�
	char rlfile[100] = {0};		 	// ���ڿ� �ٿ� ������� ���� �̸� 
	char J[64]= {0};
	
	HANDLE ghOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	printf("\n==================== ���� üũ ���Դϴ�. ====================\n");
	
	// ���� ���� (��ó�� ���) 
	Word=fopen("realword.txt", "r");
	if(Word != NULL) {
		SetConsoleTextAttribute(ghOutput, 10);
		printf("  %2d. ���� ���� �غ�\t\t\t\t\t: O\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
	} else {
		SetConsoleTextAttribute(ghOutput, 12);
		printf("  %2d. ���� ���� �غ�\t\t\t\t\t: X\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
		printf("���� ���� �غ� �߸��Ǿ����ϴ�. Ȯ�� �ٶ��ϴ�.\n");
		fclose(Word);	
		return 1;
	}
	fclose(Word);
	
	printf("\n");
	
	// ���� �� �� ���ϰ� ���� ���� ���� 
	for(j = 1; j<=testcount; j++)
	{
		// ���� �� �� ���� ���� 
		// ���� �̸� ���ϱ� 
		itoa(j, J, 10);
		strcpy(rlfile, te);
		strcat(rlfile, J);
		strcat(rlfile, ".txt");
		
		Plain = fopen(rlfile, "r");
		if(Plain != NULL) {
			SetConsoleTextAttribute(ghOutput, 10);
			printf("  %2d. ���� �� �� ���� ����%d �غ�\t\t\t: O\n", i++, j);
			SetConsoleTextAttribute(ghOutput, 7);
		} else {
			SetConsoleTextAttribute(ghOutput, 12);
			printf("  %2d. ���� �� �� ���� ����%d �غ�\t\t\t: X\n", i++, j);
			SetConsoleTextAttribute(ghOutput,7);
			printf("���� �� �� ���� ����%d �غ� �߸��Ǿ����ϴ�. Ȯ�� �ٶ��ϴ�.\n");
			fclose(Plain);
			return 1;
		}
		fclose(Plain);
		
		// ���� ���� ���� 
		// ���� �̸� ���ϱ� 
		itoa(j, J, 10);
		strcpy(rlfile, co);
		strcat(rlfile, J);
		strcat(rlfile, ".txt");
		
		Collect = fopen(rlfile, "r");
		if(Collect != NULL) {
			SetConsoleTextAttribute(ghOutput, 10);
			printf("  %2d. ���� ���� ����%d �غ�\t\t\t\t: O\n", i++, j);
			SetConsoleTextAttribute(ghOutput, 7);
		} else {
			SetConsoleTextAttribute(ghOutput, 12);
			printf("  %2d. ���� ���� ����%d �غ�\t\t\t\t: X\n", i++, j);
			SetConsoleTextAttribute(ghOutput, 7);
			printf("���� ���� ����%d �غ� �߸��Ǿ����ϴ�. Ȯ�� �ٶ��ϴ�.\n", j);
			fclose(Collect);
			return 1;
		}
		fclose(Collect);
	}
	
	printf("\n");
	
	// ���� ��� ���� (���α׷� 1) 
	Result_Simple = fopen("result_simple.txt", "w");
	if(Result_Simple != NULL) {
		SetConsoleTextAttribute(ghOutput, 10);
		printf("  %2d. (���α׷�1) ���� ��� ���� ���� Ȥ�� �غ�\t: O\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
	} else {
		SetConsoleTextAttribute(ghOutput, 12);
		printf("  %2d. (���α׷�1) ���� ��� ���� ���� Ȥ�� �غ�\t: X\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
		printf("(���α׷�1) ���� ��� ���� ���� Ȥ�� �غ� �߸��Ǿ����ϴ�. Ȯ�� �ٶ��ϴ�.\n");
		fclose(Result_Simple);
		return 1;
	}
	fclose(Result_Simple);
	
	// ���� ��� ���� (���α׷� 2) 
	Result_check = fopen("result_check.txt", "w");
	if(Result_check != NULL) {
		SetConsoleTextAttribute(ghOutput, 10);
		printf("  %2d. (���α׷�2) ���� ��� ���� ���� Ȥ�� �غ�\t: O\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
	} else {
		SetConsoleTextAttribute(ghOutput, 12);
		printf("  %2d. (���α׷�2) ���� ��� ���� ���� Ȥ�� �غ�\t: X\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
		printf("(���α׷�2) ���� ��� ���� ���� Ȥ�� �غ� �߸��Ǿ����ϴ�. Ȯ�� �ٶ��ϴ�.\n");
		fclose(Result_Simple);
		return 1;
	}
	fclose(Result_check);
	
	printf("===================== ���� üũ �Ϸ�!! ======================\n\n");
	
	return 0;
}

// ����, �м�, ���� ���� 
int selmode()
{
	int i = 0;
	printf("=============================================================\n");
	printf("\t  [1] ���ܾ� ���� ���α׷� �� ����\n");
	printf("\t  [2] ���ܾ� ���� ȿ�� �м�\n");
	printf("\t  [3] ���α׷� ����\n");
	printf("=============================================================\n>>> ");
	scanf("%d", &i);

	while(!((i>=1) && (i<=3))) {
		while (getchar() != '\n');	// ���� �Է½� ���ѷ��� ���� �� ������ 
		printf("\n 1�̻� 3������ ������ �Է����ּ���\n");
		printf("=============================================================\n");
		printf("\t  [1] ���ܾ� ���� ���α׷� �� ����\n");
		printf("\t  [2] ���ܾ� ���� ȿ�� �м�\n");
		printf("\t  [3] ���α׷�- ����\n");
		printf("=============================================================\n>>> ");
		scanf("%d", &i);
	}
	return i;
}

// ���ܾ� ���� ȿ���� �м� 
void analysis()
{
	int i, rpnt;

	printf("=============================================================\n");
	printf("  [1] ���� ��� ����ϱ�  [2] ���� ��� ������� �ʱ� \n>>> ");
	scanf("%d", &rpnt);

	while((rpnt!=1) && (rpnt!=2)) {
		while (getchar() != '\n');	// ���� �Է½� ���ѷ��� ���� �� ������ 
		printf("\n 1, 2 �� �ϳ��� �Է����ּ���\n");
		printf("=============================================================\n");
		printf(" [1] ���� ��� ����ϱ�  [2] ���� ��� ������� �ʱ� \n>>> ");
		scanf("%d", &rpnt);
	}
	
	// ���ܾ� ���� �� ��ġ�� ���� 
	for(i= 0; i<testcount; i++)
	{
		printf("\n��������%d�� ���Ⱑ ����˴ϴ�.\n", i+1);
		
		// �ɸ��� �ð� ���� 
		time_check(i);
		
		// ��ġ�ϴ� ���� �� ���� 
		Wordcheck(i, rpnt);	
		
		printf("\n\n���α׷�1 �ɸ� �ð� : %llf��\n", result.time1b[i]);
		printf("���α׷�2 �ɸ� �ð� : %llf��\n", result.time2b[i]);
		
		printf("���α׷�1 ��ġ�ϴ� ������ �� : %d, ��ü ���ڼ� : %d, ���α׷�1 �ܾ� �� : %d, ���� �ܾ� �� : %d\n", bsim.match, real.rmat, bsim.wcnt, real.wcnt);
		printf("���α׷�1�� ��ġ�� : %llf\n", result.match1b[i]); 
		
		printf("���α׷�2 ��ġ�ϴ� ������ �� : %d, ��ü ���ڼ� : %d, ���α׷�2 �ܾ� �� : %d, ���� �ܾ� �� : %d\n", bchk.match, real.rmat, bchk.wcnt, real.wcnt);
		printf("���α׷�2�� ��ġ�� : %llf\n", result.match2b[i]);
		printf("====================================================================================================\n");
	}
	
	// ���� ��� ǥ�� 
	for(i= 0; i<testcount; i++)
	{
		printf("��������%d\n", i+1);
		
		printf("���α׷�1 �ɸ� �ð� : %llf��\n", result.time1b[i]);		
		printf("���α׷�1�� ��ġ�� : %llf, ��ü ���� �� : %d\n\n", result.match1b[i], result.restr[i]);
		
		printf("���α׷�2 �ɸ� �ð� : %llf��\n", result.time2b[i]); 
		printf("���α׷�2�� ��ġ�� : %llf, ��ü ���� �� : %d\n\n", result.match2b[i], result.restr[i]);
	}
}

// ���α׷�2 main(�ܾ� ������ ���� �ܾ� �ٽ� Ȯ��) 
void Chkbrute(int j)
{
	int i;
	// �ܾ�� ���ڼ� �ʱ�ȭ 
	p.fircnt = 0;
	p.seccnt = 0;
	
	printf("���α׷�2�� �������Դϴ�.");
	
	//���α׷�2 ���� ���� ���� 
	Fileopen_check(j);
	
	//������ ������ ������ ����ֱ�(�� ���ھ�) (MaxSten���� ����) 
	for(i = 0; !feof(Plain); i++)
	{
		if(i >= MaxSten){
			enter_check();
			clear(i--);
			i = 0;
		}
		
		pltext[i] = fgetc(Plain);
    }
    
    // ���� ������ ���ڿ��� Maxten �� �̸��� ���ڷ� �̷���� ���� �ʴ� ������ ���
	// �ܾ �м��Ͽ� ���� ���Ѽ� �־��ش�. 
	if(i != 0){
		enter_check();
	}
	
	// �� ���α׷��� �ܾ first, second ������ �ְ� ����° �ܾ �����ϸ� first�� �ִ� ����̴�. 
	// ������ ������ ������ ���� first, second�� �����ϳ� ����° �ܾ�� �������� �ʴ´�. (��ǻ�ʹ� ����° �ܾ� ���� ������ Ȯ������ ���Ѵ�.)
	// �׷��� ������ 2���� �ܾ ���Ͽ� �־��־� ���⸦ �ϼ��Ѵ�.
	fprintf(Result_Simple, "%s ", p.first);
	fprintf(Result_Simple, "%s ", p.second);
	
	fclose(Word);
	fclose(Plain);
	fclose(Result_Simple);
	
	printf("\r���α׷�2�� ������ ����Ǿ����ϴ�.\n");
}

// ���α׷�2 ���� ���� ���� 
void Fileopen_check(int i)
{
	char te[] = "test";				// ���� �� �� ������ ����κ� �̸� 
	char rlfile[100] = {0};		 	// ���ڿ� �ٿ� ������� ���� �̸� 
	char J[64]= {0};
	
	// ���� �̸� ���ϱ� 
	itoa(i+1, J, 10);
	strcpy(rlfile, te);
	strcat(rlfile, J);
	strcat(rlfile, ".txt");
	
	// ���� �� �� ���� ���� 
	Plain = fopen(rlfile, "r");
	Word = fopen("realword.txt", "r");
	Result_check = fopen("result_check.txt", "w");
}

// ���α׷�1 ���� ���� ���� 
void Fileopen_simple(int i)
{
	char te[] = "test";				// ���� �� �� ������ ����κ� �̸� 
	char rlfile[100] = {0};		 	// ���ڿ� �ٿ� ������� ���� �̸� 
	char J[64]= {0};
	
	// ���� �̸� ���ϱ� 
	itoa(i+1, J, 10);
	strcpy(rlfile, te);
	strcat(rlfile, J);
	strcat(rlfile, ".txt");
	
	// ���� �� �� ���� ���� 
	Plain = fopen(rlfile, "r");
	Word = fopen("realword.txt", "r");
	Result_Simple = fopen("result_simple.txt", "w");
}

//���� ���Ͽ� ���ϴ� �ܾ �ִ��� Ȯ�� 
int Iswordin(char word[])
{
	char line[MaxWord];
	int i, leline, leword = len(word); //leline : ���� ���� �ܾ�(line)�� ���� ��, leword : ���ϴ� �ܾ�(word)�� ���� �� 
	
	// ���� ������ �����͸� ó�� ��ġ�� �ʱ�ȭ�Ͽ� �׻� ó������ �˻��� �� �ֵ���!! 
	fseek(Word, 0, SEEK_SET);
	
	while(!feof(Word))
	{
		fgets(line, MaxWord, Word);
		leline = len(line);
		// ���ϴ� �ܾ��� ���ڼ��� ���� ���� �ܾ��� ���ڼ��� ���� ��츸 �ε��� 1���� ������ �˻� 
		if(leline == leword)
		{
			for(i=0; i < leline; i++) if(line[i] != word[i]) break;
			if(i == leline) return 1;
		}
    }
    return 0;
}

// text�� ���ڼ� ��ȯ 
int len(char text[])
{
	int check;
	for(check = 0; (text[check] != '\n')&&(text[check] != '\0')&&(check <= MaxSten); check++);
	return check;
} 

// ���� ������� ���� �ʱ�ȭ 
void clear(int max)
{
	int i;
	for(i = 0; i <= max; i++) pltext[i] = '\0';
}

// ���ڿ� �����̽� 
void slycing(int a, int b)
{
	int i;
	for(i = 0; i < b-a; i++) tmp[i] = pltext[a+i];
	tmp[b-a] = '\0';
}

// ���α׷�2 ���� ����� ��� ���Ͽ� �ֱ� 
void enter_check()
{
	char temp[MaxWord];					//temp : ���� ���Ͽ� �ִ� �ܾ� ����� 
	int curi = 0;						// 4.����� �����ϱ� ���� ����, ���� ���Ͽ� �ִ� �ܾ� ���� �ε��� ���� ����Ŵ, ���� ���ÿ����� �ι�° I�� ����Ű�� �� 
	int Hasres = 0;						// 4.���� ���� ���Ͽ� �ܾ �ִ���(1) ������(0) Ȯ���ϴ� �뵵 
	int pllen = len(pltext);			//������ ������ ���ڼ� ���ؼ� ����
	int check = 0;						//���� �ܾ 2�� �˻��ص� ���� ���, �ش� �ܾ �ǳʶٰ� ���� �ܾ p.first�� ��� �뵵 
	int i = 0, j, k;
	
	//������ ���� ��ü�� �� ���� ���ƺ��� �ܾ� �ľ� 
	while(i < pllen-1)
	{
		//���� �� ���� ã�ƺ��� �ܾ��ľ�, �ܾ ã���� �ܾ� ���̸�ŭ ������ �Ѿ 
		for(j = i+1; (j <= pllen)&&(j <= i+MaxWord); j++)
		{
			slycing(i, j);
			if(Iswordin(tmp))
			{
				//���� ���Ͽ� �ִ� �ܾ� ���� => �ܾ�, �ܾ� ������ �ε����� ���� 
				strcpy(temp, tmp);
				temp[j-i+1] = '\0';
				Hasres = 1;
				curi = j;
			}
		}
		//�ܾ� ���� => "�ܾ� " ��� txt�� �Է� 
		if(Hasres)
		{
			//ù ��°�� ���� �� �ܾ ������ ��, �ܾ �ι� �˻��ߴµ��� ���� ��� 
			if(check == 0) {
				//ù ��° �ܾ ù ��° �ܾ ������� 
				p.fircnt = len(temp); 
				strcpy(p.first, temp); //���ڿ� ���� temp -> p.first
				check = 1;
			} else if(check == 1) {
				//�� ��°�� ���� �� �ܾ ������ ��, �ܾ �ι� �˻��Ͽ� ������ ��� ���� �ܾ ���� 
				p.seccnt = len(temp); 
				strcpy(p.second, temp); //���ڿ� ���� temp -> p.second
				check = 2;
			} else {
				//��Ȯ�� �ܾ txt���Ͽ� �ִ� �뵵 
				fprintf(Result_check, "%s ", p.first);
				//��� �ӽ� �迭�� �� ��° �ܾ ù ��° �ܾ��� ��ġ�� �̴� ��
				strcpy(p.first, p.second);
				p.fircnt = p.seccnt;
				//��� �ӽ� �迭�� �� ���� �߰��� �ܾ �ִ� ���� 
				strcpy(p.second, temp);	//���ڿ� ���� temp -> p.second
				p.seccnt = len(p.second);
			}
			i = curi;
		} else {
			// �ܾ� ���� => ���� ���� �ܾ �ٽ� �˻� 
			if(check == 1)
			{
				k = 0;
				//�ι�° �ܾ �˻��ϴµ� ���� ��� 
				//�� ��° �ܾ� ���� �ε��� : curi => ù ��° �ܾ� ���� �ε��� : curi-p.fircnt 
				for(i = curi-p.fircnt+1; i < curi; i++)
				{
					slycing(curi, i);
					if(Iswordin(tmp))
					{
						//���� ���Ͽ� �ִ� �ܾ� ���� => �ܾ�, �ܾ� ������ �ε����� ���� 
						strcpy(temp, tmp);
						temp[i] = '\0';
						Hasres = 1;
						curi = i;
					}
				}
				
				// ù��° �ܾ �� �̻� �� ���� ���ڼ��� �ܾ ���� ���
				if(!(Hasres))
				{
					//ù ��° �ܾ� �ֱ�
					fprintf(Result_check, "%s ", p.first);
					p.first[0] = '\0';
					p.fircnt = 0;
					
					//�� ��° �ܾ �˻��ϴ� �� ���ٴ� ���� ���������� �߸��� => �������� ���Ͽ� �ְ�, 1ĭ �б� 
					fprintf(Result_check, "%c ", pltext[i]);
					// �ٽ� ó������ �����ϴ� �Ͱ� ����
					check = 0;
					//�ٵ� ���������� i+1��° ���� (�߸��� �������� ����)
					i++; 
				} 
			} else {
				// ����° �̻��� �ܾ �˻��ϴµ� ���� ��� : i�� �ι�° �ܾ��� ���� �ε��� ���� ������ ���� 
				k = i-p.fircnt-p.seccnt;
				for(i = k+1; i < k+p.fircnt; i++)
				{
					slycing(k, i);
					if(Iswordin(tmp))
					{
						//���� ���Ͽ� �ִ� �ܾ� ���� => �ܾ�, �ܾ� ������ �ε����� ���� 
						strcpy(temp, tmp);
						//temp[i-k+1] = '\0';
						Hasres = 1;
						curi = i;
					}
				}				
				// ���� �ٽ� �˻��ϴµ��� �ܾ ���ٸ� ó�� ���ڸ� ��� ���Ͽ� ���� ó�� ���ڸ� ���� ���ڷ� �Ѿ 
				if(!(Hasres))
				{
					i = k;
					// ���� �Է��� ��, �������� �̻��� ���� ���� => ���ĺ��� �ƴϸ� ��� ���Ͽ� ���� ����
					if((pltext[i]>=65) && (pltext[i]<=90))
					{
						fprintf(Result_check, "%c ", pltext[i]);
					}
					p.first[0] = '\0';
					p.second[0] = '\0';
					p.fircnt = 0;
					p.seccnt = 0;
					i++;
					// ���� ���ڷ� �Ѿ�� p.first���� �ܾ �ֱ� ���� 
					check = 0; 
				}
				
			}
			if(check)
			{
				strcpy(p.first, temp);	// temp -> p.first
				p.fircnt = len(p.first);
				p.seccnt = 0;
				// �ܾ ��� p.first�� �־����Ƿ� ���� �ܾ�� p.second�� ������
				check = 1;
			} 			
		}
		//�ٽ� ���ƾ� �ϴ� �ܾ� �������� ���� 
		Hasres = 0;
		
		if(check) i = curi;
	}
}

// ���α׷�1 main (�� ���� Ȯ��)
void Simbrute(int j)
{
	int i;
	
	printf("���α׷�1�� �������Դϴ�.");
	
	Fileopen_simple(j);
	
	//������ ������ ������ ����ֱ� (MaxSten���� ���� Ȥ�� .���� ���еǴ� ����) 
	for(i = 0; !feof(Plain); i++)
	{
		if(i >= 2<<10){
			enter_simple();
			clear(i--);
			i = 0;
		}
		
		pltext[i] = fgetc(Plain);
		
		/*
		if(pltext[i] == '.'){
			//printf("\n==%c==", pltext[i]);
			//i--;
			//printf("==%c==\n", pltext[i]);
			enter_simple();
			//printf("%s", pltext);
			clear(i);
			i = 0;
		}
		*/
    }
    
	if(i != 0){
		enter_simple();
		//printf("%s\n", pltext);
		//clear(i--);
		//i = 0;
	}
	
	fclose(Word);
	fclose(Plain);
	fclose(Result_Simple);
	
	printf("\r���α׷�1�� ������ ����Ǿ����ϴ�.\n");
}

// ���α׷�1 ���� ����� ��� ���Ͽ� �ֱ� 
void enter_simple()
{
	char temp[MaxWord];					//temp : ���� ���Ͽ� �ִ� �ܾ� ����� 
	int curi = 0;						// 4.����� �����ϱ� ���� ����, ���� ���Ͽ� �ִ� �ܾ� ���� �ε��� ���� ����Ŵ, ���� ���ÿ����� �ι�° I�� ����Ű�� �� 
	int Hasres = 0;						// 4.���� ���� ���Ͽ� �ܾ �ִ���(1) ������(0) Ȯ���ϴ� �뵵 
	int pllen = len(pltext);			//������ ������ ���ڼ� ���ؼ� ����
	int i = 0, j;
	
	//������ ���� ��ü�� �� ���� ���ƺ��� �ܾ� �ľ� 
	while(i < pllen)
	{
		//���� �� ���� ã�ƺ��� �ܾ��ľ�, �ܾ ã���� �ܾ� ���̸�ŭ ������ �Ѿ 
		for(j = i+1; (j <= pllen)&&(j <= i+MaxWord); j++)
		{
			slycing(i, j);
			if(Iswordin(tmp))
			{
				//printf("%s\t : [%s]\n", pltext, temp);
				//���� ���Ͽ� �ִ� �ܾ� ���� => �ܾ�, �ܾ� ������ �ε����� ���� 
				strcpy(temp, tmp);
				temp[j-i+1] = '\0';
				Hasres = 1;
				curi = j;
			}
		}
		
		//�ܾ� ���� => "�ܾ� " ��� txt�� �Է� 
		if(Hasres)
		{
			fprintf(Result_Simple, "%s ", temp);
			//printf("1 : %s\n", temp);
			i = curi;
		}
		//�ܾ� ���� => ���� ���� �ְ� �� ���� �Ѿ(���� �Է��� ��, �������� �̻��� ���� ���� => ���ĺ��� �ƴϸ� ��� ���Ͽ� ���� ����) 
		else
		{
			if((pltext[i]>=65) && (pltext[i]<=90))
			{
				fprintf(Result_Simple, "%c ", pltext[i]);
			}
			i++;
		}
		
		//�ٽ� ���ƾ� �ϴ� �ܾ� �������� ���� 
		Hasres = 0; 
		
	}
}

// �ܾ� ��ġ�� ��� main 
void Wordcheck(int i, int set)
{
	int all = 0; // ��ü �����Ǽ� 	

	Fileopen_wcheck(i);
	
	//������ ������ ������ ����ֱ�(�� ���ھ�) (MaxSten_check���� ����) 
	if(!feof(Result_Simple)) fgets(sistrb, MaxSten, Result_Simple);
	if(!feof(Result_check)) fgets(chstrb, MaxSten, Result_check);
	if(!feof(Collect)) fgets(rlstr, MaxSten, Collect);
	
	if(set == 1)
	{
		printf("\n ���� ����\n");
		printf("%s\n", rlstr);
		printf("\n ���α׷�1 ���� ���\n");
		printf("%s\n", sistrb);
		printf("\n ���α׷�2 ���� ���\n");
		printf("%s\n", chstrb);
	}

	// ���� ������ ���ڼ�, �ܾ�� �ʱ�ȭ 
	real.rmat = 0;			// ���� ���� ���ڼ� 
	real.wcnt = 0;			// ���� ���� �ܾ�� 
	// ���α׷�1 ���� ����� ��ġ�ϴ� ���ڼ�, �ܾ�� �ʱ�ȭ 
	bsim.match = 0;			// ���α׷�1�� ��ġ�ϴ� ���ڼ� 
	bsim.wcnt = 0;			// ���α׷�1�� �ܾ��
	//���α׷�2�� ���� ����� ��ġ�ϴ� ���ڼ�, �ܾ�� �ʱ�ȭ 
	bchk.match = 0;			// ���α׷�2�� ��ġ�ϴ� ���ڼ� 
	bchk.wcnt = 0;			// ���α׷�2�� �ܾ�� 
	
	// ��ġ�ϴ� ���ڼ�, �ܾ�� ���� 
	count_wcheck();
	
	result.match1b[i] =  bsim.match*100.0/real.rmat;	// ���α׷�1�� ���� ��ġ�� ���� 
	result.match2b[i] =  bchk.match*100.0/real.rmat;	// ���α׷�2�� ���� ��ġ�� ����
	result.restr[i] = real.rmat;						// �� ������ ��ü ���ڼ� ���� 
	
	fclose(Result_Simple);
	fclose(Result_check);
	fclose(Collect);
}

// �ܾ� ��ġ�� �м� ���� ���� ���� 
void Fileopen_wcheck(int i)
{
	char co[] = "collect";			// ���� ���� ������ ����κ� �̸�
	char rlfile[100] = {0};		 	// ���ڿ� �ٿ� ������� ���� �̸� 
	char J[64]= {0};
	
	// ���� �̸� ���ϱ� 
	itoa(i+1, J, 10);
	strcpy(rlfile, co);
	strcat(rlfile, J);
	strcat(rlfile, ".txt");
	
	// ���� �� �� ���� ���� 
	Collect = fopen(rlfile, "r");
	Result_Simple = fopen("result_simple.txt", "r");
	Result_check = fopen("result_check.txt", "r");
}

// ���ڿ� �ܾ�� ���� 
void count_wcheck()
{
	// �ܼ� ����(���α׷�1) ��� : sistrb
	// 2�� Ȯ��(���α׷�2) ��� : chstrb
	// ��Ȯ�� ���� : rlstr 

	// wcnt : ��� �ܾ��� �� 
	int i = 0, j = 0, k;				// i:���� ���� �ε���, j:��� ���� �ε���, k : ���ڼ� Ȥ�� �ܾ�� �� �� �� ���� 
	int rdcheck = 1;		// rdcheck ��� ���ڿ��� ���� ���ڿ��� �� ������ 0 
	
	for(k=0; rlstr[k] != '\0'; k++)
	{
		//���� ���ڿ��� �ܾ� �� ���� : �������� �������� �Ǿ������� �ܾ ����!! 
		if(rlstr[k] == ' ') real.wcnt++;
	}
	// ���� ���ڿ��� ���ڼ� 
	real.rmat = k;
	
	for(k=0; sistrb[k] != '\0'; k++)
	{
		//���1 ���ڿ��� �ܾ� �� ���� : �������� �������� �Ǿ������� �ܾ ����!! 
		if(sistrb[k] == ' ') bsim.wcnt++;
	}
	
	for(k=0; chstrb[k] != '\0'; k++)
	{
		//���2 ���ڿ��� �ܾ� �� ���� : �������� �������� �Ǿ������� �ܾ ����!! 
		if(chstrb[k] == ' ') bchk.wcnt++;
	}
	
	// ��α� ���� ����: �ܼ� ����(���α׷�1) ��� �м� 
	while(rdcheck)
	{		
		// ���乮�ڿ��� i��° ���ڿ� ��� ���ڿ��� j��° ���ڰ� ���� => �Ѿ  
		if(rlstr[i] == sistrb[j])
		{
			i++;
			j++;
			bsim.match++;
		} else {
			// ���乮�ڿ��� i��° ���ڿ� ��� ���ڿ��� j��° ���ڰ� �ٸ� => error�� 1���ϰ� ��쿡 ���� ����
			
			// ���� : ����, ��� : ���� => ���Ⱑ ���� ���� => ����� ����� �ùٸ� ����
			// => ����� ���� ȿ���� ���� �ε���+1 (����� ������ ���� ��) => �˻� �簳 
			if(rlstr[i] == ' ')
			{
				// ���� ���ڿ��� �ε����� +1 
				i++;
			}
			
			// ���� ��찡 �ƴ� ���; ���� : ����, ��� : ���� => �߸��� ���Ⱑ �� => ����� �ٿ���� �ùٸ� ����
			// => ����� �ٿ����� ȿ���� ��� �ε���+1 (����� ������ ���� ��) => �˻� �簳 
			else
			{
				// ��� ���ڿ��� �ε����� +1 
				j++;
			}
		}
		
		if((rlstr[i] == '\0') && (sistrb[j] == '\0')) rdcheck = 0;
	}
	real.rmat = i-1;			// ������ �ε����� ����� �� : '\0' : ���ڿ��� ���� ��Ÿ���Ƿ� ���ڰ� �ƴ� => i-1 �����Ͽ� ��ü ���� �˷��� 
	
	i = 0; j = 0; rdcheck = 1;
	
	// ��α� ���� ����: 2�� Ȯ��(���α׷�2) ��� �м� 
	while(rdcheck)
	{		
		// ���乮�ڿ��� i��° ���ڿ� ��� ���ڿ��� j��° ���ڰ� ���� => �Ѿ  
		if(rlstr[i] == chstrb[j])
		{
			i++;
			j++;
			bchk.match++;
		} else {
			// ���� : ����, ��� : ���� => ���Ⱑ ���� ���� => ����� ����� �ùٸ� ����
			// => ����� ���� ȿ���� ���� �ε���+1 (����� ������ ���� ��) => �˻� �簳 
			if(rlstr[i] == ' ')
			{
				// ���� ���ڿ��� �ε����� +1 
				i++;
			}
			
			// ���� ��찡 �ƴ� ���; ���� : ����, ��� : ���� => �߸��� ���Ⱑ �� => ����� �ٿ���� �ùٸ� ����
			// => ����� �ٿ����� ȿ���� ��� �ε���+1 (����� ������ ���� ��) => �˻� �簳 
			else
			{
				// ��� ���ڿ��� �ε����� +1 
				j++;
			}
		}
		
		if((rlstr[i] == '\0') && (chstrb[j] == '\0')) rdcheck = 0;
	}
} 

//  �ɸ� �ð� ���� 
void time_check(int i)
{
	// �ɸ� �ð� ������ �� ������ 
	LARGE_INTEGER freq, t_1, t_2; //t_1:���� ��	t_2:���� �� 
	LONGLONG t_diff;
	double elapsed_time;
	
	// ���α׷�1 �ɸ� �ð� ���� 
	QueryPerformanceCounter(&t_1);		//�Լ� ���� �� �ð� ����
	QueryPerformanceFrequency(&freq);

	Simbrute(i);						// ���α׷�1 ���� ���� 

	QueryPerformanceCounter(&t_2);		//�Լ� ���� �� �ð� ���� 
	t_diff = t_2.QuadPart-t_1.QuadPart;
	elapsed_time = ((double) t_diff / freq.QuadPart);	//�ɸ��ð� ���� 
	result.time1b[i] = elapsed_time;			// �ɸ� �ð� ���� 
	
	// ���α׷�2 �ɸ� �ð� ���� 
	QueryPerformanceCounter(&t_1);		//�Լ� ���� �� �ð� ����
	QueryPerformanceFrequency(&freq);

	Chkbrute(i);						//���α׷�2 ���� ���� 

	QueryPerformanceCounter(&t_2);		//�Լ� ���� �� �ð� ���� 
	t_diff = t_2.QuadPart-t_1.QuadPart;
	elapsed_time = ((double) t_diff / freq.QuadPart);	//�ɸ��ð� ���� 
	result.time2b[i] = elapsed_time;			// �ɸ� �ð� ���� 
}

