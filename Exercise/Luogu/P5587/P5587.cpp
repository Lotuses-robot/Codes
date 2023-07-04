// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

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

std::vector<std::string> s;
int mem[1003];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    std::string t;
    std::getline(std::cin, t);
    while (t != "EOF") {
        s.push_back(t);
        std::getline(std::cin, t);
    }

    int cnt = 0, ans = 0;
    std::getline(std::cin, t);
    while (t != "EOF") {
        int i = 0, j = 0;
        while (i < t.length() && (j < s[cnt].length() || t[i] == '<')) {
            if (t[i] == '<') {
                j -= 2; if (j < -1) j = 0;
                mem[j] = 0;
            } else {
                mem[j] = t[i] == s[cnt][j];
            }
            i++; j++;
        }
        for (int i = 0; i < s[cnt].length(); i++) {
            ans += mem[i]; mem[i] = 0;
        }
        cnt++;
        std::getline(std::cin, t);
        // writeln(ans);
    }

    int tt;
    read(tt);

    printf("%d\n", int(floor(ans * 60.0 / tt + 0.50000001)));
    return 0;
}
