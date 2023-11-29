#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAXN 100005
#define MAXM 200005

// �ڽӱ�ڵ�
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// �ڽӱ�
typedef struct {
    Node* head;
} AdjList;

// ͼ�ṹ
typedef struct {
    int V; // ������
    AdjList* array; // �ڽӱ�����
} Graph;

// �����ڵ�
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// ����ͼ
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// ��ӱ�
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// ��̬�滮������·������
int countShortestPaths(Graph* graph, int* distance, int* count, int src, int dest) {
    if (src == dest) {
        return 1;
    }

    int paths = 0;
    Node* current = graph->array[dest].head;
    while (current != NULL) {
        int neighbor = current->dest;
        if (distance[neighbor] == distance[dest] - 1) {
            paths = (paths + countShortestPaths(graph, distance, count, src, neighbor)) % MOD;
        }
        current = current->next;
    }

    return paths;
}

// BFS�������·��
void shortestPaths(Graph* graph, int src, int* distance, int* count) {
    int queue[MAXN];
    int front = 0, rear = 0;

    queue[rear++] = src;
    distance[src] = 0;
    count[src] = 1;

    while (front != rear) {
        int current = queue[front++];
        Node* temp = graph->array[current].head;

        while (temp != NULL) {
            int neighbor = temp->dest;

            if (distance[neighbor] == -1) {
                queue[rear++] = neighbor;
                distance[neighbor] = distance[current] + 1;
                count[neighbor] = count[current];
            } else if (distance[neighbor] == distance[current] + 1) {
                count[neighbor] = (count[neighbor] + count[current]) % MOD;
            }

            temp = temp->next;
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Graph* graph = createGraph(N);

    for (int i = 0; i < M; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(graph, x - 1, y - 1);
    }

    int* distance = (int*)malloc(N * sizeof(int));
    int* count = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i) {
        distance[i] = -1;
        count[i] = 0;
    }

    shortestPaths(graph, 0, distance, count);

    for (int i = 1; i < N; ++i) {
        int result = countShortestPaths(graph, distance, count, 0, i);
        printf("%d\n", result);
    }

    free(distance);
    free(count);
    free(graph->array);
    free(graph);

    return 0;
}

