#include<bits/stdc++.h>
#define RG register
#define I inline
#define R RG int
#define G c=getchar()
using namespace std;
typedef long long LL;
const int N=5009,YL=1e8;
char x[N],y[N];
int ff[N],gg[N],mff[N],mgg[N];
int main(){
    freopen(".in", "r", stdin);
    freopen(".ans", "w", stdout);
    scanf("%s%s",x+1,y+1);
    R n=strlen(x+1)-1,m=strlen(y+1)-1,i,j,*f=ff,*g=gg,*mf=mff,*mg=mgg;
    g[0]=1;for(j=0;j<=m;++j)f[j]=1;
    for(i=1;i<=n;++i,swap(f,g),swap(mf,mg)){//滚动数组
        memset(g +1,0,m<<2);//注意清空
        memset(mg+1,0,m<<2);
        for(j=1;j<=m;++j){//三方向转移
            if(x[i]==y[j])mg[j]=mf[j-1]+1,g[j]=f[j-1];
            if(mf[j]>mg[j])mg[j]=mf[j],g[j]=f[j];//覆盖
            else if(mf[j]==mg[j])(g[j]+=f[j])%=YL;//相加
            if(mg[j-1]>mg[j])mg[j]=mg[j-1],g[j]=g[j-1];
            else if(mg[j-1]==mg[j])(g[j]+=g[j-1])%=YL;
            if(mf[j-1]==mg[j])(g[j]+=YL-f[j-1])%=YL;//减掉重复的部分
            printf("%d ", g[j]);
        }
        puts("");
    }
    printf("%d\n%d\n",mf[m],f[m]);
    return 0;
}
