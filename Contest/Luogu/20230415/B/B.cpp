/*
# 「TAOI-1」Apollo

## 题目背景

Execution.

这题原来叫 `std::cout << std::fixed << std::setprecision(1) << 6.5 << '\n';`。

[被当事人删掉的图片.jpg]

## 题目描述

给出 $n$ 个十进制小数 $a_1 \dots a_n$。

对于一个十进制小数 $a$，定义其精度 $f(a)$ 表示最小的非负整数 $k$ 使得 $10^k\times a$ 为整数。对于两个十进制小数 $a, b$，定义 $g(a, b)$ 为对于所有十进制小数 $c \in [\min(a,b), \max(a,b)]$ 的 $f(c)$ 的最小值。

对于所有 $1 \leq i \leq n$，你需要求出 $\sum\limits_{j=1}^ng(a_i, a_j)$ 的值并输出。

定义十进制小数是一个含有整数部分和小数部分的数，其小数部分不为 $0$。

## 输入格式

从标准输入中读入数据。

第一行一个整数 $n$。

接下来 $n$ 行，每行一个十进制小数 $a_i$。

## 输出格式

输出到标准输出。

$n$ 行，每行一个整数，分别表示 $i = 1 \dots n$ 对应的答案。

## 样例 #1

### 样例输入 #1

```
5
11.4514
11.4778
11.1338
11.1236
11.4789
```

### 样例输出 #1

```
10
11
9
9
11
```

## 样例 #2

### 样例输入 #2

```
8
1.1145
1.114
1.1145
1.514
1.19198
1.1154
1.114
1.1145
```

### 样例输出 #2

```
24
21
24
10
18
22
21
24
```

## 提示

### 数据范围

**本题采用捆绑测试。**

令 $\sum\limits_{i=1}^n f(a_i) = t$。

- Subtask 1（15 points）：$a_i \leq 10$，$n \leq 5$，$t \leq 10$。
- Subtask 2（15 points）：$a_i \leq 10$，$n \leq 100$，$t \leq 1000$。
- Subtask 3（20 points）：$n \leq 10^3$。
- Subtask 4（15 points）：$a_i \leq 1$。
- Subtask 5（35 points）：无特殊限制。

对于所有数据，$0 \leq a_i \leq 10^9, 1 \leq n \leq 10^5, 1 \leq t \leq 3 \times 10^6$，**保证 $\bm{a_i}$ 没有后导 [$\color{black}\bm 0$](https://cdn.luogu.com.cn/upload/image_hosting/pg66fm1z.png)，不保证 $\bm{a_i}$ 互不相同**。

### 样例解释

以 $i = 1$ 为例：

+ $j = 1$：取 $c = 11.4514$，$f(c) = 4$；
+ $j = 2$：取 $c = 11.46$，$f(c) = 2$；
+ $j = 3$：取 $c = 11.2$，$f(c) = 1$；
+ $j = 4$：取 $c = 11.3$，$f(c) = 1$；
+ $j = 5$：取 $c = 11.47$，$f(c) = 2$。

故 $\sum\limits_{j=1}^n g(a_1, a_j) = 4 + 2 + 1 + 1 + 2 = 10$。对于同一个 $j$，上文给出的所有 $c$，都可能有其它的不同的 $c$ 满足 $f(c)$ 同样最小。
*/
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

const int maxn = 2.8e6 + 10;
const int logn = 20;

struct Trie {
    struct Trie_Node {
        int nxt[10];
        char ch;
        std::vector<int> ok;
    };
    Trie_Node tree[maxn];
    const int root = 0;
    int Len;

    void init_Node(int it, char ch) {
        tree[it].ch = ch;
        tree[it].ok.clear();
        memset(tree[it].nxt, 0, sizeof(tree[it].nxt));
    }
    void init() {
        init_Node(0, '\0');
        Len = 1;
    }
    void insert(char *ch, int id) {
        int len = strlen(ch), nowId = root;
        for (int i = 0; i < len; i++) {
            if (tree[nowId].nxt[ch[i] - '0'] == 0) {
                init_Node(Len, ch[i]);
                tree[nowId].nxt[ch[i] - '0'] = Len;
                Len++;
            }
            nowId = tree[nowId].nxt[ch[i] - '0'];
        }
        tree[nowId].ok.push_back(id);
    }
} tr;


int n;
char ch[maxn + 10];
// int ln[maxn + 10], cnt = 0;
// int mp[maxn + 10], plc[maxn + 10];
int dep[maxn + 10];
// int fa[maxn + 10][logn + 10];
// int mp[maxn + 10];

int sub[maxn + 10];
int f[maxn + 10];
int bef[maxn + 10];

// sub
void dfs2(int cur, int fa) {
    dep[cur] = dep[fa] + 1;
    if (tr.tree[cur].ok.size()) {
        sub[cur] = tr.tree[cur].ok.size();
    }
    for (int i = 0; i < 10; i++) {
        if (tr.tree[cur].nxt[i] != 0) {
            dfs2(tr.tree[cur].nxt[i], cur);
            sub[cur] += sub[tr.tree[cur].nxt[i]];
        }
    }
}

void dfs3(int cur, int fa) {
    if (cur != 0 && tr.tree[cur].ok.size()) {
        int ans = std::max(0, dep[cur] - 13) * sub[cur];
        ans += bef[fa];
        ans += (sub[fa] - sub[cur]) * std::max(0, dep[cur] - 13) - tr.tree[fa].ok.size();
        for (int id : tr.tree[cur].ok) {
            f[id] = ans;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (tr.tree[cur].nxt[i] != 0) {
            bef[cur] = bef[fa] + (sub[fa] - sub[cur]) * std::max(0, dep[cur] - 13) - tr.tree[fa].ok.size();
            dfs3(tr.tree[cur].nxt[i], cur);
        }
    }
}

// void dfs(int cur, int fnode) {
//     if (tr.tree[cur].ok.size()) {
//         for (int id : tr.tree[cur].ok) {
//             mp[id] = cur;
//         }
//     }
//     fa[cur][0] = fnode;
//     dep[cur] = dep[fnode] + 1;
//     for (int i = 1; i < logn; i++) {
//         fa[cur][i] = fa[fa[cur][i - 1]][i - 1];
//     }

//     for (int i = 0; i < 10; i++) {
//         if (tr.tree[cur].nxt[i] != 0) {
//             dfs(tr.tree[cur].nxt[i], cur);
//         }
//     }
// }

// void dfs(int nowId, int dep) {
//     if (tr.tree[nowId].ok.size()) {
//         ln[++cnt] = dep;
//         for (int id : tr.tree[nowId].ok) {
//             mp[id] = cnt;
//             plc[id] = nowId;
//             height[nowId] = dep;
//         }
//     }
//     for (int i = 0; i < 10; i++) {
//         if (tr.tree[nowId].nxt[i] != 0) {
//             dfs(tr.tree[nowId].nxt[i], dep + 1);
//         }
//     }
// }

// 倍增
// int find(int x, int y) {
//     if (dep[x] > dep[y]) std::swap(x, y);
//     int tmp = dep[y] - dep[x];
//     for (int j = 0; tmp; ++j, tmp >>= 1) {
//         if (tmp & 1) {
//             y = fa[y][j];
//         }
//     }
//     if (y == x) return dep[x];
//     for (int j = logn - 1; j >= 0 && x != y; --j) {
//         if (fa[x][j] != fa[y][j]) {
//             x = fa[x][j];
//             y = fa[y][j];
//         }
//     }

//     return dep[x];
// }

// int lf[100005 + 10], rf[100005 + 1];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n);

    tr.init();
    for (int i = 1; i <= n; i++) {
        scanf("%s", ch + 11);
        int it = 11;
        while (ch[it] != '.') it++;
        ch[it] = '0';
        it -= 11;
        for (int j = it; ch[j] == '\0'; j++) {
            ch[j] = '0';
        }

        tr.insert(ch + it, i);
    }

    // dfs(tr.root, 0);

    // for (int i = 1; i <= n; i++) {
    //     int ans = 0;
    //     for (int j = 1; j <= n; j++) {
    //         ans += std::max(0, find(mp[i], mp[j]) - 13);
    //     }
    //     writeln(ans);
    // }

    // for (int i = 1; i <= n; i++) {
    //     lf[i] = lf[i - 1] + std::max(0, find(mp[1], mp[i]) - 13);
    // }
    // for (int i = n; i >= 1; i--) {
    //     rf[i] = rf[i + 1] + std::max(0, find(mp[i], mp[n]) - 13);
    // }
    // for (int i = 1; i <= n; i++) {
    //     printf("%d\n", lf[i - 1] + rf[i + 1] + std::max(0, find(mp[i], mp[i]) - 13));
    // }

    dfs2(tr.root, 0);
    dfs3(tr.root, 0);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", f[i]);
    }
    return 0;
}
