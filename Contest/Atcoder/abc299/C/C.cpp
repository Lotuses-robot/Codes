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

char ch[200005];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    scanf("%s", ch + 1);

    bool flag = true, flag1 = true;
    for (int i = 1; i <= n; i++) {
        if (ch[i] == '-') {
            flag = false;
        }
        if (ch[i] == 'o') {
            flag1 = false;
        }
    }
    if (flag || flag1) {
        puts("-1");
        return 0;
    }

    int maxx = 0, last = 1;
    for (int i = 1; i <= n; i++) {
        if (ch[i] == '-') {
            if (i - last > maxx) {
                maxx = i - last;
            }
            last = i + 1;
        } else if (i == n) {
            if (i - last + 1 > maxx) {
                maxx = i - last + 1;
            }
        }
    }

    writeln(maxx);
    return 0;
}
