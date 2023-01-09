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

char ch[3114514];

#define ceil(a) ((a) % 2 ? a / 2 + 1 : a / 2)

int query(int l, int r) {
    int ans = 0;
    for (int i = l; i <= r; i++)
        if (ch[i] != ch[i - 1])
            ans++;
    return ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T, n;
    read(T);
    scanf("%s", ch); n = strlen(ch);
    int cnt = 1, last = ch[0];
    for (int i = 1; i < n; i++) {
        if (ch[i] != last) {
            cnt++;
            last = ch[i];
        }
    }
    printf("%d\n", ceil(cnt));

    int i = 0;
    while (T--) {
        int p; char c;
        read(p); scanf("%c", &c); p--;
        cnt -= query(p, p + 1);
        ch[p] = c;
        cnt += query(p, p + 1);
        printf("%s\n", ch);
        printf("%d %d %d\n", ++i, ceil(cnt), cnt);
    }
    return 0;
}
