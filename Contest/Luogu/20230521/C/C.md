普及难度的 $O(n^2)$。

```cpp
// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

#define maxn 1000006

char ch[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, sum = 0;
        read(n);
        scanf("%s", ch + 1);
        for (int i = 1; i <= n; i++) {
            int mx = 0, id = i - 1, val = 0;
            for (int j = i; j <= n; j++) {
                val += ch[j] == '(' ? -1 : 1;

                if (val > mx) {
                    mx = val;
                    id = j;
                } else if (val == mx) {
                    if (id != i - 1) {
                        mx = val;
                        id = j;
                    } 
                }

                sum += std::abs(val) + (id != i - 1 && id != j);
            }
        }
        writeln(sum);
    }
}

```



分别统计 $\text{std::val}$ 和 $\text{(id != i - 1 and id != j))}$？

如何在 $O(n)$ 统计出：
$$
\sum_{l}\sum_{i = l} ^ n |s_i - s_{l - 1}|
$$
其中 $s$ 是对数组 $a$ 的前缀和，$a_i\in \{1,-1\}$。

分讨：
$$
\begin{cases}
s_i - s_{l - 1} & (s_i \ge s_{l - 1}) \\
s_{l - 1} - s_i & (s_i < s_{l - 1})
\end{cases}
$$

$$
\sum_{i = l} ^ n [s_i \ge s_{l - 1}]\cdot s_i - \sum_{i = l} ^ n [s_i < s_{l - 1}]\cdot s_i\\
-(\sum_{i = l} ^ n [s_i \ge s_{l - 1}]\cdot s_{l - 1} - \sum_{i = l} ^ n [s_i < s_{l - 1}]\cdot s_{l - 1})
$$

$$
\sum_{i = l} ^ n [s_i \ge s_{l - 1}]\cdot s_i - \sum_{i = l} ^ n [s_i < s_{l - 1}]\cdot s_i\\
-(\sum_{i = l} ^ n [s_i \ge s_{l - 1}] - \sum_{i = l} ^ n [s_i < s_{l - 1}]) \cdot s_{l - 1}
$$



观察后面这一坨东西，发现好像可以通过排序+线段树（？）的方式做到一遍 $O(\log n)$（[？](https://www.luogu.com.cn/discuss/610920)）。

那么后面的

