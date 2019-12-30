//file update is not implemnted!
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USER_ID 100
#define MAX_NAME_LEN 100
#define MAX_GERNAME_LEN 40
#define MOVDAT "movies.dat"
#define TAGDAT "tags.dat"
#define HOWMANY 200
#define MAX_GENRE 18

#define MAX_TAGCONTENTS_LEN 100
#define HOWMANYTAG 200

struct _MOVIES {
	char num[20];
	char NAME[MAX_NAME_LEN];
	char GENRE[18][MAX_GERNAME_LEN];
	int GENRE_NUM;
};

typedef struct _MOVIES MOVIE;

MOVIE *movie[HOWMANY];

struct _TAGS {
	char userid[20];
	char movieid[20];
	char tagcontents[MAX_TAGCONTENTS_LEN];
	char timetable[100];
};
typedef struct _TAGS TAG;
TAG *tag[HOWMANYTAG];

void Run();

int SelectMenu();
int getnum();

void movieget(char *fp);
void tagget(char *fp);
void m_search();
void t_search();
void g_search();
void u_search();
void tag_attached();

int main() {
	Run();
}

void Run()
{
	int key = 0;
	while ((key = SelectMenu()) != 0)
	{
		switch (key)
		{
		case 1:m_search(); break;
		case 2:t_search(); break;
		case 3:g_search(); break;
		case 4:u_search(); break;
		case 5:tag_attached(); break;
		default: printf("No number.\n\n"); break;
		}
	}
}

int SelectMenu()
{
	printf("+------------------------+ \n");
	printf("|<MOVIE SEARCH PROGRAM!!>| \n");
	printf("+------------------------+ \n");
	printf("1: MOVIE SEARCH 2: TAG SEARCH 3: GENRE SEARCH 4: USER SEARCH 5: MOVIE SEARCH WITH TAG 6: FILE UPDATE\n0: EXIT \n\n");
	return getnum();
}

int getnum()
{
	int num = 0;
	if (scanf_s("%d", &num) == 0)
	{
		char buf[256];
		gets_s(buf, sizeof(buf));
	}
	return num;
}


void movieget(char *fp) {                              //process of storing movie data into structure

	char buff[HOWMANY][150] = { 0, };
	char *ptr;
	char *ptrgen;
	int a = 0;

	for (int i = 0; i < HOWMANY; i++)
	{
		int b = 0;
		int G_NUM = 0;
		movie[i] = (MOVIE *)malloc(sizeof(MOVIE));
		fgets(buff[i], sizeof(buff[i]), fp);

		ptr = buff[i];

		a = strlen(ptr);

		for (int k = 0; k < a - 1; k++)
		{
			if (buff[i][k] == 58 && buff[i][k + 1] == 58)
			{
				buff[i][k] = NULL;
				buff[i][k + 1] = NULL;

				strcpy(movie[i]->num, ptr);
				b = strlen(ptr);
				break;
			}

		}

		for (int k = b + 2; k < a - 1; k++)
		{
			ptr = buff[i] + b + 2;
			if (buff[i][k] == ':' && buff[i][k + 1] == ':')
			{
				buff[i][k] = NULL;
				buff[i][k + 1] = NULL;

				strcpy(movie[i]->NAME, ptr);
				b = b + strlen(ptr);
				break;
			}

		}

		ptr = buff[i] + b + 4;

		ptrgen = strtok(ptr, "|");

		for (int s = 0; s < 18; s++) {
			if (ptrgen != NULL)
			{
				strcpy(movie[i]->GENRE[s], ptrgen);
				ptrgen = strtok(NULL, "|");
				G_NUM++;
			}
		}
		movie[i]->GENRE_NUM = G_NUM;
	}
}

void tagget(char *fp) {                                         //process of stroing tag data into structure
	char buff[HOWMANYTAG][200] = { 0, };
	char *ptr;
	for (int i = 0; i < HOWMANYTAG; i++)
	{
		tag[i] = (TAG *)malloc(sizeof(TAG));
		fgets(buff[i], sizeof(buff[i]), fp);
		ptr = strtok(buff[i], "::");
		if (ptr != NULL)
		{
			strcpy(tag[i]->userid, ptr);
			ptr = strtok(NULL, "::");
		}
		if (ptr != NULL)
		{
			strcpy(tag[i]->movieid, ptr);
			ptr = strtok(NULL, "::");
		}
		if (ptr != NULL)
		{
			strcpy(tag[i]->tagcontents, ptr);
			ptr = strtok(NULL, "::");
		}
		if (ptr != NULL)
		{
			strcpy(tag[i]->timetable, ptr);
			ptr = strtok(NULL, "::");
		}
	}
}


//영화 찾는 함수
void m_search() {

	char movie_name[MAX_NAME_LEN];
	printf("Write name of the movie you want to search : ");
	getchar();
	gets(movie_name);


	FILE *fp = fopen(MOVDAT, "r");

	while (feof(fp) == 0) {

		movieget(fp);
		for (int i = 0; i < HOWMANY; i++) {
			if (strncmp(movie_name, movie[i]->NAME, strlen(movie_name)) == 0)
			{
				if (movie[i]->num == NULL) {
					break;
				}
				printf("Movie Number: %s\n", movie[i]->num);
				printf("Movie Name: %s\n", movie[i]->NAME);

				for (int g = 0; g < movie[i]->GENRE_NUM; g++) {
					printf("Movie Genre: %s\n", movie[i]->GENRE[g]);
				}
			}
		}
		for (int i = 0; i < HOWMANY; i++) {
			free(movie[i]);
		}
	}
	fclose(fp);
}

void t_search() {

	char tag_name[MAX_NAME_LEN];
	printf("Write name of the tag you want to search : ");
	getchar();
	gets(tag_name);
	FILE *fp1 = fopen(TAGDAT, "r"); // open tag data to get movie num

	int checknum = 0;
	char tagnum[500][20] = { NULL, };
	char tagcon[500][MAX_TAGCONTENTS_LEN];
	char tagid[500][MAX_USER_ID];

	while (feof(fp1) == 0) {
		tagget(fp1);
		for (int i = 0; i < HOWMANYTAG; i++) {
			if (strncmp(tag_name, tag[i]->tagcontents, strlen(tag_name)) == 0)
			{
				strcpy(tagnum[checknum], tag[i]->movieid);
				strcpy(tagcon[checknum], tag[i]->tagcontents);
				strcpy(tagid[checknum], tag[i]->userid);
				checknum++;
			}
		}
		for (int i = 0; i < HOWMANYTAG; i++) {
			free(tag[i]);
		}
	}
	fclose(fp1); // get movie num and save it to tagnum

	FILE *fp2 = fopen(MOVDAT, "r");
	while (feof(fp2) == 0) {
		movieget(fp2);
		for (int i = 0; i < HOWMANY; i++) {
			for (int j = 0; j < 500; j++) {
				if (strcmp(tagnum[j], movie[i]->num) == 0)
				{
					printf("Movie Tag : %s\n", tagcon[j]);
					printf("User ID: %s \n", tagid[j]);
					printf("Movie Number: %s\n", movie[i]->num);
					printf("Movie Name: %s\n", movie[i]->NAME);
					for (int g = 0; g < movie[i]->GENRE_NUM; g++) {
						printf("Movie Genre: %s\n", movie[i]->GENRE[g]);
					}
				}
			}
		}
		for (int i = 0; i < HOWMANY; i++) {
			free(movie[i]);
		}
	}
	//Compare number and show data
	fclose(fp2);
}

void g_search() {
	char G_NAME[MAX_GENRE][MAX_GERNAME_LEN];
	int G_NUM[MAX_GENRE] = { 0, };
	int S_NUM = 0;
	printf("Number of Genre You want to search : ");
	scanf("%d", &S_NUM);
	printf("Choose Genre you want to Search\n");
	printf("1. Action\n2. Adventure\n3. Animation\n4. Children's\n5. Comedy\n6. Crime\n7. Documentary\n8. Drama\n9. Fantasy\n");
	printf("10. Film-Noir\n11. Horror\n12. Musical\n13. Mystery\n14. Romance\n15. Sci-Fi\n16. Thriller\n17. War\n18. Western\n");
	for (int l = 0; l < S_NUM; l++) {
		printf("Num : ");
		scanf("%d", &G_NUM[l]);
		switch (G_NUM[l]) {
		case 1: strcpy(G_NAME[l], "Action"); break; case 2: strcpy(G_NAME[l], "Adventure"); break; case 3: strcpy(G_NAME[l], "Animation"); break;
		case 4: strcpy(G_NAME[l], "Children"); break; case 5: strcpy(G_NAME[l], "Comedy"); break; case 6: strcpy(G_NAME[l], "Crime"); break;
		case 7: strcpy(G_NAME[l], "Documentary"); break; case 8: strcpy(G_NAME[l], "Drama"); break; case 9: strcpy(G_NAME[l], "Fantasy"); break;
		case 10: strcpy(G_NAME[l], "Film - Noir"); break; case 11: strcpy(G_NAME[l], "Horror"); break; case 12: strcpy(G_NAME[l], "Musical"); break;
		case 13: strcpy(G_NAME[l], "Mystery"); break; case 14: strcpy(G_NAME[l], "Romance"); break; case 15: strcpy(G_NAME[l], "Sci-Fi"); break;
		case 16: strcpy(G_NAME[l], "Thriller"); break; case 17: strcpy(G_NAME[l], "War"); break; case 18: strcpy(G_NAME[l], "Western"); break;
		default: printf("That number is out of range\n"); break;
		}
	}
	FILE *fp = fopen(MOVDAT, "r");
	while (feof(fp) == 0) {
		movieget(fp);
		for (int i = 0; i < HOWMANY; i++) {
			int c_num = 0;
			for (int j = 0; j < movie[i]->GENRE_NUM; j++) {
				for (int k = 0; k < S_NUM; k++) {
					if (strncmp(G_NAME[k], movie[i]->GENRE[j], strlen(G_NAME[k])) == 0)
					{
						c_num++;
					}
					
				}
				
				}
			if (c_num == S_NUM) {
				printf("Movie Number: %s\n", movie[i]->num);
				printf("Movie Name: %s\n", movie[i]->NAME);
				for (int g = 0; g < movie[i]->GENRE_NUM; g++) {
					printf("Movie Genre: %s\n", movie[i]->GENRE[g]);
				}
			}
		}
		for (int m = 0; m < HOWMANY; m++) {
			free(movie[m]);
		}
	}
	fclose(fp);
}

void u_search() {
	char user_id[MAX_USER_ID];

	printf("Write User Id you want to search : ");
	getchar();
	gets(user_id);

	int cnum = 0;

	int checknum = 0;
	char tagcon[1500][MAX_TAGCONTENTS_LEN];
	char tagnum[1500][MAX_USER_ID];

	FILE *fp1 = fopen(TAGDAT, "r"); // open tag data to get movie num

	while (feof(fp1) == 0) {
		tagget(fp1);
		for (int i = 0; i < HOWMANYTAG; i++) {
			if (strcmp(user_id, tag[i]->userid) == 0)
			{
				strcpy(tagnum[checknum], tag[i]->movieid);
				strcpy(tagcon[checknum], tag[i]->tagcontents);
				checknum++;
			}
		}
		for (int i = 0; i < HOWMANYTAG; i++) {
			free(tag[i]);
		}
	}
	fclose(fp1);

	printf("Tags of USER ID: %s\n", user_id);

	FILE *fp2 = fopen(MOVDAT, "r");
	while (feof(fp2) == 0) {
		movieget(fp2);
		for (int i = 0; i < HOWMANY; i++) {
			for (int j = 0; j < 1500; j++) {
				if (strcmp(tagnum[j], movie[i]->num) == 0)
				{
					printf("Movie Tag : %s\n", tagcon[j]);
					printf("Movie Number: %s\n", movie[i]->num);
					printf("Movie Name: %s\n", movie[i]->NAME);
					for (int g = 0; g < movie[i]->GENRE_NUM; g++) {
						printf("Movie Genre: %s\n", movie[i]->GENRE[g]);
					}
					cnum++;
				}
			}
		}
		for (int i = 0; i < HOWMANY; i++) {
			free(movie[i]);
		}
	}
	if (cnum == 0) {
		printf("No Tags Here! \n");
	}
	fclose(fp2);
}

void tag_attached() { // NEW
	char movie_name[MAX_NAME_LEN];
	printf("Write Movie You want to Search : ");
	getchar();
	gets(movie_name);

	FILE *fp1 = fopen(MOVDAT, "r");

	while (feof(fp1) == 0) {
		movieget(fp1);
		for (int i = 0; i < HOWMANY; i++) {
			if (strncmp(movie_name, movie[i]->NAME, strlen(movie_name)) == 0)
			{
				printf("Movie Number: %s\n", movie[i]->num);
				printf("Movie Name: %s\n", movie[i]->NAME);
				int tag_count = 0;
				FILE *fp2 = fopen(TAGDAT, "r");
				while (feof(fp2) == 0) {
					tagget(fp2);
					for (int j = 0; j < HOWMANYTAG; j++) {
						if (strncmp(movie[i]->num, tag[j]->movieid, strlen(movie[i]->num)) == 0)
						{
							printf("%s\n", tag[j]->tagcontents);
							tag_count++;
						}
					}

					for (int k = 0; k < HOWMANYTAG; k++) {
						free(tag[k]);
					}

				}
				printf("Number of %s's Tag : %d\n", movie[i]->NAME, tag_count);
				printf("\n");
				fclose(fp2);
				system("pause");
			}
		}
		for (int i = 0; i < HOWMANY; i++) {
			free(movie[i]);
		}
	}
	fclose(fp1);

}
