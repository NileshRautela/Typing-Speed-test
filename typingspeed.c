#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX 500

struct Player
{
    char name[50];
    int wpm;
};

char paragraphs[3][200] =
{
    "The quick brown fox jumps over the lazy dog.",

    "Programming in C is simple and powerful.",

    "Typing speed improves with practice."
};

void startTest();
void showScoreboard();
void resetScoreboard();
void saveScore(char name[], int wpm);

int main()
{
    int choice;

    srand(time(NULL));

    while (1)
    {
        printf("\n========================");
        printf("\n TYPING SPEED TEST");
        printf("\n========================");

        printf("\n1. Start Test");
        printf("\n2. Scoreboard");
        printf("\n3. Reset Scoreboard");
        printf("\n4. Exit");

        printf("\n\nEnter choice: ");
        scanf("%d", &choice);

        getchar();

        switch (choice)
        {
            case 1:
                startTest();
                break;

            case 2:
                showScoreboard();
                break;

            case 3:
                resetScoreboard();
                break;

            case 4:
                return 0;

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}

void startTest()
{
    char typed[MAX];
    char name[50];

    int correct = 0;

    int index = rand() % 3;

    char *paragraph = paragraphs[index];

    printf("\n\nType this:\n");
    printf("\n%s\n", paragraph);

    printf("\nStart typing:\n");

    time_t start, end;

    time(&start);

    fgets(typed, sizeof(typed), stdin);

    time(&end);

    typed[strcspn(typed, "\n")] = '\0';

    int len1 = strlen(paragraph);
    int len2 = strlen(typed);

    int min;

    if (len1 < len2)
        min = len1;
    else
        min = len2;

    printf("\n\nTyped Text:\n");

    for (int i = 0; i < min; i++)
    {
        if (typed[i] == paragraph[i])
        {
            printf("%c", typed[i]);
            correct++;
        }
        else
        {
            /* Red color for wrong letters */
            printf("\033[31m%c\033[0m", typed[i]);
        }
    }

    double seconds = difftime(end, start);

    if (seconds == 0)
        seconds = 1;

    int words = len2 / 5;

    int wpm = (words * 60) / seconds;

    double accuracy =
        ((double)correct / len1) * 100;

    printf("\n\n========================");

    printf("\nRESULT");

    printf("\n========================");

    printf("\nSpeed    : %d WPM", wpm);

    printf("\nAccuracy : %.2f%%", accuracy);

    printf("\nEnter name: ");

    fgets(name, sizeof(name), stdin);

    name[strcspn(name, "\n")] = '\0';

    saveScore(name, wpm);

    printf("\nScore Saved!\n");
}

void saveScore(char name[], int wpm)
{
    FILE *fp;

    fp = fopen("scores.txt", "a");

    if (fp == NULL)
    {
        printf("\nFile error!\n");
        return;
    }

    fprintf(fp, "%s %d\n", name, wpm);

    fclose(fp);
}

void showScoreboard()
{
    FILE *fp;

    struct Player p[100], temp;

    int count = 0;

    fp = fopen("scores.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo scores found!\n");
        return;
    }

    while (fscanf(fp, "%s %d",
                  p[count].name,
                  &p[count].wpm) != EOF)
    {
        count++;
    }

    fclose(fp);

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (p[j].wpm > p[i].wpm)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    printf("\n\n====== SCOREBOARD ======\n");

    printf("\nRank\tName\t\tWPM\n");

    for (int i = 0; i < count; i++)
    {
        printf("%d\t%-15s%d\n",
               i + 1,
               p[i].name,
               p[i].wpm);
    }
}

void resetScoreboard()
{
    FILE *fp;

    fp = fopen("scores.txt", "w");

    if (fp == NULL)
    {
        printf("\nError resetting scoreboard!\n");
        return;
    }

    fclose(fp);

    printf("\nScoreboard Reset!\n");
}