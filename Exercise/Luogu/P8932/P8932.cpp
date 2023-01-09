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

char ch[3114514];

#define ceil(a) ((a) % 2 ? a / 2 + 1 : a / 2)

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".ans", "w", stdout);
    #endif
    
    int T, n;
    read(T);
    scanf("%s", ch); n = strlen(ch);
    int cnt = 1, last = ch[0];
    for (int i = 1; i < n; i++) {
        if (ch[i] != last) {
            cnt++;
            last = ch[i];
        }
    }
    printf("%d\n", ceil(cnt));

    int i = 0;
    while (T--) {
        int p; char c;
        read(p); scanf("%c", &c); p--;
        // 1. edge
        if (p == 0) {
            cnt += (ch[1] == ch[0] && ch[1] != c);
            cnt -= (ch[1] != ch[0] && ch[1] == c);
        } else if (p == n - 1) {
            cnt += (ch[p - 1] == ch[p] && ch[p - 1] != c);
            cnt -= (ch[p - 1] != ch[p] && ch[p - 1] == c);
        } else {
            if (ch[p - 1] == ch[p + 1]) {
                if (ch[p] == ch[p - 1]) {
                    cnt += 2 * (c != ch[p - 1]);
                } else {
                    cnt -= 2 * (c == ch[p - 1]);
                }
            } else {
                if (ch[p] == ch[p - 1] || ch[p] == ch[p + 1]) {
                    cnt += (c != ch[p - 1] && c != ch[p + 1]);
                } else {
                    cnt -= (c == ch[p - 1] || c == ch[p + 1]);
                }
            }
        }
        ch[p] = c;
        // printf("%s\n", ch);
        printf("%d\n", ceil(cnt));
    }
    return 0;
}
