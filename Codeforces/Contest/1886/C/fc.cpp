// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

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

std::vector<std::string> tr;

std::string calc(std::string s) {
    tr.clear();
    for (int i = 0; i < s.length(); i++) {
        tr.push_back(s.substr(i, i) + s.substr(i + 1));
    }
    std::sort(tr.begin(), tr.end(), [] (std::string a, std::string b) {
        for (int i = 0; i < std::min(a.length(), b.length()); i++) {
            if (a[i] != b[i]) return a[i] < b[i];
        }
        return a.length() < b.length();
    });
    return *tr.begin();
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        std::string s, e = s;
        std::cin >> s;
        for (int i = s.length() - 1; i >= 1; i--) {
            s = calc(s);
            e += s;
        }
        std::cout << e << '\n';
    }
    return 0;
}