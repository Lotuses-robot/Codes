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

#define int long long

int n, m, k, r;

struct Node {
    int p, c, id;
    bool operator < (const Node b) const {
        int ap, bp;
        if (c == 1) ap = 2 * p; else ap = p + k;
        if (b.c == 1) bp = 2 * b.p; else bp = b.p + k;
        return ap - p > bp - b.p;
    }
};
std::vector<Node> v;
std::vector<Node> f, c;
bool vis[3][1000006];

signed main() {
    #ifdef LOCAL
        freopen("data/genshin4.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m, k);
    for (int i = 1; i <= n; i++) {
        read(r);
        v.push_back({r, 1, i});
        f.push_back({r, 1, i});
    }
    for (int i = 1; i <= m; i++) {
        read(r);
        v.push_back({r, 2, i});
        c.push_back({r, 2, i});
    }
    std::sort(v.begin(), v.end());
    std::sort(f.begin(), f.end());
    std::sort(c.begin(), c.end());

    int ans = 0, fi = n - 1, ci = m - 1;
    for (int i = 0; i < n + m; i++) {
        if (vis[v[i].c][v[i].id]) continue;
        if (v[i].c == 1) {
            while (ci >= 0 && vis[2][c[ci].id]) ci--;
            if (ci >= 0) {
                ans += c[ci].p;
                ans += v[i].p * 2;
                vis[1][v[i].id] = vis[2][c[ci].id] = true;
                // printf("2%d 1%d ", c[ci].id, v[i].id);
                ci--;
            } else {
                break;
            }
        } else {
            while (fi >= 0 && vis[1][f[fi].id]) fi--;
            if (fi >= 0) {
                ans += f[fi].p;
                ans += v[i].p + k;
                vis[1][f[fi].id] = vis[2][v[i].id] = true;
                // printf("1%d 2%d ", f[fi].id, v[i].id);
                fi--;
            } else {
                break;
            }
        }
    }

    while (fi >= 0) {
        if (vis[1][f[fi].id]) goto fk;
        ans += f[fi].p;
        // printf("1%d ", f[fi].id);
        fk: fi--;
    }

    while (ci >= 0) {
        if (vis[2][c[ci].id]) goto fk2;
        ans += c[ci].p;
        // printf("2%d ", c[ci].id);
        fk2: ci--;
    }

    writeln(ans);
    return 0;
}
