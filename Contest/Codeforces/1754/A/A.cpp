// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

char ch[114514];

int main() {
    int T;
    read(T);
    while (T--) {
        int n, t = 0;
        read(n);
        scanf("%s", ch);
        for (int i = n - 1; i >= 0; i--) {
            if (ch[i] == 'Q') {
                t--;
                if (t < 0) break;
            } else {
                t++;
            }
        }
        if (t < 0) {
            puts("No");
        } else {
            puts("Yes");
        }
    }
    return 0;
}
