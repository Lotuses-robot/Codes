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

#define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

#define maxn 1000006

char ch[maxn];

// int f(int l, int r) {
//     int mx = 0, id = l - 1, val = 0;
//     for (int i = l; i <= r; i++) {
//         val += ch[i] == '(' ? -1 : 1;
//         if (val > mx) {
//             mx = val;
//             id = i;
//         } else if (val == mx) {
//             if (id != l - 1) {
//                 mx = val;
//                 id = i;
//             } 
//         }
//     }
//     return std::abs(val) + (id != l - 1 && id != r);
// }

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, sum = 0;
        read(n);
        scanf("%s", ch + 1);
        for (int i = 1; i <= n; i++) {
            int mx = 0, id = i - 1, val = 0;
            for (int j = i; j <= n; j++) {
                val += ch[j] == '(' ? -1 : 1;

                if (val > mx) {
                    mx = val;
                    id = j;
                } else if (val == mx) {
                    if (id != i - 1) {
                        mx = val;
                        id = j;
                    } 
                }

                sum += std::abs(val) + (id != i - 1 && id != j);
                // sum += f(i, j);
                debug(i, j, (id != i - 1 && id != j));
            }
        }
        writeln(sum);
    }
}
