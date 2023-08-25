#include<bits/stdc++.h>
#define Max 11
#define int long long
#define dg(a) ((a)<'0'||(a)>'9')

using namespace std;

void read(int &r)
{
    r=0;char ch,f='t';ch=getchar();
    while(dg(ch)){f=ch;ch=getchar();}
    while(!dg(ch)){r=(r<<3)+(r<<1)+ch-'0';ch=getchar();}
    if(f=='-')r=-r;
}

void write(int x)
{
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);
    putchar(x%10+'0');
}

int n,re;
int bin[Max],ans=-1e9;
int line[Max];
map<int,int>mp[2];

void add(int x,int y)
{
    if(mp[re].find(x)==mp[re].end())mp[re][x]=y;
    else mp[re][x]=max(mp[re][x],y);
}

int cline(int q1,int q2)
{
    int num=0,sum=0;
    memset(line,0,sizeof(line));
    for(int i=0;i<n;i++)
    {
        int x=(q1>>(3*i))&7;
        if(!x)continue;
        if(!line[x])line[x]=++num;
        sum+=line[x]*bin[i];
    }
    if(num==1&&ans<q2)ans=q2;
    return sum;
}

bool check(int q1,int p2)
{
    int num=0;
    for(int i=0;i<n;i++)
    {
        if((q1>>(3*i)&7)==p2)num++;
    }
    return num>1;
}

int m[20];
void print(int x) {
    int cnt = 0;
    do {
        m[cnt++] = x % 8;
    } while (x >>= 3);
    for (int i = 0; i <= 6; i++) {
        if (i >= cnt) write(0);
        else write(m[i]);
    }
    putchar(' ');
}

signed main()
{
    freopen("data.in", "r", stdin);
    freopen("data.ans", "w", stdout);
    read(n);add(0,0);
    bin[0]=1;
    for(int i=1;i<=n;i++)bin[i]=(bin[i-1]<<3);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            re^=1;
            mp[re].clear();
            int x;read(x);
            for(auto &q:mp[re^1])
            {
                int q1=q.first;int q2=q.second;
                // print(q1);
                int p1=0,p2=(q1>>(3*(j-1)))&7;
                if(j!=1)p1=(q1>>(3*(j-2)))&7;
                if(!p1&&!p2)
                {
                    add(cline(q1,q2),q2);
                    add(cline((q1+7*bin[j-1]),q2+x),q2+x);
                }
                else if(p1&&!p2)
                {
                    add(cline(q1,q2),q2);
                    add(cline((q1+p1*bin[j-1]),q2+x),q2+x);
                }
                else if(!p1&&p2)
                {
                    if(check(q1,p2))add(cline(q1-p2*bin[j-1],q2),q2);
                    add(cline(q1,q2+x),q2+x);
                }
                else
                {
                    if(check(q1,p2))add(cline(q1-p2*bin[j-1],q2),q2);
                    if(p1!=p2)
                    {
                        for(int i=0;i<n;i++)
                        {
                            if((q1>>(3*i)&7)==p2)q1+=p1*bin[i]-p2*bin[i];
                        }
                    }
                    add(cline(q1,q2+x),q2+x);
                }
            }
        }
    }
    write(ans);
    return 0;
}