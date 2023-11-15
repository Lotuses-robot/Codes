#include<bits/stdc++.h>
using namespace std;

const double dif=1e-7;
const int MAXN=13;

int n;
double coe[MAXN+5];

double check(double x)//不用秦九韶公式，普通计算……
{
	double temp=1.0,ans=0.0;
	for(int i=n;i>=0;i--,temp*=x) ans+=coe[i]*temp;
	return ans;
}

double Find(double L,double R)
{
	double Lmid,Rmid;
	while(L+dif<=R)
	{
		Lmid=L+(R-L)/3.0;
		Rmid=R-(R-L)/3.0;
		if(check(Lmid)>check(Rmid)) R=Rmid;
		else L=Lmid;
        printf("%.6lf %.6lf\n", L, R);
	}
	return (Lmid+Rmid)/2.0;
}

int main()
{
	double L,R;
	scanf("%d",&n),cin>>L>>R;
	for(int i=0;i<=n;i++) cin>>coe[i];
	printf("%.5lf\n",Find(L,R));
	//printf("%.5lf\n",check(-0.41421));
	return 0;
}