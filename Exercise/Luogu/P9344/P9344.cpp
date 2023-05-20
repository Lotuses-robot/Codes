#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

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

const int maxn = 2000006;

int a[maxn];
int c[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        for (int i = 1; i <= n; i++) {
            read(a[i]);
        }
        for (int i = 1; i <= n; i++) {
            read(c[i]);
        }
        if (c[1] == c[n]) {
            printf("%lld\n", a[1] + a[n]);
        } else {
            int min = 1e10;
            for (int i = 1; i < n; i++) {
                if (c[i] == c[1] && c[i + 1] == c[n]) {
                    min = std::min(min, a[i] + a[i + 1]);
                }
            }
            printf("%lld\n", a[1] + min + a[n]);
        }
    }
    return 0;
}
