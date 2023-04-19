/*
# 你的牌太多了

## 题目描述

笨蛋扶苏和坏蛋小 F 在打一种很新的牌。

初始时，扶苏和小 F 手中各有 $n$ 张牌。每张牌有一个花色 $f$ 和一个点数 $p$。在本题中，花色是不超过 $m$ 的正整数，点数是不超过 $r$ 的正整数。

打牌共会进行 $n$ 轮，每轮扶苏会从手中选择一张牌打出。小 F 会从当前手牌中，选择与扶苏本轮打出的牌**花色相同**且点数**大于**扶苏打出的牌中点数最小的一张打出。如果这样的牌不存在，那么小 F 不会接牌（也就是不会出牌）。

注意，无论小 F 打出什么牌，本轮都立即结束，扶苏不会继续接牌，而是会开启下一轮出牌。

给出扶苏的出牌顺序，请你求出小 F 最终手里剩了几张牌。

## 输入格式

第一行是三个整数，表示一个人的手牌数 $n$，花色的上界 $m$ 和点数的上界 $r$。  
第二行有 $n$ 个整数，第 $i$ 个整数表示扶苏第 $i$ 张牌的花色 $f1_i$。  
第三行有 $n$ 个整数，第 $i$ 个整数表示扶苏第 $i$ 张牌的点数 $p1_i$。  
第四行有 $n$ 个整数，第 $i$ 个整数表示小 F 第 $i$ 张牌的花色 $f2_i$。  
第五行有 $n$ 个整数，第 $i$ 个整数表示小 F 第 $i$ 张牌的点数 $p2_i$。  
第六行是一个长度为 $n$ 的排列，描述扶苏的出牌情况。第 $i$ 个整数 $p_i$ 表示扶苏第 $i$ 轮出了第 $p_i$ 张牌。

## 输出格式

输出一行一个整数，表示坏蛋小 F 结束时手里剩余的牌数。

## 样例 #1

### 样例输入 #1

```
3 1 2
1 1 1
1 2 1
1 1 1
2 2 1
2 3 1
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
3 2 2
1 2 1
1 1 1
1 2 1
2 2 2
1 2 3
```

### 样例输出 #2

```
0
```

## 提示

### 样例 1 解释

小 F 花色为 $1$ 且点数也为 $1$ 的牌管不住任何牌。其余牌都被打出去了。

### 数据规模与约定

- 对于 $10\%$ 的数据，$r = 1$；
- 对于 $20\%$ 的数据，$n = 1$；
- 对于 $50\%$ 的数据，$m = 1$；
- 对于 $100\%$ 的数据，$1 \leq n,m,r \leq 100$，$1 \leq f1_i, f2_i \leq m$，$1 \leq p1_i, p2_i \leq r$。$1 \leq p_i \leq n$，$p$ 是长度为 $n$ 的排列。
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

const int maxn = 105;
int card[maxn][maxn], n, m, r;
int fsf[maxn], fsp[maxn];
int xf[maxn], xp[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m, r);
    for (int i = 1; i <= n; ++i) read(fsf[i]);
    for (int i = 1; i <= n; ++i) read(fsp[i]);
    for (int i = 1; i <= n; ++i) read(xf[i]);
    for (int i = 1; i <= n; ++i) read(xp[i]);
    
    for (int i = 1; i <= n; ++i) {
        card[xf[i]][++card[xf[i]][0]] = xp[i];
    }
    int q, ans = n;
    for (int i = 1; i <= n; ++i) {
        read(q);
        int low = 0x7fffff, lowid = -1;
        for (int j = 1; j <= card[fsf[q]][0]; ++j) {
            if (card[fsf[q]][j] > fsp[q] && card[fsf[q]][j] < low) {
                low = card[fsf[q]][j];
                lowid = j;
            }
        }
        if (lowid != -1) {
            card[fsf[q]][lowid] = 0;
            ans--;
        }
    }
    writeln(ans);
    return 0;
}