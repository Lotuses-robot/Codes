#include <cstdio>
#include <cstring>
#include <vector>
#define abs(a) ((a) > 0 ? (a) : -(a))

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

char ch[214514];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%s", ch);
        int n = strlen(ch);
        int s1 = 0, s2 = 0;
        for (int i = 0; i < n; i++) {
            if (ch[i] == '(') s1++;
            if (ch[i] == ')') s1--;
            if (ch[i] == '?') s2++;
            if (s1 + s2 == 1) {
                s1 = 1;
                s2 = 0;
            }
        }
        if (abs(s2) == s1) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
}
