#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
#define ll "lld"

typedef long long LL;

const int BASE = 10000000, MAXLEN = 10330;
char s[MAXLEN << 3];

struct BigInt {
    int len;
    LL bt[MAXLEN];

    void Zzero() {
        while (!bt[len] && len != 1)
            --len;
    }
    void Zbit() {
        LL x(0);
        for (int i = 1; i <= len; i++) {
            if (bt[i] < 0) {
                bt[i] += BASE;
                --bt[i + 1];
            }
            bt[i] += x;
            x = bt[i] / BASE;
            bt[i] %= BASE;
        }
        while (x)
            bt[++len] = x % BASE, x /= BASE;
    }
    BigInt(LL num) : len(1) {
        memset(bt, 0, sizeof bt);
        bt[1] = num;
        Zbit();
    }
    BigInt() : len(1) { memset(bt, 0, sizeof bt); }
    BigInt operator=(LL x) {
        len = 1;
        memset(bt, 0, sizeof bt);
        bt[1] = x;
        Zbit();
        return *this;
    }
    BigInt operator=(BigInt x) {
        len = x.len;
        memcpy(bt, x.bt, sizeof(bt));
        return *this;
    }
    void read() {
        scanf("%s", s);
        len = 0;
        char c[10];
        int tmp = strlen(s);
        for (; tmp >= 8; tmp -= 8) {
            strncpy(c, s + tmp - 8, 8);
            sscanf(c, "%" ll, &bt[++len]);
        }
        if (tmp) {
            memset(c, 0, sizeof c);
            strncpy(c, s, tmp);
            sscanf(c, "%" ll, &bt[++len]);
        }
        Zzero();
    }
    void write() {
        printf("%" ll, bt[len]);
        for (int i = len - 1; i; i--)
            printf("%08" ll, bt[i]);
        printf("\n");
    }
    BigInt add(LL x) {
        bt[1] += x;
        Zbit();
        return *this;
    }                                    // this += x
    BigInt div(LL x) {
        for (int i = len; i; i--) {
            bt[i - 1] += (bt[i] % x) * BASE;
            bt[i] /= x;
        }
        Zzero();
        return *this;
    }
    BigInt mul(LL x) {
        for (int i = 1; i <= len; i++)
            bt[i] *= x;
        Zbit();
        return *this;
    }
    LL _mod(LL x) {
        LL tmp = 0;
        for (int i = len; i; i--)
            tmp = (tmp * BASE + bt[i]) % x;
        return tmp;
    }
    BigInt _mul(LL x) {
        BigInt ans(*this);
        return ans.mul(x);
    }
    BigInt _add(LL x) {
        BigInt ans(*this);
        return ans.add(x);
    }
    BigInt _div(LL x) {
        BigInt ans(*this);
        return ans.div(x);
    }
    bool operator<(const BigInt &lhs) const {
        if (len != lhs.len)
            return len < lhs.len;
        for (int i = len; i; i--)
            if (bt[i] != lhs.bt[i])
                return bt[i] < lhs.bt[i];
        return false;
    }
    bool operator==(const BigInt &lhs) const {
        return (!(*this < lhs)) && (!(lhs < *this));
    }
    bool operator>(const BigInt &lhs) const { return lhs < *this; }
    bool operator<=(const BigInt &lhs) const { return !(*this > lhs); }

    BigInt operator*(const BigInt &b) const {
        BigInt ans(0ll);
        ans.len = len + b.len - 1;
        for (int i = 1; i <= len; i++)
            for (int j = 1; j <= b.len; j++) {
                ans.bt[i + j - 1] += bt[i] * b.bt[j];
                ans.bt[i + j] += ans.bt[i + j - 1] / BASE;
                ans.bt[i + j - 1] %= BASE;
            }
        if (ans.bt[ans.len + 1])
            ++ans.len;
        return ans;
    }
    BigInt operator-(const BigInt &b) const {
        BigInt ans(*this);
        ans.len = len;
        for (int i = 1; i <= b.len; i++)
            ans.bt[i] = bt[i] - b.bt[i];
        ans.Zbit();
        ans.Zzero();
        return ans;
    }
    BigInt operator+(const BigInt &b) const {
        BigInt ans(0ll);
        ans.len = max(len, b.len);
        for (int i = 1; i <= ans.len; i++)
            ans.bt[i] = bt[i] + b.bt[i];
        ans.Zbit();
        return ans;
    }
    BigInt operator/(const BigInt &b) const {
        for (BigInt l(0ll), r = *this;;) {
            if (r <= l._add(1ll))
                return r * b <= *this ? r : l;
            BigInt mid = (l + r).div(2ll);
            mid * b <= (*this) ? l = mid : r = mid;
        }
    }
    BigInt operator%(const BigInt &b) const { return (*this) - ((*this) / b) * (b); }
};

BigInt gcd(BigInt a, BigInt b) {
    BigInt r;
    BigInt zero(0);
    while (b > zero) {
        if (a < b) std::swap(a, b);
        r = a - b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    BigInt a, b;
    a.read();
    b.read();
    gcd(a, b).write();
}