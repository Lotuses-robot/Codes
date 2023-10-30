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

int a[200005];
std::vector<std::pair<int, int> > ans;

int main() {
    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        for (int i = 0; i < n; i++) {
            read(a[i]);
        }

        if (n % 2) {
            puts("-1");
            continue;
        }


        ans.clear();
        for (int i = 0; i < n / 2; i++) {
            if (a[i * 2] == a[i * 2 + 1]) {
                ans.push_back(std::make_pair(i * 2 + 1, i * 2 + 2));
            } else {
                ans.push_back(std::make_pair(i * 2 + 1, i * 2 + 1));
                ans.push_back(std::make_pair(i * 2 + 2, i * 2 + 2));
            }
        }
        printf("%d\n", ans.size());
        for (auto q : ans) {
            printf("%d %d\n", q.first, q.second);
        }
    }
    return 0;
}
