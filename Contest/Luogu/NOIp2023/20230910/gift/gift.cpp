#include <cstdio>
#include <algorithm>

#define gc getchar()
template<typename T>
void read(T &r) {
	char ch = gc, last = 'z'; r = 0;
	while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    if (last == '-') r = -r;
}

#define int long long

const int maxn = 3e5 + 10;
int n, tot;
int d[maxn], p[maxn], num[maxn]; bool v[maxn];

void pre() {
    tot = 0;
    d[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) p[++tot] = i, d[i] = 2, num[i] = 1;
        for (int j = 1; j <= tot && i <= n / p[j]; ++j) {
            v[p[j] * i] = 1;
            if (i % p[j] == 0) {
                num[i * p[j]] = num[i] + 1;
                d[i * p[j]] = d[i] / num[i * p[j]] * (num[i * p[j]] + 1);
                break;
            } else {
                num[i * p[j]] = 1;
                d[i * p[j]] = d[i] * 2;
            }
        }
    }
}

int b[maxn];

bool cmp(int x, int y) {
    return x > y;
}

signed main() {
    read(n); pre();
    for (int i = 1; i <= n; i++) {
        b[i] = n / i - d[i];
    }
    std::sort(b + 1, b + n + 1, cmp);
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += b[i];
        printf("%lld ", s);
    }
    puts("");
    return 0;
}
