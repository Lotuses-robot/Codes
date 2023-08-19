// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <deque>

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
const int maxn = 2e5 + 10;
int h[maxn];
int f[maxn];
int q[maxn], head = 1, tail = 1;

double slope(int i, int j) {
    return (double)(f[i] + h[i] * h[i] - f[j] - h[j] * h[j]) / (h[i] - h[j]);
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, c;
    read(n, c);
    for (int i = 1; i <= n; i++) {
        read(h[i]);
    }

    f[1] = 0;
    q[head = tail] = 1;
    for (int i = 2; i <= n; i++) {
        while (head < tail && slope(q[head], q[head + 1]) <= 2 * h[i]) ++head;
        int j = q[head];
        f[i] = f[j] + c + (h[i] - h[j]) * (h[i] - h[j]);
        while (head < tail && slope(q[tail - 1], q[tail]) >= slope(q[tail - 1], i)) tail--;
        q[++tail] = i;
    }
    writeln(f[n]);
    return 0;
}
