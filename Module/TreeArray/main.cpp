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

#define maxn 500005
struct treeArray {
    int n, ar[maxn];
    int lowbit(int x) { return x & (-x); }
    void init(int n) {
        this -> n = n;
        memset(ar, 0, sizeof(ar));
    }
    void add(int x, int k) {
        while (x <= n) {
            ar[x] += k;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int ans = 0;
        while (x > 0) {
            ans += ar[x];
            x -= lowbit(x);
        }
        return ans;
    }
};
treeArray ta;

int main() {
    int n, m, k;
    read(n, m);
    ta.init(n);
    for (int i = 1; i <= n; i++) {
        read(k);
        ta.add(i, k);
    }

    while (m--) {
        int ch, a, b;
        read(ch, a, b);
        if (ch == 1) {
            ta.add(a, b);
        } else {
            printf("%d\n", ta.query(b) - ta.query(a - 1));
        }
    }
    return 0;
}
