#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000

// 用于存储匹配情况的数组
int match[MAXN];

// 用于标记是否已经访问过的数组
int visited[MAXN];

// 邻接矩阵表示的图
int graph[MAXN][MAXN];

// 递归实现的匈牙利算法
int dfs(int u, int n, int m) {
    for (int v = 0; v < m; v++) {
        if (graph[u][v] && !visited[v]) {
            visited[v] = 1;

            // 如果v尚未匹配或者v的匹配对象可以找到新的匹配，递归调用
            if (match[v] == -1 || dfs(match[v], n, m)) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

// 匈牙利算法主函数
int hungarian(int n, int m) {
    int result = 0;

    // 初始化匹配数组
    memset(match, -1, sizeof(match));

    // 遍历每个小花的朋友
    for (int i = 0; i < n; i++) {
        // 初始化访问数组
        memset(visited, 0, sizeof(visited));

        // 尝试匹配
        result += dfs(i, n, m);
    }

    return result;
}

int main() {
    int N, M, E;
    scanf("%d %d %d", &N, &M, &E);

    // 初始化邻接矩阵
    memset(graph, 0, sizeof(graph));

    // 读取好感关系
    for (int i = 0; i < E; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        // 转换为从0开始的下标
        x--;
        y--;
        // 添加好感关系到邻接矩阵
        graph[x][y] = 1;
    }

    // 调用匈牙利算法求解最大匹配数
    int result = hungarian(N, M);

    printf("%d\n", result);

    return 0;
}

