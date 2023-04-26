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

const int Maxn = 2e3, Mod = 1e9 + 7;

int n, ans, s[Maxn + 5]; char ss[Maxn + 5];
int f[Maxn + 5][Maxn + 5], g[Maxn + 5][Maxn + 5];
bool fv[Maxn + 5][Maxn + 5], gv[Maxn + 5][Maxn + 5];
int F(int x, int y);
int G(int x, int y);

inline int Get(int x, int y) {
    if (x == 0)
        return 0;
    if (x == n + 1)
        return 1;
    return s[n - (x - y)];
}
inline int F(int x, int y) {
    if (x == 0)
        return 0;
    if (fv[x][y])
        return f[x][y];
    int res = 0;
    for (int i = x; i; i--)
        if (Get(x, i) != Get(y, i)) {
            res = (F(i - 1, y) + 1 + G(i - 1, x)) % Mod;
            break;
        }
    fv[x][y] = 1, f[x][y] = res;
    return res;
}
inline int G(int x, int y) {
    if (x == 0)
        return 0;
    if (gv[x][y])
        return g[x][y];
    int res = 0;
    for (int i = x; i; i--)
        if (Get(x, i) != Get(y, i)) {
            res = (F(i - 1, x) + 1 + G(i - 1, y)) % Mod;
            break;
        }
    gv[x][y] = 1, g[x][y] = res;
    return res;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    read(n);
    scanf("%s", ss + 1);
    for (int i = 1; i <= n; i++) s[i] = ss[i] - '0';
    ans = (F(n, 0) + 1 + G(n, n + 1)) % Mod;
    writeln(ans);
    return 0;
}
