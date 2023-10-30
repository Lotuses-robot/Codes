// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>

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

std::map<int, int> mp, bg, ck;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, np, q;
        read(n, q);

        np = n;
        mp.clear();
        for (int i = 2; i * i <= np; i++) {
            while (np % i == 0) {
                np /= i;
                mp[i]++;
            }
        }
        if (np != 1) {
            mp[np]++;
        }
        bg = mp;
        np = n;

        while (q--) {
            int op;
            read(op);
            if (op == 1) {
                int x, res = 1;
                read(x);
                // n *= x;
                for (int i = 2; i * i <= x; i++) {
                    while (x % i == 0) {
                        x /= i;
                        mp[i]++;
                    }
                }
                if (x != 1) {
                    mp[x]++;
                }

                for (auto p : mp) {
                    // writeln(p.first, p.second);
                    res *= p.second + 1;
                }
                // if (res != 1) res++;
                // writeln(n, res);
                // writeln(res);

                bool flag = true;
                ck = mp;
                for (int i = 2; i * i <= res; i++) {
                    while (res % i == 0) {
                        if (ck[i] <= 0) {
                            // writeln(i);
                            flag = false;
                            break;
                        }
                        ck[i]--;
                        res /= i;
                    }
                }
                if (res > 1) {
                    // writeln(res);
                    if (ck[res] <= 0) {
                        flag = false;                        
                    }
                }

                if (flag) {
                    puts("YES");
                } else {
                    puts("NO");
                }

                // if (n % res == 0) {
                //     puts("YES");
                // } else {
                //     puts("NO");
                // }
            } else {
                mp = bg;
                n = np;
            }
        }
        puts("");
    }
    return 0;
}