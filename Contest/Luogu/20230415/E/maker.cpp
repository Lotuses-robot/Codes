#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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

const int maxn = 3001;
int map[maxn][maxn];

std::vector<std::pair<int, int> > v;

int main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        freopen(".in", "w", stdout);
    #endif
    srand(time(NULL));

    int n = 20, m = 20, q = 300;
    writeln(n, m, q);
    for (int i = 1; i <= q; i++) {
        rd: int x = rand() % n + 1, y = rand() % m + 1;
        if (!map[x][y]) map[x][y] = 1;
        else goto rd;
        v.push_back(std::make_pair(x, y));
    }
    std::sort(v.begin(), v.end());
    for (auto p : v) {
        writeln(p.first, p.second);
    }
    return 0;

}
