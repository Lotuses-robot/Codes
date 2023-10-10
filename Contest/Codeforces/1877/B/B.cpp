// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

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

const int maxn = 1e5 + 10;
struct Node {
    int cost, num;
    bool operator < (Node b) const {
        return cost > b.cost;
    }
};
std::priority_queue<Node> q1, q2;
int a[maxn], b[maxn];

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        while (!q1.empty()) q1.pop();
        int n, p, cost = 0;
        read(n, p);
        q1.push({p, (int)1e9});
        for (int i = 1; i <= n; i++) {
            read(a[i]);
        }
        for (int i = 1; i <= n; i++) {
            read(b[i]);
            q2.push({b[i], a[i]});
        }
        while (!q2.empty()) {
            Node t1 = q1.top(), t2 = q2.top();
            q1.pop(); q2.pop();

            // writeln(t1.cost, t1.num);
            cost += t1.cost;
            t1.num--;
            if (t1.num > 0) q1.push(t1);

            q1.push(t2);
        }
        writeln(cost);
    }
    return 0;
}