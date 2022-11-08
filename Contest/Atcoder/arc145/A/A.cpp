#include <cstdio>

int main() {
    int n;
    static char ch[214514];
    scanf("%d%s", &n, ch);
    bool flag = false;

    for (int i = 0; i < n / 2; i++) {
        if (ch[i] != ch[n - i - 1]) {
            if (ch[i] == 'B') {
                ch[i] = 'A';
                ch[i + 1] = 'B';
                if (n % 2 == 0 && n / 2 == i + 1) {
                    flag = true;
                    break;
                }
            } else {
                flag = true;
                break;
            }
        }
    }
    if (!flag) {
        puts("Yes");
    } else {
        puts("No");
    }
    return 0;
}