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
	int point1;
	int point2;
	int total;
	int rank;
	struct ranking* next;
}RANKING;

void Head();
void signup();
int signin();
void withdraw();
int word_test(int score);
void rank_manage(int score1, int score2, int total_score, int judge);
RANKING* sorted_insert(int score1, int score2, int total_score, RANKING* list);
void print_ranking();
int compare_game();
void show_example(FILE* fp);

char userID[15];

void main() {
	int intro;
	int end = 1;
	int score1;
	int score2;
	int judge;


	while (end) {
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
		printf("7\n");


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

				for (int i = 0; i < 2; i++) {
					score1 = word_test(score1);

				}
				system("cls");

				score2 = compare_game();

				system("cls");
				rank_manage(score1, score2, score1 + score2, judge);

				print_ranking();
				printf("==============================================\n\n");
				printf("%s님의 점수가 등록 되었습니다!\n\n", userID);
				printf("@@이전에 받았던 점수보다 높은 점수를 받았을 경우 점수가 갱신됩니다!\n");
				printf("@@이전에 받았던 점수보다 낮은 점수를 받았을 경우 점수가 등록되지않습니다!\n");
			}
			
			break;

		case 2:
			judge = 1;
			system("cls");

			printf("==============================================\n\n");
			printf("\t\tWord test!\n\n");
			printf("==============================================\n\n");

			for (int i = 0; i < 2; i++) {
				score1 = word_test(score1);

			}
			system("cls");

			score2=compare_game();

			system("cls");
			rank_manage(score1, score2, score1+score2, judge);

			print_ranking();
			printf("==============================================\n\n");
			printf("%s님의 점수가 등록 되었습니다!\n\n", userID);
			printf("@@이전에 받았던 점수보다 높은 점수를 받았을 경우 점수가 갱신됩니다!\n");
			printf("@@이전에 받았던 점수보다 낮은 점수를 받았을 경우 점수가 등록되지않습니다!\n");
			break;



		case 3:
			print_ranking();
			break;


		case 4:
			signup();
			
			break;

		case 5:
			withdraw();

			break;
		

		case 6:
			end = 0;
			printf("게임이 종료되었습니다\n");
			return 0;

		case 7:
			compare_game();

			break;


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
		return ;
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

void rank_manage(int score1, int score2, int total_score, int judge) {
	FILE* fp=fopen("Ranking.txt", "r");
	RANKING * list=NULL;
	RANKING* newnode=NULL, *current=NULL;

	while (!feof(fp)) {
		newnode = (RANKING*)malloc(sizeof(RANKING));
		fscanf(fp, "%s %d %d %d %d", newnode->id, &newnode->point1, &newnode->point2, &newnode->total, &newnode->rank);
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
	
	if (judge == 1) {
		system("cls");
		printf("사용할 닉네임을 입력하시오:");
		scanf("%s", userID);
	}

	list = sorted_insert(score1, score2, total_score, list);

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
		if (strcmp(userID, copy->id) == 0) {
			if (total_score > copy->total) {
				copy->point1 = score1;
				copy->point2 = score2;
				copy->total = total_score;
				judge = 1;

			}
			else {
				copy = copy->next;
				judge = 2;
			}


		}
		copy = copy->next;
	}

	follow = current = list;
	
	if (judge == 0) {
		
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
		Sleep(1000);
		system("cls");
	}
	for (i = 0; i < 10; i++) {
		printf("\n\n\n\n\n\n\t\t\t\t%s", word[random[i]]);
		Sleep(500);
		system("cls");
	}
	printf("현재 점수:%d\n", score);

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
		printf("정답입니다!\n");
		score += 20;
	}
	else {
		printf("틀렸습니다!\n");
	}
	fclose(fp);
	return score;

}

int compare_game() {
	FILE* fp;
	char code[100];
	int score = 0;
	int answer;

	for (int i = 5; i > 0; i--) {
		printf("%d초 후에 게임이 시작됩니다!", i);
		Sleep(1000);
		system("cls");
	}

	fp = fopen("Compare_example//Compare1.txt", "r");

	
	for (int i = 5; i > 0; i--) {
		printf("int arr[5] = { 19, 34, 2, 66, 92 };\n\n");
		printf("%d초 후에 사라집니다!", i);
		Sleep(1000);
		system("cls");
	}
	printf("현재 점수:%d\n\n", score);

	show_example(fp);

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

	for (int i = 5; i > 0; i--) {
		printf("%d초 후에 게임이 시작됩니다!", i);
		Sleep(100);
		system("cls");
	}

	fp = fopen("Compare_example//Compare2.txt", "r");

	for (int i = 5; i > 0; i--) {
		printf("int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };\n\n");
		printf("%d초 후에 사라집니다!", i);
		Sleep(1000);
		system("cls");
	}
	printf("현재 점수:%d\n", score);
	show_example(fp);

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

	for (int i = 5; i > 0; i--) {
		printf("%d초 후에 게임이 시작됩니다!", i);
		Sleep(100);
		system("cls");
	}

	fp = fopen("Compare_example//Compare3.txt", "r");

	for (int i = 10; i > 0; i--) {
		show_example(fp);
		printf("%d초 후에 사라집니다!", i);
		Sleep(1000);
		system("cls");
		fseek(fp, 0, SEEK_SET);
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