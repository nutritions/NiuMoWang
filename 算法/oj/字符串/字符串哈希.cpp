/*Description
小花有一个字符串S，她发现其中包含很多重复的子串，她为每个子串评分，分数定义为:子串的长度x子串在字符串出现的次数她想知道，分数最高的子串的分数是多少?
lnput
输入一个正整数N,表示字符串S的长度,S中包含小写字母a～z.(1 ≤N ≤5000)
Output
输出—个正整数，表示子串的最大分数*/

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
typedef unsigned long long ULL;
const int P = 131;  
//const int M = 1e9 + 9;  
ULL h[5001];
//ULL p[5001];
ULL p_last, p_new;

unordered_map<ULL, int> hashCount;
void init(int n,const string &s) {
    //p[0] = 1;
    h[0] = 0;
    for (int i = 1; i <= n; i++) {
        //p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + s[i-1];
    }
}

ULL get(int l, int len,ULL p_new) {
    return h[len + l - 1] - h[l - 1] * p_new;
}
//ULL get(int l, int len) {
//    return h[len + l - 1] - h[l - 1] * p[len];
//}

int main() {
    int N;
    string S;
    cin >> N >> S;
    p_last = 1;
    init(N, S);
    int maxScore = 0;
    ULL hashValue=0;
    for (int len = 1; len <= N; ++len) {
        p_new = p_last*P;
        for (int i = 0; i <= N - len; ++i) {
            string sub = S.substr(i, len);
            hashValue = get(i+1, len,p_new);
            p_last = p_new;
            hashCount[hashValue]++;
            int score = len * hashCount[hashValue];
            maxScore = max(maxScore, score);
        }
        for (auto it = hashCount.begin(); it != hashCount.end();) {
            //if (it->second * len != maxScore) {
            it = hashCount.erase(it);
            //}
            //else {
            //    ++it;
            //}
        }

    }

    cout << maxScore << endl;
    return 0;
}