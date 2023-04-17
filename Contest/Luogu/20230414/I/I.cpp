/*
# 扶苏与 1 (Easy Version)

## 题目背景

**本题与 Easy Version 的区别是：$x$ 的范围不同，$y$ 的长度限制不同**。

**请注意 Easy Version 和 Hard Version 不是严格的包含关系。**

扶苏在 ICPC2022 EC Final 的比赛里，开局不到五分钟，就读假了一道题，把一道数位 DP 开成了简单签到，狠狠地演了队友一把。

为了不让读假了的题被浪费，所以这道题出现在了这里。

## 题目描述

扶苏给了你一个数字 $x$，你需要给她一个数字 $y$，使得在列竖式计算 $x + y$ 时，能恰好产生 $k$ 个进位。

你给出的 $y$ 的**长度**不能超过 $10^4$。

**进位**的含义是：在进行竖式加法运算时，如果位于同一列上的数字之和（加上低位向上可能存在的进位）比 $9$ 大，则在结果的这一列上只保留这个和的个位数字，同时称这一位向它的高位产生了一个**进位**。

下图是一个竖式加法的例子，结果中标红的两位都向上产生了进位。

![](https://cdn.luogu.com.cn/upload/image_hosting/sxkzrk4i.png)

## 输入格式

**本题单测试点内有多组测试数据**。

第一行为一个整数 $T$，代表测试数据组数。  
接下来 $T$ 组数据，每组数据只有两行，每行一个整数。  
第一行的整数表示 $x$。  
第二行的整数表示 $k$。

## 输出格式

**本题采用 special judge 进行判题**。

对每组数据，输出一行一个整数，表示你给出的 $y$。

如果有多个满足要求的 $y$，你可以输出任何一个。但是必须保证如下三条限制：
- $y$ 是正整数。
- $y$ 不含前导 $0$。
- $y$ 的长度不超过 $10^4$。

特别的，如果这样的 $y$ 不存在，请你输出一行一个 $\texttt{-1}$。

## 样例 #1

### 样例输入 #1

```
5
1
1
14
1
514
2
1234
1
123456
6
```

### 样例输出 #1

```
9
8
516
7
877777
```

## 提示

### 数据规模与约定

- 对 $30\%$ 的数据，保证 $x < 10$，$k = 1$。
- 对 $70\%$ 的数据，保证 $x < 10^6$。
- 对 $100\%$ 的数据，保证 $0 \leq x < 10^{(10^3)}$，$1 \leq T \leq 5000$，$1 \leq k \leq 1+\log_{10}\max(1,x)$。输入的 $x$ 不含前导 $0$。

### 提示

输入的 $x$ 可能会很大。如果说 $x < 10^t$，则输入 $x$ 的**长度**不会超过 $t$。数据规模中式子 $k \leq 1 + \log_{10}\max(1,x) $ 的含义是：$k$ 不会超过 $x$ 的长度。
*/
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

#define maxn 10010

int x[maxn], y[maxn], k, t;

void increase(int &i) {
    for (; x[i] >= 10; i++) {
        x[i] = x[i] - 10;
        x[i + 1] += 1;
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int T;
    read(T);
    while (T--) {
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        char ch = getchar();
        while (ch < '0' || ch > '9') ch = getchar();
        t = 0;
        while (ch >= '0' && ch <= '9') x[++t] = ch - '0', ch = getchar();
        std::reverse(x + 1, x + t + 1);

        read(k);
        
        if (x[1] == 0 && t == 1) {
            puts("-1");
            continue;
        }

        int i, cnt = 0; bool flag = false;
        for (i = 1; cnt <= k; i++) {
            if (x[i] == 0) {
                continue;
            }
            y[i] = 10 - x[i];
            x[i] = 10;
            int bi = i;
            increase(i); i--;
            cnt += (i - bi + 1);
            // writeln(cnt, k, i);
            if (cnt > k) {
                flag = true;
            } else if (cnt == k) break;

        }

        if (flag) {
            puts("-1");
        } else {
            bool fl = 0;
            for (int j = i; j >= 1; j--) {
                if (y[j] == 0 && !fl) {
                    continue;
                } else {
                    fl = 1;
                }
                write(y[j]);
            }
            puts("");
        }
    }
    return 0;
}
