/*生成随机矩阵源程序*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 200000
typedef int count;
count i, j;

int main()
{
    FILE *fp;
    fp = fopen("putout.txt", "w");
    if (fp == NULL)
    {
        printf("FILE CANNOT OPEN!");
        exit(0);
    }
    int n;
    int matrix[N];
    scanf("%d", &n);
    srand((unsigned)time(NULL));
    for (i = 0; i < n * n; i++)
    {
        matrix[i] = (int)(rand() % 10);
    }
    for (i = 0; i < n * n; i++)
    {
        fprintf(fp, "%d ", matrix[i]);
        if((i+1)%n==0)
        {
            fprintf(fp,"\n");
        }
    }
    fclose(fp);
    return 0;
}
