// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
// #include <queue>
#include <string>
#include <iostream>
#include <algorithm>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T x) { write(x); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif
#define ins(a, b) (G[a].push_back(b))

#define int long long
const int maxn = 2e5 + 10;
string s[maxn];
struct Point {
    int i, j, f;
    bool operator < (Point b) const {
        if (f != b.f) return f > b.f;
        if (i != b.i) return i < b.i;
        return j < b.j;
    }
}; std::vector<Point> v;
bool vis[maxn]; int n;
set<string> st;
int ans = 0;

namespace sub {
    struct Trie {
        struct Node {
            std::map<std::pair<char, char>, int> ch;
            int cnt;
        } nd[maxn];
        int cnt;
        int c() {
            return ++cnt;
        }
        Trie() { cnt = 1; }
        void add(string s) {
            int u = 1;
            for (int i = 0; i < s.length(); i++) {
                if (!nd[u].ch[{s[i] - 'a', s[s.length() - i - 1] - 'a'}]) {
                    nd[u].ch[{s[i] - 'a', s[s.length() - i - 1] - 'a'}] = c();
                }
                u = nd[u].ch[{s[i] - 'a', s[s.length() - i - 1] - 'a'}];
            }
            nd[u].cnt++;
        }
        int query(int u, int len, int &ct) {
            if (u == 0) return 0;
            int cnt = nd[u].cnt, ans = 0;
            // for (int i = 0; i < 26; i++) {
            for (auto p : nd[u].ch) {
                ans += query(nd[u].ch[p.first], len + 1, cnt);
            }
            // }
            ct += cnt % 2;
            return ans + cnt / 2 * len * len;
        }
    } tr;
    void solve() {
        for (int i = 1; i <= n; i++) {
            tr.add(s[i]);
        }
        int tt;
        writeln(tr.query(1, 0, tt) + ans);
    }
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        if (st.find(s[i]) != st.end()) {
            ans += s[i].length() * s[i].length();
            st.erase(s[i]);
        } else {
            st.insert(s[i]);
        }
    }

    bool flag = true;
    n = 0;
    for (auto sc : st) {
        s[++n] = sc;
        if (flag)
        for (int i = 0; i < s[n].length() / 2; i++) {
            if (s[n][i] != s[n][s[n].length() - i - 1]) {
                flag = false;
                break;
            }
        }
    }

    if (true) {
        sub::solve();
        return 0;
    }

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int k = -1, cnt, len = std::min(s[i].length(), s[j].length());
            while (k + 1 < len && s[i][k + 1] == s[j][k + 1]) k++;
            cnt = k + 1; k = -1;
            while (k + 1 < len && s[i][s[i].length() - (k + 1) - 1] == s[j][s[j].length() - (k + 1) - 1]) k++;
            cnt = std::min(cnt, k + 1);
            v.push_back({i, j, cnt * cnt});
        }
    }

    std::sort(v.begin(), v.end());
    for (auto p : v) {
        if (vis[p.i] || vis[p.j]) continue;
        ans += p.f;
        vis[p.i] = vis[p.j] = true;
    }
    writeln(ans);
    return 0;
}