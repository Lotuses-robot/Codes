// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

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

int m, k;
int a[114514];

int check(int n) {
    int word = 0, cnt = 0;
    for (int i = 0; i < m; i++) {
        word += a[i];
        word = word < 0 ? 0 : word;
        if (word >= n) {
            word = 0;
            cnt++;
        }
    }
    return cnt;
}

int div1() {
    int l = 1, r = 100005ll * 1000000009ll;
    while (l + 10 < r) {
        int mid = (l + r) >> 1;
        int nowk = check(mid);
        // printf("check %d\n", nowk);
        if (nowk <= k) {
            r = mid;
        } else {
            l = mid;
        }
        // printf("debug %d %d\n", l, r);
    }
    int i;
    for (i = l; i <= r; i++) {
        int nowk = check(i);
        if (nowk == k) break;
    }
    if (check(i) != k) return -1;
    return i;
}

int div2() {
    int l = 1, r = 100005ll * 1000000009ll;
    while (l + 10 < r) {
        int mid = (l + r) >> 1;
        int nowk = check(mid);
        if (nowk < k) {
            r = mid;
        } else {
            l = mid;
        }
    }
    int i;
    for (i = r; i >= l; i--) {
        int nowk = check(i);
        if (nowk == k) break;
    }
    if (check(i) != k) return -1;
    return i;
}

signed main() {
    read(m, k);
    for (int i = 0; i < m; i++) {
        read(a[i]);
    }

    int ans1 = div1(),
        ans2 = div2();

    if (ans1 == -1 || ans2 == -1) {
        puts("-1");
        return 0;
    }

    printf("%lld %lld\n", ans1, ans2);
    return 0;
}
