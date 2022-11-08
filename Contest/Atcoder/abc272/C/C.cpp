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

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

int a[214514];

int main() {
    int n, totod = 0, totev = 0, odmx1 = -1145141919, odmx2 = -1145141919, evmx1 = -1145141919, evmx2 = -1145141919;
    read(n);
    for (int i = 0; i < n; i++) {
        read(a[i]);
        if (a[i] % 2) {
            totod++;
            if (a[i] > odmx1) {
                odmx2 = odmx1;
                odmx1 = a[i];
            } else if (a[i] > odmx2) {
                odmx2 = a[i];
            }
        } else {
            totev++;
            if (a[i] > evmx1) {
                evmx2 = evmx1;
                evmx1 = a[i];
            } else if (a[i] > evmx2) {
                evmx2 = a[i];
            }
        }
    }
    int ans = -1145141919;

    if (totod >= 2 && totev >= 2) {
        ans = std::max(odmx1 + odmx2, evmx1 + evmx2);
    } else if (totod >= 2) {
        ans = odmx1 + odmx2;
    } else if (totev >= 2) {
        ans = evmx1 + evmx2;
    } else {
        ans = -1;
    }

    printf("%d\n", ans);
    return 0;
}
