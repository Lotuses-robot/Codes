#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) {
	char ch = gc, last = 'z'; r = 0;
	while (ch < '0' || ch > '9') last = ch, ch = gc;
	while (ch >= '0' && ch <= '9') r = r * 10 + ch - '0', ch = gc;
	if (last == '-') r = -r;
}
#define int long long

const int maxn = 1e6 + 10;
std::vector<int> G1[maxn], G[maxn];
int n, m;
int fa[maxn], a[maxn], aq[maxn], in[maxn], cnt[maxn];
std::vector<int> leave;

int low[maxn], dfn[maxn], id[maxn], idx = 0;
bool ins[maxn], conn[maxn];
std::stack<int> st;
std::vector<std::vector<int> > sc;
void tarjan(int u) {
    dfn[u] = low[u] = ++idx; ins[u] = true; st.push(u);
    for (int v : G1[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        std::vector<int> subc;
        while (st.top() != u) {
            subc.push_back(st.top());
            ins[st.top()] = false;
            id[st.top()] = sc.size();
            st.pop();
        }
        subc.push_back(st.top());
        ins[st.top()] = false;
        id[st.top()] = sc.size();
        st.pop();
        sc.push_back(subc);
    }
}

int dfs(int u, int x) {
    // printf("%d %d\n", u, a[u]);
    int c = 0;
    for (int v : G[u]) {
        c += dfs(v, x);
    }
    c += x * cnt[u] - a[u];
    return std::max(0ll, c);
}

bool check(int x) {
    int sum = 0;
    for (int u : leave) {
        sum += dfs(u, x);
    }
    return sum <= m;
}

signed main() {
	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		read(fa[i]);
		if (fa[i] != -1) G1[fa[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		read(aq[i]);
        if (!dfn[i]) tarjan(i);
	}
    for (auto subc : sc) {
        int prid;
        for (int u : subc) {
            cnt[id[u]]++;
            prid = id[u];
            a[id[u]] += aq[u];
            for (int v : G1[u]) {
                if (!conn[id[v]] && id[v] != id[u]) {
                    G[id[u]].push_back(id[v]);
                    conn[id[v]] = true;
                }
            }
        }
        for (int v : G[prid]) {
            conn[v] = false;
            in[v]++;
            // printf("%d %d\n", prid, v);
        }
    }
    for (int i = 0; i < sc.size(); i++) {
        if (!in[i]) leave.push_back(i);
        // printf("in %d %d\n", i, in[i]);
    }   (n);
	int l = 0, r = 1e9;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}
	if (check(l + 1)) printf("%lld\n", l + 1);
	else printf("%lld\n", l);
	return 0;
}