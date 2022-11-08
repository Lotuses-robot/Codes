#include <bits/stdc++.h>

#define int long long

int read() {
    int r = 0;
    char ch = getchar(), last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = getchar();
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar();
    if (last == '-') r = -r;
    return r;
}

#define mod 1000000007
int n,k,dp[510][510][6];
char s[510];

#define For(var, l, r) for (int var = l; var <= r; var++)

bool compare(int a,int b) {return (s[a]=='('||s[a]=='?')&&(s[b]==')'||s[b]=='?');}
signed main(){
    n=read(),k=read();
    scanf("%s",s+1);
    For(i,1,n) dp[i][i-1][0]=1;
    For(len,1,n){
        For(l,1,n-len+1){
            int r=l+len-1;
            if(len<=k) dp[l][r][0]=dp[l][r-1][0]&&(s[r]=='*'||s[r]=='?');
            if(len>=2){
                if(compare(l,r)) dp[l][r][1]=(dp[l+1][r-1][0]+dp[l+1][r-1][2]+dp[l+1][r-1][3]+dp[l+1][r-1][4])%mod;
                For(i,l,r-1){
                    dp[l][r][2]=(dp[l][r][2]+dp[l][i][3]*dp[i+1][r][0])%mod;
                    dp[l][r][3]=(dp[l][r][3]+(dp[l][i][2]+dp[l][i][3])*dp[i+1][r][1])%mod;
                    dp[l][r][4]=(dp[l][r][4]+(dp[l][i][4]+dp[l][i][5])*dp[i+1][r][1])%mod;
                    dp[l][r][5]=(dp[l][r][5]+dp[l][i][4]*dp[i+1][r][0])%mod;
                }
            }
            dp[l][r][5]=(dp[l][r][5]+dp[l][r][0])%mod;
            dp[l][r][3]=(dp[l][r][3]+dp[l][r][1])%mod;
        }
    }
    printf("%lld\n",dp[1][n][3]);
}
