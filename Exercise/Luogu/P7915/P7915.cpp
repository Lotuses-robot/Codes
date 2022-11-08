#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

int a[1014514];
int n;

// false -> L      true -> R
bool ans[1014514];
bool ansre[1014514];

// type is false -> from the left
bool calc(bool type) {
    int ll = 0, rr = n - 1, fstch, step = 0;
    if (!type) { // -> left
        fstch = a[0];
        ll = 1;
        ans[step] = false;
        ansre[step] = false;
    } else {
        fstch = a[n - 1];
        rr = n - 2;
        ans[step] = true;
        ansre[step] = false;
    }

    int mid;
    for (int i = ll; i <= rr; i++) {
        if (a[i] == fstch) {
            mid = i;
            break;
        }
    }

    int lr = mid - 1, rl = mid + 1;

    while (ll <= lr || rl <= rr) {
        step++;
        if (ll <= lr && rl <= rr) {
            if (a[ll] == a[lr] && ll != lr) {
                ll++; lr--;
                ans[step] = false;
                ansre[step] = false;
            } else if (a[ll] == a[rl]) {
                ll++; rl++;
                ans[step] = false;
                ansre[step] = true;
            } else if (a[rr] == a[lr]) {
                rr--; lr--;
                ans[step] = true;
                ansre[step] = false;
            } else if (a[rr] == a[rl] && rr != rl) {
                rr--; rl++;
                ans[step] = true;
                ansre[step] = true;
            } else {
                return false;
            }
        } else if (ll <= lr) {
            if (a[ll] == a[lr]) {
                ll++; lr--;
                ans[step] = false;
                ansre[step] = false;
            } else {
                return false;
            }
        } else if (rl <= rr) {
            if (a[rl] == a[rr]) {
                rl++; rr--;
                ans[step] = true;
                ansre[step] = true;
            } else {
                return false;
            }
        }
    }
    return true;
}

void out() {
    for (int i = 0; i < n / 2; i++) {
        putchar(ans[i] ? 'R' : 'L');
    }
    for (int i = n / 2 - 1; i >= 0; i--) {
        putchar(ansre[i] ? 'R' : 'L');
    }
    puts("");
}

int main() {
    freopen("data/P7915_1.in", "r", stdin);
    freopen("P7915.out", "w", stdout);

    int T;
    read(T);

    while (T--) {
        read(n); n *= 2;
        for (int i = 0; i < n; i++) read(a[i]);

        // if (T == 2) {
        //     puts("fk5");
        // }

        if (calc(false)) {
            out();
        } else if (calc(true)) {
            out();
        } else {
            puts("-1");
        }
    }

    return 0;
}
