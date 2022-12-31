/*=============================================================================
			작성자 : 경산과학고 2학년 2반 13번 이연준 
		프로그램명 : 영단어 띄어쓰기 구현 및 효율성 분석 
	입력파일 형식
	1. 띄어쓰기 안 된 파일 : 모든 문자가 영어 대문자로만 이루어져야함
								test_.txt (_:번호, 1부터 시작 (1<=_<=n))
	2. 실제 띄어쓰기 파일 : 모든 문자가 영어 대문자 혹은 공백으로 이루어져야함
								collet_.txt (_:번호, 1부터 시작 (1<=_<=n))
	3. 단어 사전 파일 : 모든 문자가 영어 대문자로 되어있어야하며,
						엔터로 구분되야함
						realword.txt 
=============================================================================*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h> 

#define MaxWord 68				//사전 파일의 단어의 최대 문자수 : 68 
#define MaxSten 2<<10			//띄어쓰기 검사할 문장의 최대 문자수 : 2048 (가정) 
#define testcount 8				//test 파일의 수

// 함수 
// 1. 기본 
void explain();					// 프로그램 설명
int selexplain();				// 설명 선택
void prexplain();				// 띄어쓰기 프로그램 설명
void spexplain();				// 일치도 계산 알고리즘 설명 
// 파일이 정상적으로 모두 있는지 검사 : 없으면 어떤 파일이 없는 지 알려주고 종료
int chFile();
// 프로그램 설명, 효율성 분석, 종료 선택 
int selmode();

// 2. 영단어 띄어쓰기
// 2.0 영단어 띄어쓰기 공통파일
int Iswordin(char plword[]);	//띄어쓰기 검사할 단어가 사전파일에 있는지 확인 
int len(char text[]);			//단어 길이를 세는 함수, 파이썬의 len(a) 
void clear(int max);			//띄어쓰기할 단어넣는 변수를 \0으로 초기화 
void slycing(int a, int b);		//문자열 슬라이싱, 파이썬의 tmp[1, 3]을 slycing(1, 3)으로 대체! 

// 2.1 프로그램1 (한 번만 확인)
void Fileopen_simple(int i);	// 프로그램1 관련 파일 열기  
void enter_simple();			// 프로그램1 단어를 띄어쓰기 해주는 함수 
void Simbrute(int j);			// 프로그램1의 main 함수 

// 2.2 프로그램2 (단어가 없을 시 이전 단어를 다른 단어로 검사) 
void Fileopen_check(int i);		// 프로그램2 관련 파일 열기 
void enter_check();				// 프로그램2 단어를 띄어쓰기 해주는 함수 
void Chkbrute(int j);			// 프로그램2의 main 함수 

//3. 띄어쓰기 효율성 분석
//3.0 띄어쓰기 효율성 분석의 main 함수
void analysis(); 
//3.1 걸린시간 측정 
void time_check(int i);
// 일치하는 문자수 세기 
void Fileopen_wcheck(int i);	// 일치하는 문자 수 세기 관련 파일 여는 함수 
void count_wcheck();			// 일치하는 문자 수 세기 
void Wordcheck(int i, int set);			// 일치도 하는 문자수 세기의 main 함수 

//4. 분석 시각화 
void chart();					// 표로 시각화 

//5. 분석 결과
void anresult(); 
 
// 띄어쓰기 안 된 문자열을 저장할 변수, MaxSten만큼씩 저장 가능 
char pltext[MaxSten];
// 사전 파일에 있는 띄어쓰기 안 된 문자열의 단어를 임시적으로 저장하는 용도
char tmp[MaxWord];

// 프로그램2에서 단어를 임시적으로 넣는 구조체 
struct Pointer {
	char first[MaxWord];		// 첫 번째 단어 
	int fircnt;					// 첫 번째 단어의 문자수 
	char second[MaxWord];		// 두 번째 단어 
	int seccnt;					// 두 번째 단어의 문자수
} p;

// 실제 띄어쓰기 
char rlstr[MaxSten+1];			// 정확한 띄어쓰기 결과 넣는 문자열 
struct real{
	int wcnt;					// 실제 단어의 수 
	int rmat;					// 실제 문자의 수 
} real;

// 프로그램1 띄어쓰기 
char sistrb[MaxSten+1];			// 단순 띄어쓰기(프로그램1) 결과 넣는 문자열
// 프로그램1 결과의 단어의 수, 일치하는 문자의 수 저장 
struct bsim{
	int wcnt;					// 띄어쓰기 한 횟수 (검사 결과 단어의 수) 
	int match;					// 일치하는 문자의 수
} bsim;

// 프로그램2 띄어쓰기 
char chstrb[MaxSten+1];			// 다시 확인하는 띄어쓰기(프로그램2) 결과 넣는 문자열
// 프로그램2 결과의 단어의 수, 일치하는 문자의 수 저장 
struct bchk{
	int wcnt;					// 띄어쓰기 한 횟수 (검사 결과 단어의 수) 
	int match;					// 일치하는 문자의 수
} bchk;

// 분석 결과 넣는 곳
struct result{
	float time1b[10];			// 프로그램1 동작하는데 걸린 시간 
	float time2b[10];			// 프로그램2 동작하는데 걸린 시간
	float match1b[10];			// 프로그램1의 일치도(일치하는 문자수*100/전체 문자수) 
	float match2b[10];			// 프로그램2의 일치도(일치하는 문자수*100/전체 문자수)
	int restr[10];				// 각 파일의 전체 문자수  
} result;


// 파일 
//Word : 단어 사전 파일, Plain : 띄어쓰기 안 된 문장
FILE *Word = NULL, *Plain = NULL;
// 프로그램1 단어 띄어쓰기 결과 저장 파일 
FILE *Result_Simple = NULL;
// 프로그램2 단어 띄어쓰기 결과 저장 파일 
FILE *Result_check = NULL;
FILE *Collect = NULL;			// 실제 띄어쓰기 파일 

int main()
{ 
	int i;
	srand((unsigned)time(NULL));
	
	printf("=============================================================\n"); 
	printf("              2213 이연준 데이터 분석 프로그램\n");
	printf("             영단어 띄어쓰기 구현 및 효율성 분석\n");
	printf("=============================================================\n"); 
	
	if(chFile())
	{
		fflush(stdin);
		printf("종료하시려면 enter 키를 입력하세요.\n");
		getchar();
		return 1;
	}
	
	// 설명, 분석, 종료 선택 
	i = selmode();
	
	while(i != 2)
	{
		switch(i) {
			// 설명 
			case 1:
				explain();
				i = selmode();
				break;
			// 종료 
			case 3:
				fflush(stdin);
				printf("프로그램을 종료합니다. 종료하시려면 enter 키를 입력하세요.\n");
				getchar();
				return 0;
		}
	}
	 
	printf("\n");
	
	// 분석
	analysis();
	
	// 분석 결과 보기 혹은 종료 선택 
	printf("==========================================\n");
	printf("  [1] 데이터 분석 결과 보기  [2] 종료하기\n>>> ");
	scanf("%d", &i);
	
	while((i!=1)&&(i!=2)) {
		while (getchar() != '\n');	// 문자 입력시 무한루프 도는 것 방지용 
		printf("\n 1, 2 중 하나만 입력해주세요\n");
		printf("==========================================\n");
		printf("   [1] 데이터 분석 표 보기  [2] 종료하기\n>>> ");
		scanf("%d", &i);
	}
	
	// 분석 결과 보기 
	if(i == 1) chart();
	
	anresult();
	
	// 종료 
	fflush(stdin);
	printf("프로그램을 종료합니다. 종료하시려면 enter 키를 입력하세요.\n");
	getchar();
	return 0;
}

// 분석 결과 
void anresult()
{
	printf("============================================ 결과 분석 =============================================\n ");
	printf(" 단어를 한 번만 확인하며 띄어쓰기를 진행(프로그램1)한 것이 없는 단어가 생기면 이전 단어를 다시 검사\n");
	printf(" 하며 띄어쓰기를 진행(프로그램2)한 것보다 항상 더 적은 시간이 걸렸다. 하지만, 걸린 시간의 차이가\n");
	printf(" 문자의 수에 비례한 것으로는 나타나지 않았다. 이는 사전 파일 전체를 찾아보는 brute-force 기법의\n");
	printf(" 특성상 사전파일에 알맞는 단어가 존재하면 빨리 끝났고, 존재하지 않으면 오래 걸리기 때문이다.\n");
	printf("----------------------------------------------------------------------------------------------------\n");
	printf(" 일치도의 경우도 마찬가지로, 단어를 한 번만 확인하는데 알맞은 단어로만 확인했다면 일치율은 높아진다.\n");
	printf(" 하지만 단어를 한번만 확인(프로그램1)한 경우와 없는 단어가 생기면 다시 확인(프로그램2)한 경우 둘다\n");
	printf(" 정확도가 95%%를 웃도는 것으로 보아, 더 많은 단어를 가진 사전파일을 사용하고,\n");
	printf(" 띄어쓰기 알고리즘을 조금 더 보완한다면 더 효율적인 영단어 띄어쓰기를 구현할 수 있을 것으로 보인다.\n");
	printf("====================================================================================================\n\n");
}

// 영단어 띄어쓰기 결과를 표로 나타냄 
void chart()
{
	int i;
	
	HANDLE ghOutput;
	ghOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	system("cls");
	
	// 문자수에 따른 걸린 시간 
	printf("각 프로그램에 따른 문자수 변화에 따른 걸린 시간(초)\n");
	printf("=============");
	for(i=0; i<testcount; i++) printf("=============");
	printf("\n|   글자수  |"); 
	for(i=0; i<testcount; i++) printf("    %4d    |", result.restr[i]);
	printf("\n| 프로그램1 |"); 
	for(i=0; i<testcount; i++) printf(" %10.6llf |", result.time1b[i]);
	printf("\n| 프로그램2 |");
	for(i=0; i<testcount; i++) printf(" %10.6llf |", result.time2b[i]);
	printf("\n| 차이(2-1) |");
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
	
	// 문자수에 따른 일치도 
	printf("\n\n각 프로그램에 따른 문자수 변화에 따른 일치도(%%)\n");
	printf("=============");
	for(i=0; i<testcount; i++) printf("=============");
	printf("\n|   글자수  |"); 
	for(i=0; i<testcount; i++) printf("    %4d    |", result.restr[i]);
	printf("\n| 프로그램1 |"); 
	for(i=0; i<testcount; i++) printf(" %10.6llf |", result.match1b[i]);
	printf("\n| 프로그램2 |");
	for(i=0; i<testcount; i++) printf(" %10.6llf |", result.match2b[i]);
	printf("\n| 차이(2-1) |");
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

// 설명 선택할 때, 프로그램 설명, 일치도 계산 설명, 설명 종료 입력 예외처리 
int selexplain()
{
	int i = 0;
	while(!((i>=1) && (i<=3))) {
		while (getchar() != '\n');	// 문자 입력시 무한루프 도는 것 방지용 
		printf("\n 1, 2, 3 중 하나만 입력해주세요\n");
		printf("==========================================================================================\n");
		printf("  [1] 프로그램1, 2에 대한 추가 설명  [2] 단어 일치도 분석 알고리즘 설명  [3] 설명 나가기\n>>> ");
		scanf("%d", &i);
	}
	return i; 
}

// 기본적인 프로그램 설명 
void explain()
{
	int i = 0;
	system("cls");	//콘솔 화면 지우고 설명 
	
	printf("\n====================================== 프로그램 설명 ======================================\n");
	printf(" 이 프로그램은 영어 문장의 띄어쓰기를 구현하고 걸린시간, 정확도를 분석하는 프로그램입니다.\n");
	printf(" 영어 문장을 띄어쓰는데 총 2개의 프로그램을 사용합니다.\n");
	printf(" 이 프로그램에서 사용하는 영어 문장은 제 영어 수행평가 일부와 2022년 수능 지문 일부입니다.\n");
	printf(" 사전 파일의 출처는 https://blog.daum.net/edrjang/7968274와\n");
	printf(" https://www.wordfrequency.info/samples.asp의 첫번째 항목의 4번째 파일 입니다.\n");
	printf("======================================== 파일 설명 =======================================\n");
	printf(" realword.txt : 사전 파일\n");
	printf(" result_simple.txt : 프로그램1 결과 파일, result_check.txt : 프로그램2 결과 파일\n");
	printf(" test1.txt, test2.txt,,,,, : 띄어쓰기 안 된 문장 파일\n");
	printf(" collect1.txt, collect2.txt,,,,, : 실제 띄어쓰기 된 문장 파일\n");
	printf("\n - 프로그램1 : 단어 검사를 한 번만 합니다.\n");
	printf(" - 프로그램2 : 단어가 없다면 이전 2개의 단어를 다시 검사합니다.\n");
	printf("==================================== 일치도 계산 방식 ====================================\n");
	printf(" 띄어쓰기의 일치도는 프로그램에 의해 띄어쓰기 된 문장과 실제 띄어쓰기 문장을 비교했을때\n");
	printf(" (일치하는 문자 수/ 전체 문자수) * 100 으로 계산했습니다.\n");
	printf("==========================================================================================\n");
	printf("  [1] 프로그램1, 2에 대한 추가 설명  [2] 단어 일치도 분석 알고리즘 설명  [3] 설명 나가기\n>>> ");
	scanf("%d", &i);

	if(!((i>=1)&&(i<=3))) i = selexplain();

	while(1)
	{		
		if(i == 3) {
			system("cls");	//설명 끝나고 콘솔화면 지우기
			return;
		} else if(i == 1) {
			i = 0;
			// 프로그램 설명 
			prexplain();
		} else if(i == 2){
			i = 0;
			// 일치도 분석 설명 
			spexplain();
		}
		
		while (getchar() != '\n');	// 문자 입력시 무한루프 도는 것 방지용 
		printf("  [1] 프로그램1, 2에 대한 추가 설명  [2] 단어 일치도 분석 알고리즘 설명  [3] 설명 나가기\n>>> ");
		scanf("%d", &i);
		
		if(!((i>=1)&&(i<=3))) i = selexplain();
	}
} 

// 프로그램 설명 
void prexplain()
{
	HANDLE ghOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");	//콘솔 화면 지우고 설명
	printf("\n============================================= 프로그램1 설명 =============================================\n");
	printf(" 1. 띄어쓰기 안 된 파일에서2040자의 문자로 구성된 문장을 읽습니다.\n");
	printf(" 2. 앞에서 부터 문자 한 개씩 추가하며 단어가 사전 파일에 있는지 확인합니다.\n");
	printf(" 3. 만일 사전파일에 단어가 있다면 단어에 관한 정보(단어, 단어의 문자 수)를 저장하고 2.를 계속 반복합니다.\n");
	printf(" 4. 전체 문장을 다 돌았을 때, 단어가 있다면 띄어쓰고 띄어쓴 단어 다음부터 2.의 과정을 반복합니다.\n");
	printf("	 만일 단어가 없다면 다음 단어부터 2.의 과정을 반복합니다.\n");
	printf("-------------------------------------------------- 예시 --------------------------------------------------\n");
	printf(" 원래 문장 : COMES TO MIND WHEN\n");
	printf(" INPUT : COMESTOMINDWHEN\n");
	printf("\n 처리 과정\n");
	printf(" 1.2. C, ,, : 사전파일에 없음 => 그냥 넘어감\n");
	printf("   3. COMES : 사전파일에 있음 => COMES 저장, 문자 수 5 저장\n");
	printf("   3. COMEST : 사전파일에 있음 => COMEST 저장, 문자 수 6 저장\n");
	printf("   3. COMESTO : 사전파일에 없음 => 최종 단어를 COMEST로 저장\n");
	printf("   4. 단어 다음인 COMESTOMIN의 두 번째 O 부터 다시 검사함 (2.3. 과정 반복)\n");
	printf("   4. => OMIN이 최종 단어로 결정, OMIND에서 D부터 다시 검사하지만 D, DW, ,,, : 사전 파일에 없음\n");
	printf("   4. D는 넘어가고 WHEN 부터 검사 시작(2.3. 과정 반복)\n");
	printf("==========================================================================================================\n");
	
	printf("\n============================================= 프로그램2 설명 =============================================\n");
	printf(" 1. 띄어쓰기 안 된 파일에서2040자의 문자로 구성된 문장을 읽습니다.\n");
	printf(" 2. 앞에서 부터 문자 한 개씩 추가하며 단어가 사전 파일에 있는지 확인합니다.\n");
	printf(" 3. 만일 사전파일에 단어가 있다면 단어에 관한 정보(단어, 단어의 문자 수)를 저장하고 2.를 계속 반복합니다.\n");
	printf(" 4. 전체 문장을 다 돌았을 때, 단어가 있다면 띄어쓰고 띄어쓴 단어 다음부터 2.의 과정을 반복합니다.\n");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("	 만일 단어가 없다면 이전 2개의 단어를 다시 검사하여 다른 단어를 최종 단어로 결정합니다.\n");
	printf("	 이후 다시 2.의 과정을 돌아갑니다.\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("-------------------------------------------------- 예시 --------------------------------------------------\n");
	printf(" 원래 문장 : COMES TO MIND WHEN\n");
	printf(" INPUT : COMESTOMINDWHEN\n");
	printf("\n 처리 과정\n");
	printf(" 1.2. C, ,, : 사전파일에 없음 => 그냥 넘어감\n");
	printf("   3. COMES : 사전파일에 있음 => COMES 저장, 문자 수 5 저장\n");
	printf("   3. COMEST : 사전파일에 있음 => COMEST 저장, 문자 수 6 저장\n");
	printf("   3. COMESTO : 사전파일에 없음 => 최종 단어를 COMEST로 저장\n");
	printf("   4. 단어 다음인 COMESTOMIN의 두 번째 O 부터 다시 검사함 (2.3. 과정 반복)\n");
	printf("   4. => OMIN이 최종 단어로 결정, OMIND에서 D부터 다시 검사하지만 D, DW, ,,, : 사전 파일에 없음\n");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("   4. D 이전 두 단어부터 다시 검사 시작 : OMIN, COMEST => COMEST 부터 다시 검사\n");
	printf("   4. COMES : 사전 파일에 있음, COMEST : 사전 파일에 있으나 이전에 사용함 => COMES를 최종단어로 결정\n");
	printf("   4. COMES 다음인 TOMIN의T 부터 다시검사(2.3. 과정 반복)\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("==========================================================================================================\n");
} 

// 띄어쓰기 일치도 분석 알고리즘 설명 
void spexplain()
{
	HANDLE ghOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");	//콘솔 화면 지우고 설명
	printf("\n===================================== 띄어쓰기 일치도 분석 알고리즘 ====================================\n");
	printf(" 실제 띄어쓰기 문장과 프로그램에 의해 띄어쓰기가 된 파일의 문자를 1개씩 비교하며 일치도를 분석합니다.\n");
	printf(" 일치도 분석 프로그램에서는 실제 띄어쓰기 문장과 띄어쓰기 된 문장에서 일치하는 문자의 수를 저장합니다.\n");
	printf(" 문자가 서로 일치하지 않을 때는 프로그램이 띄어쓰기를 수행할 때, 잘못 띄어쓰거나 띄어쓰지 않은 경우입니다.\n");
	printf(" 즉, 이 경우는 실제 문장의 문자 혹은 띄어쓰기한 문장의 문자에 공백이 있는 경우입니다.\n");
	printf("\n 일치하지 않는 문자가 나타났을 경우\n");
	printf(" 1. 실제 띄어쓰기 문장의 문자가 공백인 경우에는 실제 문장의 인덱스를 1 증가시킵니다.\n");
	printf("    이를 통해 실제 띄어쓰기 문장과 띄어쓰기한 문장의 시작점을 동일하게 맞추고 다시 검사합니다.\n");
	printf(" 2. 띄어쓰기 한 문장의 문자가 공백인 경우에는 띄어쓰기 한 문장의 인덱스를 1 증가시킵니다.\n");
	printf("    이를 통해 실제 띄어쓰기 문장과 띄어쓰기한 문장의 시작점을 동일하게 맞추고 다시 검사합니다.\n");
	printf("-------------------------------------------------- 예시 --------------------------------------------------\n");
	printf(" 실제 띄어쓰기 문장 : ES_TO :(_:공백)\n");
	printf(" 띄어쓰기된 문장    : EST_O :(_:공백)\n");
	printf("\n 처리 과정(각 문장의 인덱스 위치의 문자를 출력합니다:COME에서 인덱스가 0이라면 C 출력)\n\n");
	printf(" 1. 실제 띄어쓰기 문장 : ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("E");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("                             2. 실제 띄어쓰기 문장 : E");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("S\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" 1. 띄어쓰기된 문장    : ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("E");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("                             2. 띄어쓰기된 문장    : E");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("S\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("   => ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("E문자 일치");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" => 일치하는 문자 수+1                   => ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("S문자 일치");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" => 일치하는 문자 수+1\n\n"); 
	
	printf(" 3. 실제 띄어쓰기 문장 : ES");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("_\n");
	SetConsoleTextAttribute(ghOutput, 7);	
	printf(" 3. 띄어쓰기된 문장    : ES");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("T\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("   => ");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("문자 불일치");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(", 실제 띄어쓰기 문장의 문자:공백 => 실제 띄어쓰기 문장 인덱스+1\n");
	printf("   => 실제 띄어쓰기 문장 : ES_T\n\n");
	
	printf(" 4. 실제 띄어쓰기 문장 : ES_");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("T\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" 4. 띄어쓰기된 문장    :  ES");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("T\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("   => ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("T문자 일치");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" => 일치하는 문자 수+1\n\n");
	
	printf(" 5. 실제 띄어쓰기 문장 : ES_T");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("O\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" 5. 띄어쓰기된 문장    :  EST");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("_\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("   => ");
	SetConsoleTextAttribute(ghOutput, 12);
	printf("문자 불일치");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(", 띄어쓰기 된 문장의 문자:공백 => 띄어쓰기 된 문장 인덱스+1\n");
	printf("   => 띄어쓰기 된 문장 : ES_T_O\n\n");
	
	printf(" 6. 실제 띄어쓰기 문장 : ES_T");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("O\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" 6. 띄어쓰기된 문장    : EST_");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("O\n");
	SetConsoleTextAttribute(ghOutput, 7);
	printf("   => ");
	SetConsoleTextAttribute(ghOutput, 11);
	printf("O문자 일치");
	SetConsoleTextAttribute(ghOutput, 7);
	printf(" => 일치하는 문자 수+1\n\n");
	printf("==========================================================================================================\n");
}

// 필요한 파일이 존재하는 지 확인 
int chFile()
{
	int i = 1;
	int j;
	char te[] = "test";				// 띄어쓰기 안 된 파일의 공통부분 이름 
	char co[] = "collect";			// 실제 띄어쓰기 파일의 공통부분 이름
	char rlfile[100] = {0};		 	// 문자열 붙여 만들어진 실제 이름 
	char J[64]= {0};
	
	HANDLE ghOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	printf("\n==================== 파일 체크 중입니다. ====================\n");
	
	// 사전 파일 (전처리 결과) 
	Word=fopen("realword.txt", "r");
	if(Word != NULL) {
		SetConsoleTextAttribute(ghOutput, 10);
		printf("  %2d. 사전 파일 준비\t\t\t\t\t: O\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
	} else {
		SetConsoleTextAttribute(ghOutput, 12);
		printf("  %2d. 사전 파일 준비\t\t\t\t\t: X\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
		printf("사전 파일 준비가 잘못되었습니다. 확인 바랍니다.\n");
		fclose(Word);	
		return 1;
	}
	fclose(Word);
	
	printf("\n");
	
	// 띄어쓰기 안 된 파일과 실제 띄어쓰기 파일 
	for(j = 1; j<=testcount; j++)
	{
		// 띄어쓰기 안 된 문장 파일 
		// 파일 이름 정하기 
		itoa(j, J, 10);
		strcpy(rlfile, te);
		strcat(rlfile, J);
		strcat(rlfile, ".txt");
		
		Plain = fopen(rlfile, "r");
		if(Plain != NULL) {
			SetConsoleTextAttribute(ghOutput, 10);
			printf("  %2d. 띄어쓰기 안 된 문장 파일%d 준비\t\t\t: O\n", i++, j);
			SetConsoleTextAttribute(ghOutput, 7);
		} else {
			SetConsoleTextAttribute(ghOutput, 12);
			printf("  %2d. 띄어쓰기 안 된 문장 파일%d 준비\t\t\t: X\n", i++, j);
			SetConsoleTextAttribute(ghOutput,7);
			printf("띄어쓰기 안 된 문장 파일%d 준비가 잘못되었습니다. 확인 바랍니다.\n");
			fclose(Plain);
			return 1;
		}
		fclose(Plain);
		
		// 실제 띄어쓰기 파일 
		// 파일 이름 정하기 
		itoa(j, J, 10);
		strcpy(rlfile, co);
		strcat(rlfile, J);
		strcat(rlfile, ".txt");
		
		Collect = fopen(rlfile, "r");
		if(Collect != NULL) {
			SetConsoleTextAttribute(ghOutput, 10);
			printf("  %2d. 실제 띄어쓰기 파일%d 준비\t\t\t\t: O\n", i++, j);
			SetConsoleTextAttribute(ghOutput, 7);
		} else {
			SetConsoleTextAttribute(ghOutput, 12);
			printf("  %2d. 실제 띄어쓰기 파일%d 준비\t\t\t\t: X\n", i++, j);
			SetConsoleTextAttribute(ghOutput, 7);
			printf("실제 띄어쓰기 파일%d 준비가 잘못되었습니다. 확인 바랍니다.\n", j);
			fclose(Collect);
			return 1;
		}
		fclose(Collect);
	}
	
	printf("\n");
	
	// 띄어쓰기 결과 파일 (프로그램 1) 
	Result_Simple = fopen("result_simple.txt", "w");
	if(Result_Simple != NULL) {
		SetConsoleTextAttribute(ghOutput, 10);
		printf("  %2d. (프로그램1) 띄어쓰기 결과 파일 생성 혹은 준비\t: O\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
	} else {
		SetConsoleTextAttribute(ghOutput, 12);
		printf("  %2d. (프로그램1) 띄어쓰기 결과 파일 생성 혹은 준비\t: X\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
		printf("(프로그램1) 띄어쓰기 결과 파일 생성 혹은 준비가 잘못되었습니다. 확인 바랍니다.\n");
		fclose(Result_Simple);
		return 1;
	}
	fclose(Result_Simple);
	
	// 띄어쓰기 결과 파일 (프로그램 2) 
	Result_check = fopen("result_check.txt", "w");
	if(Result_check != NULL) {
		SetConsoleTextAttribute(ghOutput, 10);
		printf("  %2d. (프로그램2) 띄어쓰기 결과 파일 생성 혹은 준비\t: O\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
	} else {
		SetConsoleTextAttribute(ghOutput, 12);
		printf("  %2d. (프로그램2) 띄어쓰기 결과 파일 생성 혹은 준비\t: X\n", i++);
		SetConsoleTextAttribute(ghOutput, 7);
		printf("(프로그램2) 띄어쓰기 결과 파일 생성 혹은 준비가 잘못되었습니다. 확인 바랍니다.\n");
		fclose(Result_Simple);
		return 1;
	}
	fclose(Result_check);
	
	printf("===================== 파일 체크 완료!! ======================\n\n");
	
	return 0;
}

// 설명, 분석, 종료 선택 
int selmode()
{
	int i = 0;
	printf("=============================================================\n");
	printf("\t  [1] 영단어 띄어쓰기 프로그램 상세 정보\n");
	printf("\t  [2] 영단어 띄어쓰기 효율 분석\n");
	printf("\t  [3] 프로그램 종료\n");
	printf("=============================================================\n>>> ");
	scanf("%d", &i);

	while(!((i>=1) && (i<=3))) {
		while (getchar() != '\n');	// 문자 입력시 무한루프 도는 것 방지용 
		printf("\n 1이상 3이하의 정수만 입력해주세요\n");
		printf("=============================================================\n");
		printf("\t  [1] 영단어 띄어쓰기 프로그램 상세 정보\n");
		printf("\t  [2] 영단어 띄어쓰기 효율 분석\n");
		printf("\t  [3] 프로그램- 종료\n");
		printf("=============================================================\n>>> ");
		scanf("%d", &i);
	}
	return i;
}

// 영단어 띄어쓰기 효율성 분석 
void analysis()
{
	int i, rpnt;

	printf("=============================================================\n");
	printf("  [1] 띄어쓰기 결과 출력하기  [2] 띄어쓰기 결과 출력하지 않기 \n>>> ");
	scanf("%d", &rpnt);

	while((rpnt!=1) && (rpnt!=2)) {
		while (getchar() != '\n');	// 문자 입력시 무한루프 도는 것 방지용 
		printf("\n 1, 2 중 하나만 입력해주세요\n");
		printf("=============================================================\n");
		printf(" [1] 띄어쓰기 결과 출력하기  [2] 띄어쓰기 결과 출력하지 않기 \n>>> ");
		scanf("%d", &rpnt);
	}
	
	// 영단어 띄어쓰기 및 일치도 측정 
	for(i= 0; i<testcount; i++)
	{
		printf("\n예시파일%d의 띄어쓰기가 진행됩니다.\n", i+1);
		
		// 걸리는 시간 측정 
		time_check(i);
		
		// 일치하는 문자 수 측정 
		Wordcheck(i, rpnt);	
		
		printf("\n\n프로그램1 걸린 시간 : %llf초\n", result.time1b[i]);
		printf("프로그램2 걸린 시간 : %llf초\n", result.time2b[i]);
		
		printf("프로그램1 일치하는 문자의 수 : %d, 전체 문자수 : %d, 프로그램1 단어 수 : %d, 실제 단어 수 : %d\n", bsim.match, real.rmat, bsim.wcnt, real.wcnt);
		printf("프로그램1의 일치도 : %llf\n", result.match1b[i]); 
		
		printf("프로그램2 일치하는 문자의 수 : %d, 전체 문자수 : %d, 프로그램2 단어 수 : %d, 실제 단어 수 : %d\n", bchk.match, real.rmat, bchk.wcnt, real.wcnt);
		printf("프로그램2의 일치도 : %llf\n", result.match2b[i]);
		printf("====================================================================================================\n");
	}
	
	// 측정 결과 표시 
	for(i= 0; i<testcount; i++)
	{
		printf("예시파일%d\n", i+1);
		
		printf("프로그램1 걸린 시간 : %llf초\n", result.time1b[i]);		
		printf("프로그램1의 일치도 : %llf, 전체 문자 수 : %d\n\n", result.match1b[i], result.restr[i]);
		
		printf("프로그램2 걸린 시간 : %llf초\n", result.time2b[i]); 
		printf("프로그램2의 일치도 : %llf, 전체 문자 수 : %d\n\n", result.match2b[i], result.restr[i]);
	}
}

// 프로그램2 main(단어 없으면 이전 단어 다시 확인) 
void Chkbrute(int j)
{
	int i;
	// 단어믜 문자수 초기화 
	p.fircnt = 0;
	p.seccnt = 0;
	
	printf("프로그램2가 동작중입니다.");
	
	//프로그램2 관련 파일 열기 
	Fileopen_check(j);
	
	//띄어쓰기할 문장을 변수에 집어넣기(한 문자씩) (MaxSten개의 문자) 
	for(i = 0; !feof(Plain); i++)
	{
		if(i >= MaxSten){
			enter_check();
			clear(i--);
			i = 0;
		}
		
		pltext[i] = fgetc(Plain);
    }
    
    // 만일 마지막 문자열이 Maxten 개 미만의 문자로 이루어져 있지 않는 문장일 경우
	// 단어를 분석하여 띄어쓰기 시켜서 넣어준다. 
	if(i != 0){
		enter_check();
	}
	
	// 이 프로그램은 단어를 first, second 변수에 넣고 세번째 단어가 존재하면 first를 넣는 방식이다. 
	// 하지만 파일의 끝으로 가면 first, second는 존재하나 세번째 단어는 존재하지 않는다. (컴퓨터는 세번째 단어 존재 유무를 확인하지 못한다.)
	// 그래서 마지막 2개의 단어를 파일에 넣어주어 띄어쓰기를 완성한다.
	fprintf(Result_Simple, "%s ", p.first);
	fprintf(Result_Simple, "%s ", p.second);
	
	fclose(Word);
	fclose(Plain);
	fclose(Result_Simple);
	
	printf("\r프로그램2의 동작이 종료되었습니다.\n");
}

// 프로그램2 관련 파일 열기 
void Fileopen_check(int i)
{
	char te[] = "test";				// 띄어쓰기 안 된 파일의 공통부분 이름 
	char rlfile[100] = {0};		 	// 문자열 붙여 만들어진 실제 이름 
	char J[64]= {0};
	
	// 파일 이름 정하기 
	itoa(i+1, J, 10);
	strcpy(rlfile, te);
	strcat(rlfile, J);
	strcat(rlfile, ".txt");
	
	// 띄어쓰기 안 된 문장 파일 
	Plain = fopen(rlfile, "r");
	Word = fopen("realword.txt", "r");
	Result_check = fopen("result_check.txt", "w");
}

// 프로그램1 관련 파일 열기 
void Fileopen_simple(int i)
{
	char te[] = "test";				// 띄어쓰기 안 된 파일의 공통부분 이름 
	char rlfile[100] = {0};		 	// 문자열 붙여 만들어진 실제 이름 
	char J[64]= {0};
	
	// 파일 이름 정하기 
	itoa(i+1, J, 10);
	strcpy(rlfile, te);
	strcat(rlfile, J);
	strcat(rlfile, ".txt");
	
	// 띄어쓰기 안 된 문장 파일 
	Plain = fopen(rlfile, "r");
	Word = fopen("realword.txt", "r");
	Result_Simple = fopen("result_simple.txt", "w");
}

//사전 파일에 원하는 단어가 있는지 확인 
int Iswordin(char word[])
{
	char line[MaxWord];
	int i, leline, leword = len(word); //leline : 사전 파일 단어(line)의 문자 수, leword : 원하는 단어(word)의 문자 수 
	
	// 사전 파일의 포인터를 처음 위치로 초기화하여 항상 처음부터 검색할 수 있도록!! 
	fseek(Word, 0, SEEK_SET);
	
	while(!feof(Word))
	{
		fgets(line, MaxWord, Word);
		leline = len(line);
		// 원하는 단어의 문자수와 사전 파일 단어의 문자수가 같을 경우만 인덱스 1개씩 같은지 검사 
		if(leline == leword)
		{
			for(i=0; i < leline; i++) if(line[i] != word[i]) break;
			if(i == leline) return 1;
		}
    }
    return 0;
}

// text의 문자수 반환 
int len(char text[])
{
	int check;
	for(check = 0; (text[check] != '\n')&&(text[check] != '\0')&&(check <= MaxSten); check++);
	return check;
} 

// 띄어쓰기 집어넣을 변수 초기화 
void clear(int max)
{
	int i;
	for(i = 0; i <= max; i++) pltext[i] = '\0';
}

// 문자열 슬라이싱 
void slycing(int a, int b)
{
	int i;
	for(i = 0; i < b-a; i++) tmp[i] = pltext[a+i];
	tmp[b-a] = '\0';
}

// 프로그램2 띄어쓰기 결과를 결과 파일에 넣기 
void enter_check()
{
	char temp[MaxWord];					//temp : 사전 파일에 있는 단어 저장용 
	int curi = 0;						// 4.기능을 수행하기 위한 변수, 사전 파일에 있는 단어 다음 인덱스 값을 가리킴, 위의 예시에서는 두번째 I를 가리키게 됨 
	int Hasres = 0;						// 4.에서 사전 파일에 단어가 있는지(1) 없는지(0) 확인하는 용도 
	int pllen = len(pltext);			//띄어쓰기할 문장의 문자수 구해서 저장
	int check = 0;						//만일 단어를 2번 검사해도 없을 경우, 해당 단어를 건너뛰고 다음 단어를 p.first에 담는 용도 
	int i = 0, j, k;
	
	//띄어쓰기할 문장 전체를 한 번씩 돌아보며 단어 파악 
	while(i < pllen-1)
	{
		//문자 한 개씩 찾아보며 단어파악, 단어를 찾으면 단어 길이만큼 포인터 넘어감 
		for(j = i+1; (j <= pllen)&&(j <= i+MaxWord); j++)
		{
			slycing(i, j);
			if(Iswordin(tmp))
			{
				//사전 파일에 있는 단어 등장 => 단어, 단어 다음의 인덱스값 저장 
				strcpy(temp, tmp);
				temp[j-i+1] = '\0';
				Hasres = 1;
				curi = j;
			}
		}
		//단어 존재 => "단어 " 결과 txt에 입력 
		if(Hasres)
		{
			//첫 번째로 띄어쓰기 된 단어가 들어왔을 때, 단어를 두번 검사했는데도 없을 경우 
			if(check == 0) {
				//첫 번째 단어에 첫 번째 단어를 집어넣음 
				p.fircnt = len(temp); 
				strcpy(p.first, temp); //문자열 복사 temp -> p.first
				check = 1;
			} else if(check == 1) {
				//두 번째로 띄어쓰기 된 단어가 들어왔을 때, 단어를 두번 검사하여 없었던 경우 이후 단어를 저장 
				p.seccnt = len(temp); 
				strcpy(p.second, temp); //문자열 복사 temp -> p.second
				check = 2;
			} else {
				//정확한 단어를 txt파일에 넣는 용도 
				fprintf(Result_check, "%s ", p.first);
				//결과 임시 배열의 두 번째 단어를 첫 번째 단어의 위치로 미는 것
				strcpy(p.first, p.second);
				p.fircnt = p.seccnt;
				//결과 임시 배열에 또 새로 추가된 단어를 넣는 과정 
				strcpy(p.second, temp);	//문자열 복사 temp -> p.second
				p.seccnt = len(p.second);
			}
			i = curi;
		} else {
			// 단어 없음 => 이전 이전 단어를 다시 검사 
			if(check == 1)
			{
				k = 0;
				//두번째 단어를 검사하는데 없는 경우 
				//두 번째 단어 시작 인덱스 : curi => 첫 번째 단어 시작 인덱스 : curi-p.fircnt 
				for(i = curi-p.fircnt+1; i < curi; i++)
				{
					slycing(curi, i);
					if(Iswordin(tmp))
					{
						//사전 파일에 있는 단어 등장 => 단어, 단어 다음의 인덱스값 저장 
						strcpy(temp, tmp);
						temp[i] = '\0';
						Hasres = 1;
						curi = i;
					}
				}
				
				// 첫번째 단어도 더 이상 더 작은 문자수의 단어가 없는 경우
				if(!(Hasres))
				{
					//첫 번째 단어 넣기
					fprintf(Result_check, "%s ", p.first);
					p.first[0] = '\0';
					p.fircnt = 0;
					
					//두 번째 단어를 검사하는 데 없다는 것은 시작지점이 잘못됨 => 시작지점 파일에 넣고, 1칸 밀기 
					fprintf(Result_check, "%c ", pltext[i]);
					// 다시 처음부터 시작하는 것과 같음
					check = 0;
					//근데 시작지점은 i+1번째 부터 (잘못된 시작지점 다음)
					i++; 
				} 
			} else {
				// 세번째 이상의 단어를 검사하는데 없는 경우 : i는 두번째 단어의 시작 인덱스 값을 가지고 있음 
				k = i-p.fircnt-p.seccnt;
				for(i = k+1; i < k+p.fircnt; i++)
				{
					slycing(k, i);
					if(Iswordin(tmp))
					{
						//사전 파일에 있는 단어 등장 => 단어, 단어 다음의 인덱스값 저장 
						strcpy(temp, tmp);
						//temp[i-k+1] = '\0';
						Hasres = 1;
						curi = i;
					}
				}				
				// 만일 다시 검색하는데도 단어가 없다면 처음 문자를 결과 파일에 적고 처음 문자를 다음 문자로 넘어감 
				if(!(Hasres))
				{
					i = k;
					// 파일 입력할 때, 마지막에 이상한 값이 들어옴 => 알파벳이 아니면 결과 파일에 넣지 않음
					if((pltext[i]>=65) && (pltext[i]<=90))
					{
						fprintf(Result_check, "%c ", pltext[i]);
					}
					p.first[0] = '\0';
					p.second[0] = '\0';
					p.fircnt = 0;
					p.seccnt = 0;
					i++;
					// 다음 문자로 넘어가서 p.first부터 단어를 넣기 위함 
					check = 0; 
				}
				
			}
			if(check)
			{
				strcpy(p.first, temp);	// temp -> p.first
				p.fircnt = len(p.first);
				p.seccnt = 0;
				// 단어가 없어서 p.first에 넣었으므로 다음 단어는 p.second에 들어가야함
				check = 1;
			} 			
		}
		//다시 돌아야 하니 단어 없음으로 변경 
		Hasres = 0;
		
		if(check) i = curi;
	}
}

// 프로그램1 main (한 번만 확인)
void Simbrute(int j)
{
	int i;
	
	printf("프로그램1이 동작중입니다.");
	
	Fileopen_simple(j);
	
	//띄어쓰기할 문장을 변수에 집어넣기 (MaxSten개의 문자 혹은 .으로 구분되는 문장) 
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
	
	printf("\r프로그램1의 동작이 종료되었습니다.\n");
}

// 프로그램1 띄어쓰기 결과를 결과 파일에 넣기 
void enter_simple()
{
	char temp[MaxWord];					//temp : 사전 파일에 있는 단어 저장용 
	int curi = 0;						// 4.기능을 수행하기 위한 변수, 사전 파일에 있는 단어 다음 인덱스 값을 가리킴, 위의 예시에서는 두번째 I를 가리키게 됨 
	int Hasres = 0;						// 4.에서 사전 파일에 단어가 있는지(1) 없는지(0) 확인하는 용도 
	int pllen = len(pltext);			//띄어쓰기할 문장의 문자수 구해서 저장
	int i = 0, j;
	
	//띄어쓰기할 문장 전체를 한 번씩 돌아보며 단어 파악 
	while(i < pllen)
	{
		//문자 한 개씩 찾아보며 단어파악, 단어를 찾으면 단어 길이만큼 포인터 넘어감 
		for(j = i+1; (j <= pllen)&&(j <= i+MaxWord); j++)
		{
			slycing(i, j);
			if(Iswordin(tmp))
			{
				//printf("%s\t : [%s]\n", pltext, temp);
				//사전 파일에 있는 단어 등장 => 단어, 단어 다음의 인덱스값 저장 
				strcpy(temp, tmp);
				temp[j-i+1] = '\0';
				Hasres = 1;
				curi = j;
			}
		}
		
		//단어 존재 => "단어 " 결과 txt에 입력 
		if(Hasres)
		{
			fprintf(Result_Simple, "%s ", temp);
			//printf("1 : %s\n", temp);
			i = curi;
		}
		//단어 없음 => 없는 문자 넣고 한 문자 넘어감(파일 입력할 때, 마지막에 이상한 값이 들어옴 => 알파벳이 아니면 결과 파일에 넣지 않음) 
		else
		{
			if((pltext[i]>=65) && (pltext[i]<=90))
			{
				fprintf(Result_Simple, "%c ", pltext[i]);
			}
			i++;
		}
		
		//다시 돌아야 하니 단어 없음으로 변경 
		Hasres = 0; 
		
	}
}

// 단어 일치도 계산 main 
void Wordcheck(int i, int set)
{
	int all = 0; // 전체 문자의수 	

	Fileopen_wcheck(i);
	
	//띄어쓰기할 문장을 변수에 집어넣기(한 문자씩) (MaxSten_check개의 문자) 
	if(!feof(Result_Simple)) fgets(sistrb, MaxSten, Result_Simple);
	if(!feof(Result_check)) fgets(chstrb, MaxSten, Result_check);
	if(!feof(Collect)) fgets(rlstr, MaxSten, Collect);
	
	if(set == 1)
	{
		printf("\n 실제 문장\n");
		printf("%s\n", rlstr);
		printf("\n 프로그램1 띄어쓰기 결과\n");
		printf("%s\n", sistrb);
		printf("\n 프로그램2 띄어쓰기 결과\n");
		printf("%s\n", chstrb);
	}

	// 실제 띄어쓰기의 문자수, 단어수 초기화 
	real.rmat = 0;			// 실제 띄어쓰기 문자수 
	real.wcnt = 0;			// 실제 띄어쓰기 단어수 
	// 프로그램1 띄어쓰기 결과의 일치하는 문자수, 단어수 초기화 
	bsim.match = 0;			// 프로그램1의 일치하는 문자수 
	bsim.wcnt = 0;			// 프로그램1의 단어수
	//프로그램2의 띄어쓰기 결과의 일치하는 문자수, 단어수 초기화 
	bchk.match = 0;			// 프로그램2의 일치하는 문자수 
	bchk.wcnt = 0;			// 프로그램2의 단어수 
	
	// 일치하는 문자수, 단어수 측정 
	count_wcheck();
	
	result.match1b[i] =  bsim.match*100.0/real.rmat;	// 프로그램1의 문자 일치도 저장 
	result.match2b[i] =  bchk.match*100.0/real.rmat;	// 프로그램2의 문자 일치도 저장
	result.restr[i] = real.rmat;						// 각 파일의 전체 문자수 저장 
	
	fclose(Result_Simple);
	fclose(Result_check);
	fclose(Collect);
}

// 단어 일치도 분석 관련 파일 열기 
void Fileopen_wcheck(int i)
{
	char co[] = "collect";			// 실제 띄어쓰기 파일의 공통부분 이름
	char rlfile[100] = {0};		 	// 문자열 붙여 만들어진 실제 이름 
	char J[64]= {0};
	
	// 파일 이름 정하기 
	itoa(i+1, J, 10);
	strcpy(rlfile, co);
	strcat(rlfile, J);
	strcat(rlfile, ".txt");
	
	// 띄어쓰기 안 된 문장 파일 
	Collect = fopen(rlfile, "r");
	Result_Simple = fopen("result_simple.txt", "r");
	Result_check = fopen("result_check.txt", "r");
}

// 문자와 단어수 세기 
void count_wcheck()
{
	// 단순 띄어쓰기(프로그램1) 결과 : sistrb
	// 2번 확인(프로그램2) 결과 : chstrb
	// 정확한 띄어쓰기 : rlstr 

	// wcnt : 모든 단어의 수 
	int i = 0, j = 0, k;				// i:정답 파일 인덱스, j:결과 파일 인덱스, k : 문자수 혹은 단어수 셀 때 쓸 변수 
	int rdcheck = 1;		// rdcheck 결과 문자열과 정답 문자열을 다 읽으면 0 
	
	for(k=0; rlstr[k] != '\0'; k++)
	{
		//정답 문자열의 단어 수 세기 : 마지막이 공백으로 되어있으면 단어가 끝남!! 
		if(rlstr[k] == ' ') real.wcnt++;
	}
	// 정답 문자열의 문자수 
	real.rmat = k;
	
	for(k=0; sistrb[k] != '\0'; k++)
	{
		//결과1 문자열의 단어 수 세기 : 마지막이 공백으로 되어있으면 단어가 끝남!! 
		if(sistrb[k] == ' ') bsim.wcnt++;
	}
	
	for(k=0; chstrb[k] != '\0'; k++)
	{
		//결과2 문자열의 단어 수 세기 : 마지막이 공백으로 되어있으면 단어가 끝남!! 
		if(chstrb[k] == ' ') bchk.wcnt++;
	}
	
	// 블로그 사전 파일: 단순 띄어쓰기(프로그램1) 결과 분석 
	while(rdcheck)
	{		
		// 정답문자열의 i번째 문자와 결과 문자열의 j번째 문자가 동일 => 넘어감  
		if(rlstr[i] == sistrb[j])
		{
			i++;
			j++;
			bsim.match++;
		} else {
			// 정답문자열의 i번째 문자와 결과 문자열의 j번째 문자가 다름 => error에 1더하고 경우에 따라 나눔
			
			// 정답 : 공백, 결과 : 문자 => 띄어쓰기가 되지 않음 => 결과를 띄어써야 올바른 띄어쓰기
			// => 결과를 띄어쓰는 효과로 정답 인덱스+1 (제대로 띄어썼을 경우로 됨) => 검사 재개 
			if(rlstr[i] == ' ')
			{
				// 정답 문자열의 인덱스값 +1 
				i++;
			}
			
			// 위의 경우가 아닌 경우; 정답 : 문자, 결과 : 공백 => 잘못된 띄어쓰기가 됨 => 결과를 붙여써야 올바른 띄어쓰기
			// => 결과를 붙여쓰는 효과로 결과 인덱스+1 (제대로 띄어썼을 경우로 됨) => 검사 재개 
			else
			{
				// 결과 문자열의 인덱스값 +1 
				j++;
			}
		}
		
		if((rlstr[i] == '\0') && (sistrb[j] == '\0')) rdcheck = 0;
	}
	real.rmat = i-1;			// 마지막 인덱스에 저장된 값 : '\0' : 문자열의 끝을 나타내므로 문자가 아님 => i-1 저장하여 전체 문자 알려줌 
	
	i = 0; j = 0; rdcheck = 1;
	
	// 블로그 사전 파일: 2번 확인(프로그램2) 결과 분석 
	while(rdcheck)
	{		
		// 정답문자열의 i번째 문자와 결과 문자열의 j번째 문자가 동일 => 넘어감  
		if(rlstr[i] == chstrb[j])
		{
			i++;
			j++;
			bchk.match++;
		} else {
			// 정답 : 공백, 결과 : 문자 => 띄어쓰기가 되지 않음 => 결과를 띄어써야 올바른 띄어쓰기
			// => 결과를 띄어쓰는 효과로 정답 인덱스+1 (제대로 띄어썼을 경우로 됨) => 검사 재개 
			if(rlstr[i] == ' ')
			{
				// 정답 문자열의 인덱스값 +1 
				i++;
			}
			
			// 위의 경우가 아닌 경우; 정답 : 문자, 결과 : 공백 => 잘못된 띄어쓰기가 됨 => 결과를 붙여써야 올바른 띄어쓰기
			// => 결과를 붙여쓰는 효과로 결과 인덱스+1 (제대로 띄어썼을 경우로 됨) => 검사 재개 
			else
			{
				// 결과 문자열의 인덱스값 +1 
				j++;
			}
		}
		
		if((rlstr[i] == '\0') && (chstrb[j] == '\0')) rdcheck = 0;
	}
} 

//  걸린 시간 측정 
void time_check(int i)
{
	// 걸린 시간 측정에 쓸 변수들 
	LARGE_INTEGER freq, t_1, t_2; //t_1:실행 전	t_2:실행 후 
	LONGLONG t_diff;
	double elapsed_time;
	
	// 프로그램1 걸린 시간 측정 
	QueryPerformanceCounter(&t_1);		//함수 실행 전 시간 측정
	QueryPerformanceFrequency(&freq);

	Simbrute(i);						// 프로그램1 띄어쓰기 실행 

	QueryPerformanceCounter(&t_2);		//함수 실행 후 시간 측정 
	t_diff = t_2.QuadPart-t_1.QuadPart;
	elapsed_time = ((double) t_diff / freq.QuadPart);	//걸린시간 측정 
	result.time1b[i] = elapsed_time;			// 걸린 시간 저장 
	
	// 프로그램2 걸린 시간 측정 
	QueryPerformanceCounter(&t_1);		//함수 실행 전 시간 측정
	QueryPerformanceFrequency(&freq);

	Chkbrute(i);						//프로그램2 띄어쓰기 실행 

	QueryPerformanceCounter(&t_2);		//함수 실행 후 시간 측정 
	t_diff = t_2.QuadPart-t_1.QuadPart;
	elapsed_time = ((double) t_diff / freq.QuadPart);	//걸린시간 측정 
	result.time2b[i] = elapsed_time;			// 걸린 시간 저장 
}

