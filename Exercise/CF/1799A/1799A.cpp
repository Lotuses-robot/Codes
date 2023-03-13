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

int pop[100005];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        memset(pop, -1, sizeof(pop));
        int n, m, now;
        read(n, m); now = n;
        for (int i = 1; i <= m; i++) {
            int p;
            read(p);
            if (pop[p]) {
                pop[p] = 0;
                if (now >= 0) pop[now--] = i;
            }
        }

        for (int i = 1; i <= n; i++) {
            printf("%d ", pop[i]);
        }
        puts("");
    }
    return 0;
}
