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

#define int long long

const int maxn = 1ll << 15;
const int P = 299987;
int n;
int head[P + 20], nxt[maxn], F[2][maxn], S[2][maxn], cnt[2];
int now, lst;

int m[maxn];
void print(int x) {
    int cnt = 0;
    do {
        m[cnt++] = x % 8;
    } while (x >>= 3);
    for (int i = 1; i <= 6; i++) {
        if (i >= cnt) write(0);
        else write(m[i]);
    }
    putchar(' ');
}

void add(int s, int f) {
    // print(s); writeln(f);
    int r = s % P + 1;
    for (int i = head[r]; i; i = nxt[i]) {
        if (S[now][i] == s) {
            F[now][i] = std::max(F[now][i], f);
            return;
        }
    }
    nxt[++cnt[now]] = head[r];
    head[r] = cnt[now];
    F[now][cnt[now]] = f;
    S[now][cnt[now]] = s;
}

int mp[9], idx = 0, ans = -2e9;
int cline(int s, int f) {
    memset(mp, 0, sizeof(mp));
    // print(s); puts("fk");
    idx = 0;
    for (int j = 1; j <= n; j++) {
        int r = (s >> 3 * j) % (1 << 3);
        // writeln(r);
        if (!r) continue;
        if (!mp[r]) {
            mp[r] = ++idx;
            // writeln(r, mp[r]);
        }
        s ^= (r << 3 * j) ^ (mp[r] << 3 * j);
    }
    if (idx == 1 && ans < f) ans = f;
    return s;
}

bool check(int s, int p) {
    int cnt = 0;
    for (int j = 1; j <= n; j++) {
        cnt += ((s >> 3 * j) % (1 << 3) == p);
    }
    return cnt > 1;
}

signed main() {
    #ifdef LOCAL
        freopen("data.in", "r", stdin);
        freopen("data.out", "w", stdout);
    #endif

    read(n);
    add(0, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x; read(x);
            lst = now; now ^= 1; cnt[now] = 0;
            memset(head, 0, sizeof(head));
            for (int k = 1; k <= cnt[lst]; k++) {
                int f = F[lst][k], s = S[lst][k];
                // puts("----------------");
                // writeln(i, j);
                // write(k); putchar(' '); print(s); writeln(f);
                int p1 = 0, p2 = (s >> 3 * j) % (1 << 3);
                if (j != 1) p1 = (s >> 3 * (j - 1)) % (1 << 3);
                if (!p1 && !p2) {
                    // puts("1");
                    add(cline(s, f), f);
                    add(cline(s ^ 7ll << 3 * j, f + x), f + x);
                } else if (p1 && !p2) {
                    // puts("2");
                    add(cline(s, f), f);
                    add(cline(s ^ p1 << 3 * j, f + x), f + x);
                } else if (!p1 && p2) {
                    // puts("3");
                    if (check(s, p2)) add(cline(s ^ p2 << 3 * j, f), f);
                    add(cline(s, f + x), f + x);
                } else {
                    // puts("4");
                    if (check(s, p2)) add(cline(s ^ p2 << 3 * j, f), f);
                    if (p1 != p2) {
                        for (int z = 1; z <= n; z++) {
                            int r = (s >> 3 * z) % (1 << 3);
                            if (r == p2) s ^= p1 << 3 * z ^ p2 << 3 * z;
                        }
                    }
                    add(cline(s, f + x), f + x);
                }
            }
        }
    }
    writeln(ans);
    return 0;
}
