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

const int maxn = 1e5 + 5;
unsigned a[maxn], b[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n; long long k; unsigned sum = 0;
        read(n, k);

        for (int i = 1; i <= n; i++) {
            read(a[i]);
            sum ^= a[i];
        }

        if (n % 2) {
            // a[i] -> ^ [i != j] a[j]
            for (int i = 1; i <= n; i++) {
                write(sum ^ a[i]);
                putchar(' ');
            }
        } else {
            if (k % 2 == 0) {
                for (int i = 1; i <= n; i++) {
                    write(a[i]);
                    putchar(' ');
                }
            } else {
                for (int i = 1; i <= n; i++) {
                    write(sum ^ a[i]);
                    putchar(' ');
                }
            }
        }
        puts("");
    }
    
    return 0;
}
