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

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, s, x, y;
    st:read(n, s);

    if (n == 0 && s == 0) {
        return 0;
    }

    v.clear();
    for (int i = 0; i < n; i++) {
        read(x, y);
        v.push_back(std::make_pair(y, x));
    }

    std::sort(v.begin(), v.end());
    
    bool flag = false;
    for (auto p : v) {
        if (s >= p.first) {
            s += p.second;
        } else {
            flag = true;
            break;
        }
    }

    if (!flag) {
        puts("YES");
    } else {
        puts("NO");
    }

    goto st;
    return 0;
}
