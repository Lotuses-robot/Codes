#include<bits/stdc++.h>
using namespace std;
const int N=1e5*8+10;
int n,x,len,cnt[1<<8];
char s[N];
bool check(int x){
    memset(cnt,0,sizeof cnt);
    for(int i=0;i<len;i+=8)
        cnt[x^(s[i]-'0')<<7|x^(s[i+1]-'0')<<6|x^(s[i+2]-'0')<<5|x^(s[i+3]-'0')<<4|x^(s[i+4]-'0')<<3|x^(s[i+5]-'0')<<2|x^(s[i+6]-'0')<<1|x^(s[i+7]-'0')]++;
    for(int i='a';i<='z';i++)
        if(cnt[i]&&cnt[i]!=cnt[i-97])
            return 0;
    return 1;
}
int main(){
    scanf("%d%s",&n,s);
    len=n*8;
    for(int i=0;i<len;i++)
        s[i]-='0';
    for(int i=0;i<256;i++)
        if(check(i)){
            for(int j=0;j<len;j+=8){
                x=s[j]^i<<7|s[j+1]^i<<6|s[j+2]^i<<5|s[j+3]^i<<4|s[j+4]^i<<3|s[j+5]^i<<2|s[j+6]^i<<1|s[j+7]^i;
                if(x<97||x>122){
                    puts("NIE");
                    return 0;
                }
                cout<<(char)x;
            }
            return 0;
        }
    puts("NIE");
    return 0;
}
