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

int a[4514];
char ch[4514];
char map[4514];

int main() {
    int T;
    read(T);
    while (T--) {
        memset(map, 0, sizeof(map));
        int n;
        read(n);
        for (int i = 0; i < n; i++) {
            read(a[i]);
        }
        scanf("%s", ch);

        bool flag = false;
        for (int i = 0; i < n; i++) {
            if (!map[a[i]]) {
                map[a[i]] = ch[i];
            } else {
                if (map[a[i]] != ch[i]) {
                    flag = true;
                    break;
                }
            }
        }

        puts(flag ? "NO" : "YES");
    }
}
