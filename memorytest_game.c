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
	int total;
	int rank;
	struct ranking* next;
}RANKING;

void Head();
void signup();
int signin();
void withdraw();
int word_test(int score);
void rank_manage(int point);
RANKING* sorted_insert(int point, RANKING* list);

char userID[15];

void main() {
	int intro;
	int end = 1;
	int score = 0;


	while (end) {
		Head();
		printf("1. 로그인\n");
		printf("2. 회원가입\n");
		printf("3. 회원탈퇴\n");
		printf("4. 게임 종료\n");

		printf("Enter the nubmer:");
		scanf("%d", &intro);


		system("cls");
		switch (intro) {

		case 1:
			if (signin()==1) {
				system("cls");
				printf("==============================================\n\n");
				printf("\t\tWord test!\n\n");
				printf("==============================================\n\n");

				for (int i = 0; i < 4; i++) {
					score = word_test(score);

				}

				rank_manage(score);
			}
			
			break;

		case 2:
			signup();
			
			break;

		case 3:
			withdraw();

			break;
		

		case 4:
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
	fp = fopen("Account.txt", "a");
	
	printf("==============================================\n\n");
	printf("\t\t회원가입\n\n");
	printf("==============================================\n\n");
	printf("      ID:");
	scanf("%s", user.id);
	printf("PASSWORD:");
	scanf("%s", user.password);
	fprintf(fp, "%s %s\n",user.id,  user.password);
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

	strcpy(userID, user.id);

	fp = fopen("Account.txt", "r");


	while (!feof(fp)) {
		fscanf(fp, "%s %s", list.id, list.password);

		if (strcmp(user.id, list.id) == 0 && strcmp(user.password, list.password) == 0) {
			judge = 1;
		}

	}

	if (judge == 1) {
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

	while (!feof(fp)) {
		newnode = (ACCOUNT*)malloc(sizeof(ACCOUNT));
		fscanf(fp, "%s %s", newnode->id, newnode->password);
		newnode->next = list;
		list = newnode;
	}
	list = list->next;

	current = follow = list;

	while ((current != NULL)&& (strcmp(user.id, current->id) != 0 || strcmp(user.password, current->password) != 0)) {
		follow = current;
		current = current->next;
	}

	if (current == NULL) {
		printf("삭제하고자하는 정보가 없습니다\n");
		return 0;
	}
	if (list == current) {
		list = current->next;
	}
	
	else if (current->next == NULL) {
		follow->next = NULL;
	}
	else {
		follow->next = current->next;
	}

	free(current);
	fclose(fp);

	fp = fopen("Account.txt", "w");
	
	while (list != NULL) {
		fprintf(fp, "%s %s\n", list->id, list->password);
		list = list->next;
	}
	printf("%s님의 탈퇴가 완료되었습니다\n", user.id);
	fclose(fp);

}

void rank_manage(int point) {
	FILE* fp=fopen("Ranking.txt", "r");
	RANKING * list=NULL;
	RANKING* newnode=NULL, *current=NULL;

	while (!feof(fp)) {
		newnode = (RANKING*)malloc(sizeof(RANKING));
		fscanf(fp, "%s %d %d", newnode->id, &newnode->total, &newnode->rank);
		//printf("%s %d %d\n", newnode->id, newnode->total, newnode->rank);
		newnode->next = NULL;
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
	printf("\n");
	
	list = sorted_insert(point, list);

	fclose(fp);

	fp = fopen("Ranking.txt", "w");

	while (list != NULL) {
		fprintf(fp, "%s %d %d\n", list->id, list->total, list->rank);
		list = list->next;
		if (list->next == NULL) {
			list = list->next;
		}
	}
	list = current;
	fclose(fp);

}

RANKING* sorted_insert(int point, RANKING* list) {
	RANKING* current = NULL, * follow = NULL, * newnode = NULL;
	current = follow = list;
	
	
	if ((newnode = (RANKING*)malloc(sizeof(RANKING))) == NULL) {
		printf("No memory allocated..\n");
		return NULL;
	}
	newnode->total = point;
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
		newnode->rank = (follow->rank)+1;
		follow->next = newnode;
	}

	while (current != NULL) {
		current->rank += 1;
		current = current->next;
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
	int point = 0;


	fp = fopen("Word.txt", "r");

	while (!feof(fp)) {
		fgets(word[i], 10, fp);
		word[i][strlen(word[i]) - 1] = '\0';
		i++;
	}

	srand(time(NULL));

	for (i = 0; i < 11; i++) {
		random[i] = rand() % 40;
		for (j = 0; j < i; j++) {
			if (random[i] == random[j]) {
				i--;
			}
		}
	}

	for (i = 0; i < 11; i++) {
		sequence[i] = rand() % 11;
		for (j = 0; j < i; j++) {
			if (sequence[i] == sequence[j]) {
				i--;
			}
		}
	}


	system("pause");
	system("cls");
	
	

	for (int i = 5; i > 0; i--) {
		printf("%d초 후에 게임이 시작됩니다!", i);
		Sleep(100);
		system("cls");
	}
	for (i = 0; i < 10; i++) {
		printf("\n\n\n\n\n\n\t\t\t\t%s", word[random[i]]);
		Sleep(50);
		system("cls");
	}
	printf("점수:%d\n", score);

	printf("======================================\n");
	printf("다음 중 나온적이 없었던 단어는?\n");
	printf("======================================\n\n");
	for (i = 0; i < 11; i++) {
		printf("%s\n", word[random[sequence[i]]]);
	}
	
	printf("hidden:%s\n", word[random[sequence[10]]]);
	printf("답:");
	scanf("%s", ip);
	
	printf("\n");
	if (strcmp(ip, word[random[sequence[10]]]) == 0) {
		printf("정답입니다!");
		score += 25;
	}
	else {
		printf("틀렸습니다");
	}
	fclose(fp);
	return score;

}








/* 소스코드를 파일에 입력하고 파일로 부터 출력하는 코드
#include <stdio.h>
#include <string.h>

int main() {
	FILE* fp;
	char code[100];
	fp = fopen("memory.txt", "w");



	while (1) {
		gets(code);
		if (strcmp(code, "0")==0) {
			break;
		}
		fprintf(fp, "%s\n", code);
	}


	fclose(fp);

	fp = fopen("memory.txt", "r");

	while (!feof(fp)) {
		fgets(code, 100, fp);
		printf("%s\n", code);
	}
}*/