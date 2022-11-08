#include <cstdio>
#include <cstring>
#include <queue>

struct Trie_Node
{
    int nxt[27], fail;
    char ch;
    bool over;
};

#define maxn 1000006

struct Trie
{
    Trie_Node tree[maxn];
    int Len;
    const int root = 0;
    void init_Node(int it, char ch)
    {
        memset(tree[it].nxt, 0, sizeof(tree[it].nxt));
        tree[it].ch = ch;
        tree[it].fail = 0;
        tree[it].over = false;
    }
    void init()
    {
        init_Node(0, '\0');
        Len = 1;
    }
    void insert(char *ch)
    {
        int len = strlen(ch), nowId = root;
        for (int i = 0; i < len; i++)
        {
            if (!tree[nowId].nxt[ch[i] - 'A'])
            {
                init_Node(Len, ch[i]);
                tree[nowId].nxt[ch[i] - 'A'] = Len++;
            }
            nowId = tree[nowId].nxt[ch[i] - 'A'];
        }
        tree[nowId].over = true;
    }
    void build()
    {
        static std::queue<int> q;

        // init root
        tree[root].fail = root;
        for (int i = 0; i < 26; i++)
        {
            if (tree[root].nxt[i])
            {
                tree[tree[root].nxt[i]].fail = root;
                q.push(tree[root].nxt[i]);
            }
        }

        // binary search
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
            {
                if (tree[u].nxt[i])
                {
                    tree[tree[u].nxt[i]].fail = tree[tree[u].fail].nxt[i];
                    tree[u].over |= tree[tree[u].nxt[i]].over;
                    q.push(tree[u].nxt[i]);
                }
                else
                {
                    tree[u].nxt[i] = tree[tree[u].fail].nxt[i];
                }
            }
        }
    }
} trie;

struct matrix {
    typedef int ll;
    const int sz = 114, MOD = 100000;

    ll a[114][114];
    matrix() { memset(a, 0, sizeof(a)); }
    matrix operator = (const matrix T) {
        memcpy(a, T.a, sizeof(T.a));
        return *this;
    }
    matrix operator - (const matrix T) const
    {
        matrix res;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
                res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
        return res;
    }
    matrix operator + (const matrix T) const {
        matrix res;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
                res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
        return res;
    }
    matrix operator * (const matrix T) const {
        matrix res;
        int r;
        for (int i = 0; i < sz; ++i)
            for (int k = 0; k < sz; ++k)
            {
                r = a[i][k];
                for (int j = 0; j < sz; ++j)
                    res.a[i][j] += 1ll * T.a[k][j] * r % MOD, res.a[i][j] %= MOD;
            }
        return res;
    }
    matrix operator ^ (ll x) const {
        matrix res, bas;
        for (int i = 0; i < sz; ++i)
            res.a[i][i] = 1;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
                bas.a[i][j] = a[i][j] % MOD;
        while (x)
        {
            if (x & 1)
                res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }
} mat;

int main()
{
    trie.init();
    static char ch[114514];
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++)
    {
        scanf("%s", ch);
        trie.insert(ch);
    }
    trie.build();
    // put into a matrix
    for (int i = 0; i < trie.Len; i++) {
        for (int j = 0; j < 26; j++) {
            if (!trie.tree[trie.tree[i].nxt[j]].over) {
                if (trie.tree[i].over) continue;
                mat.a[i][trie.tree[i].nxt[j]]++;
            }
        }
        mat.a[i][i] = 1;
    }
    mat = mat ^ n;
    int ans = 0;
    for (int i = 0; i < trie.Len; i++) {
        ans += mat.a[0][i];
        ans %= mat.MOD;
    }
    printf("%d\n", ans);
    return 0;
}