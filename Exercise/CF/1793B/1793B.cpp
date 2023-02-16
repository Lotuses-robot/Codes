// Copyright 2023 Lotuses
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

std::vector<int> ans;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        ans.clear();
        int x, y;
        read(x, y);
        for (int i = x; i >= y; i--) {
            ans.push_back(i);
        }
        for (int i = y + 1; i < x; i++) {
            ans.push_back(i);
        }
        printf("%d\n", ans.size());
        for (int v : ans) {
            printf("%d ", v);
        }
        puts("");
    }
    return 0;
}

/*
It's seemed to be hard to prove this solution.
there's an example for x-> x/2, x/2-1, x/2 -> it can solve x/2 by 3 steps and save 1/2 steps for down
but there's x/2-1 for y.

here's an example
x->6 y->3
6 5 4 3 4 5
2 1 2 1 2 1

but the length is the same!
*/