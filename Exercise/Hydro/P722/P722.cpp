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
const int maxn = 2e7 + 7;
char ch[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, k, ans = 0, zero = 0;
    read(n, k);
    scanf("%s", ch + 1);

    if (k == 0) {
        for (int i = 1; i <= n; i++) {
            ans++;
            if (ch[i] != '0') {
                ans += n - i;
            }
        }
        writeln(ans);
        return 0;
    }

    int mod = 1 << k;
    for (int i = 1; i <= n; i++) {
        int r = 0, base = 1;
        for (int j = i, l = std::max(1ll, i - k + 1); j >= l; j--) {
            r += (ch[j] - '0') * base;
            base *= 10;
            writeln(666, j, r, mod);
            if (r % mod == 0 && (ch[j] != '0' || j == i)) {
                ans++;
                writeln(i, j);
            }
        }
        if (i - k + 1 > 1 && r % mod == 0) {
            ans += i - k - zero;
            writeln(i, k, zero);
        }
        if (i - k + 1 >= 1 && ch[i - k + 1] == '0') {
            zero++;
        }
    }
    writeln(ans);
    return 0;
}
