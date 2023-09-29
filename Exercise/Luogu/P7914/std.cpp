#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define For(i,j,k) for(register int i=j;i<=k;i++)
#define Rof(i,j,k) for(register int i=j;i>=k;i--)
#define ckmx(a,b) if(a<b){a=b;}
#define N 510
#define madd(a,b) a=(a+b%mod)%mod;
const ll mod=1000000007;
char s[N];
int n,k,R;
ll f[N][N],g[N][N],tmp,cur[N];
int id,nxt[N];
bool X[N][N];
signed main(){
    freopen(".in", "r", stdin);
    freopen(".ans", "w", stdout);
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	For(l,1,n) For(r,l,n) X[l][r]=0;
	For(l,1,n){
		if(s[l]!='?' && s[l]!='*') continue;
		X[l][l]=1;
		For(r,l+1,n){
			if(s[r]=='?' || s[r]=='*'){
				X[l][r]=1;
			}
			else break;
		}
	}
	For(len,2,n){
		int r;
		For(l,1,n-len+1){
			r=l+len-1;
			f[l][r]=g[l][r]=0;
			if((s[l]!='(' && s[l]!='?') || (s[r]!=')' && s[r]!='?'))
				continue;
			if(l+1==r){
				madd(f[l][r],1);
				continue;
			}
			//integral
			if(r-l-1<=k && X[l+1][r-1]){
				madd(f[l][r],1);
			}
			madd(f[l][r],f[l+1][r-1]+g[l+1][r-1]);
			For(l1,l+1,min(r-2,l+k))//记得取 min，我考试挂在这 
				if(X[l+1][l1])
					madd(f[l][r],f[l1+1][r-1]+g[l1+1][r-1]);
			Rof(r1,r-1,max(l+2,r-k))//记得取 max，我考试挂在这 
				if(X[r1][r-1])
					madd(f[l][r],f[l+1][r1-1]+g[l+1][r1-1]);
			//separated
			id=0;
			For(i,l+1,r-2){
				if(id<=i) id=i+1;
				while((s[id]=='*' || s[id]=='?') && id<r-1) id++;
				nxt[i]=min(i+k+1,id);
			}
			tmp=0;
			For(j,l+2,nxt[l+1]){
				madd(tmp,f[j][r]);
			}
			madd(g[l][r],(f[l][l+1]+g[l][l+1])%mod*tmp);
			For(i,l+2,r-2){
				madd(tmp,mod-f[i][r]);
				For(j,nxt[i-1]+1,nxt[i]) madd(tmp,f[j][r]);
				madd(g[l][r],(f[l][i]+g[l][i])%mod*tmp);
			}
		}
	}
	printf("%lld\n",(f[1][n]+g[1][n])%mod);
	return 0;
}