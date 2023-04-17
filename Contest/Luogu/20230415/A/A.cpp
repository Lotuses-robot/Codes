/*
# 「TAOI-1」拼凑的断音

## 题目背景

> flick tap flick tap 面を滑って \
> swipe tap swipe tap 「A.R→T」\
> flick tap flick tap 開いて叩いて \
> swipe swipe swipe swipe …もう嫌だな \
> ズルズル 糸が呟く

## 题目描述

你的面前有 $n$ 个音符，它们的动听程度由数列 $\{a_n\}$ 描述。

现在有 $n$ 种魔法，第 $i$ 种魔法会让 $a_i$ 增加 $s(s \gt 0)$。每种魔法的成功几率都为 $\dfrac{p}{q}$，并且彼此独立。

求在施加魔法情况下，最终最动听的音符的动听程度（即，$\max\limits_{i=1}^n a_i$）的期望。

**本题目有 Special Judge，你可以用两种不同的方式输出答案，具体见【输出格式】处**。

## 输入格式

第一行为四个整数 $n, p, q, s$。

第二行为 $n$ 个整数 $a_i$，由空格隔开。

## 输出格式

**本题有两种不同的输出格式**。

- 第一种输出格式：

  请在第一行输出 `1`。
  
  接着，在第二行输出所求的期望，它应当是一个实数。
  
  如果您的答案与标准答案相差不超过 $10^{-4}$，则判定为正确。但由于众所周知的浮点数的误差，不保证评测结果百分百准确。如果您确信自己的程序正确但无法 AC，可以尝试使用第二种输出方式。

- 第二种输出格式：
  
  请在第一行输出 `2`。
  
  接下来，若你求出的期望是 $\dfrac{m}{n}$（显然期望为一个有理数），则请在第二行输出它对 $998244353$ 取模的结果，即一个 $[0, 998244353)$ 的整数 $x$，使得 $xn \equiv m \pmod {998244353}$。

## 样例 #1

### 样例输入 #1

```
3 1 3 2
1 2 3
```

### 样例输出 #1

```
1
3.888889
```

## 样例 #2

### 样例输入 #2

```
3 1 3 2
1 2 3
```

### 样例输出 #2

```
2
554580200
```

## 提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 1（20 points）：$n \leq 15$。
- Subtask 2（15 points）：保证 $\forall i \in [1, n), a_i \leq a_{i+1}$，$a_n \geq a_{n-1}+s$。
- Subtask 3（15 points）：保证 $\forall i,j\in[1,n], a_i = a_j$。
- Subtask 4（50 points）：无特殊限制。

对于所有测试数据，$1 \leq n \leq 10^5$，$1 \leq p \lt q \leq 10^7$，$1 \leq a_i,s \leq 10^7$。

### 样例解释

注意到两个样例的输入相同，区别仅在于输出格式不同。

以下列举了所有可能的魔法施加情况和其对应的最大值以及出现概率：

| 魔法情况 | 动听度最大值 | 出现概率 | 对期望的贡献 |
| :------: | :----------: | :------: | :----------: |
|${\color{black}1},{\color{black}2},{\color{black}3}$|$3$|$\dfrac{8}{27}$|$\dfrac{8}{9}$|
|${\color{red}3},{\color{black}2},{\color{black}3}$|$3$|$\dfrac{4}{27}$|$\dfrac{4}{9}$|
|${\color{black}1},{\color{red}4},{\color{black}3}$|$4$|$\dfrac{4}{27}$|$\dfrac{16}{27}$|
|${\color{black}1},{\color{black}2},{\color{red}5}$|$5$|$\dfrac{4}{27}$|$\dfrac{20}{27}$|
|${\color{red}3},{\color{red}4},{\color{black}3}$|$4$|$\dfrac{2}{27}$|$\dfrac{8}{27}$|
|${\color{red}3},{\color{black}2},{\color{red}5}$|$5$|$\dfrac{2}{27}$|$\dfrac{10}{27}$|
|${\color{black}1},{\color{red}4},{\color{red}5}$|$5$|$\dfrac{2}{27}$|$\dfrac{10}{27}$|
|${\color{red}3},{\color{red}4},{\color{red}5}$|$5$|$\dfrac{1}{27}$|$\dfrac{5}{27}$|

可得，最终的答案为 $\dfrac{35}{9}$。

+ 若使用第一种输出方式，它的值约为 $3.888889$。
+ 若使用第二种输出方式，可以发现 $554580200 \times 9 \equiv 35 \pmod {998244353}$。
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>

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

const int maxn = 1e5 + 10;
int a[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, p, q, s;
    read(n, p, q, s);

    for (int i = 1; i <= n; ++i) read(a[i]);
    double frec = 0, pre = 1;
    std::sort(a + 1, a + n + 1, std::greater<int>());
    
    for (int i = 1; i <= n; i++) {
        // printf("%d\n", a[i] + s);
        frec += (std::max(a[i] + s, a[1])) * (pre * p / q);
        // printf("%d %lf\n", (std::max(a[i] + s, a[n])), pre * p / q);
        pre *= (double)(q - p) / q;
    }
        frec += (a[1]) * pre;

    printf("1\n%.9lf\n", frec);
    return 0;
}
