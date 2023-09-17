// Copyright 2023 Lotuses
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

// #define __DEBUG
#ifdef __DEBUGwww
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

#define int long long

const int maxn = 1 << 22;
char s[maxn];
int lt[maxn], rt[maxn];
int z[maxn], n;
int cnt[511];

void initz() {
    memset(z, 0, sizeof(z));
    int l = 0, r = 0;
    z[0] = n;
    debug(z[0]);
    for (int i = 1; i < n; i++) {
        if (i > r) {
            z[i] = 0;
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        } else {
            z[i] = z[i - l];
            if (i + z[i] > r) {
                z[i] = r - i + 1;
                while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            }
        }
        if (z[i] && z[i] + i > r) {
            l = i; r = z[i] + i - 1;
        }
        debug(z[i]);
    }
}

struct treeArray {
    int n, ar[255];
    int lowbit(int x) { return x & (-x); }
    void init(int n) {
        this -> n = n;
        memset(ar, 0, sizeof(ar));
    }
    void add(int x, int k) {
        while (x <= n) {
            ar[x] += k;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int ans = 0;
        while (x > 0) {
            ans += ar[x];
            x -= lowbit(x);
        }
        return ans;
    }
};
treeArray ta;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int T;
    read(T);
    while (T--) {
        scanf("%s", s); n = strlen(s);
        initz();
        memset(cnt, 0, sizeof(cnt));
        memset(lt, 0, sizeof(lt));
        lt[0] = 1; cnt[s[0]]++;
        for (int i = 1; i < n; i++) {
            cnt[s[i]]++;
            lt[i] = lt[i - 1] + ((cnt[s[i]] & 1) ? 1 : -1);
            debug(i, lt[i]);
        }
        memset(cnt, 0, sizeof(cnt));
        memset(rt, 0, sizeof(rt));
        rt[n - 1] = 1; cnt[s[n - 1]]++;
        for (int i = n - 2; i >= 0; i--) {
            cnt[s[i]]++;
            rt[i] = rt[i + 1] + ((cnt[s[i]] & 1) ? 1 : -1);
            debug(i, rt[i]);
        }
        int ans = 0;
        ta.init(100);
        for (int i = 2; i < n; i++) {
            ta.add(lt[i - 2] + 1, 1);
            debug(lt[i - 2] + 1);
            int k = z[i] / i + 1, odd, even;
            debug(k, i, z[i]);
            if (k & 1) {
                even = rt[i];
                odd = rt[0];
            } else {
                even = rt[0];
                odd = rt[i];
            }
            // only c
            int c = (k + 1) / 2;
            if (k * i == n && c > 0) c--;
            debug(c, even + 1, ta.query(even + 1));
            ans += c * ta.query(even + 1);
            // abc
            c = k / 2;
            // if (z[i] + i == n && c > 0) c--;
            debug(c, odd + 1, ta.query(odd + 1));
            ans += c * ta.query(odd + 1);
        }
        writeln(ans);
    }
    return 0;
}
