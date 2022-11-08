#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#pragma GCC optimize(2)

// #define int long long
using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::deque;

deque<int> dq;
int n,k;

int height[86600];
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

vector<pair<pair<int, int>, int> > cnt[86600];

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
    ch.clear();
    for (int i = 0; i < str.length(); i++) {
        ch.push_back(make_pair(str[i], -114514));
    }
    sort(ch, rank);

    for (int i = 1, kk = 0; kk < 25; i <<= 1, kk++) {
        static vector<pair<int, int> > ls;
        ls.clear();
        for (int pos = 0; pos < str.length(); pos++) {
            ls.push_back(make_pair(rank[pos], GetRank(pos + i)));
        }
        if (sort(ls, rank)) return;
    }
}

void calheight(string str, vector<int> &sa, vector<int> &rk) {
    memset(height, 0, sizeof(height));
    int j, kk = 0;
    for (int i = 0; i < str.length(); i++) {
        if (rk[i] == 0) {kk = 0; continue;}
        if (kk) kk--;
        j = sa[rk[i] - 1];
        while (str[i + kk] == str[j + kk]) {
            kk++;
        }
        height[rk[i]] = kk;
    }
}

int check(int x, vector<int> &sa, vector<int> &rk) {
    int ans = -1;
    for (int i = 0; i < n; i++) {
        if (n - sa[i] < x) continue;
        int Max = sa[i], cnt = 1;
        while (height[i + 1] >= x && i < n - 1) {
            Max = max(Max, sa[i + 1]);
            cnt++;
            i++;
        }
        if (cnt >= k)
            ans = max(ans, Max);
    }
    return ans;
}

template<typename T>
void init(T &vec, int len) {
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = 0;
    }
    for (int i = vec.size(); i < len; i++) {
        vec.push_back(0);
    }
}

int main() {
    freopen("4080.in", "r", stdin);
    freopen("4080.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin >> k;
    while (k != 0) {
        static string str;
        cin >> str;
        n = str.length();
        // cout << str << "\n";
        static vector<int> res;
        init(res, n);
        suff(str, res);
        static vector<int> rk;
        init(rk, n);

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
        if (check(1, rk, res) == -1) {  // attention
            cout << "none\n";
            cin >> k;
            continue;
        }
        int l = 1, r = n - k + 2;
        while (l < r) {
            int mid = (l + r) / 2;
            if (check(mid, rk, res) != -1) l = mid + 1;
            else r = mid;
        }
        l--;
        cout << l << " " << check(l, rk, res) << "\n";
        cin >> k;
    }
    return 0;
}