// Copyright 2023 Lotuses
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

const int maxn = 500005;
int s[maxn], n = 0;
void read() {
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') s[++n] = ch - '0', ch = getchar();
}

std::stack<std::pair<int, int> > st;
int l[maxn], r[maxn];
void init() {
    memset(l, -1, sizeof(r));
    memset(r, -1, sizeof(r));
    for (int i = 1; i <= n; i++) {
        if (!st.empty()) {
            auto tp = st.top(); st.pop();
            switch (tp.second)
            {
                case 1:
                    l[tp.first] = i;
                    break;
                case 2:
                    r[tp.first] = i;
                    break;
            
                default:
                    break;
            }
        }

        switch (s[i])
        {
            case 1:
                st.push(std::make_pair(i, 1));
                break;
                
            case 2:
                st.push(std::make_pair(i, 2));
                st.push(std::make_pair(i, 1));
                break;

            default:
                break;
        }
    }
}

int f1[maxn][3], f2[maxn][3];

void dfs(int u) {
    if (s[u] == 0) {
        f1[u][0] = 1; f1[u][1] = f1[u][2] = 0;
        f2[u][0] = 1; f2[u][1] = f2[u][2] = 0;
    } else if (s[u] == 1) {
        dfs(l[u]);
        f1[u][0] = std::max(f1[l[u]][1], f1[l[u]][2]) + 1;
        f1[u][1] = std::max(f1[l[u]][0], f1[l[u]][2]);
        f1[u][2] = std::max(f1[l[u]][0], f1[l[u]][1]);
        
        f2[u][0] = std::min(f2[l[u]][1], f2[l[u]][2]) + 1;
        f2[u][1] = std::min(f2[l[u]][0], f2[l[u]][2]);
        f2[u][2] = std::min(f2[l[u]][0], f2[l[u]][1]);
    } else {
        dfs(l[u]);
        dfs(r[u]);
        f1[u][0] = std::max(f1[l[u]][1] + f1[r[u]][2], f1[l[u]][2] + f1[r[u]][1]) + 1;
        f1[u][1] = std::max(f1[l[u]][0] + f1[r[u]][2], f1[l[u]][2] + f1[r[u]][0]);
        f1[u][2] = std::max(f1[l[u]][0] + f1[r[u]][1], f1[l[u]][1] + f1[r[u]][0]);

        f2[u][0] = std::min(f2[l[u]][1] + f2[r[u]][2], f2[l[u]][2] + f2[r[u]][1]) + 1;
        f2[u][1] = std::min(f2[l[u]][0] + f2[r[u]][2], f2[l[u]][2] + f2[r[u]][0]);
        f2[u][2] = std::min(f2[l[u]][0] + f2[r[u]][1], f2[l[u]][1] + f2[r[u]][0]);
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read();
    init();

    memset(f1, -63, sizeof(f1));
    memset(f2, 63, sizeof(f2));
    dfs(1);
    writeln(std::max(f1[1][0], std::max(f1[1][1], f1[1][2])),
            std::min(f2[1][0], std::min(f2[1][1], f2[1][2])));
    return 0;
}
