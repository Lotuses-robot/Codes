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
void writeln(T arg) { write(arg); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

#define maxn 100005

int n, q, vg, vw, vc;
// vc charactor vg groud vw rain

int f[maxn];
int nxt[maxn];

struct Point {
    double coor, time; int id;
} p[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen("ans.out", "w", stdout);
    #endif
    
    read(n, q, vg, vw, vc);

    for (int i = 1; i <= n; i++) {
        int x, y;
        read(x, y);
        p[i].time = 1.0 * y / vg;
        p[i].coor = 1.0 * x + 1.0 * vw * p[i].time;
        p[i].id = i;
    }
    p[0].time = 0;
    std::sort(p, p + n + 1, [](const Point &a, const Point &b) {
        return a.time < b.time;
    });

    // for (int i = 0; i <= n; i++) {
    //     printf("%d %lf %lf\n", i, p[i].coor, p[i].time);
    // }

    while (q--) {
        int r;
        read(r);
        p[0].coor = r;
        
        memset(f, -63, sizeof(f));
        f[0] = 0;

        int ans = 0, ansj;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (abs(p[i].coor - p[j].coor) <= (p[i].time - p[j].time) * vc) {
                    // f[i] = std::max(f[i], f[j] + 1);
                    // writeln(i, j, f[i], f[j]);
                    if (f[i] < f[j] + 1) {
                        f[i] = f[j] + 1;
                        nxt[i] = j;
                    }
                }
            }
            // ans = std::max(ans, f[i]);
            if (ans < f[i]) {
                ans = f[i];
                ansj = i;
            }
        }
        writeln(ans);
        while (ansj) {
            writeln(p[ansj].id);
            ansj = nxt[ansj];
        }
    }
    return 0;
}