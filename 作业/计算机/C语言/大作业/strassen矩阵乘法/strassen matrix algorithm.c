/*strassen矩阵相乘算法源程序*/
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <time.h>
clock_t start, end; //计时器
//定义宏，来实现对多个二维数组动态空间的开辟，同时命名
#define buildmatrix(a,n,m)\
    int **a=(int**)malloc(sizeof(int *)*n);\
    for(int t=0;t<n;t++)\
    {\
	    a[t]=(int *)malloc(sizeof(int)*m);\
	    memset(a[t],0.0,sizeof(a[t]));\
    }
#define N 32    //确定矩阵规模，编译前修改 
#define limN 32       //确定采用传统算法的最大阶数，编译前修改
typedef int count;  //计数器
count i, j, k;
 
//定义输入函数
void input(int n, int **p)
{
    //从文件中调用矩阵
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
void output(int n, int **p)
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

//定义矩阵相加函数
void matrix_add(int n, int **X, int **Y, int **Z)
{
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            Z[i][j] = X[i][j] + Y[i][j];
        }
    }
}

//定义矩阵相减函数
void matrix_sub(int n, int **X, int **Y, int **Z)
{
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            Z[i][j] = X[i][j] - Y[i][j];
        }
    }
}

//定义传统矩阵相乘函数
void matrix_multiply(int **A, int **B, int **C)
{
    for (i = 0; i < limN ; i++)
    {
        for (j = 0; j < limN ; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < limN; k++)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

//定义strassen算法函数
void strassen(int n, int **A, int **B, int **C)
{
    //在矩阵规模小于一定阶数的时候，采用传统的矩阵乘法
    if (n <= limN)
    {
        matrix_multiply(A, B, C);
        return;
    }
    
    //二维数组的命名以及动态空间的开辟
    buildmatrix(A11,n/2,n/2);
    buildmatrix(A12,n/2,n/2);
    buildmatrix(A21,n/2,n/2);
    buildmatrix(A22,n/2,n/2);
    buildmatrix(B11,n/2,n/2);
    buildmatrix(B12,n/2,n/2);
    buildmatrix(B21,n/2,n/2);
    buildmatrix(B22,n/2,n/2);
    buildmatrix(C11,n/2,n/2);
    buildmatrix(C12,n/2,n/2);
    buildmatrix(C21,n/2,n/2);
    buildmatrix(C22,n/2,n/2);
    buildmatrix(M1,n/2,n/2);
    buildmatrix(M2,n/2,n/2);
    buildmatrix(M3,n/2,n/2);
    buildmatrix(M4,n/2,n/2);
    buildmatrix(M5,n/2,n/2);
    buildmatrix(M6,n/2,n/2);
    buildmatrix(M7,n/2,n/2);
    buildmatrix(AA,n/2,n/2);
    buildmatrix(BB,n/2,n/2);
    buildmatrix(MM1,n/2,n/2);
    buildmatrix(MM2,n/2,n/2);
    
    //分治策略
    for (i = 0; i < n / 2; i++)
    {
        for (j = 0; j < n / 2; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n / 2];
            A21[i][j] = A[i + n / 2][j];
            A22[i][j] = A[i + n / 2][j + n / 2];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + n / 2];
            B21[i][j] = B[i + n / 2][j];
            B22[i][j] = B[i + n / 2][j + n / 2];
        }
    }

    //递归
    matrix_sub(n / 2, B12, B22, BB);
    strassen(n / 2, A11, BB, M1);

    matrix_add(n / 2, A11, A12, AA);
    strassen(n / 2, AA, B22, M2);

    matrix_add(n / 2, A21, A22, AA);
    strassen(n / 2, AA, B11, M3);

    matrix_sub(n / 2, B21, B11, BB);
    strassen(n / 2, A22, BB, M4);

    matrix_add(n / 2, A11, A22, AA);
    matrix_add(n / 2, B11, B22, BB);
    strassen(n / 2, AA, BB, M5);

    matrix_sub(n / 2, A12, A22, AA);
    matrix_add(n / 2, B21, B22, BB);
    strassen(n / 2, AA, BB, M6);

    matrix_sub(n / 2, A11, A21, AA);
    matrix_add(n / 2, B11, B12, BB);
    strassen(n / 2, AA, BB, M7);

    matrix_add(n / 2, M5, M4, MM1);
    matrix_sub(n / 2, M2, M6, MM2);
    matrix_sub(n / 2, MM1, MM2, C11);

    matrix_add(n / 2, M1, M2, C12);
    matrix_add(n / 2, M3, M4, C21);

    matrix_add(n / 2, M5, M1, MM1);
    matrix_add(n / 2, M3, M7, MM2);
    matrix_sub(n / 2, MM1, MM2, C22);
    

    for (i = 0; i < n / 2; i++)
    {
        for (j = 0; j < n / 2; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + n / 2] = C12[i][j];
            C[i + n / 2][j] = C21[i][j];
            C[i + n / 2][j + n / 2] = C22[i][j];
        }
    }
    
    //释放malloc的空间
   for(i = 0; i < n/2; i++) 
   {
    	free(A11[i]);	
		free(B11[i]);	free(C11[i]);   free(M1[i]);    free(M5[i]);
		free(A12[i]);	free(B12[i]);	free(C12[i]);   free(M2[i]);    free(M6[i]);
		free(A21[i]);	free(B21[i]);	free(C21[i]);   free(M3[i]);    free(M7[i]);
		free(A22[i]);	free(B22[i]);	free(C22[i]);	free(M4[i]);
        free(AA[i]);    free(BB[i]);    free(MM1[i]);   free(MM2[i]);    
	}
        free(A11);	free(B11);	free(C11);   free(M1);    free(M5);
		free(A12);	free(B12);	free(C12);   free(M2);    free(M6);
		free(A21);	free(B21);	free(C21);   free(M3);    free(M7);
		free(A22);	free(B22);	free(C22);	 free(M4);
        free(AA);   free(BB);   free(MM1);   free(MM2); 
}

int main()
{
    buildmatrix(A,N,N);
    buildmatrix(B,N,N);
    buildmatrix(C,N,N);
    input(N, A);
	input(N, B);
    start = clock();
    strassen(N, A, B, C);
    end = clock();
    output(N, C);
    printf("time=%lf\n", (double)(end - start) / CLK_TCK);
    return 0;
}