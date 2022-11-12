#include<bits/stdc++.h>
using namespace std;

vector<int> prefix(string s)
{
	int n=s.length();
	vector<int> pi(n);
	for(int i=1;i<n;i++)
	{
		int j=pi[i-1];
		while(j>0&&s[i]!=s[j]) j=pi[j-1];
		if(s[i]==s[j]) j++;
		pi[i]=j;
	}
	return pi;
}

int main()
{
    int tot=0;
	string s1,s2="chuanzhi";
	cin>>s1;
	string mk=s2+'#'+s1;
	vector<int> ans1,ans2;
	ans1=prefix(mk);
	for(int i=0;i<ans1.size();i++)
	{
		if(ans1[i]==s2.length()) tot++;
	}
	ans2=prefix(s2);
    cout<<tot<<endl;
	// for(int i=0;i<ans2.size();i++) cout<<ans2[i]<<" ";
	return 0;
}