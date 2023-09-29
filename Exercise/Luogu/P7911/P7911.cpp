// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
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
#define debug(arg, args...) { printf("d <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 1e4 + 10;
char op[maxn][100], ad[100];
int sta[maxn], id[maxn];
std::string out[10] = { "OK", "FAIL", "ERR" };
std::vector<std::string> v;
std::string s;
std::map<std::string, int> mp;

int x;
bool getnum(std::string s, int validmax) {
    if (!isdigit(s[0]) || s.length() > 5) return true;
    sscanf(s.c_str(), "%d", &x);
    if (s[0] == '0' && x != 0) return true;
    if (x == 0 && s.length() > 1) return true;
    return x > validmax;
}

bool check() {
    s = ""; v.clear(); int len = strlen(ad);
    for (int i = 0; i < len; i++) {
        if (i == 0 || (isdigit(ad[i]) ^ isdigit(ad[i - 1])) == 0) {
            s += ad[i];
        } else {
            v.push_back(s);
            s = ad[i];
        }
    }
    if (!s.empty()) v.push_back(s);
    if (v.size() != 9) return true;
    if (getnum(v[0], 255) || v[1] != "." || getnum(v[2], 255) || v[3] != "." || getnum(v[4], 255) || v[5] != "." ||
        getnum(v[6], 255) || v[7] != ":" || getnum(v[8], 65535)) return true;
    return false;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    for (int i = 1; i <= T; i++) {
        scanf("%s%s", op[i], ad);
        if (check()) sta[i] = 2;
        else if (op[i][0] == 'S') {
            if (mp[ad]) sta[i] = 1;
            else sta[i] = 0, mp[ad] = i;
        } else {
            if (mp[ad]) sta[i] = 0, id[i] = mp[ad];
            else sta[i] = 1;
        }
    }
    for (int i = 1; i <= T; i++) {
        if (op[i][0] == 'S') {
            printf("%s\n", out[sta[i]].c_str());
        } else {
            if (sta[i] == 0) printf("%d\n", id[i]);
            else printf("%s\n", out[sta[i]].c_str());
        }
    }
    return 0;
}
