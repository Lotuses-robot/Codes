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

int n;
int save[200005];

int query(int id) {
    if (id > n) {
        return -1;
    }
    if (save[id] != -1) {
        return save[id];
    }
    printf("? %d\n", id);
    fflush(stdout);
    int q;
    scanf("%d", &q);
    return save[id] = q;
}

void answer(int q) {
    printf("! %d\n", q);
    fflush(stdout);
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    memset(save, -1, sizeof(save));

    read(n);
    int l = 1, r = n;
    while (r - l >= 2) {
        int mid = (l + r) >> 1;
        int q1 = query(mid);
        if (q1 == 1) {
            r = mid;
        } else {
            l = mid;
        }
    }
    for (int i = l; i <= r; i++) {
        int ans1 = query(i), ans2 = query(i + 1);
        if (ans1 == -1 || ans2 == -1) {
            answer(n);
            break;
        } else {
            if (ans1 != ans2) {
                answer(i);
                break;
            }
        }
    }
    return 0;
}
