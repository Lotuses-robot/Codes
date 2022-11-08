#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e8;

bool pri[maxn];
int cnt;

int main()
{
    for(int i = 2;;++i){
	if(!pri[i]){
	    if(++cnt == 1e6){
		cout<<i;
		return 0;
	    }
	    for(int j = i+i;j < maxn;j+=i)pri[j] = 1;
	}
    }
    return 0;
}