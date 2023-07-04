#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define inf 2147483647
#define mp make_pair
#define pii pair<int,int>
#define pb push_back
#define r1 rt<<1
#define r2 rt<<1|1
#define ld long double
using namespace std;
 
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}
 
const int N=800000;
const int M=22;
int i,cnt,tree[N][2],a[M],num[N],sum[100005];
 
void insert(int k,int s){
	if(s==M){num[k]=i;return;}
	int x=a[s];
	if(tree[k][x]) insert(tree[k][x],s+1);
	else{
		tree[k][x]=++cnt;
		insert(cnt,s+1);
	}
}
 
int find(int k,int s){
	int x=a[s];
	if(tree[k][x^1]) return find(tree[k][x^1],s+1);
	if(tree[k][x]) return find(tree[k][x],s+1);
	return num[k];
}
 
int main()
{
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	int n=read(),ans=-1,ansl,ansr;cnt=0;
	for(i=1;i<=n;++i){
		int x=read(),p=0;
		sum[i]=sum[i-1]^x;
		x=sum[i];
		while(p<M-1) a[++p]=x&1,x>>=1;
		for(int j=1;j<=(p>>1);++j) swap(a[j],a[p+1-j]);
		int y=find(0,1);
		if((sum[i]^sum[y])>ans){
			ansl=y+1;
			ansr=i;
			ans=sum[i]^sum[y];
		}
		insert(0,1);
	}
	printf("%d\n",ans,ansl,ansr);
	return 0;
}