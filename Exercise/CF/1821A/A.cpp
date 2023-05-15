#include <cstdio>
#include <cstring>
#include <vector>
#include <cctype>

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

int pow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res *= x;
        x *= x;
        y >>= 1;
    }
    return res;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int cnt0 = 0, cnt = 0, r = 0;
        int begin0 = -1;
        char ch;
        while (ch < '0' || ch > '?') ch = getchar();
        while (ch >= '0' && ch <= '?') {
            if (ch != '?') {
                if (cnt0 == 0) cnt0 = -1;
            } else {
                if (cnt0 == 0) cnt0 = 1;
                else cnt++;
            }
            if (ch != '?') r = r * 10 + (ch ^ 48);
            else r = 100;
            if (begin0 == -1 && ch == '0') begin0 = 1;
            else if (begin0 == -1) begin0 = 0;
            ch = getchar();
            // printf("%d\n", cnt0);
        }

        if (cnt0 == -1) cnt0 = 0;
        int ans = pow(9, cnt0) * pow(10, cnt);
        printf("%d\n", r == 0 || begin0 ? 0 : ans);
    }
    return 0;
}
