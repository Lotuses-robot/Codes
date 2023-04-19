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

#include <cstdlib>
#include <ctime>

int main() {
    #ifdef LOCAL
        freopen(".in", "w", stdout);
    #endif
    srand(time(NULL));

    int T = 100;
    writeln(T);
    while (T--) {
        int n = 10, m = 9;
        writeln(n, m);
        for (int i = 1; i <= n; i++) {
            write(rand() % 2); putchar(' ');
        }
        putchar('\n');
        for (int i = 1; i <= m; i++) {
            if (rand() % 2) writeln(i, i + 1);
            else writeln(i + 1, i);
        }
    }
    fclose(stdout);
    return 0;
}
