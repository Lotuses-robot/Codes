// 1728D 
#include <cstdio>
#include <cstring>

char ch[20001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%s", ch);
        int l = 0, r = strlen(ch) - 1;
        while (l < r && ch[l] == ch[r]) l++, r--;
        while (l < r) {
            if (ch[l] == ch[l + 1]) {
                l += 2;
                continue;
            } else if (ch[r] == ch[r - 1]) {
                r -= 2;
                continue;
            } else {
                break;
            }
        }
        if (l < r) puts("Alice");
        else puts("Draw");
    }
    return 0;
}