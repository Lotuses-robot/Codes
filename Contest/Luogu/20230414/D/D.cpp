/*
# 移植柳树 (Easy Version)

## 题目背景

**本题与 Hard Version 题意完全相同，不同的地方仅在于数据范围和单个测试点内含有的测试组数量。**

HG 在上学的路上无聊的走着，看着这马路边的一排柳树，他的脑子里突然冒出了个奇怪的问题……

## 题目描述

假设总共有 $n$ 棵柳树，每一棵间隔都为 $x$。

现在他需要对这些树做一些操作，使得在「这 $n$ 棵树的起点不变」的同时，任意两棵树的间隔都为 $y$（$y > x$）。

他被允许做的操作如下；

- 移植树木：将一个位置的树木移到另一个位置上。

如果对「起点不变」这个概念有疑惑，就是最开始的那个点不能移动。

显然操作是需要体力的，HG 想要让尽可能多的树维持原状。现在 HG 想知道，为了达成「任意两棵树的间隔都为 $y$」这个目标，他最多可以让多少棵树保持在原来的位置。

请你帮帮他吧！

## 输入格式

输入共一行三个整数 $n, x, y$，依次表示柳树的数量，未调整前每棵的间隔，想要达成的每棵的间隔。

## 输出格式

输出共一行一个整数，表示为了达成「任意两棵树的间隔都为 $y$」的目标，他最多可以让多少棵树保持在原来的位置。

## 样例 #1

### 样例输入 #1

```
8 2 3
```

### 样例输出 #1

```
3
```

## 提示

### 数据规模与约定

对于 $10\%$ 的数据，保证 $n \leq 10$，$x = 1$，$y = 2$。  
对于 $20\%$ 的数据，保证 $n \leq 10^3$，且 $y$ 是 $x$ 的倍数。  
对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^6$，$1 \leq x < y \leq 10^6$。
*/

/*
题解：
寻找到一个 $a,b$ 使得 $ax = by$。

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

#define int __int128

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, x, y;
        read(n, x, y);
        int ans = 0;
        int g = gcd(x, y);
        int q = x * y / g;
        int max = (n - 1) * x / q;

        writeln(max + 1);
    }
    return 0;
}
