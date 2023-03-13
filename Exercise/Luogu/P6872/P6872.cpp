#include<bits/stdc++.h>
using namespace std;
int n;
string brk;
string s,t1,t2;
int main(){
	scanf("%d",&n);
	cin>>brk;int N=(int)brk.size();bool fl=0;
	for(int i=0;i<N;i++){
		if(brk[i]=='*'){fl=1;continue;}
		if(fl)t2+=brk[i];
		else t1+=brk[i];
	}
	int s1=(int)t1.size(),s2=(int)t2.size();
	for(int i=0;i<n;i++){
		cin>>s;
		int m=(int)s.size();
		if(m<s1||m<s2||s1+s2>m){
			printf("NE\n");
			goto Die;
		}
		for(int j=0;j<s1;j++)if(s[j]!=t1[j]){
			printf("NE\n");
			goto Die;
		}
		for(int j=0;j<s2;j++)if(s[m-s2+j]!=t2[j]){
			printf("NE\n");
			goto Die;
		}
		printf("DA\n");
		Die:;
	}
	return 0;
}