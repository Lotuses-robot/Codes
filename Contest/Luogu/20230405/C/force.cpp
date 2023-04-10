/*
# 「GMOI R2-T3」粒子环游

## 题目背景

热爱珂学的小 Z 正在进行一项无聊的实验。

## 题目描述

实验室中有一个由 $n$ 个实验腔连接而成的环形轨道，其中第 $i$ 个实验腔顺时针连向第 $i+1$ 个实验腔（特别的，第 $n$ 个实验腔连向第 $1$ 个实验腔）。同时还有一个标号为 $n+1$ 的新建实验腔要接入这个环形轨道。它可以接在任意两个原本相连的实验腔之间。

第 $i$ 个实验腔可以将带电荷量为 $Q$ 的粒子运输到它的下一个实验腔，这个过程花费的能量为 $\vert Q \vert \times c_i$。除此之外，第 $i$ 个实验腔本身就存储了量为 $e_i$ 的电荷（电荷量有正负）。由于众所周知的电荷守恒定律，第 $n+1$ 个实验腔储存的电荷量与前 $n$ 个实验腔储存的总电荷量的代数和为 $0$。

小 Z 有一个原本不带电的粒子。等到第 $n+1$ 个实验腔接入轨道后，他要任选一个实验腔（包括第 $n+1$ 个）作为出发点，将粒子放入，并使之在实验腔的能量驱动下顺时针环游一周回到出发点。粒子每到达一个实验腔（包括出发点），它所带电荷量就会变成原来所带的电荷量和这个实验腔所储存的电荷量的代数和。

**注意：电荷量会先加上实验腔所含电荷量，再计算能量贡献。**

现在，小 Z 想知道，在所有接入新建实验腔并选定出发点的方案中，粒子环游一周所需的能量最少为多少？

## 输入格式

第一行为一个正整数 $n$ ，表示环形轨道原有实验腔数。

第二行有 $n+1$ 个非负整数，依次表示 $c_1,c_2,...,c_{n+1}$。

第三行有 $n$ 个整数，依次表示 $e_1,e_2,...,e_{n}$。

## 输出格式

输出共一行，包括一个数，表示粒子环游一周所需的最少能量。

## 样例 #1

### 样例输入 #1

```
3
1 3 2 2
3 -5 1
```

### 样例输出 #1

```
9
```

## 样例 #2

### 样例输入 #2

```
12
4 7 7 8 8 4 5 5 9 10 1 1 10 
0 -5 7 8 1 -1 -6 8 2 4 10 8
```

### 样例输出 #2

```
509
```

## 提示

样例 $1$ 解释：一种最优方案为将 $4$ 号实验腔接在 $3$ 号实验腔与 $1$ 号实验腔之间，以 $4$ 号实验腔为出发点，花费能量为 $ 1\times 2\ +\ 4\times 1\ + \vert -1 \vert \times 3 \ +\ 0 \times 2 =9$。

**本题采用 Subtask 捆绑测试。**

| Subtask | $n\le$ | $c_i\le$ | $\vert e_i\vert$ | 特殊性质 | 对应测试点 | 总分 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $300$ | $100$ | $100$ | $-$ | $1\sim 5$ | $10$ |
| $1$ | $10^3$ | $10^3$ | $10^3$ | $\bf A$ | $6\sim 7$ | $5$ |
| $2$ | $10^4$ | $10^4$ | $10^4$ | $-$ | $8\sim12$ | $15$ |
| $3$ | $10^5$ | $10^5$ | $10^5$ | $\bf B$ | $13\sim 16$ | $10$ |
| $4$ | $2.5\times 10^5$ | $10^5$ |$10^5$ | $-$ | $17\sim 25$ | $60$ |

特殊性质 $\bf A$：对于所有的 $i\in[1,n+1](i\in \Z)$，满足 $c_i=0$。

特殊性质 $\bf B$：对于所有的 $i\in[1,n+1](i\in \Z)$，满足 $c_i=1$。

对于 $100\%$ 的数据，$1\le n\le 2.5\times 10^5$，$0\le c_i\le 10^5$，$0\le |e_i|\le 10^5$。

保证答案在 long long 范围内。
*/

// 此程序是该题目的暴力解法

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

#define int long long

const int maxn = 2e5 + 100;
int n;
int c[maxn], e[maxn];

int getE(int cur, int i) {
    if (cur < i) return e[cur];
    if (cur > i) return e[cur - 1];
    if (cur == i) return e[n + 1];
}

int getC(int cur, int i) {
    if (cur < i) return c[cur];
    if (cur > i) return c[cur - 1];
    if (cur == i) return c[n + 1];
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n + 1; ++i) read(c[i]);
    for (int i = 1; i <= n; ++i) read(e[i]), e[n + 1] += e[i];

    e[n + 1] = -e[n + 1];
    int res = 1145141919;
    for (int i = 1; i <= n + 1; i++) {
        for (int begin = 1; begin <= n + 1; begin++) {
            // if (i == 4) {
            //     puts("fuck");
            // }
            int cur = begin + 1, ans = 0, pre = getE(begin, i);
            if (cur > n + 1) cur = 1;
            pre += getE(cur, i);
            ans += getC(cur, i) * std::abs(pre);
            while (cur != begin) {
                cur++;
                if (cur > n + 1) cur = 1;
                pre += getE(cur, i);
                ans += getC(cur, i) * std::abs(pre);
            }
            res = std::min(res, ans);
        }
    }
    
    writeln(res);
    return 0;    
}
