// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

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

std::string s[214514];
std::string s1, s2;

bool cmp(std::string a, std::string b) {
    s1 = a + b;
    s2 = b + a;
    return s1 < s2;
}

int main() {
    // freopen("bead.in", "r", stdin);
    // freopen("bead.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }

    // puts("---------");

    std::sort(s, s + n, cmp);

    for (int i = 0; i < n; i++) {
        printf("%s", s[i].c_str());
    }
    // puts("");
    return 0;
}
