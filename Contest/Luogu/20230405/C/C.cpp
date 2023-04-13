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
const int maxn = (int)(2e5 + 100) << 2;
const int inf = 0x3f3f3f3f3f3f3f3fll;
int n;
int c[maxn], e[maxn];
int s[maxn], t[maxn], tot = 0;

struct Tree {
    struct Node {
        int l, r, lc, rc;
        int c, x; // x mean s * c
    } nds[maxn << 2];

    int cnt = 0;
    int init(int l, int r) {
        int id = ++cnt;
        nds[id] = {l, r, -1, -1, 0, 0};
        if (l == r) return id;
        int mid = (l + r) >> 1;
        nds[id].lc = init(l, mid);
        nds[id].rc = init(mid + 1, r);
        return id;
    }

    void add(int u, int pt, int s, int c, int pos) {
        nds[u].c += c * pos; nds[u].x += c * s * pos;
        if (nds[u].l == nds[u].r) return;
        int mid = (nds[u].l + nds[u].r) >> 1;
        if (pt <= mid) add(nds[u].lc, pt, s, c, pos);
        else add(nds[u].rc, pt, s, c, pos);
    }

    int queryc(int u, int l, int r) {
        if (u == -1) return 0;
        if (l == nds[u].l && nds[u].r == r) return nds[u].c;
        int mid = (nds[u].l + nds[u].r) >> 1;
        if (r <= mid) return queryc(nds[u].lc, l, r);
        else if (l > mid) return queryc(nds[u].rc, l, r);
        else return queryc(nds[u].lc, l, mid) + queryc(nds[u].rc, mid + 1, r);
    }
    int queryx(int u, int l, int r) {
        if (u == -1) return 0;
        if (l == nds[u].l && nds[u].r == r) return nds[u].x;
        int mid = (nds[u].l + nds[u].r) >> 1;
        if (r <= mid) return queryx(nds[u].lc, l, r);
        else if (l > mid) return queryx(nds[u].rc, l, r);
        else return queryx(nds[u].lc, l, mid) + queryx(nds[u].rc, mid + 1, r);
    }

    int find() {
        int u = 1, c = 0, cpos = nds[1].c / 2;
        while (nds[u].l != nds[u].r) {
            if (c + nds[nds[u].lc].c <= cpos) {
                c += nds[nds[u].lc].c;
                u = nds[u].rc;
            } else {
                u = nds[u].lc;
            }
        }
        return nds[u].l;
    }

    int query() {
        int b = find(), qs;
        int lc = queryc(1, 1, b), rc = queryc(1, b + 1, tot);
        int lx = queryx(1, 1, b), rx = queryx(1, b + 1, tot);
        if (lc - rc != 0) qs = queryx(1, b, b) / queryc(1, b, b);
        else qs = 0;
        return (lc - rc) * qs - (lx - rx);
    }
} tr;



signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n);
    for (int i = 1; i <= n + 1; ++i) read(c[i]);
    for (int i = 1; i <= n; ++i) read(e[i]), t[++tot] = s[i] = s[i - 1] + e[i];
    e[n + 1] = -s[n]; t[++tot] = s[n + 1] = s[n] + e[n + 1];
    for (int i = 1; i <= n; i++) {
        t[++tot] = s[i] - (e[i] - e[n + 1]);
    }
    std::sort(t + 1, t + tot + 1);

    tr.init(1, tot);
    for (int i = 1; i <= n + 1; i++) {
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], 1);
    }
    int ans = inf;
    for (int i = n; i >= 1; i--) {
        ans = std::min(ans, tr.query());
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], -1);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i + 1]) - t, s[i + 1], c[i + 1], -1);
        // writeln(std::lower_bound(t + 1, t + tot + 1, s[i]) - t, tr.queryc(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, std::lower_bound(t + 1, t + tot + 1, s[i]) - t));
        s[i] -= (e[i] - e[n + 1]); std::swap(c[i], c[i + 1]);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], 1);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i + 1]) - t, s[i + 1], c[i + 1], 1);
    }
    writeln(ans);
    return 0;
}
