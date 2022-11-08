#include <cstdio>
#include <queue>
#include <string>
#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::deque;

deque<int> dq;
int n,k;

int height[1000006];
int ps1(int t)
{
    while(!dq.empty()&&height[dq.back()]>=height[t]) dq.pop_back();
    dq.push_back(t);
    while(dq.front()<=t-k) dq.pop_front();
    return height[dq.front()];
}

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}

vector<pair<pair<int, int>, int> > cnt[1000660];

#define max(a, b) ((a) > (b) ? (a) : (b))

void sort(vector<pair<pair<int, int>, int> > &v) {
    int maxn = 0;
    
    // second order
    for (auto u : v) {
        if (u.first.second < 0) {
            cnt[0].push_back(u);
        } else {
            cnt[u.first.second].push_back(u);
            maxn = max(maxn, u.first.second);
        }
    }
    v.clear();
    for (int i = 0; i <= maxn; i++) {
        for (auto u : cnt[i]) {
            v.push_back(u);
        }
        cnt[i].clear();
    }

    // first order
    maxn = 0;
    for (auto u : v) {
        cnt[u.first.first].push_back(u);
        maxn = max(maxn, u.first.first);
    }
    v.clear();
    for (int i = 0; i <= maxn; i++) {
        for (auto u : cnt[i]) {
            v.push_back(u);
        }
        cnt[i].clear();
    }
}

bool sort(vector<pair<int, int> > &fix, vector<int> &res) {
    static vector<pair<pair<int, int>, int> > v;
    v.clear();
    for (int i = 0; i < fix.size(); i++) {
        v.push_back(make_pair(fix[i], i));
    }
    sort(v);
    bool flag = true;
    int rk = 1; auto last = v[0].first;
    for (int i = 0; i < v.size(); i++) {
        if (last != v[i].first) {
            last = v[i].first;
            rk++;
        } else if (i != 1) {
            flag = false;
        }
        res[v[i].second] = rk;
    }
    return flag;
}

#define GetRank(x) ((x) >= str.length() ? -114514 : rank[(x)])

void suff(string &str, vector<int> &rank) {
    // sort natstr
    static vector<pair<int, int> > ch;
    for (int i = 0; i < str.length(); i++) {
        ch.push_back(make_pair(str[i], -114514));
    }
    sort(ch, rank);

    for (int i = 1, k = 0; k < 20; i <<= 1, k++) {
        static vector<pair<int, int> > ls;
        ls.clear();
        for (int pos = 0; pos < str.length(); pos++) {
            ls.push_back(make_pair(rank[pos], GetRank(pos + i)));
        }
        if (sort(ls, rank)) return;
    }
}

void calheight(string str, vector<int> &sa, vector<int> &rk) {
    int j, k = 0;
    for (int i = 0; i < str.length(); i++) {
        if (rk[i] == 0) {k = 0; continue;}
        if (k) k--;
        j = sa[rk[i] - 1];
        while (str[i + k] == str[j + k]) {
            k++;
        }
        height[rk[i]] = k;
    }
}

int main() {
    cin >> n >> k; k--;
    string str;
    int ch;
    for (int i = 1; i <= n; i++) {
        cin >> ch;
        str += (char)(ch + '0');
    }
    // cout << str << "\n";
    vector<int> res(str.length());
    suff(str, res);
    vector<int> rk(res.size());

    for (int i = 0; i < str.length(); i++) {
        res[i]--;
        rk[res[i]] = i;
    }
    // printf("%d %d\n", rk.size(), res.size());
    calheight(str, rk, res);
    // for (int i = 0; i < str.length(); i++) {
    //     printf("%d %d %d\n", rk[i], res[i], height[i]);
    // }
    // puts("fk");
    int ans = 0;
    for (int i = 0; i < k; i++) ps1(i);
    for (int i = k; i < n; i++) ans = max(ps1(i), ans);
    printf("%d\n", ans);
    return 0;
}