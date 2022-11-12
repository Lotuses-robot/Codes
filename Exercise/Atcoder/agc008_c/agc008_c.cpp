#include <cstdio>
main(){int I, O, J, L, d; scanf("%d%d%*d%d%d",&I,&O,&J,&L);printf("%lld",(long long)O+I+J+L-(I&&J&&L?(d=I%2+J%2+L%2)>1?3-d:d:I%2+J%2+L%2));}