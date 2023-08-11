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

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

const int maxn = 1e6 + 5;
int a[maxn], acnt[maxn];

int main() {
    #ifdef LOCAL
        freopen("data/bag4.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, sum = 1, cnt = 1, c = 0; bool flag = true;
        int mincnt = 0;
        read(n);
        acnt[0] = 1;
        for (int i = 1; i <= n; i++) {
            read(a[i]);
            if (a[i] == -1) cnt--;
            else if (a[i] == 0) { c++, sum++, cnt++; }
            else sum++, cnt++;
            
            acnt[i] = cnt;
            if (cnt <= 0) flag = false;
        }

        for (int i = n - 1; i >= 0; i--) acnt[i] = std::min(acnt[i], acnt[i + 1]);

        if (!flag) {
            puts("-1");
            continue;
        }

        double max = (double) sum / cnt; int p = sum, q = cnt; int down = acnt[n];

        for (int i = n; i >= 1; i--) {
            down = std::min(down, acnt[i]);
            if (a[i] == 0) {
                sum--;
                cnt -= 2;
                down -= 2;
                c--;
                if (down <= 0 || sum < 0 || c < 0) break;
                if (max < (double) sum / cnt) {
                    max = sum / cnt;
                    p = sum; q = cnt;
                    // writeln(666, p, q);
                } 
            }
            // writeln(down, acnt[i]);
        }
        int g = gcd(p, q);
        writeln(p / g, q / g);
    }
    return 0;
}
