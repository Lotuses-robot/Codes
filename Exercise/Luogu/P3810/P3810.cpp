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

struct Node {
    int x[3];
    bool operator != (Node b) const {
        for (int i = 0; i < 3; i++) {
            if (x[i] != b.x[i]) {
                return true;
            }
        }
        return false;
    }
    bool operator <= (Node b) const {
        return x[1] <= b.x[1];
    }
};

bool cmp(Node __, Node ___) {
    for (int i = 0; i < 3; i++){
        if (__.x[i] != ___.x[i]) {
            return __.x[i] < ___.x[i];
        }
    }
    return false;
}

treeArray ta;
Node a[114514];
int v[114514];
int cnt[114514]; // only calc the ans in different number
                 // use id -> cnt[id] for finding
int ans[114514]; 
Node ass[114514]; // assist array for merge_sort
int n, k;
int assv[114514];
int asscnt[114514];

void cdq(int l, int r) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) >> 1, pt = 0;
    cdq(l, mid); cdq(mid + 1, r);
    // printf("debug %d %d\n", l, r);
    ta.n = 2e5;
    // memset(ta.ar, 0, sizeof(ta.ar));
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            // printf("debug1 %d %d %d %d %d %d\n", i, j, a[i].x[0], a[i].x[1], a[i].x[2], v[i]);
            ta.add(a[i].x[2], v[i]);
            assv[pt] = v[i];
            asscnt[pt] = i;
            ass[pt++] = a[i];
            i++;
        } else {
            cnt[j] += ta.query(a[j].x[2]);
            // printf("debug2 %d %d %d %d %d %d\n", i, j, a[j].x[0], a[j].x[1], a[j].x[2], v[j]);
            // printf("query %d\n", ta.query(a[j].x[2]));
            assv[pt] = v[j];
            asscnt[pt] = j;
            ass[pt++] = a[j];
            j++;
        }
    }

    while (i <= mid) {
        assv[pt] = v[i];
        asscnt[pt] = i;
        ass[pt++] = a[i];
        ta.add(a[i].x[2], v[i]); // need add because -add there
        i++;
    }
    while (j <= r) {
        assv[pt] = v[j];
        asscnt[pt] = j;
        ass[pt++] = a[j];
        // printf("debug2 %d %d %d %d %d %d\n", i, j, a[j].x[0], a[j].x[1], a[j].x[2], v[j]);
        // printf("query %d\n", ta.query(3));
        cnt[j] += ta.query(a[j].x[2]);
        j++;
    }

    for (int p = 0; p < pt; p++) {
        asscnt[p] = cnt[asscnt[p]];
    }

    for (int p = l; p <= r; p++) {
        if (p <= mid) {
            ta.add(a[p].x[2], -v[p]);
        }
        a[p] = ass[p - l];
        v[p] = assv[p - l];
        cnt[p] = asscnt[p - l];
    }
}

int main() {
    read(n, k);
    for (int i = 0; i < n; i++) {
        read(a[i].x[0], a[i].x[1], a[i].x[2]);
    }
    std::sort(a, a + n, cmp);

    int j = 1; v[0]++;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) {
            a[j++] = a[i];
        }
        v[j - 1]++;
    }

    // debug unique
    // printf("%d\n", j);
    // for (int i = 0; i < j; i++) {
    //     printf("%d %d %d\n", a[i].x[0], a[i].x[1], a[i].x[2]);
    // }

    cdq(0, j - 1);

    for (int i = 0; i < j; i++) {
        // ans[cnt[i] + v[i] - 1] += v[i];
        cnt[i] += v[i] - 1;
        ans[cnt[i]] += v[i];
    }

    for (int i = 0; i < n; i++) {
        // printf("%d %d %d %d %d\n", v[i], cnt[i], a[i].x[0], a[i].x[1], a[i].x[2]);
        printf("%d\n", ans[i]);
    }
    return 0;
}
