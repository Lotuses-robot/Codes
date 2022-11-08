#include <cstdio>
#include <cstring>

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        static char ch[114514];
        static bool vis[27];
        int len, tot = 0;;
        scanf("%d%s", &len, ch);
        memset(vis, 0, sizeof(vis));

        for (int i = 0; i < len; i++) {
            if (!vis[ch[i] - 'A']) {
                tot++;
                vis[ch[i] - 'A'] = true;
            }
            tot++;
        }
        printf("%d\n", tot);
    }
    return 0;
}