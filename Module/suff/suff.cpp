#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::pair;
using std::make_pair;

#define maxn 1000006

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}

// vector<pair<pair<int, int>, int> > cnt[maxn];
int n;
int num[maxn];

#define max(a, b) ((a) > (b) ? (a) : (b))
#define doit(a) ((a) < 0 ? 0 : (a))

void sort(pair<pair<int, int>, int> v[]) {
    static pair<pair<int, int>, int> u[maxn];
    memset(u, 0, sizeof(u));
    memset(num, 0, sizeof(num));
    int Max = 0;
    
    // second order
    for (int i = 0; i < n; i++) {
        num[doit(v[i].first.second)]++;
        Max = max(Max, doit(v[i].first.second));
    }
    for (int i = 1; i <= Max; i++) {
        num[i] += num[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        u[--num[doit(v[i].first.second)]] = v[i];
    }
    memcpy(v, u, sizeof(u));

    memset(u, 0, sizeof(u));
    memset(num, 0, sizeof(num));
    Max = 0;
    
    // second order
    for (int i = 0; i < n; i++) {
        num[v[i].first.first]++;
        Max = max(Max, v[i].first.first);
    }
    for (int i = 0; i <= Max; i++) {
        num[i] += num[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        u[--num[v[i].first.first]] = v[i];
    }
    memcpy(v, u, sizeof(u));
}

bool sort(pair<int, int> fix[], int res[]) {
    static pair<pair<int, int>, int> v[maxn];
    for (int i = 0; i < n; i++) {
        v[i] = make_pair(fix[i], i);
    }
    sort(v);
    bool flag = true;
    int rk = 1; auto last = v[0].first;
    for (int i = 0; i < n; i++) {
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

void suff(string &str, int rank[]) {
    // sort natstr
    static pair<int, int> ch[maxn];
    for (int i = 0; i < n; i++) {
        ch[i] = make_pair(str[i], -114514);
    }
    sort(ch, rank);

    for (int i = 1, k = 0; k < 20; i <<= 1, k++) {
        static pair<int, int> ls[maxn];
        for (int pos = 0; pos < n; pos++) {
            ls[pos] = make_pair(rank[pos], GetRank(pos + i));
        }
        if (sort(ls, rank)) return;
    }
}

int main() {
    string str;
    cin >> str;
    n = str.length();
    // vector<int> res(str.length());
    static int res[maxn], ans[maxn];
    suff(str, res);
    for (int i = 0; i < str.length(); i++) {
        ans[res[i] - 1] = i + 1;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", ans[i]);
    }
    puts("");
    return 0;
}