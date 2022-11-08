#include <bits/stdc++.h>
#define int unsigned __int128
using namespace std;

int kpow(int a, int b, int mod) {
    int ans = 1, base = a % mod;
    do
    {
        if (b & 1) ans *= base, ans %= mod;
        base *= base; base %= mod;
    } while (b >>= 1);
    return ans;
}

#define gc getchar()
#define isd(ch) (ch >= '0' && ch <= '9')
template <typename T>
void read(T &r) {
    r = 0; char ch = gc, last = 'z';
    while (!isd(ch)) last = ch, ch = gc;
    while (isd(ch)) r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    if (last == '-') r = -r;
}

#define pc(ch) putchar(ch)
signed _buf[500], _len;
template <typename T>
void write(T w)
{
    _len = 0;
    if (w < 0) w = -w, pc('-');
    do _buf[_len++] = w % 10; while (w /= 10);
    for (signed i = _len - 1; i >= 0; i--)
        pc(_buf[i] + '0');
}

signed main() {
    int n, k, p, ans1 = 0, ans2 = 1, f = 1;
    read(n), read(k), read(p);
    for (int i = 1; i <= min(n, p - 1); i++)
        f *= i, f %= p, ans1 += f, ans1 %= p;
    ans2 = kpow(ans1, k, p);
    write(ans2);
    pc('\n');
    return 0;
}