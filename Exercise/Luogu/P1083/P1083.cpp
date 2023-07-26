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

const int maxn = 1000006;
int r[maxn];
int d[maxn], s[maxn], t[maxn];

#define maxn 4000006
#define max(a, b) ((a) > (b) ? (a) : (b))
template <typename T> struct segmt {
    struct tree {
        int l, r, lc, rc;
        T lazy2, ansMax;
    } tr[2 * maxn];
    T a[maxn];
    int tot, n;
    inline int bt(int l, int r) {
        int pos = ++tot;
        tr[pos].l = l;
        tr[pos].r = r;
        tr[pos].lazy2 = 0;
        if (l == r) {
            tr[pos].lc = tr[pos].rc = -1;
            tr[pos].ansMax = a[l];
        } else {
            tr[pos].lc = bt(l, l + r >> 1);
            tr[pos].rc = bt((l + r >> 1) + 1, r);
            tr[pos].ansMax = std::min(tr[tr[pos].lc].ansMax, tr[tr[pos].rc].ansMax);
        }
        return pos;
    }
    inline void update(int pos) {
        if (tr[pos].lazy2) {
            change(tr[pos].lc, tr[tr[pos].lc].l, tr[tr[pos].lc].r, tr[pos].lazy2);
            change(tr[pos].rc, tr[tr[pos].rc].l, tr[tr[pos].rc].r, tr[pos].lazy2);
            tr[pos].lazy2 = 0;
        }
        tr[pos].ansMax = std::min(tr[tr[pos].lc].ansMax, tr[tr[pos].rc].ansMax);
    }
    inline void change(int pos, int l, int r, T x) {
        if (tr[pos].l == l && tr[pos].r == r) {
            tr[pos].lazy2 = (tr[pos].lazy2 + x);
            tr[pos].ansMax += x;
            return;
        }
        update(pos);
        if (r <= tr[tr[pos].lc].r)
            change(tr[pos].lc, l, r, x);
        else if (l >= tr[tr[pos].rc].l)
            change(tr[pos].rc, l, r, x);
        else {
            change(tr[pos].lc, l, tr[tr[pos].lc].r, x);
            change(tr[pos].rc, tr[tr[pos].rc].l, r, x);
        }
        tr[pos].ansMax = std::min(tr[tr[pos].lc].ansMax, tr[tr[pos].rc].ansMax);
    }
    inline int query2(int pos, int l, int r) {
        if (tr[pos].l == l && r == tr[pos].r)
            return tr[pos].ansMax;
        update(pos);
        if (r <= tr[tr[pos].lc].r)
            return query2(tr[pos].lc, l, r);
        else if (l >= tr[tr[pos].rc].l)
            return query2(tr[pos].rc, l, r);
        else
            return std::min(query2(tr[pos].lc, l, tr[tr[pos].lc].r), 
                            query2(tr[pos].rc, tr[tr[pos].rc].l, r));
    }
};
segmt<int> sg;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(r[i]);
        sg.a[i] = r[i];
    }
    sg.n = n;
    sg.bt(1, n);
    for (int i = 1; i <= m; i++) {
        read(d[i], s[i], t[i]);
        sg.change(1, s[i], t[i], -d[i]);
        int res = sg.query2(1, 1, n);
        // writeln(res);
        if (res < 0) {
            puts("-1");
            writeln(i);
            return 0;
        }
    }
    puts("0");
    return 0;
}
