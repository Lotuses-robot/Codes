#include<cstdio>
#include<iostream> 
const int m=20;
int n;
int f[200005]; 
struct node{int kid[2],num;}trie[2000005];
int tot=1;
void insert(int k){//插入函数
     int t=1,i;
     for(i=m;i>=0;i--){//从最高位开始讨论存储
         int now=(f[k]>>i)&1;//取出高位
         if(trie[t].kid[now]==0)
             trie[t].kid[now]=++tot;
         t=trie[t].kid[now];
     }
     trie[t].num=k;
}
int find(int k){//查询函数(查找与当前数异或值最大的数)
    int t=1,i;
    for(i=m;i>=0;i--){
        int now=1-(f[k]>>i)&1;//尽量找与当前数相反的数使异或值最大
        if(trie[t].kid[now]!=0)t=trie[t].kid[now];
        else t=trie[t].kid[1-now];
    }
    return trie[t].num;
} 
int main(){
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
     scanf("%d",&n);
     int i,x;
     int s=1,t=1;
     for(i=1;i<=n;i++){
     	scanf("%d",&x);
     	f[i]=f[i-1]^x;
     }
     int ans=f[1];
     insert(1);
     for(i=2;i<=n;i++){
         int p=find(i);
         if((f[i]^f[p])>ans){
            ans=f[i]^f[p];
            s=p+1;
            t=i;
         }
         insert(i);
     }
     printf("%d %d %d",ans,s,t);
}