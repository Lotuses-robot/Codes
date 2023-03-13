#include <bits/stdc++.h>
using namespace std;

struct node{
    double x,y;
};
struct Nxt{
    int x,y,z;
};
istream& operator >> (istream& CIN,node &x){CIN>>x.x>>x.y;return CIN;}
bool operator > (const node &x,const node &y){return x.y>y.y;}
double operator * (const node &x,const node &y){
    return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}

#define NUM 2000
node a[NUM];
double f[NUM][NUM][2];
Nxt nxt[NUM][NUM][2];
int n;
int nd(int x){
    x%=n;
    if(x==0)return n;
    else return x;
}

int main(){
    freopen("tree.in", "r", stdin);
    freopen("tree.ans", "w", stdout);
    cin>>n;
    for(int i=1; i<=n; i++)cin>>a[i];
    int id=0; a[0]=(node){-1000000000.00,-1000000000.00};
    for(int i=1; i<=n; i++)if(a[i]>a[id])id=i;
    for(int len=2; len<=n; len++){
        for(int i=1; i<=n; i++){
            if(a[i]*a[nd(i+1)]+f[nd(i+1)][len-1][0]<a[i]*a[nd(i+len-1)]+f[nd(i+1)][len-1][1]){
                f[i][len][0]=a[i]*a[nd(i+1)]+f[nd(i+1)][len-1][0];
                nxt[i][len][0]=(Nxt){nd(i+1),len-1,0};
            }
            else{
                f[i][len][0]=a[i]*a[nd(i+len-1)]+f[nd(i+1)][len-1][1];
                nxt[i][len][0]=(Nxt){nd(i+1),len-1,1};
            }
            if(a[i]*a[nd(i+len-1)]+f[i][len-1][0]<a[nd(i+len-2)]*a[nd(i+len-1)]+f[i][len-1][1]){
                f[i][len][1]=a[i]*a[nd(i+len-1)]+f[i][len-1][0];
                nxt[i][len][1]=(Nxt){i,len-1,0};
            }
            else{
                f[i][len][1]=a[nd(i+len-2)]*a[nd(i+len-1)]+f[i][len-1][1];
                nxt[i][len][1]=(Nxt){i,len-1,1};
            }
        }
    }
    cout<<id<<" ";
    Nxt now=nxt[id][n][0];
    for(int i=1; i<n; i++){
        if(now.z==0){
            cout<<now.x<<" ";
        }
        else{
            cout<<nd(now.x+now.y-1)<<" ";
        }
        now=nxt[now.x][now.y][now.z];
    }
    return 0;
}
