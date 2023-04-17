大前提有 $n$ 种情况，分别是 $n+1$ 加入到环中的 $n$ 种情况。

将环重新编号（$0\sim n$），已知 $c_i$，$e_i$。

设从 $i$ 号开始，计算 $s_{i - 1} = 0, s_j=s_{j - 1} + e_j$ 环状前缀和；

求
$$
\min_i\sum_{j = 0} ^ n c_j \times|s_j|
$$
就是说，$e$ 的前缀和与 $c$ 同位结合，前缀和开始的位置依次向后。

每一次迭代，$s_j \to s_j - s_{i - 1}, s_{i - 2} = s_{\text{all}}$。

也就是说，如果要~~暴力~~直接统计（无论用什么统计方法，由于是计算最大值，最终都需要计算 $n^2$ 种情况）的话，时间复杂度是 $O(n^2)$。

目标：$O(n) \sim O(n \log n)$。

---

## sub1

观察特殊数据，$i \in [1,n+1](i∈\Z)$，满足 $c_i=0$。

由于是 $c_i = 0$，式子总为 $0$。答案为 $0$。

---

## sub3

观察特殊数据，$i \in [1,n+1](i∈\Z)$，满足 $c_i=1$。

与特殊性质 $A$ 有所区别的，是后面 $c_i$ 的数值。

带入。

即
$$
\min_i\sum_{j = 1} ^ {n + 1} |s_j|
$$
题意变为插入一个下标为 $i$ 位置的 $(e,c)_{i + 1}$ 使得从某一位置开始统计的环形前缀和绝对值总和最小。

要求 $O(n)$ 或 $O(n\log n)$。

（提示）$i$ 的取舍并不合适。

（提示）（关键）可以改变一下前缀和的形式：$s_i' = s_{i - 1}' + e_i$，对应到当 $s_i$ 做开头时的环形前缀和，$s_j = s_j' - s_{i - 1}'$，**这里 $s'$ 表示以 $1$ 作为开头的前缀和**。

（提示）事实上，无论 $s'$ 表示从何处开始的前缀和，计算前缀和的方式都是 $s_j = s_j' - s_{i - 1}'$。

（提示）证明：当 $j > i$ 时，这条式子是原形式。当 $i > j$ 时，即跨边界进行了前缀和时，$(s_j'-s_{i-1}') \to (-\sum_{q = i} ^ j e_q)$；由于整个环加和为 $0$，那么这一段的相反数正好就是这一段跨边界的前缀和值。

（提示）那么就可以将 $s$ 数组适当联想。

由于 $i$ 并不好降低枚举复杂度，所以这一步直接枚举。（修改插入 $c_{n + 1}$ 的位置对前缀和的影响为单点修改，不会影响整体复杂度）

有了上面的提示，那么可以转换为：
$$
\min_i \sum_{j = 1} ^ {n + 1} |s_j' - s_{i - 1}'|
$$
单独抽出来，
$$
\sum_{j = 1} ^ {n + 1} |s_j' - s_i'|\ (为方便讨论将\ (i - 1) \to i)
$$
这条式子不就是所有点到 $i - 1$ 的距离之和吗？

于是把数组 $s$ 抽象到坐标轴上，那么问题转化为在一个点集中选择一个点让使所有点到该点的距离之和**最小**。于是问题就转换为我们熟悉的问题。

结论是：理想到数轴上的中间的位置，即位置 $i$ 满足在中间的位置。

如果是偶数个点，那么左右两边的点都是欧克的。

理由，任意向中间移动距离 $x$，并当前的位置为 $i$，都会增加少 $(i - 1)x$ 的总贡献，且减少 $(n - i + 1)x$，那么相减就是 $(2i-2-n)x$。当 $i = n / 2 + 1$ 即 $2(i - 1) =n $ 时，（就是说有偶数个点并在中心左边）原式 $=0$。即当 由中心偏左位置 向 中心偏右位置 移动时，移动贡献为 $0$。

利用这个线性的性质，可以 $O(1)$ 计算出最优的**开始位置** $b$。

解决开始问题后，就剩下统计最终的答案。

那么如何 $O(\log n) \text{ or } O(1)$ 求
$$
\sum_{j = 1} ^ {n + 1} |s_b' - s_j'|
$$
其中 $b$ 为选定的开始，并且在 $s'$ 有单点修改（插入的位置）的情况呢？（此处为本题难点）

对 $s'$ 排序，得到 $t$。拆开这条式子，可以得到
$$
\sum_{j = 1} ^ {b'} (s_b' - s_j') \cdot c_j + \sum_{j = b' + 1} ^ {n + 1}(s_j' - s_b')\cdot c_j
$$
所以最后答案是
$$
\sum_{j = b' + 1} ^ {n + 1}s_j'\cdot c_j -\sum_{j = 1} ^ {b'} s_j' \cdot c_j + s_b'\cdot \left(\sum_{j = 1} ^ {b'} c_j- \sum_{j = b' + 1} ^ {n + 1}c_j\right)
$$
于是我们发现需要维护的是区间的 $\sum s_j'\cdot c_j$ 和 $\sum c_j$。

考虑到每次改变某一个前缀和位置的时候要求 $\log n$ 做，修改的内容是什么？

修改的就是 $s_j'$，和对应 $c_j$ 的位置。（由于是有序的，所以得保证 $s_j'$ 和 $c_j$ 位置是对应的，否则统计不了）

如果每一次修改 $s_j'$ 都移动整个数列来让整个线段树变得有序，那么就不是 $O(\log n)$ 的了。

可以考虑用空间换时间，由于每次修改的内容是确定的，并且每一个位置对应的修改的最终值是确定唯一的，那么可以想到开到两倍的线段树，初始将所有的 $s_j'$ 和 $s_j' - (e_j + e_{n + 1})$（这里的式子原因在后面）都预加入，一起排序，得到的预排序结果就包含了增加修改的部分。

解决了有序的问题之后，考虑解决前缀和改变后，整个前缀和数组的改变。

这是样例前缀和数组改变的规律：

```
3 -5 1 1  3 -2 -1 0
          1 3  2  2
3 -5 1 1  3 -2 -1 0
          1 3  2  2
3 1 -5 1  3 4 -1 0
          1 2 3  2
1 3 -5 1  1 4 -1 0
          2 1 3  2
```

可以通过观察数据得到以下规律，

由于一开始 $e_{n + 1}$ 已经预加入到 $s'$ 中，那么设当前移动后来到了 $i$ 的位置，那么就要修改 $s_i \to s_i - (e_i + e_{n + 1})$。

维护的方法，每次移动的时候，先删除当前的 $s'$，再加入 $s_i - (e_i + e_{n + 1})$ 就好聊。别忘了移动 $c_i$。

---

解决了性质 B，其实在性质 B 之后可以直接做正解了。只是需要多维护个 $c$ 就可以了。每次只需要移动一次 $c_{i}$ 和 $c_{i + 1}$，同时维护一下两个 $\Sigma$ 就口以了。

在前文中已经暗示了含 $c_i$ 的做法，所以不多讲解；我的 Code：

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

#define int long long
const int maxn = (int)(2e5 + 100) << 2;
const int inf = 0x3f3f3f3f3f3f3f3fll;
int n;
int c[maxn], e[maxn];
int s[maxn], t[maxn], tot = 0;

struct Tree {
    struct Node {
        int l, r, lc, rc;
        int c, x; // x mean s * c
    } nds[maxn << 2];

    int cnt = 0;
    int init(int l, int r) {
        int id = ++cnt;
        nds[id] = {l, r, -1, -1, 0, 0};
        if (l == r) return id;
        int mid = (l + r) >> 1;
        nds[id].lc = init(l, mid);
        nds[id].rc = init(mid + 1, r);
        return id;
    }

    void add(int u, int pt, int s, int c, int pos) {
        nds[u].c += c * pos; nds[u].x += c * s * pos;
        if (nds[u].l == nds[u].r) return;
        int mid = (nds[u].l + nds[u].r) >> 1;
        if (pt <= mid) add(nds[u].lc, pt, s, c, pos);
        else add(nds[u].rc, pt, s, c, pos);
    }

    int queryc(int u, int l, int r) {
        if (u == -1) return 0;
        if (l == nds[u].l && nds[u].r == r) return nds[u].c;
        int mid = (nds[u].l + nds[u].r) >> 1;
        if (r <= mid) return queryc(nds[u].lc, l, r);
        else if (l > mid) return queryc(nds[u].rc, l, r);
        else return queryc(nds[u].lc, l, mid) + queryc(nds[u].rc, mid + 1, r);
    }
    int queryx(int u, int l, int r) {
        if (u == -1) return 0;
        if (l == nds[u].l && nds[u].r == r) return nds[u].x;
        int mid = (nds[u].l + nds[u].r) >> 1;
        if (r <= mid) return queryx(nds[u].lc, l, r);
        else if (l > mid) return queryx(nds[u].rc, l, r);
        else return queryx(nds[u].lc, l, mid) + queryx(nds[u].rc, mid + 1, r);
    }

    int find() {
        int u = 1, c = 0, cpos = nds[1].c / 2;
        while (nds[u].l != nds[u].r) {
            if (c + nds[nds[u].lc].c <= cpos) {
                c += nds[nds[u].lc].c;
                u = nds[u].rc;
            } else {
                u = nds[u].lc;
            }
        }
        return nds[u].l;
    }

    int query() {
        int b = find(), qs;
        int lc = queryc(1, 1, b), rc = queryc(1, b + 1, tot);
        int lx = queryx(1, 1, b), rx = queryx(1, b + 1, tot);
        if (lc - rc != 0) qs = queryx(1, b, b) / queryc(1, b, b);
        else qs = 0;
        return (lc - rc) * qs - (lx - rx);
    }
} tr;



signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n);
    for (int i = 1; i <= n + 1; ++i) read(c[i]);
    for (int i = 1; i <= n; ++i) read(e[i]), t[++tot] = s[i] = s[i - 1] + e[i];
    e[n + 1] = -s[n]; t[++tot] = s[n + 1] = s[n] + e[n + 1];
    for (int i = 1; i <= n; i++) {
        t[++tot] = s[i] - (e[i] - e[n + 1]);
    }
    std::sort(t + 1, t + tot + 1);

    tr.init(1, tot);
    for (int i = 1; i <= n + 1; i++) { // 为什么是 n + 1
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], 1);
    }
    int ans = inf;
    for (int i = n; i >= 1; i--) {
        ans = std::min(ans, tr.query());
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], -1);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i + 1]) - t, s[i + 1], c[i + 1], -1); // 为什么要更新这里？
        // writeln(std::lower_bound(t + 1, t + tot + 1, s[i]) - t, tr.queryc(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, std::lower_bound(t + 1, t + tot + 1, s[i]) - t));
        s[i] -= (e[i] - e[n + 1]); std::swap(c[i], c[i + 1]);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], 1);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i + 1]) - t, s[i + 1], c[i + 1], 1);
    }
    writeln(ans);
    return 0;
}

```



