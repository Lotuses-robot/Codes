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

#define maxn 5000006

int fk[maxn], lowest = 2000000;

void add(int x) {
    int i = lowest;
    do {
        fk[i--] += (x & 1);
    } while (x >>= 1);
}

void time() {
    lowest++;
}

void init() {
    lowest = 2000000;
    memset(fk, 0, sizeof(fk));
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);

    while (T--) {
        init();
        int n;
        read(n);
        for (int i = 0; i < n; i++) {
            int op, d;
            read(op);
            if (op == 1) {
                time();
            } else {
                read(d);
                add(d);
            }
        }

        int pus = 0, last = lowest, vis = 0;
        for (int i = lowest; i >= 0; i--) {
            if (!vis && fk[i]) {
                vis = true;
                last = i;
            }
            fk[i] += pus;
            pus = fk[i] / 2;
            fk[i] %= 2;
        }

        int first = 0;
        for (int i = 0; i <= lowest; i++) {
            if (fk[i]) {
                first = i;
                break;
            }
        }

        if (first == 0) {
            puts("0");
            continue;
        }

        for (int i = first; i <= lowest; i++) {
            putchar(fk[i] + '0');
        }
        puts("");
    }
    return 0;
}
