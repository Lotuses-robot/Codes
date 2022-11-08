// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

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

int sum[1145144];
char ch[114514];

void init() {
    sum[0] = 0;
    int nowpt = 0;
    for (int i = 1; ; i++) {
        sprintf(ch, "%lld", i); // NOLINT
        int len = strlen(ch);

        for (int j = 0; j < i; j++) {
            for (int k = 0; k < len; k++) {
                nowpt++;
                if (nowpt >= 1000005) break;
                sum[nowpt] = sum[nowpt - 1] + ch[k] - '0';
            }
            if (nowpt >= 1000005) break;
        }
        if (nowpt >= 1000005) break;
    }
}

signed main() {
    int T;
    init();
    read(T);

    while (T--) {
        int l, r;
        read(l, r);
        printf("%lld\n", sum[r] - sum[l - 1]);
    }
    return 0;
}
