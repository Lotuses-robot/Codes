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

std::pair<int, int> s[1003];
int n;
std::vector<std::pair<int, int> > ans;

void action(int i, int j) {
    s[i].first = s[i].first / s[j].first + (s[i].first % s[j].first == 0 ? 0 : 1);
    ans.push_back(std::make_pair(s[i].second, s[j].second));
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int T;
    read(T);
    while (T--) {
        ans.clear();
        read(n);
        bool same = 1, one = 0;
        for (int i = 1; i <= n; i++) {
            read(s[i].first);
            if (i >= 2) same &= s[i].first == s[i - 1].first;
            one |= s[i].first == 1;
            s[i].second = i;
        }
        if (same || n == 1) {
            puts("0");
            continue;
        } else if (one) {
            puts("-1");
            continue;
        }

        while (true) {
            std::sort(s + 1, s + n + 1);
            if (s[1].first == s[n].first) break;
            action(n, 1);
        }

        printf("%d\n", ans.size());
        for (auto e : ans) {
            printf("%d %d\n", e.first, e.second);
        }
    }
    return 0;
}
