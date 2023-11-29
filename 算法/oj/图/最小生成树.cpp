#include <stdio.h> //连通输出-1还未解决 
#include <stdlib.h>
int parent[10];
int n,m;
int i,j;
 
struct edge{
	int u,v,w; //边的顶点，权值
}edges[10];
 
//初始化并查集
void UFset(){
	for(i=1; i<=n; i++) parent[i] = -1;
}
 
//查找i的跟
int find(int i){
	int temp;
	//查找位置
	for(temp = i; parent[temp] >= 0; temp = parent[temp]);
	//压缩路径
	while(temp != i){
		int t = parent[i];
		parent[i] = temp;
		i = t;
	}
	return temp;
}
//合并两个元素a,b
void merge(int a,int b){
	int r1 = find(a);
	int r2 = find(b);
	int tmp = parent[r1] + parent[r2]; //两个集合节点数的和
	if(parent[r1] > parent[r2]){
		parent[r1] = r2;
		parent[r2] = tmp;
	}else{
		parent[r2] = r1;
		parent[r1] = tmp;
	}
}
 
void kruskal(){
	int sumWeight = 0;
	int num = 0;
	int u,v;
	UFset();
	for(int i=0; i<m; i++)
	{
		u = edges[i].u;
		v = edges[i].v;
 
		if(find(u) != find(v)){ //u和v不在一个集合
			//printf("加入边：%d %d,权值： %d\n", u,v,edges[i].w);
			sumWeight += edges[i].w;
			num ++;
			merge(u, v); //把这两个边加入一个集合。
		}
	}
	printf("%d\n", sumWeight);
}
 
//比较函数，用户排序
int cmp(const void * a, const void * b){
	edge * e1 = (edge *)a;
	edge * e2 = (edge *)b;
	return e1->w - e2->w;
}
 
int main() {
 
	scanf("%d %d", &n, &m);
	for(i=0; i<m; i++){
		scanf("%d %d %d", &edges[i].u,  &edges[i].v,  &edges[i].w);
	}
	qsort(edges, m, sizeof(edge), cmp);
 
	kruskal();
 
 
	return 0;
}
