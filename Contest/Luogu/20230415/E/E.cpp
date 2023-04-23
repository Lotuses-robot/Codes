#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
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

const int mod = 998244353;
#define int long long

struct Node {
    int x, y;
    bool operator < (Node b) const {
        if (x == b.x) return y < b.y;
        return x < b.x;
    }
};

std::map<int, std::vector<Node> > mp;

struct seg {
    int l, r, x;
};

std::vector<seg> nxt;
std::vector<seg> nxtt;

int qpow(int x, int y) {
    int base = x, ans = 1;
    do {
        if (y & 1) ans *= base, ans %= mod;
        base *= base; base %= mod;
    } while (y >>= 1);
    return ans;
}

signed main() {
    #ifdef LOCAL
        freopen("hack/hack3.in", "r", stdin);
        freopen("hack/hack3.out", "w", stdout);
    #endif
    
    int n, m, q;
    read(n, m, q);

    for (int i = 1; i <= q; i++) {
        int x, y;
        read(x, y);
        mp[x].push_back({x, y});
    }

    // calc
    int lasty = 1;
    // std::sort(mp[1].begin(), mp[1].end());
    for (Node c : mp[1]) {
        // writeln(c.x, c.y);
        if (lasty == c.y) { lasty = c.y + 1; continue; }
        nxt.push_back({lasty, c.y - 1, c.y - lasty});
        lasty = c.y + 1;
    }
    if (lasty <= m) {
        // puts("F?f");
        nxt.push_back({lasty, m, m - lasty + 1});
    }

    // for (auto p : nxt) {
    //     writeln(p.l, p.r, p.x);
    // }
    // puts("");
    
    int lastx = 1, cnt = 0;
    for (auto &p : mp) {
        if (p.second.empty() || p.first == 1) { cnt++; continue; }
        // std::sort(p.second.begin(), p.second.end());
        if (p.second[0].x - lastx != 1) {
            int ans = 0;
            for (auto pp : nxt) {
                ans += (pp.r - pp.l + 1) * pp.x % mod;
                ans %= mod;
                // if (p.second[0].x == 2144) {
                //     writeln(pp.l, pp.r, pp.x);
                // }
            }
            nxtt.push_back({1, m, ans * qpow(m, p.second[0].x - lastx - 2) % mod});
            nxt = nxtt;
            nxtt.clear();
        }
        if (nxt.size() == 0) break;
        lastx = p.second[0].x;
        int last = 1, j = 0, lastend = m + 1; // two pointer
        for (Node &c : p.second) {
            if (c.x == 2138 && c.y >= 1400) {
                // stop;
                // puts("fk");
            }
            // writeln(c.x, c.y);
            if (nxt[j].l > nxt[j].r) j++;
            if (c.y == last) { last = c.y + 1; nxt[j].l = std::max(nxt[j].l, c.y + 1); continue; }
            int ans = 0;
            while (j < nxt.size() && nxt[j].r <= c.y - 1) {
                ans += nxt[j].x * (nxt[j].r - std::max(nxt[j].l, last) + 1) % mod;
                ans %= mod;
                j++;
            }
            if (j == nxt.size()) {
                lastend = last;
                if (ans > 0) nxtt.push_back({last, std::max(nxt[j - 1].r, c.y - 1), ans});
                break;
            }
            if (j == 0 || nxt[j - 1].r != c.y - 1) {
                // writeln(c.y, nxt[j].l);
                ans += std::max(0ll, (c.y - nxt[j].l)) * nxt[j].x % mod;
                ans %= mod;
            }
            if (ans > 0) nxtt.push_back({last, c.y - 1, ans});
            nxt[j].l = std::max(c.y + 1, nxt[j].l);
            // nxt[j].l = c.y + 1;
            last = c.y + 1;
            // here insert the new vector
        }
        if (last != lastend) {
            int ans = 0;
            while (j < nxt.size()) {
                ans += nxt[j].x * (nxt[j].r - std::max(nxt[j].l, last) + 1) % mod;
                ans %= mod;
                j++;
            }
            if (ans > 0) nxtt.push_back({last, m, ans});
        }
        // here exchange the vector and clear
        // puts("FK");
        nxt = nxtt;
        nxtt.clear();

        // writeln(p.second[0].x);
        // if (p.second[0].x == 2138) {
        //     puts("fk");
        // }
        // for (auto p : nxt) {
        //     writeln(p.l,  p.r, p.x);
        // }
        // puts("");
    }

    // writeln(nxt[0].l, nxt[0].r, nxt[0].x);

    int ans = 0;
    for (auto p : nxt) {
        ans += (p.r - p.l + 1) * p.x % mod;
        ans %= mod;
    }
    // writeln(ans);
    ans *= qpow(m, n - lastx);
    ans %= mod;
    writeln(ans);
    return 0;
}
