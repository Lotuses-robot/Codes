// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
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

const int maxn = 2e3;
int a[maxn], suf[maxn];
int n;

struct Edge {
    int u, v;
}; std::vector<Edge> G[maxn];

std::queue<int> q;

int col[maxn];

int pos = 1;
std::stack<int> S[2];

inline void out(char ch) {
	putchar (ch); putchar (' ');
}

inline bool Pop(int id) {
	if (!S[id].empty() && S[id].top() == pos) {
		out(id ? 'd' : 'b'), S[id].pop(), ++ pos;
		return true;
	}
	return false;
}

inline void Push(int cur, int id) {
	if (id == 1) { while(Pop(0)); }
	while (!S[id].empty() && S[id].top() < cur)
		if (!Pop(id)) Pop(id ^ 1);
	if (id == 1) { while(Pop(0)); }
	S[id].push(cur); out(id ? 'c' : 'a');
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    suf[n + 1] = n + 1;
    for (int i = n; i >= 1; i--) {
        suf[i] = std::min(suf[i + 1], a[i]);
    }

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (suf[j + 1] < a[i] && a[i] < a[j]) {
                G[i].push_back({i, j}); G[j].push_back({j, i}); col[i] = col[j] = -1;
            }
        }
    }
    memset(col, -1, sizeof(col));
    for (int i = 1; i <= n; i++) {
        if (!~col[i]) {
            q.push(i); col[i] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (auto e : G[u]) {
                    if (~col[e.v] && col[e.v] != (col[u] ^ 1)) {
                        puts("0");
                        return 0;
                    }
                    if (!~col[e.v]) {
                        col[e.v] = col[u] ^ 1;
                        q.push(e.v);
                    }
                }
            }
        }
    }

    
	for (int i = 1; i <= n; i++)
		Push(a[i], col[i]);

	bool flag = true;
	while (flag) {
		flag = false;
		while(Pop(0)) flag = true;
		while(Pop(1)) flag = true;
	}
    return 0;
}
