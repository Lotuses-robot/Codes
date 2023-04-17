#include <cstdio>
#include <cstring>
#include <vector>
#include <map>

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

int n, k; bool flag;
int num[50004];
std::map<std::pair<int, int>, int> mp;

#define cg(x) ((x) > n ? (x) - n + 1 : (x))

int cnt = 0;

int query(int x, int y) {
    // if (x > n) x -= n - 1;
    // if (y > n) y -= n - 1;
    cnt++;
    if (cnt > k) return 1;
    if (mp.count(std::make_pair(x, y))) return mp[std::make_pair(x, y)];
    printf("? %d %d\n", x, y);
    fflush(stdout);
    int z;
    // read(z);
    scanf("%d", &z);
    mp[std::make_pair(x, y)] = z;
    return z;
}

void fuckin() {
    int a = query(1, 2), b = query(2, 3), c = query(3, 1);
    if (a > b && a > c) {
        if (b > c) {
            printf("! %d\n", 2);
        } else {
            printf("! %d\n", 3);
        }
    }
    else if (b > a && b > c) {
        if (a > c) {
            printf("! %d\n", 1);
        } else {
            printf("! %d\n", 3);
        }
    }
    else if (c > a && c > b) {
        if (a > b) {
            printf("! %d\n", 1);
        } else {
            printf("! %d\n", 2);
        }
    }
}

int main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        memset(num, 0, sizeof(num));
        mp.clear();
        cnt = 0;
        flag = false;
        scanf("%d%d", &n, &k);

        if (n == 3) {
            fuckin();
            continue;
        }

        if (n % 2) flag = true, n--;
        for (int i = 1; i <= n; i += 2) {
            num[i / 2 + 1] = query(i, i + 1);
        }
        // if (flag) {
        //     num[n / 2 + 1] = query(1, n + 1);
        // }
        int maxx = -1, id;
        for (int i = 1; i <= n / 2; i++) {
            if (num[i] > maxx) {
                maxx = num[i];
                id = i;
            }
        }
        int i = id * 2 + 1;
        if (i > n && flag) i = n + 1;
        else if (i > n) i = 1;
        int a = query(id * 2 - 1, cg(i));
        int b = query(id * 2, cg(i));
        if (flag) {
            int c = query(n + 1, i);
            if (c >= a && c >= b) {printf("! %d\n", n + 1), fflush(stdout);continue;}
        }
        if (a > b) {
            printf("! %d\n", id * 2 - 1);
            fflush(stdout);
        } else {
            printf("! %d\n", id * 2);
            fflush(stdout);
        }
    }
    return 0;
}