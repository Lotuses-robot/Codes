#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 100000000
#define inf 0x3f3f3f3f
int dp[5010][5010];
int f[5010][5010];
char s1[5010],s2[5010];
int main()
{
    for(int cas=1;cas<=1;cas++)
    {
        scanf("%s%s",s1+1,s2+1);
        int lena=strlen(s1+1) - 1;
        int lenb=strlen(s2+1) - 1;
        // memset(dp,0,sizeof(dp));
        // memset(f,0,sizeof(f));
        for(int i=0;i<=lena;i++) f[i][0]=1;
        for(int i=0;i<=lenb;i++) f[0][i]=1;
        for(int i=1;i<=lena;i++)
        {
            for(int j=1;j<=lenb;j++)
            {
                if(s1[i]==s2[j])
                {
                    dp[i][j]=dp[i-1][j-1]+1;
                    f[i][j]=f[i-1][j-1];
                }
                else if(dp[i][j-1]>dp[i-1][j])
                {
                    dp[i][j]=dp[i][j-1];
                    f[i][j]=f[i][j-1];
                }
                else if(dp[i][j-1]<dp[i-1][j])
                {
                    dp[i][j]=dp[i-1][j];
                    f[i][j]=f[i-1][j];
                }
                else
                {
                    dp[i][j]=dp[i-1][j];
                    f[i][j]=(f[i-1][j]+f[i][j-1]-(dp[i][j]==dp[i-1][j-1]?f[i-1][j-1]:0)%mod+2*mod)%mod;
                }
            }
        }
        printf("%d\n%d\n",dp[lena][lenb],f[lena][lenb]);
    }
    return 0;
}