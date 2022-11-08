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

int a[114514];

int main() {
    freopen("Editor.in", "r", stdin);
    freopen("Editor.ans", "w", stdout);
    int n, m;
    read(n), read(m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    while (m--) {
        int ch, c1, c2;
        read(ch), read(c1), read(c2);
        if (ch == 1) {
            a[c1] = c2;
        } else {
            int tot = 1, lst = 24;
            for (int i = c1; i <= c2; i++) {
                if (lst >= a[i]) {
                    lst -= a[i];
                } else {
                    tot++; lst = 24 - a[i];
                }
            }
            printf("%d\n", tot);
        }
    }
    return 0;
}
