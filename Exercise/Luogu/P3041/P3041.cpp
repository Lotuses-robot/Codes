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

struct Trie_Node {
    int nxt[5];
    int fail, tot, fa;
    char ts;
};

const int maxn = 1e3 + 10;

struct Trie {
    Trie_Node  tree[maxn * 30];
    bool       vis [maxn * 30];
    const int  root = 0;
    int        Len;
    void initNode(int it, char ts) {
        tree[it].ts = ts;
        tree[it].tot = 0;
        memset(tree[it].nxt, 0, sizeof(tree[it].nxt));
    }
    void init() {
        initNode(0, '\0');
        Len = 1;
    }
    void insert(char *ch) {
        int len = strlen(ch), nowId = root;
        for (int i = 0; i < len; i++) {
            if (tree[nowId].nxt[ch[i] - 'A'] == root) {
                initNode(Len, ch[i]);
                tree[nowId].nxt[ch[i] - 'A'] = Len;
                Len++;
            }
            nowId = tree[nowId].nxt[ch[i] - 'A'];
        }
        tree[nowId].tot++;
    }
    void build() {
        tree[root].fail = root;
        tree[root].fa = root;
        static std::queue<int> q;
        for (int i = 0; i < 3; i++) {
            if (tree[root].nxt[i]) q.push(tree[root].nxt[i]);
            tree[tree[root].nxt[i]].fail = root;
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < 3; i++) {
                if (tree[u].nxt[i]) {
                    tree[tree[u].nxt[i]].fail = tree[tree[u].fail].nxt[i];
                    q.push(tree[u].nxt[i]);
                } else {
                    tree[u].nxt[i] = tree[tree[u].fail].nxt[i];
                }
            }
        }
    }
    int fail(int u) {
        if (!u) return 0;
        return tree[u].tot + fail(tree[u].fail);
    }
} tr;

char ch[maxn];
int f[maxn][4 * maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    tr.init();
    int n, k;
    read(n, k);
    for (int i = 1; i <= n; i++) {
        scanf("%s", ch);
        tr.insert(ch);
    }
    tr.build();
    memset(f, -63, sizeof(f));
    f[0][0] = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < tr.Len; j++) {
            for (int k = 0; k < 3; k++) {
                int pos = tr.tree[j].nxt[k];
                f[i + 1][pos] = std::max(f[i + 1][pos], f[i][j] + tr.fail(pos));
            }
        }
    }
    int ans = f[k][0];
    for (int i = 0; i < tr.Len; i++) ans = std::max(f[k][i], ans);
    writeln(ans);
    return 0;
}