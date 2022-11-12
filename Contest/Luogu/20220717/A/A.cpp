#include <cstdio>

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    if (k == 1) {
        for (int i = 0; i < n; i++) {
            if (i % 2) {
                putchar('l');
            } else {
                putchar('r');
            }
        }
    } else if (k >= 3) {
        for (int i = 0; i < m; i++) {
            if (i % 2) {
                putchar('l');
            } else {
                putchar('r');
            }
        }
        for (int i = m, kk = k - 1; i < n; i++, kk--) {
            if (kk < 0) {
                putchar('l');
                kk = k;
            } else {
                putchar('r');
            }
        }
    } else {
        #define min(x, y) (((x) < (y)) ? (x) : (y))
        int tot = n - m; char chr = 'l';
        static char ch[114514];
        for (int i = 0; i < min(tot, m); i++) {
            ch[i] = ch;
            if (i % 2) {
                if (ch == '')
            }
        }
        for (int i = 0; i < m; i++) {
            if (i % 2) {
                putchar('l');
            } else {
                putchar('r');
            }
        }
        if (n - m >= 3) {
            putchar('r');
        }
        if (n - m >= 4) {
            putchar('r');
        }
    }
    return 0;
}