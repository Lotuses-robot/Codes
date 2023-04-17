/*
# 冠军

## 题目描述

某校举行足球比赛，将从 $16$ 强中决出冠军。

以下是 $\dfrac{1}{8}$ 决赛的对阵图：

![](https://cdn.luogu.com.cn/upload/image_hosting/02lru9yw.png)

在蓝色方框中的数字代表场序数，队伍依次用字母 $\texttt{A} \sim \texttt{Q}$ 编号，规定一场比赛字母更靠前的队伍为主场队伍，更靠后的队伍为客场队伍。比分用 `p-q` 的形式给出，$p$ 为主队的进球数，$q$ 为客队的进球数。进球更多的队伍晋级下一轮比赛。

例如，对于场序 $1$ 和 $2$，若比分分别为 $1-2$，$4-3$，则 B 队 和 C 队将晋级下一轮比赛，他们将在场序 $9$ 碰面，且 B 队为主队。

现在，按照场序顺序给出 $15$ 场比赛的比分，问冠军是哪一队？

## 输入格式

输入 $15$ 行，第 $i$ 行为场序 $i$ 的比分，保证比赛没有平局。

## 输出格式

输出一行一个字符，代表冠军队。

## 样例 #1

### 样例输入 #1

```
1-0
1-0
1-0
1-0
1-0
1-0
1-0
1-0
1-0
1-0
1-0
1-0
1-0
1-0
1-0
```

### 样例输出 #1

```
A
```

## 提示

### 数据规模与约定

对于 $30\%$ 的数据，$p,q \in \{0,1\}$；  
对于 $100\%$ 的数据，$0 \le p,q \le 100$。
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

int a[17][2];
int wint[17];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    for (int i = 1; i <= 15; ++i) {
        read(a[i][0], a[i][1]);
    }
    
    for (int i = 1; i <= 8; i++) {
        if (a[i][0] > a[i][1]) {
            wint[i] = i * 2 - 1;
        } else {
            wint[i] = i * 2;
        }
    }

    for (int i = 1; i <= 4; i++) {
        if (a[i + 8][0] > a[i + 8][1]) {
            wint[i] = wint[i * 2 - 1];
        } else {
            wint[i] = wint[i * 2];
        }
    }

    for (int i = 1; i <= 2; i++) {
        if (a[i + 12][0] > a[i + 12][1]) {
            wint[i] = wint[i * 2 - 1];
        } else {
            wint[i] = wint[i * 2];
        }
    }

    if (a[15][0] > a[15][1]) {
        wint[1] = wint[1];
    } else {
        wint[1] = wint[2];
    }

    printf("%c", 'A' + wint[1] - 1);
    return 0;
}
