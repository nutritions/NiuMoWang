/*传统矩阵相乘源程序*/
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <time.h>
clock_t start, end; //计时
#define buildmatrix(a,n,m)\
   int **a=(int**)malloc(sizeof(int *)*n);\
    for(int t=0;t<n;t++)\
    {\
	    a[t]=(int *)malloc(sizeof(int)*m);\
	    memset(a[t],0.0,sizeof(a[t]));\
    }

#define N 32         //确定阶数，编译前修改
typedef int count;  //计数器
count i, j, k;

//定义输入函数
void input(int n,int **p)
{
    
	FILE *fp;
    fp=fopen("putout.txt","r");
    if(fp==NULL)
    {
        printf("FILE CANNOT OPEN!");
        exit(0);
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
        	fscanf(fp,"%d",&p[i][j]);
        }
    }
    fclose(fp);
}

//定义输出函数
void output(int n,int **p)
{
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%4d ", p[i][j]);
        }
        printf("\n");
    }
}

//定义矩阵相乘函数
void matrix_multiply(int n,int **X,int **Y,int **Z)
{
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            Z[i][j] = 0;
            for (k = 0; k < n; k++)
            {
                Z[i][j] = Z[i][j] + X[i][k] * Y[k][j];
            }
        }
    }
}

int main()
{
    buildmatrix(A,N,N);
    buildmatrix(B,N,N);
    buildmatrix(C,N,N);
    input(N, A);
    printf("\n");
    input(N, B);
    start = clock();
    matrix_multiply(N, A, B, C);
    end = clock();
    output(N, C);
    printf("time=%lf\n", (double)(end - start) / CLK_TCK);
    return 0;
}