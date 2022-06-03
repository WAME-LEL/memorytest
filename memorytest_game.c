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
}RANKING;

void Head();
void signup();
void signin();
void withdraw();
int word_test(int score);


void main() {
	int intro;
	int end = 1;
	int score = 0;


	while (end) {
		Head();
		printf("1. �α���\n");
		printf("2. ȸ������\n");
		printf("3. ȸ��Ż��\n");
		printf("4. ���� ����\n");
		printf("5. ���� ����\n");

		printf("Enter the nubmer:");
		scanf("%d", &intro);


		system("cls");
		switch (intro) {

		case 1:
			signin();
			break;

		case 2:
			signup();
			
			break;

		case 3:
			withdraw();

			break;
		

		case 4:
			printf("==============================================\n\n");
			printf("\t\tWord test!\n\n");
			printf("==============================================\n\n");
	
			for (int i = 0; i < 4; i++) {
				score = word_test(score);

			}

			
			break;

		case 5:
			end = 0;
			printf("������ ����Ǿ����ϴ�\n");
			return 0;

		default:
			printf("�߸��� �Է��Դϴ�\n");
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
	printf("\t\tȸ������\n\n");
	printf("==============================================\n\n");
	printf("      ID:");
	scanf("%s", user.id);
	printf("PASSWORD:");
	scanf("%s", user.password);
	fprintf(fp, "%s %s\n",user.id,  user.password);
	printf("ȸ������ ����!\n");
	fclose(fp);
}

void signin() {
	FILE* fp;
	int judge = 0;
	ACCOUNT list;
	ACCOUNT user;

	printf("==============================================\n\n");
	printf("\t\t�α���\n\n");
	printf("==============================================\n\n");
	printf("      ID:");
	scanf("%s", user.id);
	printf("PASSWORD:");
	scanf("%s", user.password);
	fp = fopen("Account.txt", "r");


	while (!feof(fp)) {
		fscanf(fp, "%s %s", list.id, list.password);

		if (strcmp(user.id, list.id) == 0 && strcmp(user.password, list.password) == 0) {
			judge = 1;
		}

	}

	if (judge == 1) {
		printf("�α��� ����! ȯ���մϴ� %s ��!\n", user.id);
	}
	else {
		printf("���� �����Դϴ�!\n");
	}
	fclose(fp);
}

void withdraw() {
	FILE* fp = fopen("Account.txt", "r");
	ACCOUNT* list=NULL;
	ACCOUNT* newnode = NULL;
	ACCOUNT* current = NULL, * follow = NULL;
	ACCOUNT user;
	char* garbage=NULL;
	
	printf("==============================================\n\n");
	printf("\t\tȸ��Ż��\n\n");
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
		printf("�����ϰ����ϴ� ������ �����ϴ�\n");
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
	printf("%s���� Ż�� �Ϸ�Ǿ����ϴ�\n", user.id);
	fclose(fp);

}

void rank_manage() {
	FILE* fp=fopen("Ranking.txt", "r");
	RANKING rk;







}

int word_test(int score) {
	FILE* fp;
	char word[40][11];
	char ip[20];
	int sequence[11];
	int i=0, j,k;
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
		printf("%d�� �Ŀ� ������ ���۵˴ϴ�!", i);
		Sleep(100);
		system("cls");
	}
	for (i = 0; i < 10; i++) {
		printf("\n\n\n\n\n\n\t\t\t\t%s", word[random[i]]);
		Sleep(50);
		system("cls");
	}
	printf("����:%d\n", score);

	printf("======================================\n");
	printf("���� �� �������� ������ �ܾ��?\n");
	printf("======================================\n\n");
	for (i = 0; i < 11; i++) {
		printf("%s\n", word[random[sequence[i]]]);
	}
	
	printf("hidden:%s\n", word[random[sequence[10]]]);
	printf("��:");
	scanf("%s", ip);
	
	printf("\n");
	if (strcmp(ip, word[random[sequence[10]]]) == 0) {
		printf("�����Դϴ�!");
		score += 25;
	}
	else {
		printf("Ʋ�Ƚ��ϴ�");
	}

	return score;

}








/* �ҽ��ڵ带 ���Ͽ� �Է��ϰ� ���Ϸ� ���� ����ϴ� �ڵ�
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