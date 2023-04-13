#include <bits/stdc++.h>
#define mid (l + r) / 2
using namespace std;

const int maxn = 300005;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n, num, rt;
ll ans = inf, b[maxn], c[maxn], e[maxn], s[maxn];
struct Seg {
	int l, r;
	ll x, c, s;
} t[maxn * 8];
int tot;
Seg merge(Seg p, Seg q) {
	return {0, 0, p.x + q.x, p.c + q.c, p.s + q.s};
}
void insert(int &p, int l, int r, int i, int x, ll c) {
	// s = b[i]
	if (!p) p = ++tot;
	t[p].x += x, t[p].c += c * x, t[p].s += c * b[i] * x;
	if (l == r) return;
	if (i <= mid) insert(t[p].l, l, mid, i, x, c);
	else insert(t[p].r, mid + 1, r, i, x, c);
}
// 大于 k 的第一个数
int find(int p, int l, int r, ll x) {
	if (l == r) return l;
	if (t[t[p].l].c > x) return find(t[p].l, l, mid, x);
	return find(t[p].r, mid + 1, r, x - t[t[p].l].c);
}
// 然后查询一个区间和。
Seg query(int p, int l, int r, int ql, int qr) {
//	cout << l << " " << r << " " << ql << " " <<qr << endl;
	if (r < ql || l > qr) return {0, 0, 0, 0};
	if (ql <= l && r <= qr) return t[p];
	return merge(query(t[p].l, l, mid, ql, qr), query(t[p].r, mid + 1, r, ql, qr));
}
ll get(int x) {
	if (x == -1) return inf;
	Seg tl = query(rt, 1, num, 1, x), tr = query(rt, 1, num, x + 1, num);
	return tl.c * b[x] - tl.s + tr.s - tr.c * b[x];
}
signed main() {
    freopen(".in", "r", stdin);
    freopen(".ans", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; ++i) scanf("%lld", c + i);
	for (int i = 1; i <= n; ++i) scanf("%lld", e + i), b[++num] = s[i] = s[i - 1] + e[i];
	e[n + 1] = -s[n];
	for (int i = n + 1; i >= 1; --i) b[++num] = s[i] + e[n + 1];
	sort(b + 1, b + 1 + num);
	num = unique(b + 1, b + 1 + num) - b - 1;
	for (int i = 1; i <= n + 1; ++i)
		insert(rt, 1, num, lower_bound(b + 1, b + 1 + num, s[i]) - b, 1, c[i]);
	for (int i = n; i >= 1; --i) {
		ans = min(ans, get(find(rt, 1, num, t[rt].c / 2)));
		insert(rt, 1, num, lower_bound(b + 1, b + 1 + num, s[i]) - b, -1, c[i]);
		insert(rt, 1, num, lower_bound(b + 1, b + 1 + num, s[i + 1]) - b, -1, c[i + 1]);
		s[i] = s[i - 1] + e[n + 1], swap(c[i], c[i + 1]);
		insert(rt, 1, num, lower_bound(b + 1, b + 1 + num, s[i]) - b, 1, c[i]);
		insert(rt, 1, num, lower_bound(b + 1, b + 1 + num, s[i + 1]) - b, 1, c[i + 1]);
	}
	printf("%lld\n", ans);
	return 0;
}