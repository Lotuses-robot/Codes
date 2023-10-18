#include <cstdio>

template<typename T>
void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;c<48||c>57;c=getchar())f|=c=='-';
    for(;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}

int main() {
    int x;
    read(x);
    printf("%d\n", x);
    return 0;
}