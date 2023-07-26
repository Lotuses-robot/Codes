#include<bits/stdc++.h>
using namespace std;

int n,m;
bool b[205][205],vis[205][205];
int f[205][205],ans;
int dx[5]{1,-1,0,0},dy[5]{0,0,-1,1};

int dfs(int x,int y,int j){
	if(x<=0||y<=0||x>n||y>m||vis[x][y]||b[x][y]==0)return 0;
	//cout<<x<<" "<<y<<'\n';
	vis[x][y]=1;int re=1;
	if(vis[x+dx[j]][y+dy[j]]==0&&b[x+dx[j]][y+dy[j]]){
		re=dfs(x+dx[j],y+dy[j],j)+1;
		vis[x][y]=0;
		return re;
	}
	for(int i(0);i<4;i++)
		re+=dfs(x+dx[i],y+dy[i],i);
	return re;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i(1);i<=n;i++)
		for(int j(1);j<=m;j++){
			char cc;scanf(" %c",&cc);
			if(cc=='.')b[i][j]=1;
		}
	cout<<dfs(2,2,4);
	return 0; 
}