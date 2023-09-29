// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
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

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("d <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 2e6 + 10;
int n, a[maxn];
std::vector<std::string> ans;
bool solve(int mid) {
    // writeln(mid);
    std::string ft = "", ed = "";
    int h1 = 1, t1 = mid, h2 = n, t2 = mid + 1;
    while (h1 <= t1 && h2 >= t2) {
        // writeln(h1, t1, h2, t2);
        if (a[h1] == a[t1] && h1 != t1) {
            ft += 'L'; ed += 'L';
            h1++; t1--;
        } else if (a[h1] == a[t2]) {
            ft += 'L'; ed += 'R';
            h1++; t2++;
        } else if (a[h2] == a[t1]) {
            ft += 'R'; ed += 'L';
            h2--; t1--;
        } else if (a[h2] == a[t2] && h2 != t2) {
            ft += 'R'; ed += 'R';
            h2--; t2++;
        } else {
            return false;
        }
    }
    // puts("??");
    while (h1 <= t1) {
        // writeln(h1, t1, h2, t2);
        if (a[h1] == a[t1]) {
            ft += 'L'; ed += 'L';
            h1++; t1--;
        } else {
            return false;
        }
    }
    while (h2 >= t2) {
        // writeln(h1, t1, h2, t2);
        if (a[h2] == a[t2]) {
            ft += 'R'; ed += 'R';
            h2--; t2++;
        } else {
            return false;
        }
    }
    // printf("%s %s\n", ft.c_str(), ed.c_str());
    std::reverse(ed.begin(), ed.end());
    ans.push_back(ft + ed);
    return true;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        ans.clear();
        read(n);
        n <<= 1;
        for (int i = 1; i <= n; i++) {
            read(a[i]);
        }
        if (n == 2) {
            puts("LL");
            continue;
        }
        for (int i = 2; i < n; i++) {
            if (a[i] == a[1]) {
                solve(i);
                solve(i + 1);
            }
            if (a[i] == a[n]) {
                solve(i);
                solve(i + 1);
            }
            // solve(i);
        }
        solve(0);
        solve(n);
        if (ans.empty()) {
            puts("-1");
        } else {
            std::sort(ans.begin(), ans.end());
            printf("%s\n", (*ans.begin()).c_str());
        }
    }
    return 0;
}
