#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 100005;

// �ڽӱ�ڵ�
struct Node {
    int dest;
    Node* next;
    Node(int d) : dest(d), next(nullptr) {}
};

// �ڽӱ�
struct AdjList {
    Node* head;
    AdjList() : head(nullptr) {}
};

// ͼ�ṹ
struct Graph {
    int V; // ������
    vector<AdjList> array; // �ڽӱ�����
    Graph(int vertices) : V(vertices), array(vertices) {}
};

// ��ӱ�
void addEdge(Graph& graph, int src, int dest) {
    Node* newNode = new Node(dest);
    newNode->next = graph.array[src].head;
    graph.array[src].head = newNode;
    newNode = new Node(src);
    newNode->next = graph.array[dest].head;
    graph.array[dest].head = newNode;
}

// ��̬�滮������·������
int countShortestPaths(const Graph& graph, const vector<int>& distance, vector<int>& count, int src, int dest) {
    if (src == dest) {
        return 1;
    }
    int paths = 0;
    Node* current = graph.array[dest].head;
    while (current != nullptr) {
        int neighbor = current->dest;
        if (distance[neighbor] == distance[dest] - 1) {
            paths = (paths + countShortestPaths(graph, distance, count, src, neighbor)) % MOD;
        }
        current = current->next;
    }

    return paths;
}

// BFS�������·��
void shortestPaths(const Graph& graph, int src, vector<int>& distance, vector<int>& count) {
    queue<int> q;
    q.push(src);
    distance[src] = 0;
    count[src] = 1;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        Node* temp = graph.array[current].head;

        while (temp != nullptr) {
            int neighbor = temp->dest;

            if (distance[neighbor] == -1) {
                q.push(neighbor);
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
    cin >> N >> M;
    Graph graph(N);
    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        addEdge(graph, x - 1, y - 1);
    }

    vector<int> distance(N, -1);
    vector<int> count(N, 0);
    shortestPaths(graph, 0, distance, count);

    for (int i = 1; i < N; ++i) {
        int result = countShortestPaths(graph, distance, count, 0, i);
        cout << result << endl;
    }

    return 0;
}

