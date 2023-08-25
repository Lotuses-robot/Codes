// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
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

const int maxn = 1e6 + 20;
char ch[maxn];

std::map<std::pair<int, int>, bool> mp[5];
std::map<char, int> pos;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    pos['L'] = 1;
    pos['R'] = 2;
    pos['U'] = 3;
    pos['D'] = 4;

    scanf("%s", ch);
    
    int curx = 0, cury = 0, ans = 1;
    int len = strlen(ch);
    mp[0][{curx, cury}] = 1;
    
    for (int i = 0; i < len; i++) {
        char p = ch[i];
        switch(p) {
            case 'L': p = 'R'; break;
            case 'R': p = 'L'; break;
            case 'D': p = 'U'; break;
            case 'U': p = 'D'; break;
        }
        mp[pos[p]][{curx, cury}] = true;

        if (ch[i] == 'L') {
            curx--;
        } else if (ch[i] == 'R') {
            curx++;
        } else if (ch[i] == 'U') {
            cury++;
        } else if (ch[i] == 'D') {
            cury--;
        }

        if (mp[0][{curx, cury}]) {
            ans += mp[pos[ch[i]]][{curx, cury}] == 0;
        } else {
            mp[0][{curx, cury}] = 1;
        }
        mp[pos[ch[i]]][{curx, cury}] = 1;
    }
    writeln(ans);
    return 0;
}
