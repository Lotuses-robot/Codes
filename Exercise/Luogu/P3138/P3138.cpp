// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <map>
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

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 1005, maxx = 1e6 + 10;
struct Point {
	int x, y;
} p[maxn];

std::map<int, int> mp;
int px[maxx], py[maxx];
int a[maxn][maxn], sum[maxn][maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
    	read(p[i].x, p[i].y);
	}
	mp.clear();
	for (int i = 1; i <= n; i++) {
		mp[p[i].x]++;
	}
	int cntx = 0;
	for (auto q : mp) {
		px[q.first] = ++cntx;
	}
	mp.clear();
	for (int i = 1; i <= n; i++) {
		mp[p[i].y]++;
	}
	int cnty = 0;
	for (auto q : mp) {
		py[q.first] = ++cnty;
	}
	for (int i = 1; i <= n; i++) {
		p[i].x = px[p[i].x];
		p[i].y = py[p[i].y];
		a[p[i].x][p[i].y]++;
	}
	for (int i = 1; i <= cntx; i++) {
		for (int j = 1; j <= cnty; j++) {
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
		}
	}
	int ans = n;
	for (int i = 0; i <= cntx; i++) {
		for (int j = 0; j <= cnty; j++) {
			int a = sum[i][j];
			int b = sum[i][cnty] - sum[i][j];
			int c = sum[cntx][cnty] - sum[i][cnty] - sum[cntx][j] + sum[i][j];
			int d = sum[cntx][j] - sum[i][j];
			ans = std::min(ans, std::max(std::max(a, b), std::max(c, d)));
		}
	}
	printf("%d\n", ans);
	return 0;
}
