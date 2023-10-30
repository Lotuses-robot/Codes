#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
bool b[100005];
int p[100005], phi[100005], f[100005];
signed main() {
    memset(b, 1, sizeof(b));
    int n, tot = 0;
    scanf("%lld", &n);
    phi[1] = 1;
    b[0] = b[1] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (b[i]) {
            p[++tot] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= tot && i * p[j] <= n; j++) {
            b[i * p[j]] = 0;
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
            phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
        f[i] = f[i - 1] + phi[i] * 2;
    }
    printf("%lld\n", f[n]);
    return 0;
}