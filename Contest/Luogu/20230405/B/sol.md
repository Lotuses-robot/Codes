按 $i$ 枚举 $j$，依次检查 $MEX(i,j)$ 是否合规。

因为 $MEX$ 不降，所以当 $MEX(i,j) > k$ 时 $i = j$。

如果刚好碰到 $MEX(i,j) = k$ 的时候就要修改一个，贪心的就修改最后一个呗。

那么修改 $a[j] = k$ 且 $i = j + 1$ 继续寻找。

注：MEX 的意思是序列中出现的最小的自然数。

思路提示：

做的时候多想想特殊的性质。 $a_i = k$ 时刚好可以将前两个分段相互隔开。

而且要联系数据范围。 想到特殊性质后，尝试在暴力的基础上修改，如果改不出来，那么将暴力的步骤拆散，看哪一部分可以被性质勾八掉。


```
@N_z_  2023-04-05 19:23
@Lotuses 我先想到了k可以把序列分开，然后是分出最长的块就好了

@RoMantic_Queue  2023-04-05 19:23
因为是顺序修改，所以每次改 j 之后都会使 [i,j] 区间满足答案，之后只需考虑 j 后的区间
```