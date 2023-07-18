#include <cstdio>
#include <cstring>
#define Min(x , y) ((x) < (y) ? (x) : (y))
#define Max(x , y) ((x) > (y) ? (x) : (y))

int n , m , ap , bp , as , bs , w , ans = 0 , f[2001][2001] , l , r , q[2001];
// f[i][j] 表示第 i 天后拥有 j 张股票赚的最多钱数
// l , r , q[x] 用于单调队列

int main(){
    freopen(".in", "r", stdin);
    freopen(".ans", "w", stdout);
    scanf("%d%d%d" , &n , &m , &w);
    memset(f , 128 , sizeof(f)); // 128 实际上给 f 数组赋的是 -inf，可以试试看
    for(int i = 1 ; i <= n ; i++){
        scanf("%d%d%d%d" , &ap , &bp , &as , &bs);
        for(int j = 0 ; j <= as ; j++)
            f[i][j] = -1 * j * ap; // 第 1 种情况，直接赋
        for(int j = 0 ; j <= m ; j++)
            f[i][j] = Max(f[i][j] , f[i - 1][j]); // 第 2 种情况，转移
        if(i <= w)
            continue; // 因为第 3，4 种情况都有 i - w - 1，如果 i <= w，会出现负下标
        // 第 3 种情况，从小转移到大
        l = 1 , r = 0; // 单调队列准备
        for(int j = 0 ; j <= m ; j++){
            while(l <= r && q[l] < j - as)
                l++; // 把过期的元素扔掉
            while(l <= r && f[i - w - 1][q[r]] + q[r] * ap <= f[i - w - 1][j] + j * ap)
                r--; // 更新单调队列元素
            q[++r] = j; // 插入最新元素
            if(l <= r)
                f[i][j] = Max(f[i][j] , f[i - w - 1][q[l]] + q[l] * ap - j * ap); 
            // 如果单调队列里有元素，即可转移
        }
        // 第 4 种情况，从大转移到小
        l = 1 , r = 0; // 单调队列再次准备
        for(int j = m ; j >= 0 ; j--){
            while(l <= r && q[l] > j + bs)
                l++; // 把过期的元素扔掉
            while(l <= r && f[i - w - 1][q[r]] + q[r] * bp <= f[i - w - 1][j] + j * bp)
                r--; // 更新单调队列元素
            q[++r] = j; // 插入最新元素
            if(l <= r)
                f[i][j] = Max(f[i][j] , f[i - w - 1][q[l]] + q[l] * bp - j * bp); 
            // 如果单调队列里有元素，即可转移
        }
    }
    for(int i = 0 ; i <= m ; i++)
        ans = Max(ans , f[n][i]); // 最后，可以留股票（实际上不留任何股票的就是最优答案），找出最优答案
    printf("%d\n" , ans);
    return 0;
}
