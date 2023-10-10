// Copyright 2023 Lotuses
#define tsz signed
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

const int maxn = 1e6 + 10;
char ch[maxn];

int ans, ans1 = 0, ans2 = 0, jmp;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    scanf("%s", ch); int n = strlen(ch);
    for (int i = 0; i < n; i++) {
        if (jmp) {
            if (ch[i] == '(') {
                int x = 1;
                while (x) {
                    i++;
                    if (ch[i] == ')') x--;
                    if (ch[i] == '(') x++;
                }
            } else if (jmp == 1 && ch[i] == '|') {
                jmp = 0;
            } else if (ch[i] == ')') {
                jmp = 0;
            } else if (jmp == 1 && ch[i] == '&') {
                ans1++;
            } else if (jmp == 2 && ch[i] == '|') {
                ans2++;
            }
        } else {
            if (ch[i] == '0') {
                ans = 0;
            } else if (ch[i] == '1') {
                ans = 1;
            } else if (ch[i] == '&' && !ans) {
                jmp = 1;
                ans1++;
            } else if (ch[i] == '|' && ans) {
                jmp = 2;
                ans2++;
            }
        }
    }
    writeln(ans);
    writeln(ans1, ans2);
    return 0;
}