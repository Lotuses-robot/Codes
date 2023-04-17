/*
# 扶苏与 0

## 题目描述

一扶苏一认为，有一些数字中，有零的影子。

如图，在数字 $2,6,9,0$ 中有 1 个零的影子，而在数字 $8$ 中有 2 个零的影子。

给出一个数，求其中零的影子的个数。

## 输入格式

输入一行一个整数 $X$。

## 输出格式

输出一行一个整数，为你的答案。

## 样例 #1

### 样例输入 #1

```
123456789
```

### 样例输出 #1

```
5
```

## 提示

### 数据规模与约定

对于 $20\%$ 的数据，$1 \le X < 10$；  
对于 $60\%$ 的数据，$1 \le X < 10^9$；  
对于 $100\%$ 的数据，$1 \le X < 10^{18}$。
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

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    long long x;
    read(x);
    int ans = 0;
    while (x) {
        switch(x % 10) {
            case 0: ans += 1; break;
            case 2: ans += 1; break;
            case 6: ans += 1; break;
            case 9: ans += 1; break;
            case 8: ans += 2; break;
        }
        x /= 10;
    }
    writeln(ans);
    return 0;
}
