// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <deque>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T x) { write(x); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 2e5 + 10;
int a[maxn];
int n, k, min;

std::deque<std::pair<int, int> > dq;
void ins(int id) {
    while (!dq.empty() && dq.back().first >= a[id]) {
        dq.pop_back();
    }
    dq.push_back({a[id], id});
}
void pop(int id) {
    while (!dq.empty() && dq.front().second >= id) {
        dq.pop_front();
    }
}
int query() {
    return dq.front().first;
}

void output() {
    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }
    puts("");
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".ans", "w", stdout);
    #endif
    
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = n - 1; i >= n - k + 1; i--) {
        ins(i);
    }
    int pt = n - k;
    while (pt >= 1 && a[pt] <= query()) {
        pop(pt + k - 1);
        ins(pt);
        pt--;
    }
    int l = pt + 1;
    for (int i = pt; i >= 1; i--) {
        if (a[i] > a[i + 1]) l = i;
        if (l - i + 1 >= k) {
            output();
            return 0;
        }
    }
    pt++;
    std::sort(a + pt, a + pt + k);
    output();
    return 0;
}
