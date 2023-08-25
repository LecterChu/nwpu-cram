package Experiment2;

public class Back4TSP {

	int NoEdge = -1;
	int bigInt = Integer.MAX_VALUE;
	int[][] a; // 邻接矩阵
	int cc = 0; // 存储当前代价
	int bestc = bigInt;// 当前最优代价
	int[] x; // 当前解
	int[] bestx;// 当前最优解
	int n = 0; // 顶点个数

	/**
	 * backtrack
	 *
	 * @param i 当前深度
//	 */
	private void backtrack(int i) {//i为初始深度
		if (i > n) {
			//深度大于n的时候更新最低cost和最佳路径
			bestc = cc;
			bestx = x;
		} else {
			// 深度还没有超过最大深度
			// 轮着交换
			for(int j = i; j <= n; j++) {
				// 交换位置i和位置j上的元素
				swap(x[i], x[j]);
				if(check(i)) {
					// i不是最后一个节点的时候不用考虑从最后一个节点回到第一个节点的路
					if(i < n && cc + a[x[i-1]][x[i]] < bestc) {
						// 更新最低cost
						cc += a[x[i-1]][x[i]];
						// 进入下一深度
						backtrack(i+1);
						// 恢复最低cost
						cc -= a[x[i-1]][x[i]];
					}
					// i是最后一个节点的时候，要考虑从最后一个节点回到第一个节点的路
					if(i == n && cc + a[x[i-1]][x[i]] < bestc) {
						// 更新最低cost
						cc += (a[x[i-1]][x[i]]+a[x[i]][1]);
						// 进入下一深度
						backtrack(i+1);
						// 恢复最低cost
						cc -= (a[x[i-1]][x[i]]+a[x[i]][1]);
					}
				}
				//交换元素
				swap(x[i], x[j]);
			}
		}
	}

	/**
	 * 交换两个位置上的元素
	 *
	 * @param i 第一个元素的位置
	 * @param j 第二个元素的位置
	 */
	private void swap(int i, int j) {
		int temp = x[i];
		x[i] = x[j];
		x[j] = temp;
	}

	/**
	 * 检查此位置上的元素是否有遍历的需要
	 *
	 * @param pos 要检查的位置
	 * @return true or fasle
	 */
	public boolean check(int pos) {
		if(pos < 2) return true;
		if(pos<n && a[x[pos - 1]][x[pos]] != NoEdge) return true;
		if(pos==n && a[x[pos - 1]][x[pos]] != NoEdge && a[x[pos]][1] != NoEdge) return true;
		return false;
	}

	/**
	 *
	 *
	 * @param b
	 * @param num
	 */
	public void backtrack4TSP(int[][] b, int num) {
		n = num;
		x = new int[n + 1];
		for (int i = 0 ; i <= n ; i++)
			x[i] = i;
		bestx = new int[n + 1];
		a = b;
		backtrack(2);
	}

}
