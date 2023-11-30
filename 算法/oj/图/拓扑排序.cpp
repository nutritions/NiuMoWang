#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 1); 
    vector<int> indegree(N + 1, 0); 
    vector<int> dp(N + 1, 0); 

    set<int> startSet, endSet;

    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        indegree[y]++;
    }

    
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) {
            startSet.insert(i);
        }
        if (graph[i].empty()) {
            endSet.insert(i);
        }
    }

    for (int start : startSet) {
        dp[start] = 1; 

        queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int next : graph[cur]) {
                dp[next] = (dp[next] + dp[cur]) % MOD; 
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
    }

    int total = 0;
    for (int end : endSet) {
        total = (total + dp[end]) % MOD; 
    }

    cout << total << endl;

    return 0;
}
