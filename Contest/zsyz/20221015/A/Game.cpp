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

    
    return 0;
}
