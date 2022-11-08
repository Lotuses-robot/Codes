#include<bits/stdc++.h>
#define isdi(a) ((a)>='0'&&(a)<='9')
#define gc getchar()
#define pc(a) putchar(a)
#define writeln(a) write(a,'\n')
#define writen(a) write(a,0)
#define int long long
//#define int __int128_t
#define ll long long
#define fio(a) freopen((string(a)+".in").c_str(),"r",stdin);freopen((string(a)+".out").c_str(),"w",stdout)
using namespace std;
#define MOD 1000000007
#define sz 5

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

main()
{
    int T;
    read(T);
    while(T--)
    {
        int n,a,d,tot=0;
        read(n),read(a),read(d);
        while(d>1)
        {
            if(d&1) break;
            tot++;
            d>>=1;
        }
        int ans=((1<<tot)-1)*(n-1);
        writeln(ans);
    }
    return 0;
}