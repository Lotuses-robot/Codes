#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

#define min(intA, intB) ((intA) < (intB) ? (intA) : (intB))

int main() {
    freopen("P4170.in", "r", stdin);
    freopen("P4170.out", "w", stdout);

    std::string str;
    static int f[51][51];
    int n;

    memset(f, 63, sizeof(f));

    std::cin >> str;
    n = str.length();

    for (int i = 0; i < 50; i++) {
        f[i][i]=1;
    }

    for (int len = 1; len < n; len++) {
        for (int i = 0; i < n - len; i++) {
            int j = i + len;

            // a substring with same char
            bool flag = true;
            for (int q = i + 1; q <= j; q++) {
                if (str[q] != str[q-1]) {
                    flag = false;
                }
            }
            if (flag) {
                f[i][j] = 1;
                continue;
            }

            // meet in middle
            f[i][j] = 998244353;
            int k1 = i,k2 = j,ch1 = str[k1],ch2 = str[k2];
            
            while (str[k1] == str[k1 + 1]) k1++;
            k1++;

            while (str[k2] == str[k2 - 1]) k2--;
            k2--;

            f[i][j] = min(f[k1][j], f[i][k2]) + 1;

            // same char
            if (ch1 == ch2) {
                f[i][j] = min(f[i][j],min(f[k1][k2] + 1, min(f[k1 - 1][k2], f[k1][k2 + 1])));
            }

            // normal split string
            for (int k = i; k < j; k++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
            }
        }
    }

    printf("%d\n", f[0][n-1]);
    return 0;
}