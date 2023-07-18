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
std::vector<int> vb[maxn];
std::vector<int> vs;
std::vector<int> vl[maxn];
std::vector<int> vr[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T, r, ans = 0;
    read(T);
    while (T--) {
        int n, m;
        read(n, m);
        if (n <= m) {
            for (int i = 1; i <= n; i++) {
                v[i].clear(); v[i].push_back(0); // init to 1
                vl[i].clear(); vr[i].clear();
            }
        } else {
            for (int i = 1; i <= m; i++) {
                v[i].clear(); v[i].push_back(0); // init to 1
                vl[i].clear(); vr[i].clear();
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                read(r);
                if (n <= m) {
                    v[i].push_back(r);
                } else {
                    v[j].push_back(r);
                }
                // write(v[i][j]); putchar(' ');
            }
            // puts("");
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                read(r);
                if (n <= m) {
                    v[i][j] -= r;
                } else {
                    v[j][i] -= r;
                }
                // write(v[i][j]); putchar(' ');
            }
            // puts("");
            vb[i] = v[i];
        }
        if (n > m) std::swap(n, m);
        
        int ansl = 0, ansr = 0; ans = 0;
        for (int i = 1; i <= n; i++) {
            vs = v[i];
            std::sort(vs.begin() + 1, vs.end());

            if (m & 1) {
                int minn = vs[m / 2 + 1];
                for (int j = 1; j <= m; j++) {
                    v[i][j] -= minn;
                    // write(v[i][j]); putchar(' ');
                }
                // puts("");
                ans += abs(minn);
            } else {
                int minn = vs[m / 2];
                vl[i].push_back(0);
                for (int j = 1; j <= m; j++) {
                    vl[i].push_back(v[i][j] - minn);
                }
                ansl += abs(minn);

                minn = vs[m / 2 + 1];
                vr[i].push_back(0);
                for (int j = 1; j <= m; j++) {
                    vr[i].push_back(v[i][j] - minn);
                }
                ansr += abs(minn);
            }
        }

        if (m & 1) {
            for (int j = 1; j <= m; j++) {
                int eq = v[1][j];
                for (int i = 2; i <= n; i++) {
                    if (eq != v[i][j]) {
                        ans = -1; break;
                    }
                }
                if (ans == -1) break;
                ans += abs(eq);
            }
            writeln(ans);
        } else {
            for (int j = 1; j <= m; j++) {
                int eq = vl[1][j];
                for (int i = 2; i <= n; i++) {
                    if (eq != vl[i][j]) {
                        ansl = -1; break;
                    }
                }
                if (ansl == -1) break;
                ansl += abs(eq);
            }
            
            for (int j = 1; j <= m; j++) {
                int eq = vr[1][j];
                for (int i = 2; i <= n; i++) {
                    if (eq != vr[i][j]) {
                        ansr = -1; break;
                    }
                }
                if (ansr == -1) break;
                ansr += abs(eq);
            }


            if (ansl == -1 && ansr == -1) {
                puts("-1");
            } else if (ansl == -1) {
                writeln(ansr);
            } else if (ansr == -1) {
                writeln(ansl);
            } else {
                writeln(std::min(ansl, ansr));
            }
        }
    }
    return 0;
}
