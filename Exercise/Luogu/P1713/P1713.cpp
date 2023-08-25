// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

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

const int maxn = 21;
int mp[maxn][maxn];
int dis[maxn][maxn];
bool vis[maxn][maxn];
int dx[4] = {1, 0, -1, 0},
    dy[4] = {0, 1, 0, -1};
int n;
struct Node {
    int x, y;
    bool check() {
        if (x < 1 || y < 1 || x > n || y > n || mp[x][y]) return false;
        return true;
    }
}; std::queue<Node> q;
int bfs() {
    q.push({1, 1});
    while (!q.empty()) {
        Node e = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            Node b = e; b.x += dx[i]; b.y += dy[i];
            if (b.check() && !vis[b.x][b.y]) {
                vis[b.x][b.y] = true;
                dis[b.x][b.y] = dis[e.x][e.y] + 1;
                q.push(b);
            }
        }
    }
    return dis[n][n];
}

const int P = 299987;
int F[2][1 << maxn + 1], st[2][1 << maxn + 1], cnt[2];
int lastt[P + 10], S[2][1 << maxn + 1], nxt[1 << maxn + 1];
int now, lst, ans;
int nm[maxn];

void print(int x) {
    int cnt = 0;
    do {
        nm[++cnt] = (x % 4);
    } while (x >>= 2);
    for (int i = 5; i >= 1; i--) {
        if (i > cnt) write(0);
        else write(nm[i]);
    }
    putchar(' ');
}

void ins(int s, int f) {
    // print(s);
    // writeln(f);
    int p = s % P + 1;
    for (int i = lastt[p]; i; i = nxt[i]) {
        if (S[now][i] == s) {
            F[now][i] = std::max(F[now][i], f);
            return;
        }
    }
    nxt[++cnt[now]] = lastt[p];
    lastt[p] = cnt[now];
    S[now][cnt[now]] = s;
    F[now][cnt[now]] = f;
}

int fuck() {
    if (!mp[1][2]) ins(3 << (n - 1 << 1), 1);
    if (!mp[2][1]) ins(3 << (n << 1), 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i == 1 ? 2 : 1; j <= n; j++) {
            // puts("-------------------------");
            // writeln(i, j);
            memset(lastt, 0, sizeof(lastt));
            lst = now; now ^= 1; cnt[now] = 0;
            for (int k = 1; k <= cnt[lst]; k++) {
                int s = S[lst][k], f = F[lst][k];
                int p = (s >> (n - j + 1 << 1)) % 4, q = (s >> (n - (j + 1) + 1 << 1)) % 4;
                // write(-1); putchar(' ');
                // print(s);
                // writeln(f, p, q);
                if (mp[i][j]) {
                    if (!p && !q) ins(s, f);
                } else if (i == n && j == n) {
                    if (s == 3 || s == 3 << 2) ans = std::max(ans, f + 1);
                } else if (!p && !q) {
                    // writeln(1);
                    ins(s, f);
                    if (!mp[i + 1][j] && !mp[i][j + 1]) ins(s ^ 1 << (n - j + 1 << 1) ^ 2 << (n - (j + 1) + 1 << 1), f + 1);
                } else if (p && !q) {
                    // writeln(2);
                    if (!mp[i][j + 1]) ins(s ^ p << (n - j + 1 << 1) ^ p << (n - (j + 1) + 1 << 1), f + 1);
                    if (!mp[i + 1][j]) ins(s, f + 1);
                } else if (!p && q) {
                    // writeln(3);
                    if (!mp[i][j + 1]) ins(s, f + 1);
                    if (!mp[i + 1][j]) ins(s ^ q << (n - j + 1 << 1) ^ q << (n - (j + 1) + 1 << 1), f + 1);
                } else if (p == 2 && q == 1) {
                    // writeln(4);
                    ins(s ^ p << (n - j + 1 << 1) ^ q << (n - (j + 1) + 1 << 1), f + 1);
                } else if (p == 2 && q == 2) {
                    // writeln(5);
                    int pt = 1;
                    for (int pos = n - j + 2; pos <= n; pos++) {
                        if ((s >> (pos << 1)) % 4 == 2) ++pt;
                        if ((s >> (pos << 1)) % 4 == 1) --pt;
                        if (!pt) {
                            ins(s ^ p << (n - j + 1 << 1) ^ q << (n - (j + 1) + 1 << 1) ^ 3 << (pos << 1), f + 1);
                            break;
                        }
                    }
                } else if (p == 1 && q == 1) {
                    // writeln(6);
                    int pt = 1;
                    for (int pos = n - j - 1; pos >= 0; pos--) {
                        if ((s >> (pos << 1)) % 4 == 1) ++pt;
                        if ((s >> (pos << 1)) % 4 == 2) --pt;
                        if (!pt) {
                            ins(s ^ p << (n - j + 1 << 1) ^ q << (n - (j + 1) + 1 << 1) ^ 3 << (pos << 1), f + 1);
                            break;
                        }
                    }
                } else if (p == 2 && q == 3) {
                    // writeln(7);
                    int pt = 1;
                    for (int pos = n - j + 2; pos <= n; pos++) {
                        if ((s >> (pos << 1)) % 4 == 2) ++pt;
                        if ((s >> (pos << 1)) % 4 == 1) --pt;
                        if (!pt) {
                            ins(s ^ p << (n - j + 1 << 1) ^ q << (n - (j + 1) + 1 << 1) ^ 2 << (pos << 1), f + 1);
                            break;
                        }
                    }
                } else if (p == 3 && q == 1) {
                    // writeln(8);
                    int pt = 1;
                    for (int pos = n - j - 1; pos >= 0; pos--) {
                        if ((s >> (pos << 1)) % 4 == 1) ++pt;
                        if ((s >> (pos << 1)) % 4 == 2) --pt;
                        if (!pt) {
                            ins(s ^ p << (n - j + 1 << 1) ^ q << (n - (j + 1) + 1 << 1) ^ 1 << (pos << 1), f + 1);
                            break;
                        }
                    }
                }
            }
        }
        for (int j = 1; j <= cnt[now]; j++) S[now][j] >>= 2;
    }
    return ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        mp[n - x + 1][y] = 1;
    }

    for (int i = 1; i <= n + 1; i++) mp[n + 1][i] = mp[i][n + 1] = 1;
    for (int i = 1; i <= n; i++) mp[0][i] = mp[i][0] = 1;
    int min = bfs();
    int max = fuck();
    
    writeln(max - min - 1);
    return 0;
}
