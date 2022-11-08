#include <cstdio>
#include <cstring>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        static char chr[9][9];
        static bool flg[9][9];
        memset(flg, 0, sizeof(flg));
        bool flag = 0;
        int x, y;
        for (int i = 1; i <= 8; i++) {
            scanf("%s", chr[i] + 1);
        }
        for (int i = 1; i <= 8; i++) {
            int j = 1;
            if (chr[i][j] == '#' && !flag) {
                for (int ii = i, jj = j; ii <= 8 && jj <= 8; ii++, jj++) {
                    flg[ii][jj] = true;
                }
                flag = true;
            } else if (chr[i][j] == '#') {
                for (int ii = i, jj = j; ii >= 1 && jj <= 8; ii--, jj++) {
                    if (flg[ii][jj]) {
                        x = ii, y = jj;
                    }
                }
            }
        }

        printf("%d %d\n", x, y);
    }
    return 0;
}