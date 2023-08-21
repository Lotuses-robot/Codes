//Luogu P3959 宝藏 
//Sep,5th,2018
//状压DP+枚举子集小技巧
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long read()
{
    long long x=0,f=1; char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int N=12+2;
const int M=1<<N;
int n,m,dis[N][N],trans[M][M],POW[N];
long long f[N][M];
int main()
{
    freopen(".ans", "w", stdout);
    n=read(),m=read();
    memset(dis,0x3f,sizeof dis);
    for(int i=1;i<=m;i++)
    {
        int s=read(),t=read(),v=read();
        if(dis[s][t]>v)
            dis[s][t]=dis[t][s]=v;
    }
    
    m=(1<<n);
    POW[0]=1;
    for(int i=1;i<=n;i++)
        POW[i]=POW[i-1]*2;
    for(int i=0;i<m;i++)
        for(int j=i;j!=0;j=(j-1)&i)
        {
            bool OK=true;
            int temp=i^j;
            for(int k=n-1;k>=0;k--)
                if(temp>=POW[k])
                {
                    int tmin=0x3f3f3f3f;
                    for(int o=1;o<=n;o++)
                        if((POW[o-1]&j)==POW[o-1])
                            tmin=min(tmin,dis[o][k+1]);
                    if(tmin==0x3f3f3f3f)
                    {
                        OK=false;
                        break;
                    }
                    trans[j][i]+=tmin;
                    temp-=POW[k];
                }
            if(OK==false)
                trans[j][i]=0x3f3f3f3f;
        }
        
    cout<<endl<<endl;
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
            cout<<i<<" "<<j<<" "<<trans[j][i]<<endl;
    
    memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;i++)
        f[1][POW[i-1]]=0;
    for(int i=2;i<=n;i++)
        for(int j=0;j<m;j++)
            for(int k=j;k!=0;k=(k-1)&j)
                if(trans[k][j]!=0x3f3f3f3f)
                    f[i][j]=min(f[i][j],f[i-1][k]+(i-1)*trans[k][j]);
    
    long long ans=0x3f3f3f3f3f3f3f3fll;
    for(int i=1;i<=n;i++)
        ans=min(ans,f[i][m-1]);
    printf("%lld",ans);
    return 0;
}