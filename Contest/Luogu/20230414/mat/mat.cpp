/*
# Matrix

## 题目背景

Matrix 是电影《黑客帝国》的英文名称，同样也是英文名词「矩阵」。

这是一道 **hack 题**。在此类型的题目中，你将得到**一个**问题和**一个**解决对应问题的代码，但是给出的代码不能对于某些输入给出正确的输出。不能给出正确的输出的情况包括：

1. 输出错误的结果。
2. 运行超时。
3. 产生一些运行时未定义行为。目前技术可检测的未定义行为仅包括数组越界。

对于这一问题，你需要提交一份符合要求的输入数据，使得给定的代码不能给出正确的输出。你可以直接使用『提交答案』功能，也可以提交一份以任何语言写成的数据生成器。

---
**提示：如果你使用提交答案功能，请在提交其他题目时记得将语言改回你所使用的语言。**

## 题目描述

以下给出这道题目的叙述：

假设你处在一个 $N \times N$ 的矩阵中。矩阵左上角坐标为 $(1, 1)$，右下角坐标为 $(N, N)$。矩阵中的每个位置 $(i, j)$ 都有两个权值 $a _ {i, j}$，$b _ {i, j}$。

我们定义两点 $(x _ 1, y _ 1)$，$(x _ 2, y _ 2)$ 之间的「距离」为曼哈顿距离，即「距离」$ = |x _ 1 - x _ 2| + |y _ 1 - y _ 2|$。

我们定义你获胜，当且仅当你处在一个位置 $(x _ 0, y _ 0)$，满足这个位置与 $(N, N)$ 间的「距离」小于等于 $2$。

初始时你处在矩阵的左上角$(1, 1)$，且你手头有无限个金币。在矩阵中的每个坐标处，你可以无限次地进行如下两种操作：（假设目前你所在的坐标是 $(i, j)$）

- 花费 $a _ {i, j}$ 个金币，向右移动一格（列坐标 $j$ 增加 $1$）。
- 花费 $b _ {i, j}$ 个金币，向下移动一格（行坐标 $i$ 增加 $1$）。

现在你想要知道，为了获胜，你至少需要花费多少金币。

## 输入格式

输入共 $2N + 1$ 行。

第一行为一个整数 $N$，代表矩阵的大小。  
第二行至第 $N + 1$ 行，每行 $N$ 个整数，其中第 $i + 1$ 行第 $j$ 个整数代表 $a _ {i, j}$。  
第 $N + 2$ 行至第 $2N + 1$ 行，每行 $N$ 个整数，其中第 $N + i + 1$ 行第 $j$ 个整数代表 $b _ {i, j}$。

## 输出格式

输出一行一个整数，代表为了获胜需要花费的最小硬币数量。

## 样例 #1

### 样例输入 #1

```
4
1 9 2 6
4 2 8 3
2 3 2 4
2 2 3 8
9 2 8 7
1 4 6 6
2 6 5 1
8 7 3 7
```

### 样例输出 #1

```
10
```

## 提示

### 样例组与实际输入的说明

如果你直接采用『提交答案』的方式，请将输入数据命名为 `1.in`，并打成 zip 压缩包进行提交；

如果你采用提交数据生成器的方式，你的生成器应当**输出对应的输入数据**。

显然，你的程序不应该读入『输入格式』里提到的任何内容（而应该构造它们），也不应该输出『样例输出』里提到的任何内容（而是只输出你构造的输入数据）。你不应该使用样例测试你的程序，这只是对这一问题的样例说明。

### 数据规模要求

你给出的数据必须满足如下要求：

1. 完全符合『输入格式』的规定，不能有多余的输入，但是可以有行末空格和文末回车。
2. 数据中所有的数字都应为整数。
3. $1 \leq n \leq 2 \times 10 ^ 3$，$1 \leq a _ i, b _ i \leq 100$。

### 目标代码

你需要 hack 如下的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[2005][2005], b[2005][2005];
int f[2005][2005], n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &b[i][j]);
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            f[i][j] = 1000000000;
    f[1][1] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (i == 1 && j == 1)
				continue;
			f[i][j] = min(f[i][j], f[i - 1][j] + b[i - 1][j]);
			f[i][j] = min(f[i][j], f[i][j - 1] + a[i][j - 1]);
        }
    int ans = 1000000000;
    ans = min(ans, f[n - 2][n]);
    ans = min(ans, f[n][n - 2]);
    ans = min(ans, f[n - 1][n - 1]);
    printf("%d\n", ans);
    return 0;
}
```

目标代码的编译选项为 `-std=c++14 -fno-asm -O2`。编译器为洛谷提供的 g++。你可以在『在线 IDE』中选择 C++14 语言来获得完全相同的编译环境。

### 判分说明

本题共一个测试点，对应唯一一个问题，hack 成功则对应测试点返回 accepted。

#### 数据判定

你给出的数据必须完全符合『数据规模要求』，否则将得到 Unaccepted 的结果。

#### 超时判定

程序每执行若干条指令，我们会检测一遍程序的运行时间。我们保证两次检测之间的指令条数是一个输入规模无关的量，也即每执行 $O(1)$ 条指令会进行一次检测。且两次检测之间的指令条数不会太多，一般不超过 $100$ 条 C++ 语句。

如果程序的运行时间超过 $500 \text{ms}$，则判定为程序运行超时，返回 accepted 结果。

#### 结果错误判定

如果程序在规定的时间内结束且给出了一个输出，我们会比较这个输出和**完全正确的输出**，如果二者不同，则判定为 hack 成功，返回 accepted 结果。

#### 未定义行为判定

我们会在每次**显式**的调用数组元素前判断数组下标是否超过数组范围，如果超过，则判定为 hack 成功，返回 accepted 结果。

这就是说，如果你希望通过未定义行为进行 hack，只能对显式的调用数组元素的行为进行 hack。

### 样例程序

如果你使用『提交答案』功能，请务必保证打开压缩包后能且仅能**直接**看到一个 `.in` 文件。这就是说，文件结构必须是：

```plain
ans.zip
 |---1.in
```

这一个文件不应该被额外的文件夹包含，即文件结构不能是：

```plain
ans.zip
 |---ans(folder)
      |---1.in
```

### 关于评测信息的说明

如果 hack 成功，对应测试点的信息为 accepted。如果返回其他信息，说明程序本身有误。

例如，如果返回 TLE，不代表成功的将对应程序 hack 至超时，而是表示数据生成器本身运行超时，测试点不得分。

特别的，返回 UKE 结果可能是数据不合法（有多余内容、缺少内容或数据范围不符合要求）。
*/

// maker.cpp 生成器

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

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    
}
