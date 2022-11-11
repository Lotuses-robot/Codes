// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define gc getchar()
template<typename T>
bool read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
    return r != 0;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

int n, t, ti[100], d[2][100];
int record[2][100][100];
struct Visit {
    int fac, id, sti, time;
    bool operator < (Visit b) const {
        return time < b.time;
    }
};
std::vector<Visit> v;

void ReadInit() {
    read(t);
    for (int i = 1; i <= n - 1; i++) {
        read(ti[i]);
    }
    v.clear();
    v.push_back({0, 0, 1, -1});
    read(d[0][0]);
    for (int i = 1; i <= d[0][0]; i++) {
        read(d[0][i]);
        int tmp = d[0][i];
        for (int j = 1; j <= n; j++) {
            v.push_back({0, i, j, tmp});
            record[0][i][j] = tmp;
            tmp += ti[j];
        }
    }
    read(d[1][0]);
    for (int i = 1; i <= d[1][0]; i++) {
        read(d[1][i]);
        int tmp = d[1][i];
        for (int j = n; j >= 1; j--) {
            v.push_back({1, i, j, tmp});
            record[1][i][j] = tmp;
            tmp += ti[j - 1];
        }
    }
    std::sort(v.begin(), v.end());
}

int f[5006];

int main() {
    #ifdef LOCAL
        freopen("P2583.in", "r", stdin);
        freopen("P2583.out", "w", stdout);
    #endif
    int cnt = 0;
    while (read(n)) {
        cnt++;
        ReadInit();

        memset(f, 63, sizeof(f));
        int ans = 1145141919;
        f[0] = 0;
        for (int i = 0, len = v.size(); i < len; i++) {
            for (int j = 0; j < i; j++) {
                // printf("%d %d\n", i, j);
                if (
                    v[j].time >= v[i].time || // eq
                    v[i].fac == 0 && v[j].sti >= v[i].sti || // station
                    v[i].fac == 1 && v[j].sti <= v[i].sti ||
                    v[j].time > record[v[i].fac][v[i].id][v[j].sti] // was it visit before train coming? 
                ) continue;
                if (v[j].time == -1) v[j].time = 0;
                f[i] = std::min(f[i], f[j] + 
                (record[v[i].fac][v[i].id][v[j].sti] - v[j].time));
                // printf("inf %d %d %d %d\n", v[j].fac, v[j].id, v[j].sti, v[j].time);
                // printf("ans %d %d %d\n", f[j], record[v[i].fac][v[i].id][v[j].sti], v[j].time);
            }
            if (v[i].sti == n && t >= v[i].time) {
                ans = std::min(ans, f[i] + (t - v[i].time));
                // printf("debug %d %d\n", f[i], t - v[i].time);
            }
        }

        printf("Case Number %d: ", cnt);
        if (ans >= 100000000) { // hacks!
            puts("impossible");
        } else {
            printf("%d\n", ans);
        }
    }
    return 0;
}