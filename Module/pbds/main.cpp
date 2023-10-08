#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
tree<pair<int, int>, null_type, less<pair<int, int> >, rb_tree_tag, tree_order_statistics_node_update> T;
int main() {
    ios::sync_with_stdio(0);
    int n;
    scanf("%d", &n);
    int lastans = 0;
    for (int i = 1; i <= n; i++) {
        int oper, x;
        scanf("%d%d", &oper, &x);
        lastans = -1e9;
        if (oper == 1)
            T.insert(make_pair(x, i));
        if (oper == 2)
            T.erase(T.lower_bound(make_pair(x, 0)));
        if (oper == 3)
            lastans = T.order_of_key(make_pair(x, 0)) + 1;
        if (oper == 4)
            lastans = T.find_by_order(x - 1) -> first;
        if (oper == 5)
            lastans = T.find_by_order(T.order_of_key(make_pair(x, 0)) - 1) -> first;
        if (oper == 6)
            lastans = T.find_by_order(T.order_of_key(make_pair(x, 0x7fffffff))) -> first;
        if (lastans != -1e9) printf("%d\n", lastans);
    }
    return 0;
}