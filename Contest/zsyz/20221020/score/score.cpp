// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

#define int long long

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
int v[1145141];

std::multiset<int> s;
std::queue<int> q;

signed main() {
    // freopen("score.in", "r", stdin);
    // freopen("score.out", "w", stdout);
    int n, S, ans = 0;
    read(n, S);
    for (int i = 1; i <= n; ++i) {
        read(v[i]);
    }
    int sum = 0;
    if (S > 0) {
        for (int i = 1; i <= n; ++i) {
            if (v[i] < 0) {
                q.push(v[i]);
                sum += v[i];
            } else {
                sum += v[i];
                s.insert(v[i]);
            }
            while (!q.empty()) {
                int x = q.front(); q.pop(); // NOLINT
                while (x < 0 && !s.empty()) {
                    auto it = s.begin();
                    x += *it;
                    s.erase(it);
                }
                if (x > 0) {
                    s.insert(x);
                } if (s.empty()) { // NOLINT
                    q.push(x);
                    break;
                }
            }
            if (sum < 0) {
                sum = 0;
                while (q.size())
                    q.pop();
            }
            while (sum >= S && !s.empty()) {
                auto it = s.end(); it--; // NOLINT
                sum -= *it;
                s.erase(it);
                ans++;
            }
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            if (v[i] >= S) {
                ans++;
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
