// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

const int maxn = 45;
int s[maxn], n = 0;
int m[maxn][maxn];
int f[maxn][100005];

void read() {
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <='9') s[++n] = ch - '0', ch = getchar();
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int q;
    read();
    for (int i = 1; i <= n; i++) {
        m[i][i] = s[i];
        for (int j = i + 1; j <= n; j++) {
            m[i][j] = m[i][j - 1] * 10 + s[j];
        }
    }
    read(q);
    memset(f, 63, sizeof(f));
	f[0][0] = -1;
    for (int i = 1; i <= n; i++) {
    	for (int j = 0; j < i; j++) {
    		for (int k = q; k >= m[j + 1][i]; k--) {
                f[i][k] = std::min(f[i][k], f[j][k - m[j + 1][i]] + 1);
			}
		}
	}
    if (f[n][q] == f[0][1]) puts("-1");
    else writeln(f[n][q]);
    return 0;
}