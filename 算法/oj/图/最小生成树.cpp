#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h>
#define MAX_N 100005
int parent[MAX_N];


typedef struct edge {
	int u, v, w;
}Edge;

Edge edges[MAX_N];
int cmp(const void* a, const void* b) {
	return ((Edge*)a)->w - ((Edge*)b)->w;
}

int find(int i) {
	while (parent[i] >= 0)
		i = parent[i];
	return i;
}
void Merge(int a, int b) {
	int ra = find(a);
	int rb = find(b);
	int sum = parent[ra] + parent[rb];
	parent[ra] > parent[rb] ? (parent[ra] = rb, parent[rb] = sum) : (parent[rb] = ra, parent[ra] = sum);
}

int Kruskal(int n,int m) {
	int Sum = 0,num = 0;
	for (int i = 0; i < n; i++)
		parent[i+1] = -1;
	for (int i = 0; i < m; i++)
	{
		if (!(find(edges[i].u) == find(edges[i].v))) {
			Sum += edges[i].w;
			num++;
			Merge(edges[i].u, edges[i].v);
		}
	}
	if (num == n - 1)
		printf("%d\n", Sum);
	else
		printf("-1\n");
	return num;
}



int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
	}
	qsort(edges, m, sizeof(Edge), cmp);
	Kruskal(n,m);
	return 0;
}
