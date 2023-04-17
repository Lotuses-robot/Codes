实验室中有一个由 $n$ 个实验腔连接而成的环形轨道，其中第 $i$ 个实验腔顺时针连向第 $i+1$ 个实验腔（特别的，第 $n$ 个实验腔连向第 $1$ 个实验腔）。同时还有一个标号为 $n+1$ 的新建实验腔要接入这个环形轨道。它可以接在任意两个原本相连的实验腔之间。

第 $i$ 个实验腔可以将带电荷量为 $Q$ 的粒子运输到它的下一个实验腔，这个过程花费的能量为 $\vert Q \vert \times c_i$。除此之外，第 $i$ 个实验腔本身就存储了量为 $e_i$ 的电荷（电荷量有正负）。由于众所周知的电荷守恒定律，第 $n+1$ 个实验腔储存的电荷量与前 $n$ 个实验腔储存的总电荷量的代数和为 $0$。

小 Z 有一个原本不带电的粒子。等到第 $n+1$ 个实验腔接入轨道后，他要任选一个实验腔（包括第 $n+1$ 个）作为出发点，将粒子放入，并使之在实验腔的能量驱动下顺时针环游一周回到出发点。粒子每到达一个实验腔（包括出发点），它所带电荷量就会变成原来所带的电荷量和这个实验腔所储存的电荷量的代数和。

**注意：电荷量会先加上实验腔所含电荷量，再计算能量贡献。**

现在，小 Z 想知道，在所有接入新建实验腔并选定出发点的方案中，粒子环游一周所需的能量最少为多少？

提示：

$$
\sum_{j = 1} ^ {n + 1} |s_b' - s_j'| \cdot c_j
$$

本代码做法是维护一个 $\sum s \cdot c$ 和 $\sum c$ 之后用二分寻找分界点 $c_i$ 后直接统计。省略了读入和输出函数 read 和 writeln。


```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define int long long
const int maxn = (int)(2e5 + 100) << 2;
const int inf = 0x3f3f3f3f3f3f3f3fll;
int n;
int c[maxn], e[maxn];
int s[maxn], t[maxn], tot = 0;

struct Tree {
    struct Node {
        int l, r, lc, rc;
        int c, x;
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
        nds[u].c += c * pos; nds[u].x += /*#(1)#*/;
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
            if ( /*#(2)#*/ ) {
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
        return /*#(3)#*/;
    }
} tr;



signed main() {
    read(n);
    for (int i = 1; i <= n + 1; ++i) read(c[i]);
    for (int i = 1; i <= n; ++i) read(e[i]), t[++tot] = s[i] = s[i - 1] + e[i];
    e[n + 1] = -s[n]; t[++tot] = s[n + 1] = s[n] + e[n + 1];
    for (int i = 1; i <= n; i++) {
        t[++tot] = /*#(4)#*/;
    }
    std::sort(t + 1, t + tot + 1);

    tr.init(1, tot);
    for (int i = 1; i <= /*#(5)#*/; i++) {
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], 1);
    }
    int ans = inf;
    for (int i = n; i >= 1; i--) {
        ans = std::min(ans, tr.query());
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], -1);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i + 1]) - t, s[i + 1], c[i + 1], -1);
        // writeln(std::lower_bound(t + 1, t + tot + 1, s[i]) - t, tr.queryc(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, std::lower_bound(t + 1, t + tot + 1, s[i]) - t));
        s[i] -= (e[i] - e[n + 1]); std::swap(c[i], c[i + 1]);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], 1);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i + 1]) - t, s[i + 1], c[i + 1], 1);
    }
    writeln(ans);
    return 0;
}

```

1. A. `c * s`

   B. `c * s * pos`

   C. `s`

   D. `s * pos`

2. A. `nds[nds[u].lc].c <= cpos`

   B. `nds[nds[u].rc].c <= cpos`

   C. `c + nds[nds[u].lc].c <= cpos`

   D. `c + nds[nds[u].rc].c <= cpos`

3. A. `(lc - rc) * qs + rx - lx`

   B. `(lc - rc) * qs + lx - rx`

   C. `(rc - lc) * qs + rx - lx`

   B. `(rc - lc) * qs + lx - rx`

4. A. `s[i] + e[n + 1]`

   B. `s[i] - e[n + 1]`

   C. `s[i - 1] + e[n + 1]`

   D. `s[i - 1] - e[n + 1]`

5. A. `n * 2 + 1`

   B. `n - 1`

   C. `n`

   D. `n + 1`
