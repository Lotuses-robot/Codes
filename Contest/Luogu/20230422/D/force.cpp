#include <cstdio>
#include <cstring>
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

int n, ans = 0;

char ch[2003], now[2003];

void print() {
    for (int i = 1; i <= n + 1; i++) {
        putchar(now[i]);
    }
    puts("");
}

int dfs(int u, int pur) { // n - 1, n
    if (now[u] == ch[pur]) return 0;
    if (u == 1) {
        now[u] = ch[pur]; print(); return 1;
    }
    int ans = 0;
    for (int i = u - 1; i >= 1; i--) {
        ans += dfs(i, n - (u - i) + 1);
    }
    now[u] = ch[pur];
    ans++;
    print();
    return ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".ans", "w", stdout);
    #endif
    
    read(n);

    scanf("%s", ch + 1);
    for (int i = 1; i <= n + 1; i++) {
        now[i] = '0';
    }

    for (int i = n; i >= 0; i--) {
        if (now[i + 1] == '1') continue;
        for (int j = i; j >= 1; j--) {
            ans += dfs(j, n - (i - j));
        }
        ans++;
        now[i + 1] = '1';
        print();
    }

    printf("%d\n", ans);
    return 0;
}