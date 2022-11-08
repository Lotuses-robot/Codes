#include <cstdio>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdlib>

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

int main() {
    srand(time(0));
    freopen("Editor.in", "w", stdout);
    int n = 5, m = 5;
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("%d ", rand() % 24 + 1);
    }
    puts("");
    for (int i = 0; i < n; i++) {
        int ch = rand() % 2 + 1, c1, c2;
        if (ch == 1) {
            c1 = rand() % n + 1;
            c2 = rand() % 24 + 1;
        } else {
            c1 = rand() % n + 1;
            c2 = rand() % (n - c1 + 1);
            c2 += c1;
        }
        printf("%d %d %d\n", ch, c1, c2);
    }
    return 0;
}
