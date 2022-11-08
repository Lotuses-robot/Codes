#include<bits/stdc++.h>
#define isdi(a) ((a)>='0'&&(a)<='9')
#define gc getchar()
#define pc(a) putchar(a)
#define writeln(a) write(a,'\n')
#define writen(a) write(a,0)
#define int long long
//#define int __int128_t
#define ll long long
#define fio(a) freopen((string(a)+".in").c_str(),"r",stdin);freopen((string(a)+".out").c_str(),"w",stdout);
using namespace std;

template<typename T>
void read(T&r)
{
	r=0;char ch=gc,last='z';
	while(!isdi(ch)) last=ch,ch=gc;
	while(isdi(ch)) r=(r<<1)+(r<<3)+(ch^48),ch=gc;
	if(last=='-') r=-r;
}

template<typename... T>
void reads(T& ...rr)
{
	for(auto r:{&rr...})
	{
		(*r)=0;char ch=gc,last='z';
		while(!isdi(ch)) last=ch,ch=gc;
		while(isdi(ch)) (*r)=((*r)<<1)+((*r)<<3)+(ch^48),ch=gc;
		if(last=='-') (*r)=-(*r);
	}
}

int buf[100],len_;
template<typename T>
void write(T r,char endc=' ')
{
	if(r<0) pc('-'),r=-r;
	len_=0;
	do buf[len_++]=r%10; while(r/=10);
	for(int i=len_-1;i>=0;i--) pc(buf[i]+'0');
	if(endc!=0) pc(endc);
}

template<typename... T>
void writes(T ...ww)
{
	char endc=' ';
	for(auto w:{ww...})
	{
		if(w<0) pc('-'),w=-w;
		len_=0;
		do buf[len_++]=w%10; while(w/=10);
		for(int i=len_-1;i>=0;i--) pc(buf[i]+'0');
		pc(endc);
	}
	pc('\n');
}

template<typename T>
T gcd(T a,T b)
{
	while(b^=a^=b^=a%=b);
	return a;
}

#define bgcd(a,b) ((a)*(b)/gcd((a),(b)))
#define eps 1e-4

signed main()
{
    // freopen("math.in","r",stdin);
    // freopen("math.out","w",stdout);
    int t;
    read(t);
    while(t--)
    {
        ll x,z,cd,fm,fz;
        reads(x,z);
        cd=gcd(x*x,z);
		if(cd==0) {cout<<"-1"<<endl;continue;}
        fz=x*x/cd;fm=z/cd;

		if(x*fm*gcd(x,fm)==z) writeln(fm);
		else
		{
			if((x*fm*gcd(x,fm))==0) {cout<<"-1"<<endl;continue;}
			ll need=z/(x*fm*gcd(x,fm));
			// cout<<need<<endl;

			double turn=pow(sqrt(need),2);
			if(need-eps<=turn&&turn<=need+eps)
			{
				ll qneed=sqrt(need)+eps;
				if(qneed==0) {cout<<"-1"<<endl;continue;}
				if(x%qneed==0) writeln(fm*qneed);
				else writeln(-1);
			}
			else
			{
				sig:
				if(need==0) {cout<<"-1"<<endl;continue;}
				if(x%need==0) writeln(-1);
				else writeln(fm*need);
			}
		}

    }
    return 0;
}