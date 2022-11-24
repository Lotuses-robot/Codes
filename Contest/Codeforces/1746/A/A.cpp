// 1 0 0 0 1
// k = 3

#include <cstdio>

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

int main() {
    int T;
    read(T);
    while (T--) {
        int n, k, a, sum = 0;
        read(n, k);
        for (int i = 0; i < n; i++) {
            read(a); sum += a;
        }
        if (sum) puts("YES");
        else puts("NO");
    }
}