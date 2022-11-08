#include "testlib.h"
#include <deque>
#include <string>

using namespace std; 

typedef long long ll;
typedef long double dbl;

const int BASE = (int) (1e9);

struct bigInt {
    int neg;
    deque<int> a;

    bigInt(ll x = 0) {
        neg = 0;
        if (x < 0) {
            neg = 1;
            x = -x;
        }
        do {
            a.push_back(x % BASE);
            x /= BASE;
        } while (x > 0);
    }

    bigInt(string s) {
        neg = 0;
        if (s[0] == '-') {
            neg = 1;
            s.erase(s.begin());
        }
        for (int i = (int) s.length(); i > 0; i -= 9) {
            if (i < 9) {
                a.push_back(atoi(s.substr(0, i).c_str()));
            } else {
                a.push_back(atoi(s.substr(i - 9, 9).c_str()));
            }
        }
    }

    bigInt operator + (const bigInt &t) const {
        if (t.neg) {
            return *this - t.negative();
        }
        if (neg) {
            return t - (*this).negative();
        }

        bigInt res;
        res.a.assign(max(a.size(), t.a.size()) + 1, 0);

        for (int i = 0, carry = 0; i < (int) max(a.size(), t.a.size()) || carry; i++) {
            int x = i < (int) a.size() ? a[i] : 0;
            int y = i < (int) t.a.size() ? t.a[i] : 0;
            res.a[i] = carry + x + y;
            carry = res.a[i] >= BASE;
            if (carry) {
                res.a[i] -= BASE;
            }
        }

        res.norm();
        return res;
    }

    bigInt operator - (const bigInt &t) const {
        if (t.neg) {
            return *this + t.negative();
        }
        if (neg) {
            auto res = (*this).negative() + t;
            res.neg = 1;
            return res;
        }

        if (*this < t) {
            auto res = t - *this;
            res.neg = 1;
            return res;
        }

        bigInt res;
        res.a.assign(a.size(), 0);

        for (int i = 0, carry = 0; i < (int) a.size(); i++) {
            res.a[i] = a[i] - carry - (i < (int) t.a.size() ? t.a[i] : 0);
            carry = res.a[i] < 0;
            if (carry)  {
                res.a[i] += BASE;
            }
        }

        res.norm();
        return res;
    }

    void operator *= (int val) {
        if (val < 0) {
            neg ^= 1;
            val = -val;
        }
        for (int i = 0, carry = 0; i < (int) a.size() || carry; i++) {
            if (i == a.size()) {
                a.push_back(0);
            }
            ll cur = carry + a[i] * 1ll * val;
            a[i] = cur % BASE;
            carry = cur / BASE;
        }
        norm();
    }

    void norm() {
        while (a.size() > 1u && a.back() == 0) {
            a.pop_back();
        }
    }

    bigInt negative() const {
        auto res = *this;
        res.neg ^= 1;
        return res;
    }

    bool operator == (const bigInt &t) const {
        return neg == t.neg && a == t.a;
    }

    bool operator < (const bigInt &t) const {
        if (neg != t.neg) {
            return neg;
        }
        if (a.size () != t.a.size ()) {
            if (a.size () < t.a.size()) {
                return neg ^ 1;
            }
            else {
                return neg;
            }
        }
        for (int i = (int) a.size () - 1; i >= 0; i--) {
            if (a[i] != t.a[i]) {
                if (a[i] < t.a[i]) {
                    return neg ^ 1;
                }
                else {
                    return neg;
                }
            }
        }
        return false;
    }

    bool operator <= (const bigInt &t) const {
        return *this < t || *this == t;
    }

    void out() const {
        if (neg) {
            fprintf(stderr, "-");
        }
        fprintf(stderr, "%d", a.back());
        for (int i = (int) a.size() - 2; i >= 0; i--) {
            fprintf(stderr, "%09d", a[i]);
        }
        fprintf(stderr, "\n");
    }
};

const int N = 3000;

int n;
ll x[N], y[N];
bool used[N];

inline bigInt readValue(InStream& stream) {
    if (stream.seekEof()) {
        stream.quitf(_wa, "Unexpected EOF");
    }
    string t = stream.readToken();
    string first, second;
    bool sw = false;
    for (char c: t) {
        if (c == '.') {
            if (sw) {
                stream.quitf(_wa, "Expected double but found NAN.");
            }
            sw = true;
            first.swap(second);
            continue;
        }
        if (!isdigit(c)) {
            if (c != '-' || !first.empty()) {
                stream.quitf(_wa, "Expected double but found NAN.");
            }
        }
        first += c;
    }
    if (sw) {
        first.swap(second);
    }
    if (second.size() > 4u) {
        stream.quitf(_wa, "More than 4 digits after decimal point!");
    }
    second.resize(4, '0');
    return bigInt(first + second);
}

inline bool inSegment(bigInt l, bigInt r, ll v) {
    bigInt val(v);
    val *= 10000;
    return l <= val && val <= r;
}

inline void check(const bigInt &x1, const bigInt &y1, const bigInt &x2, const bigInt &y2, int id) {
    bigInt len1 = x2 - x1;
    bigInt len2 = y2 - y1;
    if (!(len1 == len2)) {
        quitf(_wa, "Not a square in query %d", id + 1);
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i] && inSegment(x1, x2, x[i]) && inSegment(y1, y2, y[i])) {
            used[i] = true;
            cnt++;
        }
    }
    if (cnt != 2) {
        quitf(_wa, "We have %d point(s) in query %d", cnt, id);
    }
}

void doTestCase() {
	n = inf.readInt();

    for (int i = 0; i < n; i++) {
        x[i] = inf.readLong();
        y[i] = inf.readLong();
        used[i] = 0;
    }

    string can = ouf.readToken();
    if (lowerCase(can) != "yes") {
        quitf(_wa, "The participant does not have a solution");
    }

    for (int i = 0; i < n; i += 2) {
        bigInt x1 = readValue(ouf);
        bigInt y1 = readValue(ouf);
        bigInt x2 = readValue(ouf);
        bigInt y2 = readValue(ouf);
        check(min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2), i >> 1);
    }
}

int main(int argc, char * argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt(); 
    
    while (t--) {
    	doTestCase();
	}
    
    if (!ouf.seekEof()) {
        quitf(_wa, "Extra data in output!");
    }

    quitf(_ok, "OK");
}
