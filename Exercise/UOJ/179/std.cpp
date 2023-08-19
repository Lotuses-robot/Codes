#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
 
int n,m,t;
double a[30][25];
double eps=1e-5;
int id[45];
double ans[25];
 
void pivot(int x,int y){
	swap(id[n+x],id[y]);
	double temp=a[x][y];
	for(int i=0;i<=n;i++) a[x][i]/=temp;
	a[x][y]=1/temp;
	for(int i=0;i<=m;i++) if(x!=i){
		temp=a[i][y];a[i][y]=0;
		for(int j=0;j<=n;j++) a[i][j]-=temp*a[x][j];
	}
}
 
bool prepare(){
	int x,y;
	while(1){
		x=y=0;
		for(int i=1;i<=m;i++) if(a[i][0]<-eps) {x=i;if(rand()%3!=0) break;}
		if(!x) break;
		for(int i=1;i<=n;i++) if(a[x][i]<-eps) {y=i;if(rand()%3!=0)break;}
		if(!y){
			printf("Infeasible");
			return false;
		}
		pivot(x,y);
	}
	return true;
}
 
bool simplex(){
	int x,y;
	double mmin;
	while(1){
		x=y=0;
		for(int i=1;i<=n;i++) if(a[0][i]>eps) {y=i;break;}
		if(!y) break;
		mmin=(double)1e18;
		for(int i=1;i<=m;i++) if(a[i][y]>eps && a[i][0]/a[i][y]<mmin) {x=i;mmin=a[i][0]/a[i][y];}
		if(!x) {
			printf("Unbounded");
			return false;
		}
		pivot(x,y);
	}
	return true;
}
 
int main(){
    freopen("data.in", "r", stdin);
    freopen("data.ans", "w", stdout);
	srand(23333);
	scanf("%d %d %d",&n,&m,&t);
	for(int i=1;i<=n;i++) scanf("%lf",&a[0][i]);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++) scanf("%lf",&a[i][j]);
		scanf("%lf",&a[i][0]);
	}
	for(int i=1;i<=n;i++) id[i]=i;
	if(prepare() && simplex()){
		printf("%.8lf\n",-a[0][0]);
		if(t){
			for(int i=1;i<=m;i++) if(id[n+i]>=1)ans[id[n+i]]=a[i][0];
			for(int i=1;i<=n;i++) printf("%.8lf ",ans[i]);
		}
	}
}