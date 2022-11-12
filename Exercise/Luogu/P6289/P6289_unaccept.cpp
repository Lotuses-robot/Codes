// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

struct Trie {
    struct Trie_Node {
        int nxt[27];
        char ch;
        bool ok;
    };
    Trie_Node tree[1000006];
    const int root = 0;
    int Len;

    void init_Node(int it, char ch) {
        tree[it].ch = ch;
        tree[it].ok = false;
        memset(tree[it].nxt, 0, sizeof(tree[it].nxt));
    }
    void init() {
        init_Node(0, '\0');
        Len = 1;
    }
    void insert(char *ch) {
        int len = strlen(ch), nowId = root;
        for (int i = 0; i < len; i++) {
            if (tree[nowId].nxt[ch[i] - 'a'] == 0) {
                init_Node(Len, ch[i]);
                tree[nowId].nxt[ch[i] - 'a'] = Len;
                Len++;
            }
            nowId = tree[nowId].nxt[ch[i] - 'a'];
        }
        tree[nowId].ok = true;
    }
    bool query(char *ch, int len = -1) const {
        if (len == -1) {
            len = strlen(ch);
        }
        int nowId = root;
        for (int i = 0; i < len; i++) {
            if (tree[nowId].nxt[ch[i] - 'a'] == 0) return false;
            nowId = tree[nowId].nxt[ch[i] -'a'];
        }
        return tree[nowId].ok;
    }
} trie;

char ch[20][1145141];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int n;
    read(n);
    trie.init();
    for (int i = 0; i < n; i++) {
        scanf("%s", ch[i]);
        std::sort(ch[i], ch[i] + strlen(ch[i]));
        printf("%s\n", ch[i]);
        trie.insert(ch[i]);
    }

    printf("%d\n", trie.Len);
    return 0;
}
