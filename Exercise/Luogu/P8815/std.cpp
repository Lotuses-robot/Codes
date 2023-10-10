#include<bits/stdc++.h>
using namespace std;

bool st;
string str;
bool val;// 表达式的值 
int ans1,ans2,off; //off 判断是否要跳掉，1 为 0&，2 为 1|，0 不用跳 
bool ed;

int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
//	freopen("expr.in","r",stdin);
//	freopen("expr.out","w",stdout);
//	cerr<<(&st-&ed)/1024.0/1024.0;
	cin>>str;
	for(int i=0;i<str.size();i++){
		if(off){
			if(str[i]=='('){// 跳括号 
				int x=1;
				while(x){
					i++;
					if(str[i]=='(') x++;
					if(str[i]==')') x--;
				}
			}else if(off==1&&str[i]=='|'){
				off=0;
			}else if(str[i]==')'){
				off=0;
			}else if(off==1&&str[i]=='&'){
				ans1++;
			}else if(off==2&&str[i]=='|'){
				ans2++;
			}
		}else{
			if(str[i]=='1') val=1;
			if(str[i]=='0') val=0;
			if(str[i]=='&'&&val==0){
				off=1;
				ans1++;
			}
			if(str[i]=='|'&&val==1){
				off=2;
				ans2++;
			} 
		}
	}
	cout<<val<<endl<<ans1<<' '<<ans2<<endl;

	return 0;
}
