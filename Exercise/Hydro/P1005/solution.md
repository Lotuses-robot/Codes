本题改编自 GDKOI 2008 Day2。

原题解仅列出了 dp 的规律，并未解释原因。

但这是我的递推式（实际上这已经不叫 dp 了）却和他不一样：

$$
f[i][j] = f[i - 1][j] + f[j - 1][i] + i
$$

来由：

递推首先讲究不重不漏的分类讨论。

如一个 3x2 的图（fl 表示 那个人）：

```
x   fl
x   x
x   x
```

将其分割

```
x   fl
x   x
*******
x   x
```

上面的单独算一种情况：即为 $f[i - 1][j]$。
而当 fl 突破分界线来到 $i = n$ 的地方时，再将其分割（如果图体验不佳请更换等宽字体）：

```
x | x
x | x
x | fl
```

当 fl 转向左边时，将图倒过来看，分界线左边停下来的情况就变成了 $f[j - 1][i]$。

而这两个简单相加是不行的，因为 $f[j - 1][i]$ 有个限制条件：开始不能左转。即少算了这几格的情况（用 y 表示）：

```
y | x 
y | x
x | fl
```

（左边也许有其他的 x 但是不会有影响因为统计过了。

所以要加上 $i - 1$。（y 的数量）

但是还有一个特别特殊的格子：即 fl 上张图所站的地方。

你会发现，$f[i - 1][j]$ 和 $f[j - 1][i]$ 都没有将其算入，所以还应当加 $1$。

所以最终递推式子就是 $f[i][j] = f[i - 1][j] + f[j - 1][i] + i - 1 + 1$。（消掉 $1$）。

有一些小细节要注意。这里不能使用简单顺序递推的方式，因为 $f[j - 1][i]$ 有可能在当前时刻并未计算。

要么手推递推的顺序，要么费点栈空间使用记忆化搜索。差别不大。

这是 AC Code：

```cpp
// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

int f[1001][1001];

int dfs(int x, int y) {
    if (x == 1) return 1;
    else if (y == 1) return x % 1234567;
    if (f[x][y]) return f[x][y];
    return (f[x][y] = (dfs(x - 1, y) + dfs(y - 1, x) + x) % 1234567);
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        printf("%d\n", dfs(n, m));
    }
    return 0;
}

```

---

这是原题解的讲法和 dp 式子：

```
\	1	2	3	4	5	6	7	8	9
1	1	1	1	1	1	1	1	1	1
2	2	4	7	11	16	22	29	37	46
3	3	8	17	31	51	78	113	157	211
```

啊！想当年著名的 YUYAN 同学就是这样教我们这道题的呀！！！


聪明的同学马上会看到：耶！我发现规律了！第一行的全都是 $1$！！！

更聪明的：耶！我发现的比你多！第一列第 $i$ 行的全都是 $i$！！！

最聪明的：哼！这些算什么？我发现了第 $2$ 行的数是从 $+2$ 到 $+3$ 到 $+4$ 到 $+5$ 一直这样 $+$ 上去的！！！

FL：哈哈哈！你们都没有我聪明！我发现了普遍的规律！！！

$$
f[i][j] = f[i - 1][j] + f[i][j - 1] + j - 1
$$

---

这里的递推式就可以通过顺序递推的方式求得。

也许以后有人能理解这个方程把（（