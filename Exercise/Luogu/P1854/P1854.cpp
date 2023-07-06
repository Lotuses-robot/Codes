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

const int maxn = 105;
int a[maxn][maxn], f[maxn][maxn];
int pre[maxn][maxn];

std::vector<int> anslist;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    memset(a, -63, sizeof(a));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(a[i][j]);
        }
    }

    memset(f, -63, sizeof(f));

    int ans = -114514191, ansidi, ansidj;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int maxf = -114514191, maxid = 0;
            for (int k = 0; k < j; k++) {
                if (maxf < f[i - 1][k]) {
                    maxf = f[i - 1][k];
                    maxid = k;
                }
            }
            if (i == 1) maxf = 0;
            f[i][j] = maxf + a[i][j];
            pre[i][j] = maxid;
            
            if (i == n && ans < f[i][j]) {
                ans = f[i][j];
                ansidi = i;
                ansidj = j;
            }
        }
    }

    int i = ansidi, j = ansidj;
    while (i >= 1) {
        anslist.push_back(j);
        j = pre[i][j]; i--;
    }

    printf("%d\n", ans);
    for (int i = (int)anslist.size() - 1; i >= 0; i--) { 
        if (anslist[i] != anslist[i + 1]) {
            printf("%d ", anslist[i]);
        }
    }
    puts("");
    return 0;
}
