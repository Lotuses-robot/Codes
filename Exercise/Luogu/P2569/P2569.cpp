// Copyright 2023 Lotuses
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

const int maxn = 4000;
int T, maxp, W;
int AP[maxn], BP[maxn], AS[maxn], BS[maxn];
int f[maxn][maxn], maxf[maxn], ans = 0;

std::deque<std::pair<int, int> > q;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(T, maxp, W);
    for (int i = 1; i <= T; i++) {
        read(AP[i], BP[i], AS[i], BS[i]);
    }
    memset(f, -63, sizeof(f));
    memset(maxf, -63, sizeof(maxf));
    f[1][0] = 0;
    for (int i = 1; i <= 1 + W; i++)
    for (int j = 1; j <= AS[i]; j++) {
        f[i][j] = -AP[i] * j;
    }
    for (int i = 1 + W + 1; i <= T; i++) {
        for (int j = 1; j <= AS[i]; j++) {
            f[i][j] = -AP[i] * j;
        }
        for (int j = 0; j <= maxp; j++) {
            maxf[j] = std::max(maxf[j], f[i - W - 1][j]);
        }
        for (int j = 0; j <= maxp; j++) {
            f[i][j] = std::max(f[i][j], f[i - 1][j]);
            ans = std::max(f[i][j], ans);
        }
        // Buy
        int j;
        for (j = 1; j <= maxp; j++) {
            while (!q.empty() && q.front().second <= j - AS[i]) q.pop_front();
            while (!q.empty() &&
                    q.back().first - AP[i] * (j - q.back().second + 1) < maxf[j - 1] - AP[i]) q.pop_back();
            q.push_back(std::make_pair(maxf[j - 1], j));
            f[i][j] = std::max(f[i][j], q.front().first - AP[i] * (j - q.front().second + 1));
        }
        while (!q.empty()) {
            // while (!q.empty() && q.front().second < j - AS[i]) q.pop_front();
            // f[i][j] = std::max(f[i][j], q.front().first + AP[i] * (j - q.front().second + 1));
            q.pop_back();
            j++;
        }
        // Sell
        for (j = -BS[i]; j <= maxp - BS[i]; j++) {
            while (!q.empty() && q.front().second <= j) q.pop_front();
            while (!q.empty() &&
                    q.back().first - BP[i] * (j + BS[i] - q.back().second) <
                    maxf[j + BS[i]] + BS[i] * BP[i]) q.pop_back();
            q.push_back(std::make_pair(maxf[j + BS[i]] + BS[i] * BP[i], j + BS[i]));
            if (j >= 0) f[i][j] = std::max(f[i][j], q.front().first - BP[i] * (j + BS[i] - q.front().second));
        }              
        while (!q.empty()) {
            while (!q.empty() && q.front().second <= j) q.pop_front();
            if (q.empty()) break;
            if (j >= 0) f[i][j] = std::max(f[i][j], q.front().first - BP[i] * (j + BS[i] - q.front().second));
            j++;
        }
    }
    
    ans = std::max(ans, f[T][0]);
    writeln(ans);
    return 0;
}
