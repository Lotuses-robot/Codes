# sol for 1728D 

先删去左右相同的字符

再删去连续的前缀和后缀相等的字符

最后如果非空就是 Alice

否则就是平局

（显而易见的 Bob 不可能赢，因为 Alice 总能先手选取大的，而如果 Bob 选大的会导致他得到的结果串位数高的反而高，就输掉哩）

奇怪的博弈论