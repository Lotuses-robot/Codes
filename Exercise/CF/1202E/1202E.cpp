// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
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

const int maxn = 4e5 + 5;
struct AC {
    struct Node {
        int nxt[26], fail, fa, sum, failsum;
    } nd[maxn];
    int cnt;
    void init() {
        memset(nd, 0, sizeof(nd));
        cnt = 0;
    }
    void ins(char *ch) {
        int len = strlen(ch);
        int u = 0;
        for (int i = 0; i < len; i++) {
            if (!nd[u].nxt[ch[i] - 'a']) {
                nd[u].nxt[ch[i] - 'a'] = ++cnt;
                nd[cnt].fa = u;
            }
            u = nd[u].nxt[ch[i] - 'a'];
        }
        nd[u].sum++;
    }
    void build() {
        std::queue<int> q;
        for (int i = 0; i < 26; i++) {
            int v = nd[0].nxt[i];
            if (v) q.push(v), nd[v].failsum = nd[v].sum;
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            auto &d = nd[u];
            for (int i = 0; i < 26; i++) {
                int &v = nd[u].nxt[i];
                if (v) {
                    auto &e = nd[v];
                    e.fail = nd[d.fail].nxt[i];
                    nd[v].failsum = nd[nd[v].fail].failsum + nd[v].sum;
                    q.push(v);
                } else {
                    v = nd[d.fail].nxt[i];
                }
            }
        }
    }
    int f[maxn];
    void query(char *ch) {
        int u = 0;
        for (int i = 0, len = strlen(ch); i < len; i++) {
            u = nd[u].nxt[ch[i] - 'a'];
            f[i] = nd[u].failsum;
            // write(f[i]); putchar(' ');
        }
        // puts("");
    }
} a, b;

int n;
char ch[maxn], chr[maxn], r[maxn], rr[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int len;
    scanf("%s", ch);
    strcpy(chr, ch);
    std::reverse(chr, chr + (len = strlen(chr)));
    a.init(); b.init();
    read(n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", r);
        strcpy(rr, r);
        std::reverse(rr, rr + strlen(rr));
        a.ins(r); b.ins(rr);
    }
    a.build(); b.build();
    a.query(ch); b.query(chr);

    int ans = 0;
    for (int i = 0; i < len - 1; i++) {
        ans += a.f[i] * b.f[len - i - 2];
    }
    writeln(ans);
    return 0;
}
