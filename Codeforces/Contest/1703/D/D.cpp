#include <cstdio>
#include <cstring>

struct Trie_Node {
    int nxt[27];
    char ch;
    bool ok;
};

struct Trie {
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

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        static char ch[1000006][10];
        trie.init();
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", ch[i]);
            trie.insert(ch[i]);
        }
        for (int i = 0; i < n; i++) {
            bool flag = false;
            int nowLen = strlen(ch[i]);
            for (int len = 1; len <= nowLen - 1; len++) {
                if (trie.query(ch[i], len) && trie.query(ch[i] + len, nowLen - len)) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                putchar('1');
            } else {
                putchar('0');
            }
        }
        puts("");
    }
    return 0;
}