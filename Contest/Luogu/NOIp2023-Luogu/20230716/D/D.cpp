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

int n, m, v, r;
std::vector<std::vector<int> > vec;

bool check() {
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (vec[i][0] != i) {
            flag = false;
        }
        // write(vec[i][0]); putchar(' ');
    }
    // puts("");
    return flag;
}

int calc() {
    int ans = 0;
    for (int i1 = 0; i1 < n; i1++) {
        for (int j1 = 1; j1 <= m; j1++) {
            for (int i2 = i1; i2 < n; i2++) {
                for (int j2 = j1; j2 <= m; j2++) {
                    int maxx = vec[i1][j1], minn = vec[i1][j1];
                    for (int x = i1; x <= i2; x++) {
                        for (int y = j1; y <= j2; y++) {
                            maxx = std::max(maxx, vec[x][y]);
                            minn = std::min(minn, vec[x][y]);
                        }
                    }
                    ans += (maxx ^ minn) == v;
                }
            }
        }
    }
    return ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m, v);
    for (int i = 0; i < n; i++) {
        static std::vector<int> vs;
        vs.clear();
        vs.push_back(i);
        for (int j = 0; j < m; j++) {
            read(r);
            vs.push_back(r);
        }
        vec.push_back(vs);
    }
    int ans = 0;
    while (true) {
        std::next_permutation(vec.begin(), vec.end());
        ans += calc();
        if (check()) {
            break;
        }
    }
    writeln(ans);
    return 0;
}
