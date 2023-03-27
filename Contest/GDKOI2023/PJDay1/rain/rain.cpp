#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T arg) { write(arg); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

#define maxn 1000005
#define int long long

int n, q, vg, vw, vc;
// vc charactor vg groud vw rain

int f[maxn], ans[maxn], nxt[maxn];
int d[maxn], len = 0;

struct Point {
    double x, y; int isq, id; // t, dist
    bool operator < (Point b) const {
        return y < b.y;
    }
} p[maxn];

bool op(Point a, Point b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.isq || b.isq) {
        if (a.isq && b.isq) goto out;
        if (a.isq) return 0;
        else return 1;
    }
    out: return a.y < b.y;
}

bool op2(int a, int b) {
    return p[a].y < p[b].y;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, q, vg, vw, vc);

    for (int i = 1; i <= n; i++) {
        int x, y;
        read(x, y);
        p[i].x = 1.0 * y / vg;
        p[i].y = 1.0 * x + 1.0 * vw * p[i].x;
        p[i].id = i;
        // printf("%d %lf %lf\n", i, p[i].x, p[i].y);
    }

    for (int i = n + 1; i <= n + q; i++) {
        int x;
        read(x);
        p[i].x = 0;
        p[i].y = x;
        p[i].isq = i - n;
    }
    
    n += q;
    for (int i = 1; i <= n; i++) {
        double _x = p[i].x * vc - p[i].y;
        double _y = p[i].x * vc + p[i].y; 
        p[i].x = -_x;
        p[i].y = -_y;
        // printf("%d %lf %lf %d\n", i, p[i].x, p[i].y, p[i].isq);
    }

    std::sort(p + 1, p + n + 1, op);

    for (int i = 1; i <= n; i++) {
        // printf("%d %lf %lf %d\n", i, p[i].x, p[i].y, p[i].isq);
    }

    // std::multiset<std::pair<double, int> > st; 

    f[0] = 0; int ansmax = 0;
    for (int i = 1; i <= n; i++) {
        if (p[i].isq) {
            if (!len) {
                f[i] = 0;
            } else if (p[i].y > p[d[len]].y) {
                // d[++len] = p[i].y;
                f[i] = f[d[len - 1]] + 1;
                nxt[i] = d[len - 1];
            } else {
                int j = std::upper_bound(d + 1, d + len + 1, i, op2) - d;
                // d[j] = p[i].y;
                f[i] = f[d[j - 1]];
                nxt[i] = d[j - 1];
            }
        } else {
            if (len == 0 || p[i].y > p[d[len]].y) {
                d[++len] = i;
                f[i] = f[d[len - 1]] + 1;
                nxt[i] = d[len - 1];
            } else {
                int j = std::upper_bound(d + 1, d + len + 1, i, op2) - d;
                d[j] = i;
                f[i] = f[d[j - 1]] + 1;
                nxt[i] = d[j - 1];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        // printf("%d %d\n", i, f[i]);
        if (p[i].isq) {
            ans[p[i].isq] = f[i];
            // int j = i;
            // while (j) {
            //     printf("%d (%d) ", p[j].id, p[j].isq);
            //     j = nxt[j];
            // }
            // puts("");
        }
    }

    for (int i = 1; i <= q; i++) {
        writeln(ans[i]);
    }
    return 0;
}
