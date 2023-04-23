/*
# 「TAOI-1」Pentiment

## 题目背景

近日（存疑），一款名为闊靛緥婧愮偣的游戏更新了它的 4.0 版本。在这个版本中某谱面中的大直角蛇给玩家们留下了深刻的印象……

![](https://cdn.luogu.com.cn/upload/image_hosting/qbdvtftu.png)

## 题目描述

我们规定，在 $n$ 行 $m$ 列的网格中，“直角蛇”是这样一条路径：

- 从最下方（第一行）的某个格子的中心开始，在最上方（第 $n$ 行）的某个格子的中心结束。
- 每次可以向上、向右或向左移动一格，每次移动后都到达某个格子的中心（**不能向下移动**）。
- 不能重复经过同一个格子。

特别地，为了给你增加一些考验，我们规定有一些格子是“直角蛇”不能经过的。

请你统计在给定的网格中存在多少种这样的“直角蛇”。答案对 $998244353$ 取模。

## 输入格式

第一行三个整数 $n, m, q$，代表网格的行数和列数，以及限制的数量。

接下来的 $q$ 行，每行两个整数 $x_i, y_i$，代表第 $x_i$ 行第 $y_i$ 列的格子不能经过。保证同一个格子至多出现一次。保证所有格子按照 $x_i$ 为第一关键字，$y_i$ 为第二关键字，从小到大排序后给出。（我们规定最下方的格子的行数为 $1$，最左侧格子的列数为 $1$）

## 输出格式

共一行一个整数，代表符合条件的“直角蛇”数量对 $998244353$ 取模的结果。

## 样例 #1

### 样例输入 #1

```
2 3 2
1 1
2 1
```

### 样例输出 #1

```
8
```

## 样例 #2

### 样例输入 #2

```
4 4 4
1 1
2 2
3 3
4 4
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
6 5 4
1 3
3 1
3 4
5 2
```

### 样例输出 #3

```
2000
```

## 样例 #4

### 样例输入 #4

```
100000000 100000000 0
```

### 样例输出 #4

```
103866487
```

## 提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 1（10 points）：$n \leq 10^6$，$m \leq 2$。
- Subtask 2（10 points）：$q=0$。
- Subtask 3（15 points）：$n,m \leq 10^4$。
- Subtask 4（20 points）：$n \leq 10^4$。
- Subtask 5（20 points）：$m \leq 10^4$。
- Subtask 6（25 points）：无特殊限制。

对于所有测试数据，$2 \leq n \leq 10^9$，$1 \leq m \leq 10^9$，$0 \leq q \leq 10^5$，$1 \leq x_i \leq n$，$1 \leq y_i \leq m$。

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/dkyhh41q.png)

如图，样例一中共有八种满足条件的“直角蛇”。

对于样例二，不存在满足条件的“直角蛇”。

---

在寂若死灰中屈服。

在飘忽不定中屈服。

在功亏一篑中屈服。
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

const int mod = 998244353;
const int maxn = 1e3 + 10;
long long f[maxn][maxn][3];

int main() {
    #ifdef LOCAL
        freopen("hack/hack4.in", "r", stdin);
        freopen(".ans", "w", stdout);
    #endif
    
    int n, m, q;
    read(n, m, q);

    for (int i = 1, all = q; i <= all; i++) {
        int x, y;
        read(x, y);
        if (x > n || y > m) { q--; continue; }
        f[x][y][0] = -1;
        // puts("fk");
    }

    for (int j = 1; j <= m; j++) {
        if (f[1][j][0] != -1) f[1][j][0] = 1;
    }

    for (int j = 1; j <= m; j++) {
        int i = 1;
        if (f[i][j][0] == -1) continue;
        if (f[i][j - 1][0] != -1) {
            f[i][j][1] += f[i][j - 1][0] + f[i][j - 1][1];
            f[i][j][1] %= mod;
        }
    }
    // puts("fk");

    for (int j = m; j >= 1; j--) {
        int i = 1;
        if (f[i][j][0] == -1) continue;
        if (f[i][j + 1][0] != -1) {
            f[i][j][2] += f[i][j + 1][0] + f[i][j + 1][2];
            f[i][j][2] %= mod;
        }
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (f[i][j][0] == -1) continue;
            if (f[i - 1][j][0] != -1) {
                f[i][j][0] += f[i - 1][j][0] + f[i - 1][j][1] + f[i - 1][j][2];
                f[i][j][0] %= mod;
            }
        }
        for (int j = 1; j <= m; j++) {
            if (f[i][j][0] == -1) continue;
            if (f[i][j - 1][0] != -1) {
                f[i][j][1] += f[i][j - 1][0] + f[i][j - 1][1];
                f[i][j][1] %= mod;
            }
        }
        for (int j = m; j >= 1; j--) {
            if (f[i][j][0] == -1) continue;
            if (f[i][j + 1][0] != -1) {
                f[i][j][2] += f[i][j + 1][0] + f[i][j + 1][2];
                f[i][j][2] %= mod;
            }
        }
    }

    long long ans = 0;
    for (int j = 1; j <= m; j++) {
        if (f[n][j][0] != -1) {
            ans += ((f[n][j][0] + f[n][j][1] + f[n][j][2]) % mod);
            ans %= mod;
            // writeln(j, f[1][j][0], f[1][j][1], f[1][j][2]);
        }
    }

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         printf("%10d ", (f[i][j][0] + f[i][j][1] + f[i][j][2]) % mod);
    //     }
    //     putchar('\n');
    // }

    writeln(ans);
    return 0;
}
