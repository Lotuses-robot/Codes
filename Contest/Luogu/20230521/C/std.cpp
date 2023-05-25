#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4000005;
int n,m,sum[N],tmp[N],cnt[N],lst[N];
ll ts,ans; char str[N];
inline void solve(){
    scanf("%d%s",&n,str+1);
    for(int i=1;i<=n;i++)
        sum[i+1]=sum[i]+(str[i]=='('?1:-1);
    // 为了方便，我在这里直接把 c[0] 放在前面，后面统计贡献就全部是 1 下标了
    ans=ts=0; n++;
    for(int i=1;i<=n;i++) tmp[i]=sum[i];
	for(int i=1;i<=n+n;i++) cnt[i]=0;
    for(int i=1;i<=n;i++) cnt[tmp[i]+n]++;
    for(int i=1,j=0;i<=n+n;i++)
		for(int t=1;t<=cnt[i];t++) ans+=1ll*j*(i-n)-ts,ts+=i-n,j++;
	// 求第一部分的贡献
	ans+=1ll*n*(n-1)/2;
	for(int i=0;i<=n+n;i++) lst[i]=n+1;
    for(int i=n;i;i--){
    	int r=lst[sum[i]+n-1]-1;
    	ans-=r-i;
    	lst[sum[i]+n]=i;
	}
	for(int i=0;i<=n+n;i++) lst[i]=0;
	for(int i=1;i<=n;i++){
		int l=lst[sum[i]+n-1]+1;
		ans-=i-l;
		lst[sum[i]+n]=i;
	}
    printf("%d\n", ans);
	// 求第二部分的贡献
	for(int i=1;i<=n+n;i++) cnt[i]=0;
	for(int i=1;i<=n;i++){
		cnt[sum[i]+n]++;
		if(i==n||sum[i]>sum[i+1]){
			ans+=1ll*cnt[sum[i]+n]*(cnt[sum[i]+n]-1)/2;
			cnt[sum[i]+n]=0;
		}
	}
	for(int i=1;i<=n+n;i++) if(cnt[i]) ans+=1ll*cnt[i]*(cnt[i]-1)/2; 
	// 第二部分在 c[l]=c[r] 时会算重 
    printf("%lld\n",ans);
}
int main(){
    freopen(".in", "r", stdin);
    int tc; scanf("%d",&tc);
    while(tc--) solve();
    return 0;
}