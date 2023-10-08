// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

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

const int maxn = 1e5 + 10;
std::string s[maxn];
char ch[maxn];
std::map<std::string, bool> mp;
std::vector<std::string> v;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", ch);
        s[i] = ch;
    }

    std::sort(s + 1, s + n + 1, [] (std::string a, std::string b) {
        if (a.length() != b.length()) return a.length() < b.length();
        else return a < b;
    });
    
    int ans = 0, i, lvl = 1;
    for (i = 1; i <= n; i++) {
        if (s[i].length() <= lvl) {
            ans = 1;
            mp[s[i]] = true;
        } else {
            lvl++;
            break;
        }
    }
    for (i; i <= n; i++) {
        if (s[i].length() <= lvl) {
            // printf("%s %s\n", s[i].substr(0, s[i].length() - 1).c_str(), s[i].substr(1).c_str());
            if (mp[s[i].substr(0, s[i].length() - 1)] && mp[s[i].substr(1)]) {
                v.push_back(s[i]);
                ans = lvl;
            }
        } else {
            mp.clear();
            if (v.empty()) break;
            for (auto e : v) {
                mp[e] = true;
            }
            v.clear();
            lvl++; i--;
        }
    }
    writeln(ans);
    return 0;
}