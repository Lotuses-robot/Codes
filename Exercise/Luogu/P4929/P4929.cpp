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

const int maxn = 1e5 + 10;
struct DLX {
    struct Node {
        int l, r, u, d, R, C;
    } nd[maxn];
    int first[maxn], siz[maxn];
    int n, m, cnt;
    
    void build() {
        for (int i = 0; i <= m; i++) {
            nd[i].l = i - 1; nd[i].r = i + 1;
            nd[i].u = i; nd[i].d = i;
        }
        nd[0].l = m; nd[m].r = 0; cnt = m;
        memset(first, 0, sizeof(first));
        memset(siz, 0, sizeof(siz));
    }

    void insert(int r, int c) {
        cnt++;
        nd[cnt].R = r; nd[cnt].C = c;
        // c <-> cnt <-> u
        nd[cnt].u = nd[c].u;
        nd[cnt].d = c;
        nd[nd[cnt].u].d = cnt;
        nd[nd[cnt].d].u = cnt;
        if (first[r] == 0) {
            nd[cnt].l = cnt;
            nd[cnt].r = cnt;
            first[r] = cnt;
        } else {
            // l <-> cnt <-> first
            nd[cnt].l = nd[first[r]].l;
            nd[cnt].r = first[r];
            nd[nd[cnt].l].r = cnt;
            nd[nd[cnt].r].l = cnt;
        }
        siz[c]++;
    }

    void remove(int c) {
        for (int i = nd[c].d; i != c; i = nd[i].d) {
            for (int j = nd[i].r; j != i; j = nd[j].r) { // remove this c only need to solve nd[c]'s link 
                nd[nd[j].d].u = nd[j].u;
                nd[nd[j].u].d = nd[j].d;
                siz[nd[j].C]--;
            }
        }
        nd[nd[c].l].r = nd[c].r;
        nd[nd[c].r].l = nd[c].l;
    }

    void resume(int c) {
        nd[nd[c].l].r = c;
        nd[nd[c].r].l = c;
        for (int i = nd[c].d; i != c; i = nd[i].d) {
            for (int j = nd[i].r; j != i; j = nd[j].r) { // resume this c only need to solve nd[c]'s link 
                nd[nd[j].d].u = j;
                nd[nd[j].u].d = j;
                siz[nd[j].C]++;
            }
        }
    }

    int ans[maxn];

    bool dance(int dep) {
        if (nd[0].r == 0) {
            // print ans
            for (int i = 1; i <= dep - 1; i++) write(ans[i]), putchar(' ');
            puts("");
            return true;
        }
        int cn = nd[0].r;
        for (int i = cn; i != 0; i = nd[i].r) {
            if (siz[i] < siz[cn]) {
                cn = i;
            }
        }
        remove(cn);
        for (int i = nd[cn].d; i != cn; i = nd[i].d) {
            ans[dep] = nd[i].R;
            for (int j = nd[i].r; j != i; j = nd[j].r) {
                remove(nd[j].C);
            }
            if (dance(dep + 1)) return true;
            for (int j = nd[i].r; j != i; j = nd[j].r) {
                resume(nd[j].C);
            }
        }
        resume(cn);
        return false;
    }
} dlx;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(dlx.n, dlx.m);
    dlx.build();
    for (int i = 1; i <= dlx.n; i++) {
        for (int j = 1; j <= dlx.m; j++) {
            static int x;
            read(x);
            if (x) dlx.insert(i, j);
        }
    }

    if (!dlx.dance(1)) puts("No Solution!");
    return 0;
}
