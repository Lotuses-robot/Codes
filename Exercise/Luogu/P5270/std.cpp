#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pr; 

inline int read() {
	char c = getchar(); int x = 0, f = 1;
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}

const int N = 100005;

int n, T, q, str[N], mx, m, len[N], ord[N], pre[N];
vector<int> vec[N];
struct hashh {
	ull h[6];
	hashh() { memset(h, 0, sizeof(h)); }
} hs[N], hhh, sth;
vector<hashh> rec[N];

inline ull lar_rand() { return (ull)rand() * rand() * rand() * rand() * rand() * rand(); }
inline void add(hashh &x, hashh &y) {
	for (int i = 0; i < 6; i++) x.h[i] += y.h[i];
} 
inline void sub(hashh &x, hashh &y) {
	for (int i = 0; i < 6; i++) x.h[i] -= y.h[i];
}
inline bool equal(hashh x, hashh y) {
	for (int i = 0; i < 6; i++) if (x.h[i] != y.h[i]) return false;
	return true;
}

int main() {
	srand(time(NULL));
	n = read(); T = read(); q = read();
	for (int i = 1; i <= T; i++) str[i] = read(), mx = max(mx, str[i]);
	for (int i = 1; i <= n; i++) {
		int l = read();
		while (l--) {
			int x = read();
			vec[i].push_back(x); mx = max(mx, x);
		}
	}
	m = read();
	for (int i = 1; i <= m; i++) ord[i] = read();
	for (int i = 0; i <= mx; i++)
		for (int j = 0; j < 6; j++) hs[i].h[j] = lar_rand();
	for (int i = 1; i <= T; i++) add(sth, hs[str[i]]);
	for (int i = 1; i <= n; i++) {
		len[i] = vec[i].size(), rec[i].resize(len[i]);
		for (int j = len[i] - 1; j >= 0; j--) rec[i][j] = hs[vec[i][j]];
		for (int j = len[i] - 2; j >= 0; j--) add(rec[i][j], rec[i][j + 1]);
	}
	int curl = 0, ans = 0;
	deque<pr> que; while (!que.empty()) que.pop_back();
	for (int i = 1; i <= m && i <= q; i++) {
		add(hhh, rec[ord[i]][0]), curl += len[ord[i]];
		que.push_back(pr(ord[i], 0));
		while (curl > T) {
			pr x = que.front(); que.pop_front();
			int fir = x.first, sec = x.second;
			sub(hhh, rec[fir][sec]);
			curl -= len[fir] - sec;
			if (curl < T) {
				int np = len[fir] - (T - curl);
				que.push_front(pr(fir, np));
				add(hhh, rec[fir][np]);
				curl = T;
			}
		}
		if (equal(hhh, sth)) ans++;
	}
	if (q <= m) {
		printf("%d\n", ans);
		return 0;
	}
	q -= m; int cyc = 0;
	for (int i = 1; i <= m && i <= q; i++) {
		add(hhh, rec[ord[i]][0]), curl += len[ord[i]];
		que.push_back(pr(ord[i], 0));
		while (curl > T) {
			pr x = que.front(); que.pop_front();
			int fir = x.first, sec = x.second;
			sub(hhh, rec[fir][sec]);
			curl -= len[fir] - sec;
			if (curl < T) {
				int np = len[fir] - (T - curl);
				que.push_front(pr(fir, np));
				add(hhh, rec[fir][np]);
				curl = T;
			}
		}
		pre[i] = pre[i - 1];
		if (equal(hhh, sth)) cyc++, pre[i]++;
	}
    printf("%d %d\n", ans, cyc);
	// printf("%d\n", ans + cyc * (q / m) + pre[q % m]);
	return 0;
}