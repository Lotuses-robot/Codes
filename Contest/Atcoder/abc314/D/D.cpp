// Copyright 2023 Lotuses
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

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 5e5 + 10;
char ch[maxn];

struct op {
    int t, x; char c;
};
std::vector<op> vv;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, T, last = 0;
    read(n);
    scanf("%s", ch + 1);
    read(T);
    while (T--) {
        int t, x; char c;
        scanf("%d %d %c", &t, &x, &c);
        vv.push_back({t, x, c});
        if (t == 1) {
            ch[x] = c;
        } else if (t == 2) {
            last = 2;
            vv.clear();
        } else if (t == 3) {
            last = 3;
            vv.clear();
        }
    }
    if (last == 2) {
        for (int i = 1; i <= n; i++) {
            ch[i] = tolower(ch[i]);
        }
    } else if (last == 3) {
        for (int i = 1; i <= n; i++) {
            ch[i] = toupper(ch[i]);
        }
    }
    for (auto i : vv) {
        ch[i.x] = i.c;
    }
    printf("%s\n", ch + 1);
    return 0;
}
