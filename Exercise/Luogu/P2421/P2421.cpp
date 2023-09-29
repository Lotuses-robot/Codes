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

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

const int maxn = 20;
int c[maxn], p[maxn], l[maxn];
int n;

bool check(int m) {
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int A = p[i] - p[j], B = m, C = c[j] - c[i], x, y;
            int g = exgcd(A, B, x, y);
            if (C % g) continue;
            int k = C / g;
            int x0 = k * x, xp = B / g;
            // writeln(x0, y0);
            if (xp < 0) xp = -xp;
            x0 = (x0 % xp + xp) % xp;
            if (x0 <= l[i] && x0 <= l[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    int bg = 0;
    for (int i = 1; i <= n; i++) {
        read(c[i], p[i], l[i]);
        bg = std::max(bg, c[i]);
    }
    for (int i = bg; ; i++) {
        if (check(i)) { writeln(i); return 0; }
    }
}
