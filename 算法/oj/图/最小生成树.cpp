#include <stdio.h> 
#include <stdlib.h>
int parent[100005];
int n,m;
int i,j;
 
typedef struct edge{
	int u,v,w; 
}Edge;
 
Edge edges[100005];
//查找i的根 
int find(int i){
	int tmp=i;
	while(parent[tmp]>=0)
		tmp=parent[tmp];
	while(tmp != i){
		int t = parent[i];
		parent[i] = tmp;
		i = t;
	}
	return tmp;
}
//合并两个元素a,b
void merge(int a,int b){
	int ra = find(a);
	int rb = find(b);
	int tmp = parent[ra] + parent[rb]; //两个集合节点数的和
	if(parent[ra] > parent[rb]){
		parent[ra] = rb;
		parent[rb] = tmp;
	}else{
		parent[rb] = ra;
		parent[ra] = tmp;
	}
}
 
int kruskal(int n){
	int Sum = 0;
	int num = 0;
	int u,v;
	for(i=1; i<=n; i++) 
		parent[i] = -1;
	for(int i=0; i<m; i++)
	{
		u = edges[i].u;
		v = edges[i].v;
		if(find(u) != find(v)){ 
			Sum += edges[i].w;
			num ++;
			merge(u, v); 
		}
	}
	if(num==n-1)
		printf("%d\n", Sum);
	else
		printf("-1\n");
	return num;
}
 
int cmp(const void * a, const void * b){
	Edge * e1 = (Edge *)a;
	Edge * e2 = (Edge *)b;
	return e1->w - e2->w;
}
 
int main() {
	scanf("%d %d", &n, &m);
	for(i=0; i<m; i++){
		scanf("%d %d %d", &edges[i].u,  &edges[i].v,  &edges[i].w);
	}
	qsort(edges, m, sizeof(Edge), cmp);
    kruskal(n);
	return 0;
}
