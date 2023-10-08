#include <bits/stdc++.h>
#define y1 y114114
#define int long long

using namespace std;
const int N = 2e5 + 10;

struct node
{
	int c, u;
} a[N];

struct edge
{
	int now, val;
};

int n, p;
int vis[N], in[N], out[N];
queue<int> q;
vector<edge> e[N];

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);

	cin >> n >> p;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i].c >> a[i].u;
		if(!a[i].c) a[i].c = -1 * a[i].u;
	}
	for(int i = 1;i <= p;i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back(edge{v, w});
		out[u]++;
		in[v]++;
	}
	for(int i = 1;i <= n;i++)
		if(!in[i])
		{
			q.push(i);
			vis[i] = 1;
		}
	while(!q.empty())
	{
		int tot = q.front();
		q.pop();
		for(auto j : e[tot])
		{
			int v = j.now, w = j.val;
			if (a[tot].c > 0) a[v].c += a[tot].c * w;
			in[v]--;
			if(!in[v])
			{
				q.push(v);
			}
		}
	}
	int flag = 0;
	for(int i = 1;i <= n;i++)
		if(a[i].c > 0 && out[i] == 0)
		{
			cout << i << " " << a[i].c << '\n';
			flag = 1;
		}
	if(!flag) cout << "NULL";

	return 0;
}