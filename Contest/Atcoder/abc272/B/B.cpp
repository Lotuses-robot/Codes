#include <cstdio>
#include <cstring>
#include <vector>

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

std::vector<int> p[11451];
int mp[1145][1145];

int main() {
    int n, m, k, t;
    read(n, m);
    for (int i = 0; i < m; i++) {
        read(t);
        for (int j = 0; j < t; j++) {
            read(k);
            // p[i].push_back(k);
            mp[k][i] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            bool flag = false;
            for (int k = 0; k < m; k++) {
                if (mp[i][k] && mp[j][k]) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                puts("No");
                return 0;
            }
        }
    }
    puts("Yes");
    return 0;
}
