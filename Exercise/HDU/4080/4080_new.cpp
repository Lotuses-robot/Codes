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

#define maxn 100006

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}

// vector<pair<pair<int, int>, int> > cnt[maxn];
int n, k;
int num[1000007];

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

int height[maxn];

void calheight(string str, int sa[], int rk[]) {
    memset(height, 0, sizeof(height));
    int j, kk = 0;
    for (int i = 0; i < n; i++) {
        if (rk[i] == 0) {kk = 0; continue;}
        if (kk) kk--;
        j = sa[rk[i] - 1];
        while (str[i + kk] == str[j + kk]) {
            kk++;
        }
        height[rk[i]] = kk;
    }
}

int check(int x, int sa[], int rk[]) {
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

int main() {
    freopen("4080.in", "r", stdin);
    freopen("4080.out", "w", stdout);
    cin >> k;
    while (k != 0) {
        static string str;
        cin >> str;
        n = str.length();
        // vector<int> res(str.length());
        static int res[maxn], rk[maxn];
        memset(res, 0, sizeof(res));
        suff(str, res);
        for (int i = 0; i < str.length(); i++) {
            res[i]--;
            rk[res[i]] = i;
        }
        calheight(str, rk, res);
        

        // for (int i = 0; i < n; i++) {
        //     printf("%d ", ans[i]);
        // }

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