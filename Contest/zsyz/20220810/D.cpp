#include <cstdio>
#include <vector>

using std::pair;
#define ll long long
#define maxn 400005
#define pi pair<ll, ll>
pi listA[114510];         // orignal ans str
pi listB[114540];         // in ch's location
char ch[maxn];
int n, c, q;

char find(ll cur) {
    for (int j = 0; j <= c; j++) {
            if (listA[j].first <= cur && cur <= listA[j].second) {
            ll nxt = cur - listA[j].first;
            ll loc = listB[j].first + nxt;
            // printf("%c\n", ch[loc]);
            if (loc > n) {
                return find(loc);
            } else {
                return ch[loc];
            }
        }
    }
    return EOF;
}

int main() {
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    scanf("%d%d%d", &n, &c, &q);
    scanf("%s", ch + 1);
    listA[0].first = 1, listA[0].second = n;
    listB[0].first = 1, listB[0].second = n;
    for (int i = 1; i <= c; i++) {
        ll l, r;
        scanf("%lld%lld", &l, &r);
        listA[i].first = listA[i - 1].second + 1;
        listA[i].second = listA[i].first + r - l;
        listB[i].first = l;
        listB[i].second = r;
    }
    for (int i = 0; i < q; i++) {
        ll k;
        scanf("%lld", &k);
        printf("%c\n", find(k));
    }
    return 0;
}