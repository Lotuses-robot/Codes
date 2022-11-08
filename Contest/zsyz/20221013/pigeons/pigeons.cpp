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

struct Tree {
    struct TreeNode {
        int l, r, lc, rc, val;
    };
    TreeNode tn[214514];
}tr;

bool vis[214514];

std::pair<int, int> build(int now) {
    auto left = build(tr.tn[now].lc);
    auto right = build(tr.tn[now].rc);

    tr.tn[now].l = left.first;
    tr.tn[now].r = right.second;
    return std::make_pair(left.first, right.second);
}

void change(int pt, int l, int r, int val) {
    if (l == tr.tn[pt].l && r == tr.tn[pt].r) {
        tr.tn[pt].val = val;
        return;
    }
    int mid = tr.tn[tr.tn[pt].lc].r;
    if (l <= mid) {
        change(tr.tn[pt].lc, l, r, val);
    } else if (r > mid) {
        change(tr.tn[pt].rc, l, r, val);
    } else {
        change(tr.tn[pt].lc, l, mid, val);
        change(tr.tn[pt].rc, mid + 1, r, val);
    }
}

int query(int pt, int l, int r) {
    if (l == tr.tn[pt].l && r == tr.tn[pt].r) {
        return tr.tn[pt].val;
    }
    int mid = tr.tn[tr.tn[pt].lc].r;
    if (l <= mid) {
        return query(tr.tn[pt].lc, l, r);
    } else if (r > mid) {
        return query(tr.tn[pt].rc, l, r);
    } else {
        return query(tr.tn[pt].lc, l, mid) + query(tr.tn[pt].rc, mid + 1, r);
    }
}

int main() {
    freopen("pigeons.in", "r", stdin);
    freopen("pigeons.out", "w", stdout);
    int n, m;
    read(n, m);

    for (int i = 1; i <= n; i++) {
        tr.tn[i].lc = tr.tn[i].rc = -1;
        tr.tn[i].l = tr.tn[i].r = i;
    }

    for (int i = 0; i < n; i++) {
        read(tr.tn[i].lc, tr.tn[i].rc);
        vis[tr.tn[i].lc] = true;
        vis[tr.tn[i].rc] = true;
    }

    int rt;
    for (int i = 1; i < 2 * n - 1; i++) {
        if (!vis[tr.tn[i].lc]) {
            rt = tr.tn[i].lc;
            break;
        }
    }

    build(rt);

    while (m--) {
        int op, l, r;
        read(op, l, r);
        if (op == 1) {
            int d;
            read(d);
            change(rt, l, r, d);
        } else {
            printf("%d\n", query(rt, l, r));
        }
    }
    return 0;
}
