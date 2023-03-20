// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

#define int long long

int tt[50];
int turn(int x) {
    memset(tt, 0, sizeof(tt));
    int t = 0;
    do {
        tt[t++] = x % 3;
    } while (x /= 3);
    return t;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int x, tot = 0;
        bool flag = false;
        read(x);
        int n = turn(x);
        for (int i = 0; i < n; i++) {
            if (tt[i] == 1) {
                tot++;
                if (i == 0) tot--;
            } else if (tt[i] == 2) {
                if (i == 0) {
                    flag = true;
                    break;
                }
            }
        }
        if (flag) {
            puts("0");
        } else {
            printf("%lld\n", 1ll << tot);
        }
    }
    return 0;
}
