#include <iostream>
#include <stack>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ctime>
#define int long long
using namespace std;
struct node {
    int len;
    __gnu_pbds::priority_queue<int, less<int>, __gnu_pbds::pairing_heap_tag> q;
    node(int x): len(1) {
        q.push(x);
    }
};
vector<node> s;
int a[1000005], b[1000005];
signed main() {
    int bg = clock();
    freopen("data1.in", "r", stdin);
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i % 10000 == 0) {
            int ed = clock();
            cout << 1.0 * (ed - bg) / CLOCKS_PER_SEC << endl;
            bg = ed;
        } 
        auto ret = node(a[i] - i);
        while (!s.empty() && s.back().q.top() > ret.q.top()) {
            ret.len += s.back().len;
            ret.q.join(s.back().q);
            while (ret.q.size() > ret.len / 2 + 1)
                ret.q.pop();
            s.pop_back();
        }
        s.push_back(ret);
    }
    int ans = 0;
    for (int i = n + 1; !s.empty(); i -= s.back().len, s.pop_back())
        for (int j = 1; j <= s.back().len; j++) {
            b[i - j] = s.back().q.top() + i - j;
            ans += abs(a[i - j] - b[i - j]);
        }
    cout << ans << endl;
    for (int i = 1; i <= n; i++)
        cout << b[i] << ' ';
    cout << endl;
    return 0;
}