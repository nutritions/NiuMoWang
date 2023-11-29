#include <stdio.h>
#include <stdlib.h>

const int MOD = 1e9 + 7;
int flag[5001];
int flag1[5001];
int main()
{
    int N, M;
    scanf("%d%d", &N, &M);

    int **dp;
    dp = (int **)malloc(sizeof(int *) * (N + 1));
    for (int i = 0; i <= N; ++i)
    {
        dp[i] = (int *)malloc(sizeof(int) * (N + 1));
        for (int j = 0; j <= N; ++j)
        {
            dp[i][j] = 0;
        }
    }
    for (int i = 0; i < M; ++i)
    {
        int c, g;
        scanf("%d%d", &c, &g);
        dp[c][g] = 1;
    }

    for (int k = 1; k <= N; ++k)
    {
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                if (dp[i][k] && dp[k][j])
                {
                    dp[i][j] = (dp[i][j] + dp[i][k] * dp[k][j]) % MOD;
                }
            }
        }
    }

    int result = 0;
    
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N;i++){
            if (dp[k][i] >= 1)
                flag[k] = 1; 
            if(dp[i][k] >= 1)
                flag1[k] = 1;
        }
            
    }
    
    for (int i = 1; i <= N; ++i)
    {
        for (int j = i + 1; j <= N; ++j)
        {
            
            if (flag[j] == 0 && flag1[i] == 0)
                result = (result + dp[i][j]) % MOD;

        }
    }

    printf("%d\n", result);

    return 0;
}
