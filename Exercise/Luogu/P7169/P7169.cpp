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

#define maxn 100005
int n, a[maxn], b[maxn];

namespace Sub2 { // 12pts
    // n <= 1e5
    // B_i = B_j
    int solve() {
        int last = -1, ans = 0;
        // printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            // printf("%d %d %d\n", i, a[i], b[i]);
            if (a[i] == b[i]) {
                int l = i - 1, r = i + 1;
                while (l > last && a[l] < a[i]) l--; l++;
                while (r < n && a[r] < a[i]) r++; r--;
                last = i = r;
                ans += (r - l + 1);
            }
        }
        return ans;
    }
}

int main() {
    bool dif = 0;
    read(n);
    // printf("%d\n", n);
    for (int i = 0; i < n; i++) read(a[i]);
    for (int i = 0; i < n; i++) {
        read(b[i]);
        if (i > 0 && b[i] != b[i - 1]) dif = true;
    }
    int ans;
    if (!dif) {
        ans = Sub2::solve();
    }
    printf("%d\n", ans);
    return 0;
}
