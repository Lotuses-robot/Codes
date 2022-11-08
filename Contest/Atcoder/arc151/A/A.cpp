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

char s[214514];
char t[214514];

int main() {
    int n, q = 0, l = 0, r = 0, aq = 0;
    read(n);
    scanf("%s%s", s, t);

    for (int i = 0; i < n; i++) {
        if (s[i] != t[i]) q++;
    }


    if (q % 2 == 1) {
        puts("-1");
    } else {
        // q /= 2;
        aq = q / 2;
        // int last = -1;

        for (int i = 0; i < n; i++) {
            if (s[i] == t[i]) {
                s[i] = t[i] = '0';
            }
        }

        for (int i = 0; i < n; i++) {
            if (s[i] != t[i] && q > 0) {
                q--;
                if (s[i] == '0') {
                    l++;
                    if (l > aq) {
                        l--;
                        r++;
                        s[i] = '1';
                    }
                } else {
                    r++;
                    s[i] = '0';
                    if (r > aq) {
                        r--;
                        l++;
                        s[i] = '1';
                    }
                }
            }
            putchar(s[i]);
        }
    }
    return 0;
}
