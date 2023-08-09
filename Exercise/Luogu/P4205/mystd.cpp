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

std::vector<std::pair<int, int> > v[100] = {
    // A
    { {1, 1}, {1, 0}, {0, 1} },
    { {0, 0}, {1, 0}, {1, 1} },
    { {0, 0}, {1, 0}, {0, 1} },
    { {0, 0}, {0, 1}, {1, 1} },

    // B
    { {0, 0}, {0, 1}, {0, 2}, {0, 3} },
    { {0, 0}, {1, 0}, {2, 0}, {3, 0} },

    // C
    { {0, 0}, {0, 1}, {0, 2}, {1, 0} },
    { {0, 0}, {0, 1}, {1, 1}, {2, 1} },
    { {1, 0}, {1, 1}, {1, 2}, {0, 2} },
    { {0, 0}, {1, 0}, {2, 0}, {2, 1} },
    { {0, 0}, {0, 1}, {0, 2}, {1, 2} },
    { {0, 1}, {1, 1}, {2, 1}, {2, 0} },
    { {0, 0}, {1, 0}, {1, 1}, {1, 2} },
    { {0, 0}, {0, 1}, {1, 0}, {2, 0} },

    // D
    { {0, 0}, {0, 1}, {1, 0}, {1, 1} },

    // E
    { {0, 0}, {0, 1}, {0, 2}, {1, 0}, {2, 0} },
    { {0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2} },
    { {0, 2}, {1, 2}, {2, 2}, {2, 1}, {2, 0} },
    { {0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2} },

    // F
    { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 1} },
    { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 2} },
    { {1, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1} },
    { {2, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1} },
    { {1, 0}, {1, 1}, {1, 2}, {1, 3}, {0, 1} },
    { {1, 0}, {1, 1}, {1, 2}, {1, 3}, {0, 2} },
    { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {1, 1} },
    { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {2, 1} },
    
    // G
    { {0, 0}, {1, 0}, {0, 1}, {0, 2}, {1, 2} },
    { {0, 0}, {0, 1}, {1, 1}, {2, 1}, {2, 0} },
    { {0, 0}, {1, 0}, {1, 1}, {1, 2}, {0, 2} },
    { {0, 0}, {0, 1}, {1, 0}, {2, 0}, {2, 1} },

    // H
    { {0, 0}, {1, 0}, {2, 0}, {1, 1}, {2, 1} },
    { {0, 1}, {1, 0}, {2, 0}, {1, 1}, {2, 1} },
    { {0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2} },
    { {1, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2} },
    { {0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0} },
    { {0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 1} },
    { {0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 2} },
    { {0, 0}, {0, 1}, {1, 0}, {1, 1}, {1, 2} },

    // I
    { {0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3} },
    { {0, 0}, {0, 1}, {1, 1}, {1, 2}, {1, 3} },
    { {0, 1}, {1, 1}, {2, 1}, {2, 0}, {3, 0} },
    { {0, 1}, {1, 1}, {1, 0}, {2, 0}, {3, 0} },
    { {1, 0}, {1, 1}, {0, 1}, {0, 2}, {0, 3} },
    { {1, 0}, {1, 1}, {1, 2}, {0, 2}, {0, 3} },
    { {0, 0}, {1, 0}, {2, 0}, {2, 1}, {3, 1} },
    { {0, 0}, {1, 0}, {1, 1}, {2, 1}, {3, 1} },

    // J
    { {0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1} },

    // K
    { {0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2} },
    { {0, 0}, {0, 1}, {1, 1}, {1, 2}, {2, 2} },
    { {2, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 2} },
    { {2, 0}, {2, 1}, {1, 1}, {1, 2}, {0, 2} },

    // L
    { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 0} },
    { {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 3} },
    { {0, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1} },
    { {3, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1} },
    { {0, 0}, {0, 1}, {1, 0}, {2, 0}, {3, 0} },
    { {0, 0}, {3, 1}, {1, 0}, {2, 0}, {3, 0} },
    { {0, 0}, {1, 0}, {1, 1}, {1, 2}, {1, 3} },
    { {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3} },
};

char ch[100] {
    'A', 'A', 'A', 'A',
    'B', 'B',
    'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C',
    'D',
    'E', 'E', 'E', 'E',
    'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
    'G', 'G', 'G', 'G',
    'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H',
    'I', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 
    'J',
    'K', 'K', 'K', 'K',
    'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L',
};

const int maxc = 60;


const int maxn = 1e6 + 10;
struct DLX {
    struct Node {
        int l, r, u, d, R, C;
    } nd[maxn];
    int n, m, head[maxn], siz[maxn], cnt;

    void build() {
        for (int i = 0; i <= m; i++) {
            nd[i].l = i - 1;
            nd[i].r = i + 1;
            nd[i].u = nd[i].d = i;
        }
        nd[0].l = m;
        nd[m].r = 0;
        cnt = m;
        memset(head, 0, sizeof(head));
        memset(siz, 0, sizeof(siz));
    }

    void insert(int r, int c) {
        cnt++;
        nd[cnt].R = r;
        nd[cnt].C = c;
        nd[cnt].u = nd[c].u;
        nd[cnt].d = c;
        nd[nd[cnt].u].d = cnt;
        nd[nd[cnt].d].u = cnt;
        if (!head[r]) {
            head[r] = cnt;
            nd[cnt].l = nd[cnt].r = cnt;
        } else {
            nd[cnt].r = head[r];
            nd[cnt].l = nd[head[r]].l;
            nd[nd[cnt].l].r = cnt;
            nd[nd[cnt].r].l = cnt;
        }
        siz[c]++;
    }

    void remove(int c) {
        for (int i = nd[c].d; i != c; i = nd[i].d) {
            for (int j = nd[i].r; j != i; j = nd[j].r) {
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
            for (int j = nd[i].r; j != i; j = nd[j].r) {
                nd[nd[j].d].u = j;
                nd[nd[j].u].d = j;
                siz[nd[j].C]++;
            }
        }
    }

    int ans[maxn], len;
    bool dance(int dep) {
        if (nd[0].r == 0) {
            len = dep - 1;
            return true;
        }
        int cn = nd[0].r;
        for (int i = cn; i != 0; i = nd[i].r) {
            if (siz[cn] > siz[i]) {
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

int cx[100], cy[100];

std::vector<std::vector<int> > mp;
std::vector<char> mpx;
std::vector<int> mpm, mpc;
char cxk[20][20];
int flg[26], sum[26];
int cnt[110];

int calc(int x, int y) {
    if (y > x) return -1;
    return (1 + x - 1) * (x - 1) / 2 + y;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    for (int i = 0; i < 26; i++) flg[i] = 1;
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= i; j++) {
            cnt[calc(i, j)] = 1;
        }
    }

    for (int i = 1; i <= 10; i++) {
        scanf("%s", cxk[i] + 1);
        for (int j = 1; j <= i; j++) {
            cx[calc(i, j)] = i;
            cy[calc(i, j)] = j;
            if (cxk[i][j] != '.') {
                flg[cxk[i][j] - 'A'] = 0;
                cnt[calc(i, j)] = 0;
            }
        }
    }

    for (int i = 1; i <= calc(10, 10); i++) {
        cnt[i] += cnt[i - 1];
    }

    sum[0] = flg[0];
    for (int i = 1; i < 12; i++) {
        sum[i] = sum[i - 1] + flg[i];
    }

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k < maxc; k++) {
                if (!flg[ch[k] - 'A']) continue;
                static std::vector<int> ls; ls.clear();
                bool flag = true;
                for (auto p : v[k]) {
                    int c = cnt[calc(i + p.first, j + p.second)];
                    if (c == -1 || c > 55 || cxk[i + p.first][j + p.second] != '.') {
                        flag = false;
                        break;
                    }
                    ls.push_back(c);
                }
                if (flag) {
                    ls.push_back(cnt[calc(10, 10)] + sum[ch[k] - 'A']);
                    mp.push_back(ls);
                    mpx.push_back(ch[k]);
                    mpm.push_back(k);
                    mpc.push_back(calc(i, j));
                }
            }
        }
    }

    dlx.n = mp.size(); dlx.m = cnt[calc(10, 10)] + sum[11];
    dlx.build();

    for (int i = 0; i < mp.size(); i++) {
        for (int j : mp[i]) {
            dlx.insert(i + 1, j);
        }
    }
    if (!dlx.dance(1)) {
        puts("No solution");
    } else {
        for (int i = 1; i <= dlx.len; i++) {
            int x = cx[mpc[dlx.ans[i] - 1]], y = cy[mpc[dlx.ans[i] - 1]];
            int k = mpm[dlx.ans[i] - 1];
            for (auto p : v[k]) {
                cxk[x + p.first][y + p.second] = ch[k];
            }
        }
        for (int i = 1; i <= 10; i++) {
            printf("%s\n", cxk[i] + 1);
        }
    }
    return 0;
}
