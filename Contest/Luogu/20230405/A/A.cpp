/*
# 「GMOI R2-T1」轴对称

## 题目描述

你有一个 $n$ 行 $m$ 列的图片（矩阵），该图片的像素为 $n\times m$。

初始时，所有像素块均为黑色，RGB 是 $(0,0,0)$。每一次操作可以将一个像素块的 RGB 中的一个数字改变。

在每次操作过后，请你输出图片是否左右对称？

左右对称：即对于任何的 $i,j$，总满足第 $i$ 行第 $j$ 列的像素与第 $i$ 行第 $m-j+1$ 列的像素的 RGB 值相等。

## 输入格式

第一行三个整数 $n,m,q$，$q$ 代表操作次数。

接下来 $q$ 行，每行输入四个整数 $i,j,t,c$，表示将第 $i$ 行第 $j$ 列的格子的 RGB 值的第 $t$ 个数增加 $c$，任何一个 RGB 值的任何一个数如果超出 $255$ 则自动对 $256$ 取模。

## 输出格式

每次操作过后，如果图片左右对称，输出 `Yes`，否则输出 `No`。每组询问的输出之间用换行隔开。

## 样例 #1

### 样例输入 #1

```
6 6 9
1 2 3 4
5 6 3 4
1 5 3 4
5 1 3 4
1 3 2 260
1 4 2 4
2 2 3 5
2 5 3 7
2 2 3 258
```

### 样例输出 #1

```
No
No
No
Yes
No
Yes
No
No
Yes
```

## 提示

**本题使用 Subtask 捆绑测试。**

| Subtask | $n\le$ | $m\le$ | $q\le$ | $t\le$ | $c\le$ | 对应测试点 | 总分 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $10$ | $2$ | $50$ | $1$ | $255$ | $1\sim2$ | $10$ |
| $1$ | $100$ | $2$ | $500$ | $3$ | $10^9$ | $3\sim4$ | $15$ |
| $2$ | $100$ | $100$ | $500$ | $3$ | $10^9$ | $5\sim6$ | $15$ |
| $3$ | $100$ | $100$ | $1$ | $3$ | $10^9$ | $7\sim9$ | $15$ |
| $4$ | $100$ | $100$ | $500$ | $3$ | $10^9$ | $10\sim12$ | $45$ |

**对于 Subtask 2**，保证每个变量等概率随机生成。

对于 $100\%$ 的数据，$1\le n,m\le 100$，$1\le q\le 500$，$1\le i\le n$，$1\le j\le m$，$t\in \{1,2,3\}$，$1\le c\le 10^9$。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, r, l) for (int i = (r); i >= (l); i--)

const int N = 105;
int n, m, q, a[N][N][3], b[N][N][3];

int main() {
    scanf("%d%d%d", &n, &m, &q);
    while (q--) {
        int x, y, t, c;
        scanf("%d%d%d%d", &x, &y, &t, &c);
        a[x][y][t - 1] += c;
        a[x][y][t - 1] %= 256;
        rep(i, 1, n) rep(j, 1, m) b[i][j][t - 1] = a[i][j][t - 1];
        rep(i, 1, n) rep(j, 1, m) b[i][m - j + 1][t - 1] = a[i][j][t - 1];
        bool flag = 1;
        rep(i, 1, n) rep(j, 1, m) rep(k, 0, 2) if (a[i][j][k] != b[i][j][k]) flag = 0;
        puts(flag ? "Yes" : "No");
    }
    return 0;
}