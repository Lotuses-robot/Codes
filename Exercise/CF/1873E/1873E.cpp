#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define TP template<typename T>
#define TP_ template<typename T,typename ... T_>
TP void read(T &x)
{
	x=0;int f=1;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	x*=f;
}
TP_ void read(T &x,T_&...y){read(x);read(y...);}
TP void write(T x){if(x<0){putchar('-'),x=-x;}if(x>9)write(x/10);putchar(48+x%10);}
TP void writeln(T x){if(x<0){putchar('-'),x=-x;}if(x>9)write(x/10);putchar(48+x%10);puts("");}
TP_ void writeln(const T x,T_ ...y){write(x);putchar(' ');writeln(y...);}
typedef long long LL;
constexpr int N=2e5+5;
LL a[N],b[N],n,x;
bool check(LL mid)
{
	LL ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=max(0ll,mid-a[i]);
		if(ans>x)return false;
	}
	return true;
}
int main()
{
    freopen(".in", "r", stdin);
	int T;read(T);
	while(T--)
	{
		read(n,x);
		LL l=1,r=2e9;
		for(int i=1;i<=n;i++)
			read(a[i]);
		while(l<r)
		{
			LL mid=(l+r+1)>>1;
			if(check(mid))l=mid;
			else r=mid-1;
		}
		writeln(l);
	}
	return 0;
}
