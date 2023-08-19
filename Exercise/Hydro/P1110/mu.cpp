// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
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

#define int long long

const int maxn = 1003;
int primes[maxn], mu[maxn], cnt;
bool st[maxn];
void get_mu(){
    mu[1] = 1;
    for(int i = 2; i <= maxn; i++){
        if(!st[i]){
            mu[i] = -1;
            primes[cnt++] = i;
        }
        for(int j = 0; j < cnt && primes[j] * i <= maxn; j++){
            st[primes[j] * i] = true;
            if(i % primes[j] == 0){
                mu[primes[j] * i] = 0;
                break;
            }
            else mu[primes[j] * i] = mu[primes[j]] * mu[i];
        }
    }
}

const int mod = 998244353;
int f[maxn][maxn];
int g[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    get_mu();
    for (int i = 1; i <= m; i++) f[1][i] = 1;
    int a = 0;
    for (int i = 2; i <= n; i++) {
        memset(g, 0, sizeof(g));
        for (int k = 1; k <= m; k++) {
            for (int d = 1; d * d <= k; d++) {
                if (k % d == 0){
                    (g[d] += mu[d] * f[i - 1][k] % mod) %= mod;
                    if (k / d != d) (g[k / d] += mu[k / d] * f[i - 1][k] % mod) %= mod;
                }
            }
        }
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k * k <= j; k++) {
                if (j % k == 0) {
                    (f[i][j] += g[k]) %= mod;
                    if (j / k != k) (f[i][j] += g[j / k]) %= mod;
                }
            }
            if (i == n) (a += f[i][j]) %= mod;
        }
    }
    writeln((a + mod) % mod);
    return 0;
}
