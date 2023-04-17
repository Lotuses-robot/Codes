/*
# 排名

## 题目描述

ICPC 比赛中，决定两个队排名的是通过题目数和罚时。

比较两个队排名先后的具体步骤如下：

- 首先比较两个队通过题目数。若不同，则通过数更多者排名更靠前。
- 若两队通过题目数相同，比较两个队罚时。若不同，则罚时更小者排名更靠前。
- 若通过题目数与罚时均相同，则两队排名相同。**本题保证不存在这种情况。**

现在给出两个队伍的通过数和罚时，你需要判断哪个队伍排名更靠前。

## 输入格式

输入共两行。

输入的第一行为两个整数 $A_1,P_1$，分别代表第一个队的通过数和罚时。

输入的第二行为两个整数 $A_2,P_2$，分别代表第二个队的通过数与罚时。

## 输出格式

输出一行一个字符串。

若第一个队排名更靠前，输出 `"\n"`（包含引号）。

若第二个队排名更靠前，输出 `"\t"`（包含引号）。

## 样例 #1

### 样例输入 #1

```
2 1000
1 1
```

### 样例输出 #1

```
"\n"
```

## 样例 #2

### 样例输入 #2

```
3 200
3 100
```

### 样例输出 #2

```
"\t"
```

## 提示

### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \le A_1,A_2 \le 15$，$1 \le P_1,P_2 \le 5000$。
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
    
    int a1, p1, a2, p2;
    read(a1, p1, a2, p2);

    if (a1 > a2) {
        puts("\"\\n\"");
    } else if (a1 < a2) {
        puts("\"\\t\"");
    } else {
        if (p1 < p2) {
            puts("\"\\n\"");
        } else {
            puts("\"\\t\"");
        }
    }
    return 0;
}
