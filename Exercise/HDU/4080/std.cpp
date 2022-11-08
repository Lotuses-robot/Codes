#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int MAXLEN = 40005;
 
struct Suffix {
 
    int s[MAXLEN];
    int sa[MAXLEN], t[MAXLEN], t2[MAXLEN], c[MAXLEN], n;
    int rank[MAXLEN], height[MAXLEN];
 
    void build_sa(int m) {
	n++;
	int i, *x = t, *y = t2;
	for (i = 0; i < m; i++) c[i] = 0;
	for (i = 0; i < n; i++) c[x[i] = s[i]]++;
	for (i = 1; i < m; i++) c[i] += c[i - 1];
	for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
	for (int k = 1; k <= n; k <<= 1) {
	    int p = 0;
	    for (i = n - k; i < n; i++) y[p++] = i;
	    for (i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
	    for (i = 0; i < m; i++) c[i] = 0;
	    for (i = 0; i < n; i++) c[x[y[i]]]++;
	    for (i = 0; i < m; i++) c[i] += c[i - 1];
	    for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
	    swap(x, y);
	    p = 1; x[sa[0]] = 0;
	    for (i = 1; i < n; i++)
		x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
	    if (p >= n) break;
	    m = p;
	}
	n--;
    }
 
    void getHeight() {
	int i, j, k = 0;
	for (i = 1; i <= n; i++) rank[sa[i]] = i;
	for (i = 0; i < n; i++) {
	    if (k) k--;
	    int j = sa[rank[i] - 1];
	    while (s[i + k] == s[j + k]) k++;
	    height[rank[i]] = k;
	}
    }
} gao;
 
const int N = 40005;
 
int m;
char str[N];
 
int judge(int x) {
    int ans = -1;
    for (int i = 1; i <= gao.n; i++) {
	if (gao.n - gao.sa[i] < x) continue;
	int Max = gao.sa[i], cnt = 1;
	while (gao.height[i + 1] >= x && i < gao.n) {
	    Max = max(Max, gao.sa[i + 1]);
	    cnt++;
	    i++;
	}
	if (cnt >= m)
	    ans = max(ans, Max);
    }
    return ans;
}
 
void solve() {
    if (judge(1) == -1) {
	printf("none\n");
	return;
    }
    int l = 1, r = gao.n - m + 2;
    while (l < r) {
	int mid = (l + r) / 2;
	if (judge(mid) != -1) l = mid + 1;
	else r = mid;
    }
    l--;
    printf("%d %d\n", l, judge(l));
}
 
int main() {
    freopen("4080.in", "r", stdin);
    freopen("4080.ans", "w", stdout);
    
    while (~scanf("%d", &m) && m) {
	scanf("%s", str);
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	    gao.s[i] = str[i] - 'a' + 1;
	gao.s[len] = 0;
	gao.n = len;
	gao.build_sa(27);
	gao.getHeight();
	solve();
    }
    return 0;
}