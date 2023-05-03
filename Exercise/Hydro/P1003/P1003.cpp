// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

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

int excel[1000][1000];

std::pair<int, int> locate(std::string s) {
    int x = s[0] - 'A';
    int y = 0, i = 1;
    while (i < s.length()) {
        y *= 10; y += s[i] - '0';
        i++;
    }
    return std::make_pair(x, y - 1);
}

int main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    int n, m, T;
    read(n, m);
    read(T);
    while (T--) {
        std::string pt, key; std::cin >> pt >> key;
        auto lct = locate(pt);
        printf("%d %d\n", lct.first, lct.second);
        
        if (key == "input") {
            int x; scanf("%d", &x);
            excel[lct.first][lct.second] = x;
        } else if (key == "output") {
            printf("%d\n", excel[lct.first][lct.second]);
        } else if (key == "sum") {
            std::string pt1, pt2; std::cin >> pt1 >> pt2;
            auto lct1 = locate(pt1), lct2 = locate(pt2); 
        } else if (key == "avg") {
            std::string pt1, pt2; std::cin >> pt1 >> pt2;
            auto lct1 = locate(pt1), lct2 = locate(pt2);
            excel[lct.first][lct.second] = excel[lct1.first][lct1.second] + excel[lct2.first][lct2.second];
            excel[lct.first][lct.second] >>= 1;
        }
    }
    return 0;
}
