#include <iostream>
#include <algorithm>
using namespace std;

int n, m, s[5010][5010];
// 因为空间较为紧张，这里只用了一个数组，计算出前缀和后原数组直接被覆盖

int main() {
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		int x, y, v;
		cin >> x >> y >> v;
		s[x + 1][y + 1] += v;	// 将横纵坐标都加一，坐标范围变成 [1, 5001]，避免越界
	}
	
	int N = 5001; // N 为坐标范围
    // 方法一
	for (int i = 1; i <= N; i ++)
		for (int j = 1; j <= N; j ++)
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + s[i][j];
/*	
	// 方法二
	for (int i = 1; i <= N; i ++)
		for (int j = 1; j <= N; j ++) s[i][j] += s[i][j - 1];
	for (int j = 1; j <= N; j ++)
		for (int i = 1; i <= N; i ++) s[i][j] += s[i - 1][j];
	*/
	
	int ans = 0;
	for (int i = m; i <= N; i ++)
		for (int j = m; j <= N; j ++) {
			int num = s[i][j] - s[i - m][j] - s[i][j - m] + s[i - m][j - m];
            // num 为以 (i, j) 为右下角的边长为 m 的正方形区域中的目标价值之和
			ans = max(ans, num);
            // 用 num 更新答案
		}
	
	cout << ans << endl;
	
	return 0;
}
