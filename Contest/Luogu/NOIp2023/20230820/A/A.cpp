// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>

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

#define int long long

const int maxn = 5005;
char ch[maxn];
int cnt[1 << 12];
int cntp[1 << 12];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, k;
    read(n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", ch + 1);
        k = strlen(ch + 1);
        int num = 0;
        for (int j = 1; j <= k; j++) {
            num |= (1 << (ch[j] - '0'));
        }
        cnt[num]++;
    }

    int ans = 0;
    for (int i = 1; i < (1 << 10); i++) {
        if (cnt[i]) {
            for (int j = 1; j < (1 << 10); j++) {
                if ((j | i) == i) {
                    int ct = __builtin_popcount(j);
                    if (ct & 1) {
                        ans += cnt[i] * cntp[j];
                    } else {
                        ans -= cnt[i] * cntp[j];
                    }
                    cntp[j] += cnt[i];
                }
            }
            ans += cnt[i] * (cnt[i] - 1) / 2;
        }
    }
    writeln(ans);
    return 0;
}
