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

int n1, n2;
char ch1[1003], ch2[1003];

int main() {
    #ifdef LOCAL
        freopen("data/magnets4.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int T;
    read(T);
    while (T--) {
        scanf("%s%s", ch1, ch2);
        n1 = strlen(ch1), n2 = strlen(ch2);
        for (int i = n1; i < n1 * 2; i++) {
            ch1[i] = ch1[i - n1];
        }
        for (int i = 0; i < n1; i++) {
            if (ch1[i] == ch2[0]) {
                int l = i + 1, r = 1;
                while (true) {
                    while (l < i + n1 && r < n2 && ch1[l] != ch2[r]) l++;
                    if (l >= i + n1) break;
                    l++; r++;

                    if (r >= n2 || l >= i + n1) {
                        break;
                    }
                }
                if (r >= n2) {
                    puts("Y");
                    goto cont;
                }
            }
        }
        puts("N");
        cont:;
    }
    return 0;
}
