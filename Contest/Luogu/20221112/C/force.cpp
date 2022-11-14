// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

int a[114514];
int backup[114514];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int n, ng = 0, po = 0, q;
    read(n);
    for (int i = 0; i < n; i++) {
        read(q);
        if (q == 1) po++;
        if (q == -1) ng++;
        a[i] = backup[i] = q;
    }
    ng++; int ans = po / ng, rem = po % ng;
    // if (rem != 0) ans++;

    std::vector<int> anss;

    for (int i = 0; i < ng; i++) {
        for (int j = 0; j < ans; j++) {
            anss.push_back(1);
        }
        if (i < rem) {
            anss.push_back(1);
        }
        if (i < ng - 1) anss.push_back(-1);
    }

    ans = 0; int lt = 0;
    for (int i = 0; i < anss.size(); i++) {
        lt += anss[i];
        if (lt < 0) lt = 0;
        ans = std::max(ans, lt);
        printf("%d ", anss[i]);
    }

    printf("%d\n", ans);

    int cnt = 0;
    do {
        int last = 0, qans = 0;
        for (int i = 0; i < n; i++) {
            last += a[i];
            if (last < 0) last = 0;
            qans = std::max(qans, last);
            printf("%d ", a[i]);
        }
        printf("%d\n", qans);
        if (ans == qans) {
            cnt++;
        }
        std::next_permutation(a, a + n);
    } while (memcmp(a, backup, sizeof(backup)));
    printf("%d\n", cnt);
    return 0;
}
