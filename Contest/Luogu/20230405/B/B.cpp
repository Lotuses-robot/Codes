/*
# 「GMOI R2-T2」猫耳小

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/r8a6ylx3.png)

## 题目描述

小 R 是一个可爱的猫耳女孩子，她喜欢研究数列的 $\operatorname{mex}\text{*}$。

现在她有一个长度为 $n$ 的数列 $a$。她讨厌整数 $k$，因此她希望修改数列 $a$ 的若干个元素为任意**自然数**，使得 $a$ 的任意**连续非空子串**的 $\operatorname{mex}$ 都不等于 $k$。

请你求出最少需要修改多少个元素。

$\text{*}$ 本题中，数列的 $\operatorname{mex}$ 被定义为数列中最小未出现的**自然数**，例如：

- $\operatorname{mex}\{1,2,3\}=0$，因为 $0$ 是自然数。
- $\operatorname{mex}\{0,1,3\}=2$。
- $\operatorname{mex}\{0,1,2\}=3$。

## 输入格式

第一行两个整数 $n,k$，表示数列长度和小 R 讨厌的数。

第二行 $n$ 个整数，第 $i$ 个整数为 $a_i$，表示这个数列的第 $i$ 项。

## 输出格式

一行一个整数，表示最少需要修改的元素个数。

## 样例 #1

### 样例输入 #1

```
5 2
1 0 1 3 0
```

### 样例输出 #1

```
2
```

## 提示

**样例解释**

一种方案是将 $\{1,0,1,3,0\}$ 改为 $\{1,1,1,3,2\}$，共改动两个元素。

可以证明不存在更优的方案。

---

**本题使用 Subtask 捆绑测试。**

| Subtask | $n\le$ | $k\le$ | $a_i\le$ | 特殊性质 | 对应测试点 | 总分 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $6$ | $6$ | $6$ | $-$ | $1\sim 2$ | $10$ |
| $1$ | $100$ | $5\times 10^3$ | $5\times 10^3$ | $-$ | $3\sim 5$ | $20$ |
| $2$ | $5\times 10^3$ | $1$ | $5\times 10^3$ | $-$ | $6\sim 10$ | $20$ |
| $3$ | $5\times 10^3$ | $5\times 10^3$ | $5\times 10^3$ | $\bf A$ | $11\sim 15$ | $20$ |
| $4$ | $5\times 10^3$ | $5\times 10^3$ | $5\times 10^3$ | $-$ | $16\sim 20$ | $30$ |

特殊性质 $\bf A$：保证 $a_i < k$。

对于 $100\%$ 的数据，$1\le n\le 5\times 10^3$，$0\le k,a_i\le 5\times 10^3$。
*/
/*
题解：
按 $i$ 枚举 $j$，依次检查 $MEX(i,j)$ 是否合规。

因为 $MEX$ 不降，所以当 $MEX(i,j) > k$ 时 $i = j$。

如果刚好碰到 $MEX(i,j) = k$ 的时候就要修改一个，贪心的就修改最后一个呗。

那么修改 $a[j] = k$ 且 $i = j + 1$ 继续寻找。

注：MEX 的意思是序列中出现的最小的自然数。
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

#define maxn 5005

bool ck[maxn];
int num[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, k, i = 1, q = 0, ans = 0;
    read(n, k);
    for (int j = 1; j <= n; j++) {
        // int x;
        // read(x);
        // ck[x] = true;
        // while (ck[q]) q++;
        // if (q == k) {
        //     // ck[x] = false;
        //     memset(ck, 0, sizeof(ck));
        //     q = 0;
        //     i = j + 1;
        //     ans++;
        // } else if (q > k) {
            
        // }
        read(num[j]);
    }

    int j = 1;
    for (j = 1; j <= n; j++) {
        ck[num[j]] = true;
        while (ck[q]) q++;
        if (q == k) {
            ck[num[j]] = false;
            memset(ck, 0, sizeof(ck));
            q = 0;
            i = j + 1;
            ans++;
        } else if (q > k) {
            i++;
            j = i - 1;
            q = 0;
            memset(ck, 0, sizeof(ck));
        }
    }
    printf("%d\n", ans);
    return 0;
}
