#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1005

// 用于存储匹配情况的数组
int match[MAXN];
// 用于标记是否已经访问过的数组
int visited[MAXN];
// 邻接矩阵表示的图
int graph[MAXN][MAXN];

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

int hungarian(int n, int m) {
    int result = 0;
    memset(match, -1, sizeof(match));
    for (int i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited));
        result += dfs(i, n, m);
    }
    return result;
}

int main() {
    int N, M, E;
    scanf("%d%d%d", &N, &M, &E);
    memset(graph, 0, sizeof(graph));
    // 读取好感关系
    for (int i = 0; i < E; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--;
        y--;
        graph[x][y] = 1;
    }
    int result = hungarian(N, M);
    printf("%d\n", result);
    return 0;
}

