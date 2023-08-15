#include <iostream>

#include <vector>

#include <algorithm>

using namespace std;

const int mod =1000000000 + 7; int w0[100005];

int w1[100005]; int w2[100005];

int n, m, k, f[100005], d[100005], id[100005]; vector <int> e[100005];

void dfs(int u,int fa){ d[u] =d[fa]+1; f[u] =fa;

for(auto &v : e[u]) if(v != fa){ dfs(v,u);

} 
}
bool cmp(int a, int b){
return d[a] < d[b];
}
int main(){
cin >> n >> m >> k;
for(int i = 2;i <= n;i ++){
int u, v;
cin >> u >> v;
e[u].push_back(v);
e[v].push_back(u);
}
dfs(1, 0); // ①
for(int i = 1;i <= m;i ++){
int x, w;
cin >> x >> w;
w1[x] = (w1[x] + w) % mod;
w2[x] = (w2[x] + w) % mod;
}
for(int i = 1;i <= n;i ++)
id[i] = i;
sort(id + 1, id + 1 + n, cmp);
for(int i = 1;i <= k;i ++){
for(int j = n;j >= 1;j --){
int x = id[j];
for(auto &y : e[x]) if(y != f[x]){
w1[y] = (w1[y] + w1[x]) % mod;
}
w1[x] = 0;
}
for(int x = 1;x <= n;x ++)
w1[x] = (w1[x] - w0[x] + mod) % mod,
w0[x] = 0;
for(int j = 1;j <= n;j ++){ // ②
int x = id[j];
if(f[x]){
w1[f[x]] = (w1[f[x]] + w2[x]) % mod;
w2[f[x]] = (w2[f[x]] + w2[x]) % mod;
w0[x] = (w0[x] + w2[x]) % mod;
w2[x] = 0;}
}
}
for(int i = 1;i <= n;i ++)
cout << w1[i] << " ";
return 0;
}