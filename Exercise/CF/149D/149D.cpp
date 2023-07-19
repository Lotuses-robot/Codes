// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <stack>
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

const int mod = 1000000007;
const int maxn = 705;
char s[maxn];
int n, R[maxn];
std::stack<int> st;
int f[maxn][maxn][3][3];

// R[l] != r
// f[0][1] = (f[0][1] + f[0][2]) * (f[0][1] + f[1][1] + f[2][1]) - f[0][2] *
// f[2][1] - f[0][1] * f[1][1] f[0][2] =                                         * (f[0][2] +
// f[1][2] + f[2][2])                                    2                                     2 f[1][0] = (f[1][0]
// + f[1][2]) * (f[0][0] + f[1][0] + f[2][0]) - f[1][0] * f[0][0] - f[1][2] *
// f[2][0] f[2][0] = (f[2][0] + f[2][1]) *                                                                     2
// 2    1            1    0

// R[l] == r
// f[0][1] = f[0][0] + f[0][2] + f[1][0] + f[1][2] + f[2][0] + f[2][2]
// f[0][2] =                                1                                     1                                     1
// f[1][0] = f[0][0] + f[0][1] + f[0][2] + f[2][0] + f[2][1] + f[2][2]
// f[2][0] =                                                                 1                 1                 1

void dfs(int l, int r) {
    if (R[l] < l || R[l] > r) {
        return;
    } else if (l + 1 == r) {
        f[l][r][0][0] = f[l][r][1][1] = f[l][r][1][2] = f[l][r][2][1] =
                f[l][r][2][2] = 0;
        f[l][r][0][1] = f[l][r][1][0] = f[l][r][0][2] = f[l][r][2][0] = 1;
    } else {
        if (r == R[l]) {
            dfs(l + 1, r - 1);
            auto &p = f[l + 1][r - 1];
            f[l][r][0][1] = p[0][0] + p[0][2] + p[1][0] + p[1][2] + p[2][0] + p[2][2]; f[l][r][0][1] %= mod;
            f[l][r][0][2] = p[0][0] + p[0][1] + p[1][0] + p[1][1] + p[2][0] + p[2][1]; f[l][r][0][2] %= mod;
            f[l][r][1][0] = p[0][0] + p[0][1] + p[0][2] + p[2][0] + p[2][1] + p[2][2]; f[l][r][1][0] %= mod;
            f[l][r][2][0] = p[0][0] + p[0][1] + p[0][2] + p[1][0] + p[1][1] + p[1][2]; f[l][r][2][0] %= mod;
            // for (int i = 0; i <= 2; i++){
            //         for (int j = 0; j <= 2; j++){
            //                 if (j != 1) f[l][r][0][1] += f[l+1][r-1][i][j];
            //                 if (j != 2) f[l][r][0][2] += f[l+1][r-1][i][j];
            //                 if (i != 1) f[l][r][1][0] += f[l+1][r-1][i][j];
            //                 if (i != 2) f[l][r][2][0] += f[l+1][r-1][i][j];
            //         }
            // }
        } else {
            dfs(l, R[l]);
            dfs(R[l] + 1, r);
            auto &ll = f[l][R[l]], &rr = f[R[l] + 1][r];

            for (int i = 0; i <= 2; i++) {
                for (int j = 0; j <= 2; j++) {
                    for (int p = 0; p <= 2; p++) {
                        for (int q = 0; q <= 2; q++) {
                            if ((j == 1 && p == 1) || (j == 2 && p == 2)) continue;
                            f[l][r][i][q] += (ll[i][j] * rr[p][q] % mod);
                            f[l][r][i][q] %= mod;
                        }
                    }
                }
            }
        }
    }
}

signed main() {
#ifdef LOCAL
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif

    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '(')
            st.push(i);
        else {
            R[st.top()] = i, R[i] = st.top();
            st.pop();
        }
    }
    dfs(1, n);
    int ans = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ans += f[1][n][i][j];
            ans %= mod;
        }
    }
    writeln(ans);
    return 0;
}
