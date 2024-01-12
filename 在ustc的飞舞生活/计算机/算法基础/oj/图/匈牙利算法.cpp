#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1005

// ���ڴ洢ƥ�����������
int match[MAXN];
// ���ڱ���Ƿ��Ѿ����ʹ�������
int visited[MAXN];
// �ڽӾ����ʾ��ͼ
int graph[MAXN][MAXN];

int dfs(int u, int n, int m) {
    for (int v = 0; v < m; v++) {
        if (graph[u][v] && !visited[v]) {
            visited[v] = 1;
            // ���v��δƥ�����v��ƥ���������ҵ��µ�ƥ�䣬�ݹ����
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
    // ��ȡ�øй�ϵ
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

