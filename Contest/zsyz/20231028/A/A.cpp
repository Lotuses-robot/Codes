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
int T, i = 1, l, r, ns, ans;
char ch[maxn];
int f[2][16];

int getc(int i) {
    if (ch[i] == 'R') return 1;
    if (ch[i] == 'G') return 2;
    if (ch[i] == 'B') return 3;
    return 0;
}

#define zip(x, y) (((x) << 2) | (y))

tsz main() {
    // #ifdef LOCAL
    //     freopen(".in", "r", stdin);
    //     freopen(".out", "w", stdout);
    // #endif
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);

    read(T);
    while (T--) {
        scanf("%s", ch + 1);
        n = strlen(ch + 1); i = 1;
        memset(f[i], -63, sizeof(f[i]));
        f[i][0] = 0;
        for (int x = 1; x <= n; x++) {
            i ^= 1;
            memcpy(f[i], f[i ^ 1], sizeof(f[i]));
            for (int s = 0; s < 16; s++) {
                l = (s >> 2) & 3, r = s & 3;
                if (!l && r) continue;
                if (!l && !r) {
                    ns = zip(getc(x), 0);
                    f[i][ns] = std::max(f[i][ns], f[i ^ 1][s]);
                } else if (!r) {
                    ns = zip(l, getc(x));
                    f[i][ns] = std::max(f[i][ns], f[i ^ 1][s]);
                } else {
                    if (l == r && r == getc(x)) {
                        f[i][zip(1, 0)] = std::max(f[i][zip(1, 0)], f[i ^ 1][s] + 1);
                        f[i][zip(2, 0)] = std::max(f[i][zip(2, 0)], f[i ^ 1][s] + 1);
                        f[i][zip(3, 0)] = std::max(f[i][zip(3, 0)], f[i ^ 1][s] + 1);
                    } else if (l != r && l != getc(x) && r != getc(x)) {
                        for (int lt = 1; lt <= 3; lt++) {
                            for (int rt = 1; rt <= 3; rt++) {
                                f[i][zip(lt, rt)] = std::max(f[i][zip(lt, rt)], f[i ^ 1][s]);
                            }
                        }
                    } else {
                        f[i][zip(r, getc(x))] = std::max(f[i][zip(r, getc(x))], f[i ^ 1][s]);
                    }
                }
            }
            // writeln(x);
            // for (int s = 0; s < 16; s++) {
            //     writeln(s, f[i][s]);
            // }
            // puts("");
        }
        ans = 0;
        for (int s = 0; s < 16; s++) {
            l = (s >> 2) & 3, r = s & 3;
            if (!l && r) continue;
            ans = std::max(ans, f[i][s]);
        }
        writeln(ans);
    }
    return 0;
}