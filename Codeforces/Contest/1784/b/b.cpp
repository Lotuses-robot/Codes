// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <stack>
// #include <string>
// #include <algorithm>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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
#define ins(a, b) (G[a].emplace_back(b))

const int maxn = 1e5 + 10;
int n;
int mp[255];
int cnt[3][maxn];
char ch[maxn];
std::vector<int> todo;
struct MV {
    int id, ch;
};
std::vector<std::pair<MV, MV> > ans;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    mp['w'] = 0;
    mp['i'] = 1;
    mp['n'] = 2;
    mp[0] = 'w';
    mp[1] = 'i';
    mp[2] = 'n';

    int T;
    read(T);
    while (T--) {
        read(n);
        memset(cnt[0], 0, sizeof(int) * (n + 5));
        memset(cnt[1], 0, sizeof(int) * (n + 5));
        memset(cnt[2], 0, sizeof(int) * (n + 5));
        todo.clear(); ans.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%s", ch);
            for (int j = 0; j < 3; j++) {
                cnt[mp[ch[j]]][i]++;
            }
            if (!cnt[0][i]) todo.emplace_back(i);
        }
        auto p = todo.begin();
        for (int i = 1; i <= n; i++) {
            while (cnt[0][i] > 1) {
                if (p == todo.end()) break;
                if (cnt[1][*p] > 1 || !cnt[2][*p]) {
                    cnt[0][i]--;
                    cnt[0][*p]++;
                    cnt[1][i]++;
                    cnt[1][*p]--;
                    ans.emplace_back(std::make_pair((MV){i, 0}, (MV){*p, 1}));
                } else {
                    cnt[0][i]--;
                    cnt[0][*p]++;
                    cnt[2][i]++;
                    cnt[2][*p]--;
                    ans.emplace_back(std::make_pair((MV){i, 0}, (MV){*p, 2}));
                }
                p++;
            }
        }
        todo.clear();
        for (int i = 1; i <= n; i++) {
            if (!cnt[1][i]) todo.emplace_back(i);
        }
        p = todo.begin();
        for (int i = 1; i <= n; i++) {
            while (cnt[1][i] > 1) {
                if (p == todo.end()) break;
                cnt[1][i]--;
                cnt[1][*p]++;
                cnt[2][i]++;
                cnt[2][*p]--;
                ans.emplace_back(std::make_pair((MV){i, 1}, (MV){*p, 2}));
                p++;
            }
        }
        writeln(ans.size());
        for (auto p : ans) {
            write(p.first.id); putchar(' '); putchar(mp[p.first.ch]); putchar(' ');
            write(p.second.id); putchar(' '); putchar(mp[p.second.ch]); putchar(' ');
            puts("");
        }
    }
    return 0;
}