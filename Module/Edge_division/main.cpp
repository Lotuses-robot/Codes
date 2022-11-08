// change n-tree to 2-tree
#include <cstdio>
#include <vector>
#include <queue>

using std::vector;
using std::pair;
using std::make_pair;
using std::priority_queue;

#define pi pair<int, int>

struct Heap {
    priority_queue<pi > q, era; // dis, id
    void push(pi x) { q.push(x); }
    void erase(pi x) { era.push(x); }
    pi top(pi x) {
        while (era.top() == q.top()) { q.pop(); era.pop(); } 
        return q.top();
    }
    void pop() {
        while (era.top() == q.top()) { q.pop(); era.pop(); } 
        q.pop();
    }
};

#define maxn 2000006

int n;
struct Node {
    int fa;
    vector<pair<int, int> > sons;
    Heap hp;
};
Node tree[maxn];
void init() {
    tree[0].fa = -1;
}
void insert(int cur, int son, int w) {
    tree[cur].sons.push_back(make_pair(son, w));
    tree[son].fa = cur;
}
bool vis[maxn];
void change(int cur) {
    if (tree[cur].sons.empty()) return;

    vector<pair<int, int> > v;
    v = tree[cur].sons;

    tree[cur].sons.clear();
    for (int i = 0; i < v.size() - 2; i++) {
        tree[cur].sons.push_back(v[i]);
        change(v[i].first);
        insert(cur, n, 0);
        cur = n++;
    }
    tree[cur].sons.push_back(v[v.size() - 2]);
    change(v[v.size() - 2].first);
    tree[cur].sons.push_back(v[v.size() - 1]);
    change(v[v.size() - 1].first);
}
int ansCur, ansId;
#define abs(x) ((x) < 0 ? -(x) : (x))
int find(int cur) {
    int total = 0;
    for (int i = 0; i < tree[cur].sons.size(); i++) {
        auto e = tree[cur].sons[i];
        int res = find(e.first);
        if (abs(((n - 1) - res) - res) - 1 <= 1) {
            ansCur = cur, ansId = i;
        }
        total += res + 1;
    }
    return total;
}

std::queue<int> q;
void bfs() {
    q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto e : tree[u].sons) {
            printf("%d %d %d\n", u, e.first, e.second);
            q.push(e.first);
        }
    }
}

int Dis[maxn];
void getDis(int cur, int val) {
    Dis[cur] = val;
    for (auto e : tree[cur].sons) {
        getDis(e.first, val + e.second);
    }
}

void dfs(int rt) {
    vis[rt] = true;
    find(rt);
    int fa = ansCur, son = tree[ansCur].sons[ansId].first;
    // left

}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        insert(x, y, w);
    }
    change(0);
    bfs();
    find(0);
}