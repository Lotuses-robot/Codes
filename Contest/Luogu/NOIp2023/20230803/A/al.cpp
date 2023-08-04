#include <iostream>
#include <cstring>

using namespace std;

const int N = 55, MOD = 1e9 + 7;

int n, K;
long long a[N];
int f[N][N][N * N];

int main() {
    cin >> n >> K;
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    memset(f, 0, sizeof f);
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= K; j++) {
            for (int k = 0; k <= sum; k++) {
                f[i][j][k] = f[i - 1][j][k];
                for (int x = 0; x <= a[i] / 2 && x <= k; x++) {
                    f[i][j][k] = (f[i][j][k] + f[i][j - 1][k - x]) % MOD;
                }
            }
        }
    }
    cout << f[n][K][sum] << endl;
    return 0;
}