// Copyright 2023 Lotuses
#define tsz signed
#include <bits/stdc++.h>
// #include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <algorithm>
#include <ext/pb_ds/priority_queue.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif
#define ins(a, b) (G[a].emplace_back(b))

#define ll long long
// #define int long long

const int maxn = 1e5 + 10;
std::vector<int> G[maxn];
int n;
ll a[maxn], b[maxn], c[maxn];

__int128 check(ll i, ll bg, ll ed) {
	if (c[i] >= 0) {
		ll bgs = b[i] + c[i] * bg;
		ll eds = b[i] + c[i] * ed;
		return (__int128)(bgs + eds) * (ed - bg + 1) / 2;
	} else {
		ll edd = (1 - b[i]) / c[i];
		if (bg > edd) {
			return ed - bg + 1;
		} else if (ed > edd) {
			ll bgs = b[i] + c[i] * bg;
			ll eds = b[i] + c[i] * edd;
			return (__int128)(bgs + eds) * (edd - bg + 1) / 2 + ed - edd;
		} else {
			ll bgs = b[i] + c[i] * bg;
			ll eds = b[i] + c[i] * ed;
			return (__int128)(bgs + eds) * (ed - bg + 1) / 2;
		}
	}
}

ll calc(int i, int t) {
	int l = 1, r = t;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (check(i, mid, t) >= a[i]) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}
	if (check(i, l, t) < a[i]) return -1;
	return l;
}

struct Point {
	ll x; int id;
	bool operator < (Point b) const {
		if (x != b.x) return x < b.x;
		return id < b.id;
	}
};
std::vector<Point> q;

ll tlast[maxn];
bool vis[maxn];
int fa[maxn];
bool checkall(int ti) {
	for (int i = 1; i <= n; i++) {
		tlast[i] = calc(i, ti);
		// printf("%lld\n", tlast[i]);
		if (tlast[i] == -1) {
			// puts("");
			return false;
		}
	}
	// while (!q.empty()) q.pop();
	q.clear();
	for (int i = 1; i <= n; i++) {
		q.emplace_back((Point){tlast[i], i});
		vis[i] = 0;
	}
	std::sort(q.begin(), q.end());
	int ct = 0; // , i = 0;
	// while (i < q.size()) {
		// Point p = q[i]; i++;
		// int u = p.id;
		// while ((~u) && (!vis[u])) {
		// 	ct++; vis[u] = true;
		// 	u = fa[u];
		// }
		// if (ct > p.x) {
		// 	return false;
		// }
		// while (i < q.size() && vis[q[i].id]) i++;
	// }
	for (int i = 0, len = q.size(); i < len; i++) {
		
	}
	return true;
}

void dfs(int u, int f) {
	fa[u] = f;
	for (int v : G[u]) {
		if (v != f) {
			dfs(v, u);
		}
	}
}

signed main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	
	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]); read(b[i]); read(c[i]);
//		printf("%lf\n", floor((1.0 - b[i]) / c[i]));
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		read(u); read(v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	
	dfs(1, -1);
	int l = 1, r = 1e9;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (checkall(mid)) {
			r = mid;
		} else {
			l = mid + 1;
		}
		// printf("%d %d\n", l, r);
	}
	// checkall(8);
//	printf("%d\n", calc(3, 4));
//	printf("%d\n", calc(864, 1e9));
	// writeln(-1, calc(10, 100000));
	printf("%d\n", r);
	return 0;
}