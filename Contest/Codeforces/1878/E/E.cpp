// Copyright 2023 Lotuses
#include <cstdio>
#include <cmath>
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
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

template <typename T>
class SparseTable {
  using VT = std::vector<T>;
  using VVT = std::vector<VT>;

  VVT ST;

  static T op(const T &t1, const T &t2) { return t1 & t2; }

 public:
  void init(const std::vector<T> &v) {
    int len = v.size(), l1 = ceil(log2(len)) + 1;
    ST.assign(len, VT(l1, 0));
    for (int i = 0; i < len; ++i) {
      ST[i][0] = v[i];
    }
    for (int j = 1; j < l1; ++j) {
      int pj = (1 << (j - 1));
      for (int i = 0; i + pj < len; ++i) {
        ST[i][j] = op(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  T query(int l, int r) {
    if (l == r) return ST[l][0];
    int lt = r - l + 1;
    int q = ceil(log2(lt)) - 1;
    return op(ST[l][q], ST[r - (1 << q) + 1][q]);
  }
};

SparseTable<int> st;

std::vector<int> v;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, a;
        read(n);
        v.clear();
        for (int i = 1; i <= n; i++) {
            read(a);
            v.push_back(a);
        }
        st.init(v);
        // writeln(st.query(0, 2));
        int q;
        read(q);
        while (q--) {
            int ll, k;
            read(ll, k);
            ll--;
            int l = ll, r = n - 1;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                // writeln(ll, mid, st.query(ll, mid));
                if (st.query(ll, mid) >= k) {
                    l = mid;
                } else {
                    r = mid - 1;
                }
            }
            // writeln(ll, l);
            // writeln(st.query(0, 0));
            if (st.query(ll, l) < k) {
                write(-1);
            } else {
                if (l + 1 < n && st.query(ll, l + 1) >= k) write(l + 2);
                else write(l + 1);
            }
            putchar(' ');
        }
        puts("");
    }
    return 0;
}
