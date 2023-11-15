#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 200
#define INF 0x3f3f3f3f

int dp[MAX_N][MAX_N]; // dp[i][j] 表示从第 i 堆到第 j 堆合并后的最小总得分
int sum[MAX_N]; // 前缀和，表示前 i 堆糖果的总数

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    int candies[205];

    for (int i = 0; i < N; i++) {
        scanf("%d", &candies[i]);
        sum[i] = (i == 0) ? candies[i] : sum[i - 1] + candies[i];
    }

    for (int len = 2; len <= N; len++) {
        for (int i = 0; i + len - 1 < N; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }

    printf("%d\n", dp[0][N - 1]);

    return 0;
}
