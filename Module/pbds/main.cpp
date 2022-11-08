#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

struct Node {
    int id, val, tm;
    bool operator < (const Node b) const {
        if (val != b.val) return val < b.val;
        return tm < b.tm;
    }
};

__gnu_pbds::tree<Node, __gnu_pbds::null_type, std::less<Node>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> tr;

int main() {
    int opt, tm = 0;
    while (scanf("%d", &opt) != EOF && opt) {
        ++tm;
        if (opt == 1) {
            int x, y;
            scanf("%d%d", &x, &y);
            tr.insert({x, y, tm});
        } else if (opt == 2) {
            if (!tr.size()) {
                puts("0");
                continue;
            }
            auto p = tr.rbegin();
            printf("%d\n", p -> id);
            tr.erase(p);
        } else if (opt == 3) {
            if (!tr.size()) {
                puts("0");
                continue;
            }
            auto p = tr.begin();
            printf("%d\n", p -> id);
            tr.erase(p);
        }
    }
}