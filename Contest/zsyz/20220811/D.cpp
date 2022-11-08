#include <cstdio>
#include <cstring>

#define max(a, b) ((a) > (b) ? (a) : (b))

int a[5145];
int t[5145];
int f[5145];
int n;

void init() {
    memset(t, 0, sizeof(t));
}

void initf() {
    init(); int mx = -114514;
    for (int i = 0; i < n; i++) {
        ++t[a[i]];
        mx = max(mx, t[a[i]]);
        
        if (i % 2 && mx <= (i + 1) / 2) {
            f[i + 1] = 1;
        } else {
            f[i + 1] = 0;
        }
    }
    f[0] = 1;
}

void maintain() {
    int mx;
    for (int i = 1; i <= n; i++) {
        init();
        mx = -114514;
        if ((a[i] == a[i - 1] || i == n) && f[i - 1]) {
            f[i] = max(f[i], f[i - 1] + 1);
        }
        for (int j = i - 1; j >= 0; j--) {
            ++t[a[j]];
            mx = max(mx, t[a[j]]);
            if ((i - j) % 2 == 0 && mx <= (i - j) / 2 && (i == n || a[j - 1] == a[i]) && f[j - 1] > 0) {
                f[i] = max(f[i], f[j - 1] + 1);
            }
        }
    }
}

int main() {
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    memset(f, 0, sizeof(f));
    initf();
    maintain();

    printf("%d\n", f[n] - 1);
    return 0;
}