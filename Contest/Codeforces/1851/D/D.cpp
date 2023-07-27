// Copyright 2023 Lotuses
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

#define int long long

const int maxn = 400005;
int cnt[maxn << 1];
std::vector<int> clr;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        for (auto e : clr) {
            cnt[e] = 0;
        }
        clr.clear();
        int n, last = 0, flag = false;
        read(n);
        for (int i = 1; i < n; i++) {
            int r; read(r);
            if (flag) {
                continue;
            }
            if (r - last > 2 * n) {
                flag = true;
                continue;
            }
            // writeln(r - last);
            cnt[r - last]++;
            clr.push_back(r - last);
            last = r;
        }
        if (flag) {
            puts("NO");
            continue;
        }
        int que = -1, v0[2] = {-1, -1};
        for (int i = 1; i <= 2 * n; i++) {
            if (cnt[i] == 0) {
                if (v0[0] == -1) v0[0] = i;
                else if (v0[1] == -1) v0[1] = i;
                else if (i >= 1 && i <= n) {
                    flag = true;
                }
            }
            if (cnt[i] > 1 || (cnt[i] && i > n)) {
                if (que == -1) que = i;
                else flag = true;
            }
        }
        // writeln(que, v0[0], v0[1]);
        if (flag) {
            puts("NO");
            continue;
        }

        if (que == -1) {
            puts("YES");
        } else {
            if (que == v0[0] + v0[1]) {
                puts("YES");
            } else {
                puts("NO");
            }
        }
    }
    return 0;
}
