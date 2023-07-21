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

#define int long long

const int maxn = 1000006,
          mod = 1000000007;
char ch[maxn];
int pow2[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, k, now = 0, base = 1, ans = 0;
    read(n, k);
    scanf("%s", ch + 1);

    for (int i = 1; i <= n; i++) {
        if (i <= n / 2) std::swap(ch[i], ch[n - i + 1]);
        base <<= 1; base %= mod;
        pow2[n - i + 1] = base;
    }

    for (int i = 1; i <= n; i++) {
        // base <<= 1; base %= mod;
        // writeln(ch[i] - 'A', pow2[i]);
        if (ch[i] == 'A') now--;
        else now++;

        if (now > k) {
            ch[i] = 'A';
            now -= 2;
            ans += pow2[i];
            ans %= mod;
        }
        if (now < 0) now = 0;
    }
    writeln(ans);
    return 0;
}
