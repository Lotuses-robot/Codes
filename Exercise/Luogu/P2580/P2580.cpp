// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>

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

struct Trie {
    struct Node {
        int cnt;
        int sons[26];
    } nd[1000001];
    int cnt;
    void init() {
        cnt = 1;
        // memset(nd, 0, sizeof(nd));
    }
    int insert(std::string s, int p = 1) {
        int cur = 1;
        for (int i = 0; i < s.length(); i++) {
            if (nd[cur].sons[s[i] - 'a']) {
                cur = nd[cur].sons[s[i] - 'a'];
            } else {
                if (p == 0) return 0;
                ++cnt;
                nd[cur].sons[s[i] - 'a'] = cnt;
                cur = cnt;
            }
        }
        nd[cur].cnt += p;
        return nd[cur].cnt;
    }
} stu, rel;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    stu.init();
    rel.init();
    int n; std::string s;
    read(n);
    for (int i = 1; i <= n; i++) {
        std::cin >> s;
        stu.insert(s);
    }
    read(n);
    for (int i = 1; i <= n; i++) {
        std::cin >> s;
        int re = stu.insert(s, 0);
        if (!re) {
            puts("WRONG");
        } else {
            if (rel.insert(s) == 1) {
                puts("OK");
            } else {
                puts("REPEAT");
            }
        }
    }
    return 0;
}
