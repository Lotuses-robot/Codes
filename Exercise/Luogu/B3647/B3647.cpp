#include <bits/stdc++.h>

#define gc getchar()
template<typename T>
void read(T &r) {
	char ch = gc, last = 'z'; r = 0;
	while (ch < '0' || ch > '9') last = ch, ch = gc;
	while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
	if (last == '-') r = -r;
}

#define ll __int128
#define int long long

const int maxn = 1e5 + 10;
std::vector<int> G[maxn];
int n;
ll a[maxn], b[maxn], c[maxn];

double delt;
double solve(double a, double b, double c, double t) {
	delt = sqrt(b * b - 4 * a * c);
	double xx1 = ceil((-b + delt) / 2 / a);
	double xx2 = ceil((-b - delt) / 2 / a);
	if (xx1 < xx2) std::swap(xx1, xx2);
	if (xx2 > t) return xx2;
	return xx1;
//	return tp ? ceil((-b + delt) / 2 / a) : ceil((-b - delt) / 2 / a);
}

double check(ll i, ll t) { // find if i begins at t, when it ok
	if (c[i] == 0) {
		return a[i] % b[i] ? a[i] / b[i] + 1 : a[i] / b[i];
//		puts("?");
	} if (c[i] > 0) {
		return solve(c[i] / 2.0, c[i] / 2.0 + b[i], (1 - t) * b[i] + c[i] * t / 2.0 - c[i] * t / 2.0 * t - a[i], t);
	} else { // max(b[i] + x * c[i], 1)
//		puts("?");
		ll ed = floor((1.0 - b[i]) / c[i]) - 1; // floor, ed: last > 1' day
		ll bgc, edc = -1, sum = 0;
		if (t <= ed) {
			bgc = b[i] + t * c[i]; // take t in it
			edc = b[i] + ed * c[i];
			sum = (bgc + edc) * (ed - t + 1) / 2;
		}
		if (a[i] > sum) {
			return t > ed ? t + a[i] - 1 : ed + a[i] - sum;
		} else {
			return solve(c[i] / 2.0, c[i] / 2.0 + b[i], (1 - t) * b[i] + c[i] * t / 2.0 - c[i] * t / 2.0 * t - a[i], t);
		}
	}
}

ll calc(int i, int t) { // for point i find the max time it can be grow up >= a[i] when time <= t
//	printf("%d %d\n", i, t);
	int l = 1, r = 1e5 + 1;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
//		if (i == 1) printf("%lld\n", check(i, mid));
//		printf("calc1 %lf %lld\n", check(i, mid), t);
		if (check(i, mid) <= (double)t) {
			l = mid;
		} else {
			r = mid - 1;
		}
//		printf("calc2 %d %d\n", l, r);
	}
	if (check(i, l) > (double)t) return -1;
	return l;
}

template<typename T>
struct edq {
	std::priority_queue<T> a, b;
	void clear() {
		while (!a.empty()) a.pop();
		while (!b.empty()) b.pop();
	}
	void del() {
		while (!b.empty() && !a.empty()) {
			if (a.top() != b.top()) break;
			a.pop(); b.pop();
		}
	}
	bool empty() {
		del();
		return a.empty();
	}
	void push(T x) {
		a.push(x);
	}
	T top() {
		del();
		return a.top();
	}
	void erase(T p) {
		b.push(p);
	}
};
struct Point {
	ll x; int id;
	bool operator < (Point b) const {
		return x > b.x;
	}
	bool operator != (Point b) const {
		return id != b.id;
	}
};
edq<Point> q;

ll tlast[maxn];
bool vis[maxn];
bool checkall(int ti) {
//	puts("");
	for (int i = 1; i <= n; i++) {
		tlast[i] = calc(i, ti);
//		printf("%d %lld\n", i, tlast[i]);
		if (tlast[i] == -1){
//			puts("?");
			return false;
		}
	}
//	puts(""); 
//	puts("666");
	q.clear();
	for (int i = 1; i <= n; i++) {
		q.push({tlast[i], i});
		vis[i] = 0;
	}
//	puts("?");
	int ct = 0;
	while (!q.empty()) {
		Point p = q.top();
		int u = p.id;
		while (~u && !vis[u]) {
			ct++; vis[u] = true;
			q.erase({tlast[u], u});
//			printf("%d %d\n", u, ct);
		}
		if (ct > p.x) {
			return false;
		}
	}
	return true;
}

int fa[maxn];
void dfs(int u, int f) {
	fa[u] = f;
	for (int v : G[u]) {
		if (v != f) {
			dfs(v, u);
		}
	}
}

signed main() {
//	freopen("tree.in", "r", stdin);
//	freopen("tree.out", "w", stdout);
	
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
//		printf("%d %d\n", l, r);
	}
//	printf("%d\n", calc(3, 4));
//	printf("%d\n", calc(864, 1e9));
	printf("%d\n", r);
	return 0;
}