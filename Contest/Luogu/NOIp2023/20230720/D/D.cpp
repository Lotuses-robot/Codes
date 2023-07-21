// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>

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

const int maxn = 5003;
int a[maxn], b[maxn];
std::vector<int> sta, stb;
int n, m;

bool check() {
    if (sta.size() == 0 || stb.size() == 0) return 0;
    if (sta.size() != stb.size()) {
        return sta.size() > stb.size();
    } else {
        for (int i = 0, sz = sta.size(); i < sz; i++) {
            if (sta[i] != stb[i]) {
                return sta[i] > stb[i];
            }
        }
        return false;
    }
}

int dfs2(int cur) {
    if (cur > m) {
        // if (check()) {
        //     for (int i : sta) {
        //         printf("%d ", i);
        //     }
        //     puts("");
        //     for (int i : stb) {
        //         printf("%d ", i);
        //     }
        //     puts("");
        //     puts("");
        // }
        return check();
    }
    std::map<int, bool> mp;
    mp.clear();
    int ans = 0;
    for (int i = cur; i <= m; i++) {
        if (!mp[b[i]]) {
            mp[b[i]] = true;
            stb.push_back(b[i]);
            ans += dfs2(i + 1);
            stb.pop_back();
        }
    }
    ans += dfs2(m + 1);
    return ans;
}

int dfs1(int cur) {
    if (cur > n) {
        return dfs2(1);
    }
    std::map<int, bool> mp;
    mp.clear();
    int ans = 0;
    for (int i = cur; i <= n; i++) {
        if (!mp[a[i]]) {
            mp[a[i]] = true;
            sta.push_back(a[i]);
            ans += dfs1(i + 1);
            sta.pop_back();
        }
    }
    ans += dfs1(n + 1);
    return ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= m; i++) {
        read(b[i]);
    }
    writeln(dfs1(1));
    return 0;
}
