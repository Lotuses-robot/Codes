//f[i][j]=max(f[i-1][j],f[i-1][j-at[i]]+av[i])
#include<iostream>
#include<cstring>
using namespace std;
int f[1001][1001];
int at[1001];
int av[1001];

#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int t,m;
        cin>>m>>t;
        for(int i=1;i<=m;i++) cin>>av[i];
        for(int i=1;i<=m;i++) cin>>at[i];
        memset(f,0,sizeof(f));
        f[0][t]=0;
        for(int i=1;i<=m;i++)
        {
            for(int j=t;j>=at[i];j--)
                f[i][j]=max(f[i-1][j],f[i-1][j-at[i]]+av[i]);
            for(int j=at[i]-1;j>=0;j--)
                f[i][j]=f[i-1][j]; 
        }
        cout<<f[m][t]<<endl;
    }
	return 0;
}