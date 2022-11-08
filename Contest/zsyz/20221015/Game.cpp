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
    freopen("Game.in", "r", stdin);
    freopen("Game.out", "w", stdout);
    int n;
    read(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int i, llen, rlen;
    for (i = 0, llen = 1; i < n && a[i] < a[i + 1]; i++, llen++);
    for (i = n - 1, rlen = 1; i >= 0 && a[i - 1] > a[i]; i--, rlen++);
    
    // printf("%d %d\n", llen, rlen);
    if (llen % 2 || rlen % 2) {
        puts("Alice");
    } else {
        puts("Bob");
    }
    return 0;
}
