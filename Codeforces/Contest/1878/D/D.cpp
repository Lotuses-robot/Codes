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

const int maxn = 2e5 + 10;
char ch[maxn];
int l[maxn], r[maxn];
int pt[maxn];
int chx[maxn];

void rev(int x) {
    int lc = l[pt[x]], rc = r[pt[x]];
    int lx = std::min(x, lc + rc - x);
    // writeln(-1, lc, rc, lx);
    chx[lx] ^= 1;
}

void chd(int k) {
    for (int i = 1; i <= k; i++) {
        int mid = (l[i] + r[i]) / 2; int type = 0;
        // writeln(l[i], r[i], mid);
        for (int x = l[i]; x <= mid; x++) {
            type ^= chx[x];
            if (type) {
                // writeln(x, l[i] + r[i] - x);
                std::swap(ch[x], ch[l[i] + r[i] - x]);
            }
        }
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, k;
        read(n, k);

        memset(chx, 0, sizeof(int) * (n + 3));

        scanf("%s", ch + 1);
        for (int i = 1; i <= k; i++) read(l[i]);
        for (int i = 1; i <= k; i++) read(r[i]);

        int ptx = 1;
        for (int i = 1; i <= n; i++) {
            if (i > r[ptx]) {
                ptx++;
            }
            pt[i] = ptx;
        }

        int q;
        read(q);
        while (q--) {
            int x;
            read(x);
            rev(x);
        }
        // for (int i = 1; i <= n; i++) {
        //     writeln(chx[i]);
        // }
        chd(k);
        printf("%s\n", ch + 1);
    }
    return 0;
}