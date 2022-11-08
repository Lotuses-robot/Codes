#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

#define int long long
#define min(a, b) ((a) < (b) ? (a) : (b))

signed main() {
    // freopen("mk.txt", "r", stdin);
    int T;
    scanf("%lld", &T);

    while (T--) {
        static int a[1000005], f[1000005], change[1000005], pre_or[1000005], minl[1000005], minlid[1000005];
        static std::set<int> v;
        v.clear();
        int n, m, ors = 0;
        scanf("%lld%lld", &n, &m);

        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            f[i] = 99824435399824435ll;
            change[i] = a[i];
            pre_or[i] = 0;
            minl[i] = 99824435399824435ll;
        }

        // if (T <= 10 && n <= 50000) {
        //     int tmp = 0;
        //     for (int i = 0; i < n; i++) tmp |= a[i];
        //     if (m == 0) {
        //         printf("%lld\n", tmp);
        //         continue;
        //     }
            
        //     for (int i = 0; i < n; i++) {
        //         int sum = 0;
        //         for (int j = i; j >= 0; j--) {
        //             sum |= a[j];
        //             f[i] = min(f[i], (j > 0 ? f[j - 1] : 0) + sum - m);
        //         }
        //     }
        //     printf("%lld\n", f[n - 1]);
        //     continue;
        // }

        v.insert(0);
        minl[0] = f[0] = a[0] - m; ors = a[0]; change[0] = a[0]; pre_or[0] = a[0];
        for (int i = 1; i < n; i++) {
            ors |= a[i];
            f[i] = min(f[i], ors - m);
            f[i] = min(f[i], f[i - 1] + a[i] - m);
            std::vector<int> ver; ver.clear();
            std::vector<int> minll; minll.clear();
            for (auto j : v) {
                pre_or[minlid[j] + 1] |= a[i];
                f[i] = min(f[i], minl[j] + pre_or[minlid[j] + 1] - m);

                if (((~a[i]) & change[j]) != change[j]) {
                    change[j] = (~a[i]) & change[j];
                    if (change[j] == 0) {
                        ver.push_back(j);
                    }
                }
            }
            v.insert(i);
            std::vector<int> need; need.clear();
            for (auto i = v.begin(); i != v.end(); ++i) {
                bool flag = false;
                for (auto j : ver) {
                    if (*i == j) {
                        need.push_back(j);
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    for (auto j : need) {
                        if (minl[*i] > minl[j]) {
                            minlid[*i] = j;
                        }
                        minl[*i] = min(minl[*i], minl[j]);
                    }
                    need.clear();
                }
            }
            for (auto j : ver) {
                v.erase(j);
            }
            // printf("debug %d\n", v.size());
            // for (auto j : v) {
            //     printf(" %d", j);
            // }
            // puts("\n");
            minl[i] = min(minl[i], f[i]);
            change[i] = a[i];
            pre_or[i] = a[i];
        }

        printf("%lld\n", f[n - 1]);
    }
    return 0;
}