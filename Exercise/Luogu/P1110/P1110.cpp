// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <cctype>
#include <algorithm>

char buf[1<<25],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<25,stdin),p1==p2)?EOF:*p1++)

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

void reads(char *s) {
    while ((*s = getchar()) < 56); s++;
    while ((*s = getchar()) >= 56) s++;
}

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 1e6 + 10;
// #define int long long

template<typename T>
struct splay {
    struct Node {
        int ch[2], fa, val, cnt, sz;
    } nd[maxn];
    int rt, cnt;

    splay() { rt = -1; cnt = 0; }

    #define lc (nd[u].ch[0])
    #define rc (nd[u].ch[1])
    // #define f (nd[u].fa)
    
    private:
    int create(int fa, T val) {
        int u = ++cnt;
        lc = rc = -1;
        nd[u].fa = fa;
        nd[u].val = val; nd[u].cnt = 1;
        return u;
    }

    int pre() {
        int u = nd[rt].ch[0];
        while (~rc) u = rc;
        play(u);
        return u;
    }

    void upd(int u) {
        if (!(~u)) return;
        nd[u].sz = nd[u].cnt;
        if (~lc) nd[u].sz += nd[lc].sz;
        if (~rc) nd[u].sz += nd[rc].sz;
    }

    int get(int u) {
        if (!(~u)) return -1; // or true
        return nd[nd[u].fa].ch[1] == u;
    }

    void rotate(int x) {
        if (!(~x)) return;
        int y = nd[x].fa, z = nd[y].fa, st = get(x), sty = get(y);
        if (~z) nd[z].ch[sty] = x;
        nd[x].fa = z;
        nd[y].ch[st] = nd[x].ch[st ^ 1];
        if (~nd[y].ch[st]) nd[nd[y].ch[st]].fa = y;
        nd[y].fa = x;
        nd[x].ch[st ^ 1] = y;
        upd(y);
        upd(x);
    }

    void play(int u, int goal = -1) {
        if (!(~u)) return;
        for (int f = nd[u].fa; f != goal; f = nd[u].fa) {
            if (nd[f].fa != goal) rotate(get(u) == get(f) ? f : u);
            rotate(u);
        }
        if (!(~goal)) rt = u;
    }

    public:
    void clear() {
        rt = -1;
        cnt = 0;
    }

    void ins(T k) {
        if (!(~rt)) {
            rt = create(-1, k);
            upd(rt);
        } else {
            int u = rt, f = -1, ch;
            while (true) {
                if (nd[u].val == k) {
                    nd[u].cnt++;
                    upd(u); upd(f);
                    play(u);
                    return;
                }
                f = u;
                ch = nd[f].val < k;
                u = nd[f].ch[ch];
                if (!(~u)) {
                    nd[f].ch[ch] = create(f, k);
                    u = nd[f].ch[ch];
                    upd(u); upd(f);
                    play(u);
                    return;
                }
            }
        }
    }

    int rnk(T k) {
        int res = 0, u = rt;
        while (true) {
            if (k < nd[u].val) {
                if (!(~lc)) { play(u); return res + 1; }
                u = lc;
            } else {
                if (~lc) res += nd[lc].sz;
                if (nd[u].val < k) {
                    res += nd[u].cnt;
                    if (!(~rc)) { play(u); return res + 1; }
                    u = rc;
                } else {
                    play(u);
                    return res + 1;
                }
            }
        }
    }

    T kth(int k) {
        int u = rt;
        while (true) {
            if ((~lc) && k <= nd[lc].sz) {
                u = lc;
            } else {
                if (~lc) k -= nd[lc].sz;
                k -= nd[u].cnt;
                if (k <= 0) {
                    play(u);
                    return nd[u].val;
                }
                u = rc;
            }
        }
    }

    void del(T k) {
        rnk(k);
        if (nd[rt].cnt > 1) {
            nd[rt].cnt--;
            upd(rt);
            return;
        }
        int u = rt;
        if ((!(~lc)) && (!(~rc))) {
            clear();
        } else if (!(~lc)) {
            rt = rc;
            nd[rt].fa = -1;
        } else if (!(~rc)) {
            rt = lc;
            nd[rt].fa = -1;
        } else {
            pre();
            nd[rc].fa = rt;
            nd[rt].ch[1] = rc;
            upd(rt);
        }
    }

    int pre(T x) {
        ins(x);
        int u = nd[rt].ch[0];
        if (!(~u)) return -1e9;
        while (~rc) u = rc;
        del(x);
        play(u);
        return nd[u].val;
    }

    int suf(T x) {
        ins(x);
        int u = nd[rt].ch[1];
        if (!(~u)) return 1e9;
        while (~lc) u = lc;
        del(x);
        play(u);
        return nd[u].val;
    }

    void print(int u = -1) {
        if (u == -1) u = rt;
        if (~lc) {
            writeln(u, lc);
            print(lc);
        }
        if (~rc) {
            writeln(u, rc);
            print(rc);
        }
    }

    void printarr(int u = -1) {
        if (u == -1) u = rt;
        if (~lc) printarr(lc);
        printf("[%d,%dt] ", nd[u].val, nd[u].cnt);
        if (~rc) printarr(rc);
    }
};
splay<int> sp1, sp2;

inline int abs(int a, int b) {
    return a - b > 0 ? a - b : b - a;
}
inline int min(int a, int b) {
    return a < b ? a : b;
}

int a[maxn], b[maxn];
std::vector<int> c;
char ch[20];

tsz main() {
    #ifdef LOCAL
        freopen("P1110_2.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m, ans2 = 1e9;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]); b[i] = a[i];
        c.push_back(a[i]);
        sp2.ins(a[i]);
    }
    std::sort(c.begin(), c.end());
    for (int i = 2; i <= n; i++) {
        sp1.ins(abs(a[i] - a[i - 1]));
        ans2 = min(ans2, abs(c[i - 1] - c[i - 2]));
    }

    while (m--) {
        reads(ch);
        if (ch[0] == 'I') {
            int i, k;
            read(i, k);
            if (i < n) {
                sp1.del(abs(b[i] - a[i + 1]));
                sp1.ins(abs(b[i] - k));
                sp1.ins(abs(k - a[i + 1]));
            } else {
                sp1.ins(abs(b[i] - k));
            }
            // writeln(sp2.rnk(k), sp2.rnk(k + 1));
            if (sp2.rnk(k) < sp2.rnk(k + 1)) {
                ans2 = 0;
            } else {
                ans2 = min(ans2, min(abs(sp2.pre(k) - k), abs(sp2.suf(k) - k)));
                sp2.ins(k);
            }
            b[i] = k;
        } else {
            if (ch[4] == 'G') {
                writeln(sp1.kth(1));
            } else {
                writeln(ans2);
            }
        }
    }
    return 0;
}