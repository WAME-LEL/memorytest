//2019243065 박석주
//컴퓨터공학과 2학년
//기초프로젝트 프로젝트2
//기억력 테스트 게임


#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct account {
	char id[15];
	char password[15];
	struct account* next;
}ACCOUNT;

typedef struct ranking {
	char id[15];
	int point1;		//단어 테스트 점수
	int point2;		//코딩 테스트 점수
	int total;		//총 점수
	int rank;		//순위
	struct ranking* next;
}RANKING;

void Head();
void signup();		//회원가입 함수
int signin();		//로그인 함수
void withdraw();	//회원 탈퇴 함수
int word_test(int score);		//단어 테스트 함수
void rank_manage(int score1, int score2, int total_score, int judge);		//랭킹 관리 함수
RANKING* sorted_insert(int score1, int score2, int total_score, RANKING* list);		//새로운 랭킹 삽입 함수
void print_ranking();		//랭킹 출력 함수
int coding_game();		//코딩 테스트 함수
void show_example(FILE* fp);	//파일에 입력된 내용 출력 함수
void explain_word();
void explain_coding();

char userID[15];		//여러 함수에서 쓰기에 전역변수로 선언

void main() {
	int menu;
	int end = 1;
	int score1, score2;
	int judge;
	int i;


	while (end) {		//end가 0이 되면 반복 종료
		score1 = 0;
		score2 = 0;
		judge = 0;
		Head();
		printf("1. 로그인\n");
		printf("2. 게스트 로그인\n");
		printf("3. 랭킹 출력\n");
		printf("4. 회원가입\n");
		printf("5. 회원탈퇴\n");
		printf("6. 게임 종료\n");


		printf("Enter the nubmer:");
		scanf("%d", &menu);


		system("cls");
		switch (menu) {

		case 1:		//menu가 1일 경우 로그인 실행
			if (signin()==1) {		//로그인을 성공했을 경우 테스트 실행
				
				system("cls");
				explain_word();
				system("pause");
				system("cls");
				
				for (i = 0; i < 2; i++) {
					score1 = word_test(score1);

				}
				system("cls");

				score2 = coding_game();

				system("cls");
				rank_manage(score1, score2, score1 + score2, judge);

				print_ranking();
				printf("==============================================\n\n");
				printf("%s님의 점수가 등록 되었습니다!\n\n", userID);
				printf("@@이전에 받았던 점수보다 높은 점수를 받았을 경우 점수가 갱신됩니다!\n");
				printf("@@이전에 받았던 점수보다 낮은 점수를 받았을 경우 점수가 등록되지않습니다!\n");
			}
			
			break;

		case 2:		//menu가 2일 경우 게스트 로그인 실행
			judge = 1;

			explain_word();
			system("pause");
			system("cls");

			for (i = 0; i < 2; i++) {
				score1 = word_test(score1);

			}
			system("cls");

			score2=coding_game();

			system("cls");
			rank_manage(score1, score2, score1+score2, judge);

			print_ranking();
			printf("==============================================\n\n");
			printf("%s님의 점수가 등록 되었습니다!\n\n", userID);
			printf("@@이전에 받았던 점수보다 높은 점수를 받았을 경우 점수가 갱신됩니다!\n");
			printf("@@이전에 받았던 점수보다 낮은 점수를 받았을 경우 점수가 등록되지않습니다!\n");
			break;



		case 3:		//menu가 3일 경우 랭킹 출력 
			print_ranking();
			break;


		case 4:		//menu가 4일 경우 회원가입 실행
			signup();
			
			break;

		case 5:		//menu가 5일 경우 회원탈퇴 실행
			withdraw();

			break;
		

		case 6:		//menu가 6일 경우 게임 종료 실행
			end = 0;
			printf("게임이 종료되었습니다\n");
			return 0;

		default:
			printf("잘못된 입력입니다\n");
			break;
			
		}
		system("pause");
		system("cls");

	}

}


void Head(){

	printf("======================================\n");
	printf("==                                  ==\n");
	printf("==         Memory test game         ==\n");
	printf("==                                  ==\n");
	printf("======================================\n\n");
}

void signup() {
	FILE* fp;
	ACCOUNT user;
	system("cls");
	fp = fopen("Account.txt", "a");		//fopen의 append(추가) 모드
	
	printf("==============================================\n\n");
	printf("\t\t회원가입\n\n");
	printf("==============================================\n\n");
	printf("      ID:");
	scanf("%s", user.id);
	printf("PASSWORD:");
	scanf("%s", user.password);
	fprintf(fp, "%s %s\n",user.id,  user.password);		// "%s %s\n" 의 형태로  Account.txt에 추가
	printf("회원가입 성공!\n");
	fclose(fp);
}

int signin() {
	FILE* fp;
	int judge = 0;
	ACCOUNT list;
	ACCOUNT user;

	printf("==============================================\n\n");
	printf("\t\t로그인\n\n");
	printf("==============================================\n\n");
	printf("      ID:");
	scanf("%s", user.id);
	printf("PASSWORD:");
	scanf("%s", user.password);

	strcpy(userID, user.id);		//입력한 ID를 전역변수 userID에 대입

	fp = fopen("Account.txt", "r");


	while (!feof(fp)) {
		fscanf(fp, "%s %s", list.id, list.password);

		if (strcmp(user.id, list.id) == 0 && strcmp(user.password, list.password) == 0) {
			judge = 1; 
		}

	}

	if (judge == 1) {		//ACCOUNT.txt에 ID와 PASSWORD가 동일한것이 있을경우
		printf("로그인 성공! 환영합니다 %s 님!\n", user.id);
		return 1;
	}
	else {
		printf("없는 계정입니다!\n");
	}
	fclose(fp);
	return 0;
	
}

void withdraw() {
	FILE* fp = fopen("Account.txt", "r");
	ACCOUNT* list=NULL;
	ACCOUNT* newnode = NULL;
	ACCOUNT* current = NULL, * follow = NULL;
	ACCOUNT user;
	char* garbage=NULL;
	
	printf("==============================================\n\n");
	printf("\t\t회원탈퇴\n\n");
	printf("==============================================\n\n");
	printf("      ID:");
	scanf("%s", user.id);
	printf("PASSWORD:");
	scanf("%s", user.password);

	while (!feof(fp)) {		//파일 끝까지 연결리스트에 삽입
		newnode = (ACCOUNT*)malloc(sizeof(ACCOUNT));
		fscanf(fp, "%s %s", newnode->id, newnode->password);
		newnode->next = list;
		list = newnode;
	}
	list = list->next;

	current = follow = list; 


	//Account.txt의 같은 ID와 PASSWORD를 발견할때 까지 이동
	while ((current != NULL)&& (strcmp(user.id, current->id) != 0 || strcmp(user.password, current->password) != 0)) {
		follow = current;
		current = current->next;
	}

	//끝까지 이동했을 경우 같은 정보가 없다고 판단
	if (current == NULL) {
		printf("삭제하고자하는 정보가 없습니다\n");
		return ;
	}

	//처음에 같은 정보가 있을 경우 첫 노드 삭제 
	if (list == current) {
		list = current->next;
	}
	
	// 마지막에 같은 정보가 있을 경우 마지막 노드 삭제
	else if (current->next == NULL) {
		follow->next = NULL;
	}

	// 중간에 같은 정보가 있을 경우 중간에 있는 노드 삭제
	else {
		follow->next = current->next;
	}

	free(current);
	fclose(fp);

	fp = fopen("Account.txt", "w");
	
	while (list != NULL) {		//삭제가 완료된 정보들을 Account.txt에 다시 삽입
		fprintf(fp, "%s %s\n", list->id, list->password);
		list = list->next;
	}
	printf("%s님의 탈퇴가 완료되었습니다\n", user.id);
	fclose(fp);

}

void rank_manage(int score1, int score2, int total_score, int judge) {
	FILE* fp=fopen("Ranking.txt", "r");
	RANKING * list=NULL;
	RANKING* newnode=NULL, *current=NULL;

	while (!feof(fp)) {
		newnode = (RANKING*)malloc(sizeof(RANKING));
		fscanf(fp, "%s %d %d %d %d", newnode->id, &newnode->point1, &newnode->point2, &newnode->total, &newnode->rank);
		newnode->next = NULL;

		//노드가 하나도 없을 경우
		if (list == NULL) {
			list = newnode;
		}
		//연결리스트 마지막에 노드 삽입
		else {
			current = list;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = newnode;
		}
		
	}
	printf("\n");
	
	if (judge == 1) {		//게스트 로그인
		system("cls");
		printf("사용할 닉네임을 입력하시오:");
		scanf("%s", userID);
	}

	list = sorted_insert(score1, score2, total_score, list);	//list에 새로운 노드 삽입	

	fclose(fp);

	fp = fopen("Ranking.txt", "w");

	while (list != NULL) {
		fprintf(fp, "%s %d %d %d %d\n", list->id, list->point1, list->point2, list->total, list->rank);
		list = list->next;
		if (list->next == NULL) {
			list = list->next;
		}
	}
	list = current;
	fclose(fp);

}

RANKING* sorted_insert(int score1, int score2, int total_score, RANKING* list) {
	RANKING* current = NULL, * follow = NULL, * newnode = NULL, *copy=NULL;
	current = follow = copy = list;
	int judge = 0;


	while (copy != NULL) {
		follow = copy;
		if (strcmp(userID, copy->id) == 0) {		//Ranking.txt에 존재하는 ID와 가 같은 ID로 테스트를 진행했을 경우
			if (total_score > copy->total) {		//더 높은 점수를 받았다면 기존 점수 수정
				copy->point1 = score1;
				copy->point2 = score2;
				copy->total = total_score;

			}
			else {
				copy = copy->next;					//더 높은 점수를 받지 못했다면 그냥 넘어감
				
			}

			judge = 1;
		}
		copy = copy->next;
	}

	follow = current = list;
	
	if (judge == 0) {			//기존의 ID로 테스트를 한 기록이 없을 경우 새로운 노드 삽입
		
		if ((newnode = (RANKING*)malloc(sizeof(RANKING))) == NULL) {
			printf("No memory allocated..\n");
			return NULL;
		}
		newnode->point1 = score1;
		newnode->point2 = score2;

		newnode->total = total_score;

		strcpy(newnode->id, userID);


		while ((current != NULL) && (current->total > newnode->total)) {
			follow = current;
			newnode->rank += 1;
			current = current->next;

		}

		newnode->next = current;
		if (current == list) {
			newnode->rank = 1;
			list = newnode;
		}
		else {
			newnode->rank = (follow->rank) + 1;
			follow->next = newnode;
		}

		while (current != NULL) {
			current->rank += 1;
			current = current->next;
		}

	}

	return list;
}

int word_test(int score) {
	FILE* fp;
	char word[40][11];
	char ip[20];
	int sequence[11];
	int i = 0, j;
	int random[11];
	int r_sequence[11];

	fp = fopen("Word.txt", "r");

	while (!feof(fp)) {
		fgets(word[i], 10, fp);
		word[i][strlen(word[i]) - 1] = '\0';		//읽어온 단어의 개행문자 삭제
		i++;
	}

	srand(time(NULL));

	for (i = 0; i < 11; i++) {		//40개의 단어 중에서 11개를 랜덤하게 선택하기 위한 랜덤 인덱스
		random[i] = rand() % 40;
		for (j = 0; j < i; j++) {
			if (random[i] == random[j]) {
				i--;
			}
		}
	}

	for (i = 0; i < 11; i++) {		//문제가 랜덤하게 나오기 위한 랜덤 인덱스
		sequence[i] = rand() % 11;
		for (j = 0; j < i; j++) {
			if (sequence[i] == sequence[j]) {
				i--;
			}
		}
	}
	

	for (i = 0; i < 11; i++) {		//보기가 랜덤하게 나오기 위한 랜덤 인덱스
		r_sequence[i] = rand() % 11;
		for (j = 0; j < i; j++) {
			if (r_sequence[i] == r_sequence[j]) {
				i--;
			}
		}
	}
	
	system("cls");

	for (int i = 5; i > 0; i--) {
		printf("%d초 후에 게임이 시작됩니다!", i);
		Sleep(1000);
		system("cls");
	}
	for (i = 0; i < 10; i++) {
		printf("\n\n\n\n\n\n\t\t\t\t%s", word[random[sequence[i]]]);		//sequence의 인덱스 10만 빼고 나머지 출력 
		Sleep(500);
		system("cls");
	}

	printf("현재 점수:%d\n", score);

	printf("======================================\n");
	printf("다음 중 나온적이 없었던 단어는?\n");
	printf("======================================\n\n");
	for (i = 0; i < 11; i++) {
		printf("%s\n", word[random[r_sequence[i]]]);
	}
	
	printf("hidden:%s\n", word[random[sequence[10]]]);
	printf("답:");
	scanf("%s", ip);
	
	printf("\n");
	if (strcmp(ip, word[random[sequence[10]]]) == 0) {
		printf("정답입니다!\n");
		score += 20;
	}
	else {
		printf("틀렸습니다!\n");
	}
	fclose(fp);
	system("pause");
	return score;

}

int coding_game() {
	FILE* fp;
	char code[100];
	int score = 0;
	int answer;
	int i;

	explain_coding();
	system("pause");
	system("cls");
	

	for (i = 5; i > 0; i--) {
		printf("%d초 후에 게임이 시작됩니다!", i);
		Sleep(1000);
		system("cls");
	}

	fp = fopen("Compare_example//Compare1.txt", "r");

	
	for (i = 5; i > 0; i--) {
		printf("int arr[5] = { 19, 34, 2, 66, 92 };\n\n");
		printf("%d초 후에 사라집니다!", i);
		Sleep(1000);
		system("cls");
	}
	printf("현재 점수:%d\n\n", score);

	show_example(fp);		//Compare1.txt의 파일 내용 출력

	printf("소스코드의 출력 결과를 입력하시오:");
	scanf("%d", &answer);

	if (answer == 92) {
		printf("정답입니다!\n");
		score += 20;
	}
	else {
		printf("틀렸습니다!\n");
	}

	fclose(fp);

	printf("다음문제로->");
	system("pause");
	system("cls");

	for (i = 5; i > 0; i--) {
		printf("%d초 후에 게임이 시작됩니다!", i);
		Sleep(1000);
		system("cls");
	}

	fp = fopen("Compare_example//Compare2.txt", "r");

	for (i = 5; i > 0; i--) {
		printf("int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };\n\n");
		printf("%d초 후에 사라집니다!", i);
		Sleep(1000);
		system("cls");
	}
	printf("현재 점수:%d\n", score);
	show_example(fp);		//Compare2.txt의 파일 내용 출력

	printf("소스코드의 출력 결과를 입력하시오:");
	scanf("%d", &answer);

	if (answer == 44) {
		printf("정답입니다!\n");
		score += 20;
	}
	else {
		printf("틀렸습니다!\n");
	}

	fclose(fp);

	printf("다음문제로->");
	system("pause");
	system("cls");

	for (i = 5; i > 0; i--) {
		printf("%d초 후에 게임이 시작됩니다!", i);
		Sleep(1000);
		system("cls");
	}

	fp = fopen("Compare_example//Compare3.txt", "r");

	for (i = 10; i > 0; i--) {
		show_example(fp);		//Compare3.txt의 파일 내용 출력
		printf("%d초 후에 사라집니다!", i);
		Sleep(1000);
		system("cls");
		fseek(fp, 0, SEEK_SET);		//fp의 파일지시자를 맨앞으로 이동
	}

	
	printf("현재 점수:%d\n", score);
	
	printf("소스코드의 출력 결과를 입력하시오:");
	scanf("%d", &answer);

	if (answer == 9) {
		printf("정답입니다!\n");
		score += 20;
	}
	else {
		printf("틀렸습니다!\n");
	}

	fclose(fp);

	return score;

}

void show_example(FILE * fp){
	char code[100];

	while (!feof(fp)) {
		fgets(code, 100, fp);
		printf("%s\n", code);
	}
}

void print_ranking() {
	FILE* fp=fopen("Ranking.txt", "r");
	RANKING* list = NULL;
	RANKING* newnode = NULL, * current = NULL;

	while (!feof(fp)) {
		newnode = (RANKING*)malloc(sizeof(RANKING));
		fscanf(fp, "%s %d %d %d %d", newnode->id, &newnode->point1, &newnode->point2, &newnode->total, &newnode->rank);

		newnode->next = NULL;
		//노드를 연결리스트 맨 뒤에 삽입
		if (list == NULL) {
			list = newnode;
		}
		else {
			current = list;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = newnode;
		}

	}


	printf("==============================================\n\n");
	printf("ID\t점수1\t점수2\t총점\t순위\n\n");
	printf("==============================================\n\n");

	while (list != NULL) {
		printf("%s\t%d\t%d\t%d\t%d\n", list->id, list->point1, list->point2, list->total, list->rank);
		list = list->next;
		if (list->next == NULL) {
			list = list->next;
		}
	}
	fclose(fp);

}

void explain_word() {
	printf("\n");
	printf("===============   단어 테스트  ==============\n\n");
	printf("     제시되는 단어를 맞추는 테스트 입니다.    \n\n");
	printf(" 게임이 시작되면 10개의 단어가 하나씩 나타납니다.\n\n");
	printf("          10개의 단어가 모두 나온 뒤 \n\n");
	printf("보기중에 나타난적이 없었던 단어를 고르면 성공입니다.\n\n\n");
	
}

void explain_coding() {
	printf("\n");
	printf("===============   코딩 테스트  ==============\n\n");
	printf("	   제시되는 소스코드를 보고          \n\n");
	printf("      출력되는 값을 맞추는 테스트 입니다.    \n\n\n");

}