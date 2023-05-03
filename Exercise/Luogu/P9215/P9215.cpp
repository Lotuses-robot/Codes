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

const int maxn = 10004;

char ch[maxn]; int n, k;

struct Node {
    int c, t;
};
std::vector<Node> v;
std::vector<Node> ans;
std::vector<Node> trueans;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        scanf("%s", ch + 1);
        n = strlen(ch + 1);
        read(k);

        v.clear();
        bool kp0 = 0, kp9 = 0;
        for (int i = n; i >= 1; i--) {
            if (ch[i] != '9' && ch[i] != '0') {
                v.push_back({ch[i] - '0', 1});
                kp0 = kp9 = 0;
            } else if (ch[i] == '9') {
                if (kp9) {
                    v.rbegin() -> t++;
                } else {
                    v.push_back({ch[i] - '0', 1});
                    kp0 = false;
                    kp9 = true;
                }
            } else if (ch[i] == '0') {
                if (kp0) {
                    v.rbegin() -> t++;
                } else {
                    v.push_back({ch[i] - '0', 1});
                    kp9 = false;
                    kp0 = true;
                }
            }
        }
        v.push_back({-1, -1});

        ans.clear();
        int cnt = 0, bef9 = -1; bool f0 = false;
        for (int i = 0; i < v.size(); i++) {
            if (cnt == k) break;
            if (v[i].c == 0) {
                if (i == 0) { ans.push_back({0, v[i].t}); f0 = true; continue; } // i hate this status
                if (v[i + 1].c == 9) {
                    bef9 = v[i].c;
                    v[i].t--;
                }
                if (v[i].t > (k - cnt)) {
                    ans.push_back({9, k - cnt});
                    cnt += (k - cnt);
                } else {
                    ans.push_back({9, v[i].t});
                    cnt += v[i].t;
                }
            } else if (v[i].c == 9) {
                if (i == 0 || f0) {
                    f0 = false;
                    if (v[i].t > (k - cnt)) {
                        ans.push_back({0, v[i].t - (k - cnt)});
                        ans.push_back({1, k - cnt});
                        cnt += k - cnt;
                    } else {
                        ans.push_back({1, v[i].t});
                        cnt += v[i].t;
                    }
                } else {
                    if (v[i].t + 1 > (k - cnt)) {
                        ans.push_back({0, v[i].t + 1 - (k - cnt)});
                        ans.push_back({1, k - cnt});
                        cnt += k - cnt;
                    } else {
                        ans.push_back({9 - bef9, 1});
                        ans.push_back({1, v[i].t});
                        cnt += v[i].t + 1;
                    }
                }
            } else {
                if (i == 0 || f0) {
                    f0 = false;
                    if (v[i + 1].c == 9) {
                        bef9 = v[i].c - 1;
                        continue;
                    }
                    if (v[i].t > (k - cnt)) {
                        ans.push_back({10 - v[i].c, k - cnt});
                        cnt += (k - cnt);
                    } else {
                        ans.push_back({10 - v[i].c, v[i].t});
                        cnt += v[i].t;
                    }
                } else {
                    if (v[i + 1].c == 9) {
                        bef9 = v[i].c;
                        continue;
                    }
                    if (v[i].t > (k - cnt)) {
                        ans.push_back({9 - v[i].c, k - cnt});
                        cnt += (k - cnt);
                    } else {
                        ans.push_back({9 - v[i].c, v[i].t});
                        cnt += v[i].t;
                    }
                }
            }
        }

        if (cnt != k) {
            puts("-1");
            continue;
        }

        trueans.clear();
        for (int i = (int)ans.size() - 1; i >= 0; i--) {
            trueans.push_back(ans[i]);
        }

        for (auto p : trueans) {
            for (int i = 1; i <= p.t; i++) {
                putchar(p.c + '0');
            }
        }
        puts("");
    }
    return 0;
}
