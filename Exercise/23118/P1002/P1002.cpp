// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

std::vector<std::pair<int, int> > v;

void init() {
    v.push_back({4, 3});
    int q = 2, w = 3;
    for (int i = 3; q <= 1000; i++) {
        q *= i;
        w += i;
        v.push_back({q, w});
    }
    std::reverse(v.begin(), v.end());
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    init();
    // printf("%d\n", v.size());
    int s;
    read(s); int it = 0, ans = 0;
    while (s > 4) {
        while (it < v.size() && v[it].first > s) it++;
        if (it >= v.size()) {
            break;
        }
        s -= v[it].first;
        ans += v[it].second;
    }

    it = 2;    
    while (s >= 0) {
        s -= it;
        if (s >= 0) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
