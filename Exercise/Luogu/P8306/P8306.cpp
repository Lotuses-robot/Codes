// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>

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
struct Trie {
    struct Trie_Node {
        std::map<char, int> nxt;
        char ch;
        int cnt = 0;
    };
    Trie_Node tree[3000006];
    const static int root = 0;
    int Len;

    void init_Node(int it, char ch) {
        tree[it].ch = ch;
        tree[it].cnt = 0;
        tree[it].nxt.clear();
    }
    void init() {
        init_Node(0, '\0');
        Len = 1;
    }
    void insert(char *ch) {
        int len = strlen(ch), nowId = root;
        for (int i = 0; i < len; i++) {
            if (tree[nowId].nxt[ch[i]] == 0) {
                init_Node(Len, ch[i]);
                tree[nowId].nxt[ch[i]] = Len;
                Len++;
            }
            nowId = tree[nowId].nxt[ch[i]];
        }
        tree[nowId].cnt++;
    }
    void calc(int u = root) {
        for (auto nt : tree[u].nxt) {
            calc(nt.second);
            tree[u].cnt += tree[nt.second].cnt;
        }
    }
    int query(char *ch, int len = -1) {
        if (len == -1) {
            len = strlen(ch);
        }
        int nowId = root;
        for (int i = 0; i < len; i++) {
            if (tree[nowId].nxt[ch[i]] == 0) return 0;
            nowId = tree[nowId].nxt[ch[i]];
        }
        return tree[nowId].cnt;
    }
} tr;

const int maxn = 1e5 + 10;
char ch[maxn];

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        tr.init();
        int n, q;
        read(n, q);
        for (int i = 1; i <= n; i++) {
            scanf("%s", ch);
            tr.insert(ch);
        }
        tr.calc();
        while (q--) {
            scanf("%s", ch);
            writeln(tr.query(ch));
        }
    }
    return 0;
}