#include <bits/stdc++.h>
#define INF 200010
using namespace std;
int n;
set<int> s1, s2;
int main() {
    scanf("%d", &n);
    s1.clear();
    s2.clear();
    int q;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &q);
        if (q)
            s1.insert(i);
        else
            s2.insert(i);
    }
    s1.insert(INF);
    s2.insert(INF);
    int nw = 0;
    bool p = *s1.begin() < *s2.begin()
                             ? 0
                             : 1;
    while (!p && s1.size() > 1 || p && s2.size() > 1)
        if (!p) {
            nw = *s1.upper_bound(nw);
            if (nw == INF)
            {
                nw = 0;
                p = *s1.begin() < *s2.begin() ? 0 : 1;
                puts("");
                continue;
            }
            printf("%d ", nw);
            s1.erase(nw);
            p = !p;
        } else
        {
            nw = *s2.upper_bound(nw);
            if (nw == INF) {
                nw = 0;
                p = *s1.begin() < *s2.begin() ? 0 : 1;
                puts("");
                continue;
            }
            printf("%d ", nw);
            s2.erase(nw);
            p = !p;
        }
    puts("");
    while (s1.size() > 1)
        printf("%d\n", *s1.begin()), s1.erase(*s1.begin());
    while (s2.size() > 1)
        printf("%d\n", *s2.begin()), s2.erase(*s2.begin());
    return 0;
}
