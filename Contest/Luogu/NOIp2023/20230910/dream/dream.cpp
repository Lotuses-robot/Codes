#include <cstdio>

#define gc getchar()
template<typename T>
void read(T &r) {
	char ch = gc, last = 'z'; r = 0;
	while (ch < '0' || ch > '9') last = ch, ch = gc;
	while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
	if (last == '-') r = -r;
}

#define int long long
const int mod = 1e9 + 7;

int qpow(int x, int a) {
	int _x = 1, _b = x;
	do {
		if (a & 1) (_x *= _b) %= mod;
		(_b *= _b) %= mod;
	} while (a >>= 1);
	return _x;
}

signed main() {
	int n, k;
	read(n); read(k);
	printf("%lld\n", ((qpow(k, n) + n) % mod - 2 + mod) % mod);
	return 0;
}
