/*
# 洛谷评测机模拟器 (Easy Version)

## 题目背景

**本题与 Hard Version 题意完全相同，不同的地方在于数据范围。**

现在假装你是洛谷评测机。这一天，洛谷同时进行了 PION 自测、SCP 自测、ION 自测等等比赛。成千上万的评测落到了你的身上！

## 题目描述

现在已经知道你有 $n$ 个相同性能的评测节点，它们被分别标号为 $1, 2, \cdots, n$。一个评测节点在同一时间只能处理一个评测任务。

在某一时刻，$m$ 个评测任务同时涌入了你。我们将这些任务分别标号为 $1, 2, \cdots, m$。这些评测任务需要的评测时间分别为 $t _ 1 , t _ 2, \cdots, t _ m$。每个评测任务**需要且仅需要一个**评测节点来运行，因此你会按照如下方式按照 $1 \sim m$ 的顺序依次将这些评测任务分配到评测节点上：

对于某个耗时 $t _ i$ 的评测任务，你需要找到目前**累积评测时间**最小的评测节点将任务放入。如果有多个评测节点**累积评测时间**相同且最小，则找一个**标号最小**的节点将任务放入。

> 「累积评测时间」定义：假设对于某个评测节点，其被分配了 $a _ 1, a _ 2, \cdots, a _ k$ 共 $k$ 个任务。那么这个评测节点的「累积评测时间」就是 $t _ {a _ 1} + t _ {a _ 2} + \cdots + t _ {a _ k}$。显然的，如果某个评测节点从未被分配过这 $m$ 个任务中的任何一个，那么这个评测节点的「累积评测时间」是 $0$。

现在，你需要统计出，你的这 $n$ 个评测节点分别接受了哪一些评测任务。

## 输入格式

输入共两行。

第一行为两个整数 $n, m$，代表评测节点数量和评测任务数量。  
第二行为 $m$ 个整数 $t _ 1, t _ 2, \cdots, t _ m$，依次代表这 $m$ 个评测任务的所需时间。

## 输出格式

输出共 $n$ 行，每行若干个整数，两两之间以一个空格隔开。

对于第 $i$ 行，输出第 $i$ 个评测节点接受的评测任务编号从小到大排序后的结果。如果第 $i$ 个评测节点没有被分配任务，那么输出一行一个 $0$。

## 样例 #1

### 样例输入 #1

```
5 10
13 50 90 38 60 64 60 77 6 24
```

### 样例输出 #1

```
1 6
2 8
3
4 7
5 9 10
```

## 样例 #2

### 样例输入 #2

```
12 7
85 99 82 90 14 11 15
```

### 样例输出 #2

```
1
2
3
4
5
6
7
0
0
0
0
0
```

## 提示

### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n, m \leq 5 \times 10 ^ 3$，$0 \leq t _ i \leq 10 ^ 9$。

| 测试点编号 | $n \leq$ | $m \leq$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1 \sim 2$ | $10$ | $10$ | 无 |
| $3 \sim 4$ | $5 \times 10 ^ 3$ | $5 \times 10 ^ 3$ | $t _ i = 0$ |
| $5 \sim 6$ | $5 \times 10 ^ 3$ | $5 \times 10 ^ 3$ | $t _ i = 1$ |
| $7 \sim 10$ | $5 \times 10 ^ 3$ | $5 \times 10 ^ 3$ | 无 |
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define int long long

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


signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int n, m;
    read(n, m);
    std::vector<int> t(1000000);
    for (int i = 1; i <= m; ++i) read(t[i]);
    std::vector<std::vector<int>> ans(1000000);
    std::vector<int> sum(1000000);
    for (int i = 1; i <= m; ++i) {
        int min = 11451419198101164ll, min_id = 0;
        for (int j = 1; j <= n; ++j) {
            if (sum[j] < min) {
                min = sum[j];
                min_id = j;
            }
        }
        ans[min_id].push_back(i);
        sum[min_id] += t[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (ans[i].empty()) {
            puts("0");
            continue;
        }
        // std::sort(ans[i].begin(), ans[i].end());
        for (int j = 0; j < ans[i].size(); ++j) {
            if (j) putchar(' ');
            write(ans[i][j]);
        }
        putchar('\n');
    }
    return 0;
}
