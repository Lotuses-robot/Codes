/*
We can make an example for -1 by 1,3,5,...,6,4,2
  *
 * *
*   *

if this appear

  * *
 ^ * ^
*     *

there are two wave crest and we can choose the answer by [^,^]

it's a permutation and there's no same number.

like {2 3 6 5 4 1}

2 up 3 up 6 down 5 down 4 down 1 (with no solution)

1 up [3 down 2(crest 1) up 4 up 6(crest) down 5] up 7 (with solution of [2 6])
*/

// Copyright 2023 Lotuses
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

int n;
int a[200005];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        read(n);
        for (int i = 0; i < n; i++) {
            read(a[i]);
        }

        int l = 0, r = n - 1, mx = n, mn = 1;

        while (l < r && (a[l] == mx || a[l] == mn || a[r] == mx || a[r] == mn)) {
            if (a[l] == mx || a[l] == mn) {
                if (a[l] == mx) mx--;
                else mn++;
                l++;
            } else {
                if (a[r] == mx) mx--;
                else mn++;
                r--;
            }
            // printf("%d, %d, %d, %d\n", l, r, mx, mn);
        }

        if (l == r) {
            puts("-1");
        } else {
            printf("%d %d\n", l + 1, r + 1);
        }
    }
    return 0;
}

/*
nice for two pointer beginner :(
*/