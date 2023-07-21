// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
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

#define int long long
#define abs(a) ((a) >= 0 ? (a) : -(a))

const int maxn = 100005;
int n, m;
std::vector<int> v[maxn];
int a[maxn], b[maxn];
std::vector<int> vs;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T, r;
    read(T);
    while (T--) {
        int n, m;
        read(n, m);
        for (int i = 1; i <= n; i++) {
            v[i].clear();
            v[i].push_back(0);
            for (int j = 1; j <= m; j++) {
                read(r);
                v[i].push_back(r);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                read(r);
                v[i][j] -= r;
            }
        }
        // check -1
        
        a[1] = 0;
        b[1] = -v[1][1] - a[1];
        for (int i = 2; i <= n; i++) {
            a[i] = -v[i][1] - b[1];
        }
        for (int j = 2; j <= m; j++) {
            b[j] = -v[1][j] - a[1];
        }
        bool flag = false;
        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= m; j++) {
                if (-v[i][j] != a[i] + b[j]) {
                    flag = true;
                    break;
                }
            }
        }
        if (flag) {
            puts("-1");
            continue;
        }

        vs.clear();
        for (int i = 1; i <= n; i++) {
            vs.push_back(a[i]);
        }
        for (int j = 1; j <= m; j++) {
            vs.push_back(-b[j]);
        }

        std::sort(vs.begin(), vs.end());

        int mid = vs[(n + m) / 2];
        int ans = 0;
        for (int val : vs) {
            ans += abs(val - mid);
        }
        writeln(ans);
    }
    return 0;
}
