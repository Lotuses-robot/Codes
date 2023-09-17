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

const int maxn = 2e7 + 10;
char s[maxn * 2], s1[maxn];
int n, Z[maxn * 2];

void initZ() {
    int l = 0, r = 0;
    Z[0] = n;
    for (int i = 1; i < n; i++) {
        Z[i] = 0;
        if (i > r) {
            while (i + Z[i] < n && s[i + Z[i]] == s[Z[i]]) Z[i]++;
        } else {
            if (i + Z[i - l] > r) {
                Z[i] = r - i + 1;
                while (i + Z[i] < n && s[i + Z[i]] == s[Z[i]]) Z[i]++;
            } else {
                Z[i] = Z[i - l];
            }
        }
        if (i + Z[i] - 1 > r) {
            l = i; r = i + Z[i] - 1;
        }
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    scanf("%s", s1);
    scanf("%s", s);
    n = strlen(s);
    initZ();
    int sz = 0;
    for (int i = 0; i < n; i++) {
        sz ^= (i + 1) * (Z[i] + 1);
    }
    writeln(sz);

    s[strlen(s)] = '$';
    strcpy(s + strlen(s), s1);
    int nn = n; n = strlen(s);

    initZ();
    int bz = 0;
    for (int i = nn + 1, end = strlen(s); i < end; i++) {
        bz ^= (i - nn) * (Z[i] + 1);
    }

    writeln(bz);
    return 0;
}
