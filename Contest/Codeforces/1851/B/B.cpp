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

const int maxn = 200005;
struct Node {
    int x, id;
    bool operator < (const Node b) const {
        return x < b.x;
    }
};
std::vector<Node> a, b;
std::vector<int> a1, b1;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        a.clear();
        b.clear();
        a1.clear();
        b1.clear();
        int n;
        read(n);
        for (int i = 1; i <= n; i++) {
            int r; read(r);
            if (r % 2 == 0) {
                a.push_back({r, i});
                a1.push_back(i);
            } else {
                b.push_back({r, i});
                b1.push_back(i);
            }
        }
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        int i = 0, j = 0, id = 1, last = 0; bool flag = false;
        while (i < a.size() && j < b.size()) {
            if (a1[i] == id) {
                // writeln(1, last, b[j].x);
                if (last > a[i].x) {
                    flag = true;
                    break;
                }
                last = a[i].x;
                i++;
            } else {
                // writeln(2, last, b[j].x);
                if (last > b[j].x) {
                    flag = true;
                    break;
                }
                last = b[j].x;
                j++;
            }
            id++;
        }

        if (i < a.size()) {
            if (last > a[i].x) {
                flag = true;
            }
        }

        if (j < b.size()) {
            if (last > b[j].x) {
                flag = true;
            }
        }

        if (flag) {
            puts("NO");
        } else {
            puts("YES");
        }
    }
    return 0;
}
