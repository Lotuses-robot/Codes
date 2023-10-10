// Copyright 2023 Lotuses
#define tsz signed
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
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

#define int long long

const int maxn = 2e6 + 10;
char ch[maxn];
bool del[maxn];

std::stack<std::pair<int, int> > st;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        while (!st.empty()) st.pop();
        scanf("%s", ch);
        int n = strlen(ch), pos, v = 0, cpos = 1, rpos = n;
        memset(del, 0, sizeof(bool) * (n + 3));
        read(pos);
        // printf("%s", ch);
        for (int i = n; i >= 1; i--) {
            v += i;
            if (v >= pos) {
                v -= i;
                for (int j = 1; j <= n; j++) {
                    if (!del[j]) v++;
                    if (v == pos) {
                        putchar(ch[j - 1]);
                        break;
                    }
                }
                break;
            }
            while (cpos <= n && (st.empty() || st.top().first <= ch[cpos - 1])) {
                st.push({ch[cpos - 1], cpos});
                cpos++;
            }
            if (cpos > n) {
                cpos = -1;
            }
            if (~cpos) {
                auto p = st.top(); st.pop();
                del[p.second] = true;
            } else {
                while (del[rpos]) rpos--;
                del[rpos] = true;
            }
            // for (int j = 1; j <= n; j++) {
            //     if (!del[j]) putchar(ch[j - 1]);
            // }
            // puts("");
        }
    }
    return 0;
}