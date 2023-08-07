// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

const int maxn = 1e6 + 6;
std::map<int, int> cnt;
int sum[maxn];

char buf[1 << 21], a[20]; int p, p2 = -1;
inline void flush() {
	fwrite(buf, 1, p2 + 1, stdout);
	p2 = -1;
}
inline void print(int x) {
	if (p2 > 1 << 20) flush();
	if (x < 0) buf[++p2] = 45, x = -x;
	do {
		a[++p] = x % 10 + 48;
	} while (x /= 10);
	do {
		buf[++p2] = a[p];
	} while (--p);
	buf[++p2] = '\n';
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m, a;
    read(n, m);
    for (register int i = 1; i <= n; i++) {
        for (register int j = 1; j <= n; j++) {
            read(a);
            cnt[a]++;
        }
    }
    int id = 0;
    for (std::pair<const int, int> &e : cnt) {
        id++;
        sum[id] = sum[id - 1] + e.second;
        cnt[e.first] = id;
    }
    std::map<int, int>::iterator p; int q;
    while (m--) {
        read(q);
        p = cnt.lower_bound(q);
        if (p == cnt.begin()) {
            print(n);
            continue;
        }
        p--;
        int ct = n * n - sum[p -> second];
        if (ct > n) {
            print(n);
        } else {
            print(ct);
        }
    }
    flush();
    return 0;
}