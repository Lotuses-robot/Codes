#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

struct Trie_Node {
    int nxt[130];
    int fail, id, fa;
    char ts;
};
std::queue<int> q;

#define maxn 100005

struct Trie {
    Trie_Node  tree[maxn];
    bool       vis [maxn];
    const int  root = 0;
    int        Len;
    void initNode(int it, char ts) {
        tree[it].ts = ts;
        tree[it].id = 0;
        memset(tree[it].nxt, 0, sizeof(tree[it].nxt));
    }
    void init() {
        // for (int i = 0; i < maxn; i++) {
        //     initNode(i, '\0');
        // }
        initNode(0, '\0');
        Len = 1;
    }
    void insert(char *ch, int id) {
        int len = strlen(ch), nowId = root;
        for (int i = 0; i < len; i++) {
            if (tree[nowId].nxt[ch[i]] == root) {
                initNode(Len, ch[i]);
                tree[nowId].nxt[ch[i]] = Len;
                Len++;
            }
            nowId = tree[nowId].nxt[ch[i]];
        }
        tree[nowId].id = id;
    }
    void build() {
        tree[root].fail = root;
        tree[root].fa = root;
        for (int i = 0; i < 128; i++) {
            if (tree[root].nxt[i]) q.push(tree[root].nxt[i]);
            tree[tree[root].nxt[i]].fail = root;
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < 128; i++) {
                if (tree[u].nxt[i]) {
                    tree[tree[u].nxt[i]].fail = tree[tree[u].fail].nxt[i];
                    q.push(tree[u].nxt[i]);
                } else {
                    tree[u].nxt[i] = tree[tree[u].fail].nxt[i];
                }
            }
        }
    }
    std::pair<int, std::vector<int> > query(char *ch) {
        static std::vector<int> ansList;
        int ans = 0;
        int len = strlen(ch), nowId = root;
        ansList.clear();
        memset(vis, 0, sizeof(vis));

        for (int i = 0; i < len; i++) {
            int nxtId = tree[nowId].nxt[ch[i]];
            while (nxtId > root) {
                if (vis[nxtId]) {
                    break;
                } else {
                    vis[nxtId] = true;
                }
                if (tree[nxtId].id) {
                    ans++;
                    ansList.push_back(tree[nxtId].id);
                }
                nxtId = tree[nxtId].fail;
            }
            nowId = tree[nowId].nxt[ch[i]];
        }
        return std::make_pair(ans, ansList);
    }
}tr;


int main() {
    // freopen("2896.in", "r", stdin);
    static char chr[10004];
    tr.init();

    // puts("fk");

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", chr);
        tr.insert(chr, i + 1);
        // printf("%d\n", i);
    }
    tr.build();

    int q, tot = 0;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%s", chr);
        auto resp = tr.query(chr);
        if (resp.first) {
            std::sort(resp.second.begin(), resp.second.end());
            printf("web %d:", i + 1);
            for (auto v : resp.second) {
                printf(" %d", v);
            }
            puts("");
            tot++;
        }
    }
    printf("total: %d\n", tot);
    return 0;
}