/*
# 写大作业 (Easy Version)

## 题目背景

**本题与 Hard Version 的区别在于：输入的是字符串而不是数列，输入输出格式不同，数据规模不同**。

## 题目描述

扶苏为了写计算理论大作业已经 $36$ 小时没有合眼了。

为了能快点睡觉，扶苏找到了 $n$ 份文献，第 $i$ 份文献是一个字符串 $s_i$，她打算把这些文献组合起来。

具体来说，一共有两种操作：

- `1 x y`：把文献 $s_x$ 整体拼接到 $s_y$ 的后面，然后删除 $s_x$。
- `2 x y`：查询 $s_x$ 和 $s_y$ 是否**相似**。

我们保证在 `1 x y` 操作出现后，字符串 $s_x$ **不会**出现在接下来的任何操作中。这就是说，操作 $1$ 至多有 $n-1$ 次。

**相似**的定义是：对两个字符串 $s_x$ 和 $s_y$，如果存在一种重新排列 $s_x$ 的方法，使得重排后的 $s_x$ 和 $s_y$ 相等，则称 $s_x$ 和 $s_y$ **相似**。

例如，假设 $s_1 = \texttt{ab}, s_2 = \texttt{cd}, s_3 = \texttt{abcd}$，则执行 `1 1 2` 后，$s_1$ 被删除，$s_2 = \texttt{cdab}, s_3 = \texttt{abcd}$；继续执行 `2 2 3` 后，因为可以把 $s_2$ 重排为 $\texttt{abcd}$，所以 $s_2$ 和 $s_3$ 相似。

注意，操作 $2$ 不会对字符串做出实际修改。

## 输入格式

第一行是两个整数，分别表示文献的数量 $n$ 和操作的数量 $q$。  
接下来 $n$ 行，每行一个字符串，第 $i$ 行的字符串表示 $s_i$。  
接下来 $q$ 行，每行三个整数 $op, x, y$，其含义见『题目描述』。

## 输出格式

对个操作 $2$，输出一行一个字符串。如果 $s_x$ 和 $s_y$ 相似，则输出 $\texttt{Yes}$，否则输出 $\texttt{No}$。

## 样例 #1

### 样例输入 #1

```
4 4
ab
cd
abcd
abcc
1 1 2
2 2 3
2 3 4
2 2 4
```

### 样例输出 #1

```
Yes
No
No
```

## 提示

### 数据规模与约定

- 对 $30\%$ 的数据，保证 $n = 2$，$q = 1$。
- 对 $60\%$ 的数据，保证 $n \leq 5$，$q \leq 5$，$|s_i| \leq 5$。
- 对 $100\%$ 的数据，保证 $1 \leq n,q \leq 10^5$，$1 \leq o \leq 2$，$1 \leq x, y \leq n$，且输入字符串的总长度不超过 $10^6$，输入字符串仅含小写英文字母，且不是空串。
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

struct Map {
    int cnt[26];
    Map operator + (Map b) const {
        Map res;
        for (int i = 0; i < 26; ++i)
            res.cnt[i] = cnt[i] + b.cnt[i];
        return res;
    }
    bool operator == (Map b) const {
        for (int i = 0; i < 26; ++i)
            if (cnt[i] != b.cnt[i])
                return false;
        return true;
    }
} mp[100005];

char ch[1000005];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, q;
    read(n, q);

    for (int i = 1; i <= n; i++) {
        scanf("%s", ch); int len = strlen(ch);
        for (int j = 0; j < len; j++) {
            mp[i].cnt[ch[j] - 'a']++;
        }
    }

    while (q--) {
        int op, x, y;
        read(op, x, y);
        if (op == 1) {
            mp[y] = mp[x] + mp[y];
        } else {
            if (mp[x] == mp[y]) {
                puts("Yes");
            } else {
                puts("No");
            }
        }
    }
    return 0;
}
