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
#define max(a, b) ((a) > (b) ? (a) : (b))

const int maxn = 410, mod = 1e9 + 7;
int w[maxn];
int f[maxn][maxn];
int s1[maxn][maxn], s2[maxn][maxn];
int n;

signed main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(w[i]);
    }
    for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
            f[j][k] = 1;
        }
    }
    for (int k = 1; k <= n; k++) {
        s1[0][k] = 0; s2[0][k] = 0;
        for (int j = 1; j <= n; j++) {
            s1[j][k] = s1[j - 1][k] + f[j][k]; s1[j][k] %= mod;
            s2[j][k] = s2[j - 1][k] + f[j][k] * w[j] % mod; s2[j][k] %= mod;
        }
    }
    int x, i;
    for (x = 3; x <= n; x++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                f[j][k] = s1[j][j] * w[max(j, k)] % mod;
                if (k >= j + 1) {
                    f[j][k] += (s1[k][j] - s1[j][j]) % mod * w[k] % mod;
                    f[j][k] %= mod;
                }
                int l = max(j + 1, k + 1);
                f[j][k] += (s2[n][j] - s2[l - 1][j]) % mod;
                f[j][k] %= mod;
            }
        }
        for (int k = 1; k <= n; k++) {
            for (int j = 1; j <= n; j++) {
                s1[j][k] = s1[j - 1][k] + f[j][k]; s1[j][k] %= mod;
                s2[j][k] = s2[j - 1][k] + f[j][k] * w[j] % mod; s2[j][k] %= mod;
            }
        }
    }
    int ans = 0;
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            (ans += f[x][y]) %= mod;
        }
    }
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}