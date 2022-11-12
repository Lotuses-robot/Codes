#include<bits/stdc++.h>
#define IL inline
#define RI register int
#define mod 1000033
long long a,b,ans;

IL void read(long long &x){
	int f=1;x=0;char s=getchar();
	while(s>'9'||s<'0'){if(s=='-')f=-1;s=getchar();}
	while(s<='9'&&s>='0'){x=x*10%mod+(s-'0')%mod;s=getchar();}//改成了取模~~
    x=x%mod*f;
}

IL long long ksm(long long x,long long p)
{
	long long res=1;
	for(;p;p>>=1,x=x*x%mod)
		if(p&1)res=res*x%mod;
	return res;
}

int main()
{
	read(a);read(b);
	if(b==0){printf("Angry!");return 0;}
    //注意这里 特判！ 不要忘记 还有 不要忘记感叹号！！！
	ans=a*ksm(b,mod-2);
	printf("%lld",(ans%mod+mod)%mod);
}
