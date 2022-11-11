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
int n, a, b, c;
int l[114514];

#define abs(a) ((a) < 0 ? -(a) : (a))

int dfs(int pt, int pta, int ptb, int ptc) {
    if (pt == n) {
        if (pta == 0 || ptb == 0 || ptc == 0) return 1145141919;
        return abs(a - pta) + abs(b - ptb) + abs(c - ptc);
    }
    int ans = 1145141919;
    ans = std::min(ans, dfs(pt + 1, pta, ptb, ptc));
    ans = std::min(ans, dfs(pt + 1, pta + l[pt], ptb, ptc) + 10);
    ans = std::min(ans, dfs(pt + 1, pta, ptb + l[pt], ptc) + 10);
    ans = std::min(ans, dfs(pt + 1, pta, ptb, ptc + l[pt]) + 10);
    return ans;
}

int main() {
    read(n, a, b, c);
    for (int i = 0; i < n; i++) {
        read(l[i]);
    }

    printf("%d\n", dfs(0, 0, 0, 0) - 30);
    return 0;
}
