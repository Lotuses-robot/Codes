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

int a[200005],
    ac[200005],
    id[200005];
std::vector<std::pair<int, int> > ans;

int main() {
    int T;
    read(T);
    while (T--) {
        int n, cnt = 0;
        read(n);
        for (int i = 0; i < n; i++) {
            read(a[i]);
            cnt += a[i] == 0;
        }

        if ((n - cnt) % 2) {
            puts("-1");
            continue;
        }

        int lcnt = n - cnt;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] != 0) {
                lcnt--;
                id[lcnt] = i;
                ac[lcnt] = a[i];
            }
        }

        if (cnt == n) {
            puts("1");
            printf("%d %d\n", 1, n);
            continue;
        }

        n -= cnt;
        ans.clear();
        if (1 <= id[0]) {
            ans.push_back(std::make_pair(1, id[0]));
        }
        for (int i = 0; i < n / 2; i++) {
            if (ac[i * 2] == ac[i * 2 + 1]) {
                if (id[i * 2] + 1 == id[i * 2 + 1]) {
                    ans.push_back(std::make_pair(id[i * 2] + 1, id[i * 2 + 1] + 1));
                } else {
                    ans.push_back(std::make_pair(id[i * 2] + 1, id[i * 2 + 1] - 1));
                    ans.push_back(std::make_pair(id[i * 2 + 1], id[i * 2 + 1] + 1));
                }
            } else {
                if (id[i * 2] + 1 == id[i * 2 + 1]) {
                    ans.push_back(std::make_pair(id[i * 2] + 1, id[i * 2] + 1));
                    ans.push_back(std::make_pair(id[i * 2 + 1] + 1, id[i * 2 + 1] + 1));
                } else {
                    ans.push_back(std::make_pair(id[i * 2] + 1, id[i * 2] + 1));
                    ans.push_back(std::make_pair(id[i * 2] + 2, id[i * 2 + 1]));
                    ans.push_back(std::make_pair(id[i * 2 + 1] + 1, id[i * 2 + 1] + 1));
                }
            }
            if (i != n / 2 - 1) {
                if (id[i * 2 + 1] + 2 <= id[i * 2 + 2]) {
                    ans.push_back(std::make_pair(id[i * 2 + 1] + 2, id[i * 2 + 2]));
                }
            } else {
                if (id[i * 2 + 1] + 2 <= n + cnt) {
                    ans.push_back(std::make_pair(id[i * 2 + 1] + 2, n + cnt));
                }
            }
        }
        printf("%d\n", ans.size());
        for (auto q : ans) {
            printf("%d %d\n", q.first, q.second);
        }
    }
    return 0;
}

// 2022/10/23 16:36 : I think i make a wrong thought!
