#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int _N = 1e5 + 5;

int n, q, a[_N], b[_N];

struct segtree{
	#define INF LLONG_MAX
	struct data {
	  long long mx, mx2, mn, mn2, cmx, cmn, tmx, tmn, tad;
	  long long sum;
	} t[_N << 2];

	void pushup(int u) {
	  const int lu = u << 1, ru = u << 1 | 1;
	  t[u].sum = t[lu].sum + t[ru].sum;
	  if (t[lu].mx == t[ru].mx) {
	    t[u].mx = t[lu].mx, t[u].cmx = t[lu].cmx + t[ru].cmx;
	    t[u].mx2 = max(t[lu].mx2, t[ru].mx2);
	  } else if (t[lu].mx > t[ru].mx) {
	    t[u].mx = t[lu].mx, t[u].cmx = t[lu].cmx;
	    t[u].mx2 = max(t[lu].mx2, t[ru].mx);
	  } else {
	    t[u].mx = t[ru].mx, t[u].cmx = t[ru].cmx;
	    t[u].mx2 = max(t[lu].mx, t[ru].mx2);
	  }
	  if (t[lu].mn == t[ru].mn) {
	    t[u].mn = t[lu].mn, t[u].cmn = t[lu].cmn + t[ru].cmn;
	    t[u].mn2 = min(t[lu].mn2, t[ru].mn2);
	  } else if (t[lu].mn < t[ru].mn) {
	    t[u].mn = t[lu].mn, t[u].cmn = t[lu].cmn;
	    t[u].mn2 = min(t[lu].mn2, t[ru].mn);
	  } else {
	    t[u].mn = t[ru].mn, t[u].cmn = t[ru].cmn;
	    t[u].mn2 = min(t[lu].mn, t[ru].mn2);
	  }
	}

	void push_add(int u, int l, int r, int v) {
	  t[u].sum += (r - l + 1ll) * v;
	  t[u].mx += v, t[u].mn += v;
	  if (t[u].mx2 != -INF) t[u].mx2 += v;
	  if (t[u].mn2 != INF) t[u].mn2 += v;
	  if (t[u].tmx != -INF) t[u].tmx += v;
	  if (t[u].tmn != INF) t[u].tmn += v;
	  t[u].tad += v;
	}

	void push_min(int u, int tg) {
	  if (t[u].mx <= tg) return;
	  t[u].sum += (tg * 1ll - t[u].mx) * t[u].cmx;
	  if (t[u].mn2 == t[u].mx) t[u].mn2 = tg; 
	  if (t[u].mn == t[u].mx) t[u].mn = tg;    
	  if (t[u].tmx > tg) t[u].tmx = tg;   
	  t[u].mx = tg, t[u].tmn = tg;
	}

	void push_max(int u, int tg) {
	  if (t[u].mn > tg) return;
	  t[u].sum += (tg * 1ll - t[u].mn) * t[u].cmn;
	  if (t[u].mx2 == t[u].mn) t[u].mx2 = tg;
	  if (t[u].mx == t[u].mn) t[u].mx = tg;
	  if (t[u].tmn < tg) t[u].tmn = tg;
	  t[u].mn = tg, t[u].tmx = tg;
	}

	void pushdown(int u, int l, int r) {
	  const int lu = u << 1, ru = u << 1 | 1, mid = (l + r) >> 1;
	  if (t[u].tad)
	    push_add(lu, l, mid, t[u].tad), push_add(ru, mid + 1, r, t[u].tad);
	  if (t[u].tmx != -INF) push_max(lu, t[u].tmx), push_max(ru, t[u].tmx);
	  if (t[u].tmn != INF) push_min(lu, t[u].tmn), push_min(ru, t[u].tmn);
	  t[u].tad = 0, t[u].tmx = -INF, t[u].tmn = INF;
	}

	void build(int u = 1, int l = 1, int r = n) {
	  t[u].tmn = INF, t[u].tmx = -INF;
	  if (l == r) {
	    t[u].sum = t[u].mx = t[u].mn = a[l];
	    t[u].mx2 = -INF, t[u].mn2 = INF;
	    t[u].cmx = t[u].cmn = 1;
	    return;
	  }
	  int mid = (l + r) >> 1;
	  build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	  pushup(u);
	}

	void add(int L, int R, int v, int u = 1, int l = 1, int r = n) {
	  if (R < l || r < L) return;
	  if (L <= l && r <= R) return push_add(u, l, r, v); 
	  int mid = (l + r) >> 1;
	  pushdown(u, l, r);
	  add(L, R, v, u << 1, l, mid), add(L, R, v, u << 1 | 1, mid + 1, r);
	  pushup(u);
	}

	void tomin(int L, int R, int v, int u = 1, int l = 1, int r = n) {
	  if (R < l || r < L || t[u].mx <= v) return;
	  if (L <= l && r <= R && t[u].mx2 < v) return push_min(u, v); 
	  int mid = (l + r) >> 1;
	  pushdown(u, l, r);
	  tomin(L, R, v, u << 1, l, mid), tomin(L, R, v, u << 1 | 1, mid + 1, r);
	  pushup(u);
	}

	void tomax(int L, int R, int v, int u = 1, int l = 1, int r = n) {
	  if (R < l || r < L || t[u].mn >= v) return;
	  if (L <= l && r <= R && t[u].mn2 > v) return push_max(u, v);
	  int mid = (l + r) >> 1;
	  pushdown(u, l, r);
	  tomax(L, R, v, u << 1, l, mid), tomax(L, R, v, u << 1 | 1, mid + 1, r);
	  pushup(u);
	}

	long long qsum(int L, int R, int u = 1, int l = 1, int r = n) {
	  if (R < l || r < L) return 0;
	  if (L <= l && r <= R) return t[u].sum;
	  int mid = (l + r) >> 1;
	  pushdown(u, l, r);
	  return qsum(L, R, u << 1, l, mid) + qsum(L, R, u << 1 | 1, mid + 1, r);
	}

	long long qmax(int L, int R, int u = 1, int l = 1, int r = n) {
	  if (R < l || r < L) return -INF;
	  if (L <= l && r <= R) return t[u].mx;
	  int mid = (l + r) >> 1;
	  pushdown(u, l, r);
	  return max(qmax(L, R, u << 1, l, mid), qmax(L, R, u << 1 | 1, mid + 1, r));
	}

	long long qmin(int L, int R, int u = 1, int l = 1, int r = n) {
	  if (R < l || r < L) return INF;
	  if (L <= l && r <= R) return t[u].mn;
	  int mid = (l + r) >> 1;
	  pushdown(u, l, r);
	  return min(qmin(L, R, u << 1, l, mid), qmin(L, R, u << 1 | 1, mid + 1, r));
	}
	//from oi-wiki
}tr;

bool check() {
	n = inf.readInt();
	q = inf.readInt();
	for (int i = 1; i <= n; i++) a[i] = inf.readInt();
	for (int i = 1; i <= n * 4; i++) tr.t[i] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int q2 = 0;
	tr.build();
	for (int i = 1; i <= q; i++) {
		int op = inf.readInt(), l = inf.readInt(), r = inf.readInt();
		if (op == 1) {
			long long x = inf.readLong();
			tr.add(l, r, x);
		} else {
			q2++;
			long long x = ouf.readLong((long long)-1e15, (long long)1e15);
			tr.tomax(l, r, x);
		}
	}
	for (int i = 1; i <= n; i++) b[i] = inf.readLong();
	for (int i = 1; i <= n; i++) {
		if (tr.qsum(i, i) != b[i]) return false;
	}
	return true;
}

signed main(int argc, char** argv) {
	registerTestlibCmd(argc, argv);
	int testcase = inf.readInt();
	for (int i = 1; i <= testcase; i++) {
		if (!check()) quitf(_wa, "Wrong answer at test case %d.", i);
	}
	quitf(_ok, "Accepted.");
}
