// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

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

const int maxn = 1e4 + 5;
int t[maxn], c[maxn], p[maxn];
int f[maxn << 8];
int cnt = 0;
int itv[maxn << 8], itw[maxn << 8];

void insert(int ma, int t, int c) {
    int tmp = 1;
    while (ma > tmp) {
        ++cnt;
        itv[cnt] = t * tmp;
        itw[cnt] = c * tmp;
        ma -= tmp;
        tmp <<= 1;
    }
    tmp = ma;
    if (tmp <= 0) return;
    ++cnt;
    itv[cnt] = t * tmp;
    itw[cnt] = c * tmp;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int bh, bm, eh, em, th, tm, n;
    read(bh, bm, eh, em, n);
    tm = - (bh * 60 + bm) + (eh * 60 + em);
    if (tm < 0) {
        writeln(0);
        return 0;
    }


    memset(f, -63, sizeof(f));

    for (int i = 1; i <= n; i++) {
        read(t[i], c[i], p[i]);
        if (t[i] == 0 && p[i] == 0) { puts("LOL YOURE A FUKING PROBLEM MAKER"); return 0; }
        if (!p[i]) p[i] = 999999;
        insert(p[i], t[i], c[i]);
        
    }

    int ans = -998244353;
    f[0] = 0;
    for (int i = 1; i <= cnt; i++) {
        for (int v = tm; v >= itv[i]; v--) {
            f[v] = std::max(f[v], f[v - itv[i]] + itw[i]);
            ans = std::max(ans, f[v]);
            // writeln(i, v, f[v]);
        }
    }
    writeln(ans);
    return 0;
}
