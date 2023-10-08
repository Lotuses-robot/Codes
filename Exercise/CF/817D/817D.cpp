// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>

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

#define int long long

const int maxn = 1e6 + 10;
int a[maxn], lmx[maxn], lmn[maxn], rmx[maxn], rmn[maxn];
struct Node {
    int x, id;
};
std::stack<Node> st1, st2;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    for (int i = 1; i <= n; i++) {
        while (!st1.empty() && st1.top().x < a[i]) st1.pop();
        if (st1.empty()) lmx[i] = 0;
        else lmx[i] = st1.top().id;
        st1.push({a[i], i});

        while (!st2.empty() && st2.top().x > a[i]) st2.pop();
        if (st2.empty()) lmn[i] = 0;
        else lmn[i] = st2.top().id;
        st2.push({a[i], i});
    }

    while (!st1.empty()) st1.pop();
    while (!st2.empty()) st2.pop();

    for (int i = n; i >= 1; i--) {
        while (!st1.empty() && st1.top().x <= a[i]) st1.pop();
        if (st1.empty()) rmx[i] = n + 1;
        else rmx[i] = st1.top().id;
        st1.push({a[i], i});

        while (!st2.empty() && st2.top().x >= a[i]) st2.pop();
        if (st2.empty()) rmn[i] = n + 1;
        else rmn[i] = st2.top().id;
        st2.push({a[i], i});
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // writeln(lmx[i], i, rmx[i]);
        ans += a[i] * (i - lmx[i]) * (rmx[i] - i);
    }
    for (int i = 1; i <= n; i++) {
        // writeln(lmn[i], i, rmn[i]);
        ans -= a[i] * (i - lmn[i]) * (rmn[i] - i);
    }
    writeln(ans);
    return 0;
}