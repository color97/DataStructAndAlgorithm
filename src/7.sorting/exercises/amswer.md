1. 
original:   3, 1, 4, 1, 5, 9, 2, 6, 5
step1:      1, 3, 4, 1, 5, 9, 2, 6, 5
step2:      1, 3, 4, 1, 5, 9, 2, 6, 5
step3:      1, 1, 3, 4, 5, 9, 2, 6, 5
step4:      1, 1, 3, 4, 5, 9, 2, 6, 5
step5:      1, 1, 3, 4, 5, 9, 2, 6, 5
step6:      1, 1, 2, 3, 4, 5, 9, 6, 5
step7:      1, 1, 2, 3, 4, 5, 6, 9, 5
step8:      1, 1, 2, 3, 4, 5, 5, 6, 9

5. 
a. Θ(N^2), 定理7.3 证明

9. 
a. O(NlogN), 每趟 是 N / h 的 h次插入排序，因为有序，花费 h * N / h = N, 而共有 logN 趟这样的排序（希尔增量）
b. O(NlogN) ？

13. Heapsort uses at least (roughly) N log N comparisons on any input, so there are no particularly good
inputs. This bound is tight; see the paper by Schaeffer and Sedgewick [18]. This result applies for
almost all variations of heapsort, which have different rearrangement strategies. See Y. Ding and M.
A. Weiss, “Best Case Lower Bounds for Heapsort,” Computing 49 (1992)

17. Θ(N log N) ，因为归并操作 Θ(N)

20. 
a. O(NlogN) ,pivot 处于中间
b. O(NlogN) ,pivot 处于中间
c. O(NlogN) , 三数中值分割法和截至技术。快速排序平均 O(NlogN)

21. 
a. O(N^2), O(N^2), O(NlogN)
b. O(N^2), O(N^2), O(NlogN)
c. O(NlogN), O(NlogN), O(NlogN)
although there is an O(N2) worst case if very bad random numbers come up
d. 一般来说都是 O(NlogN)。
但是当序列为: 1, 2, 4, ..., 2^(k-1)时，平均值造成不均匀的分组。O(N^2)

33. 有 N 个树叶的决策树，深度至少为 ⌈ logN ⌉ ？

37. 唔知

41. 
a. ⌈ log4! ⌉ = ⌈ log24 ⌉ = 5
b. 归并排序

49. 两个元素所有可能的和有 N!种，排序 O(N!logN!) = O(N^2 * log(N^2)) = O(N^2*logN)，查找结果消耗线性时间。

53. 
a. 引理7.1 可知 深度为 2N 的决策树，最多有 2^2N 片树叶，表示一种序列的可能性。
而 N 个元素 共有 N! 种组合，故共有 Ω(N!/(2^2N))
b. 唔知