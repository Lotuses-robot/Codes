你可以用各种方法推导出这个公式，但是下面这个方法非常简洁有趣：

假设有一个大小为 $(n + 2)^3$ 的立方体“包住了”这个大小为 $n^3$ 的立方体。假如这个边长为 $n$ 的立方体中的每一条直线都“往两头延伸”，那么每一条线都会“穿透”外面更大的立方体中的两个单位立方体。于是，我们只需要计算出 $n^3$ 的立方体“外面的一层壳”有多少个单位立方体就行了。显然，壳子有 $(n + 2)^3 − n^3$ 个单位立方体。这个数除以 $2$ 即是我们要求的答案。

注意特判 $n=1$ 的情况。

参考代码：
```cpp
// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

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

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    if (n == 1) {
        printf("%d\n", 1);
        return 0;
    }
    int ans = 28 + (n * n - 4) * 3 + (n - 2) * 3 * 2;
    printf("%lld\n", ans);
    return 0;
}

```