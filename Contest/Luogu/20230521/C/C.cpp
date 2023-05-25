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

const int maxn = 2e6 + 100;
char ch[maxn];
int a[maxn], s[maxn];
int t[4 * maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, ans = 0;
        read(n);
        scanf("%s", ch + 1);
        s[1] = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = ch[i] == '(' ? 1 : -1;
            s[i + 1] = s[i] + a[i];
        }

        n++;
        memset(t, 0, sizeof(int) * (n + n + 100));
        for (int i = 1; i <= n; i++) {
            t[s[i] + n]++;
        }

        for (int i = -n, cnt = 0, s = 0; i <= n; i++) {
            for (int c = 1; c <= t[i + n]; c++, cnt++) {
                s += i;
                ans += (cnt + 1) * i - s; 
                debug(i, cnt + 1, s, ans);
            }
        }
        
        ans += n * (n - 1) / 2;
        // memset(t, 0, sizeof(t));
        for (int i = 0; i <= n + n; i++) t[i] = 0;
        for (int i = 1; i <= n; i++) {
            ans -= i - t[s[i] + n - 1] - 1;
            t[s[i] + n] = i;
        }

        // memset(t, 0, sizeof(t));
        for (int i = 0; i <= n + n; i++) t[i] = n + 1;
        for (int i = n; i >= 1; i--) {
            ans -= t[s[i] + n - 1] - i - 1;
            t[s[i] + n] = i;
        }

        
        memset(t, 0, sizeof(int) * (n + n + 100));
        for (int i = 1; i <= n; i++) {
            t[s[i] + n]++;
            if (s[i] > s[i + 1]) {
                ans += t[s[i] + n] * (t[s[i] + n] - 1) / 2;
                t[s[i] + n] = 0;
            }
        }

        for (int i = 1; i <= n; i++) {
            ans += t[s[i] + n] * (t[s[i] + n] - 1) / 2;
            t[s[i] + n] = 0;
        }

        writeln(ans);
    }
    return 0;
}
