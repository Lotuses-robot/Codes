// Copyright 2023 Lotuses
#define tsz signed
#include "testlib.h"
#include <cstdio>
#include <vector>

const int maxn = 2e5 + 10;
int a[maxn], x;
bool vis[maxn];
std::vector<int> b, c;

tsz main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    for (int i = 1; i <= n; i++) {
        a[i] = inf.readInt();
        // printf("%d\n", i);
    }
    
    int m = ouf.readInt();
    if (m == -1) {
        quitf(_ok, "-1.");
    }
    for (int i = 1; i <= m; i++) {
        x = ouf.readInt();
        b.push_back(x);
        vis[x] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            c.push_back(a[i]);
        }
    }
    if (b == c) {
        quitf(_ok, "Num: %d.", (int)b.size());
    } else {
        for (int i : b) {
            printf("%d ", i);
        }
        puts("");
        for (int i : c) {
            printf("%d ", i);
        }
        puts("");
        quitf(_wa, "Num: %d %d.", (int)b.size(), (int)c.size());
    }
}