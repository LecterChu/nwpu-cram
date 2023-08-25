package Experiment2;

import java.util.Collections;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Vector;

public class BB4TSP {

	final int NoEdge = -1; //表示没有边
	private int minCost = Integer.MAX_VALUE; //当前最小代价
	private int[][] minEdge; //
	Comparator<HeapNode> cmp = new Comparator<HeapNode>() {
		public int compare(HeapNode e1, HeapNode e2) {//从大到小排序
			return e2.lcost - e1.lcost;
		}
	};
	private PriorityQueue<HeapNode> priorHeap = new PriorityQueue<HeapNode>(100, cmp);//存储活节点
	private Vector<Integer> bestH = new Vector<Integer>();


	@SuppressWarnings("rawtypes")
	public static class HeapNode implements Comparable{
		Vector<Integer> cityArrange = new Vector<Integer>();//城市排列
		int lcost; //代价的下界
		int level;//0-level的城市是已经排好的
		//构造方法
		public HeapNode(Vector<Integer> cities,int lb, int lev){
			cityArrange.addAll(0, cities);
			lcost = lb;
			level = lev;
		}

		@Override
		public int compareTo(Object x) {//升序排列, 每一次pollFirst
			int xu=((HeapNode)x).lcost;
			return Integer.compare(lcost, xu);
		}
		public boolean equals(Object x){
			if(x instanceof HeapNode)
				return lcost==((HeapNode)x).lcost;
			return false;
		}

	}

	/**
	 * 计算部分解的下界.
	 *
	 * @param cityArrange 城市的排列
	 * @param level 当前确定的城市的个数.
	 * @param cMatrix 邻接矩阵，第0行，0列不算
	 * @exception IllegalArgumentException exception
	 */
	public int computeLB(Vector<Integer> cityArrange, int level, int[][] cMatrix)
	{
		int lowcost = 0;
		int average = 0;
		int n = cMatrix.length - 1;
//		int max = selectMax(cMatrix);
		for (int i = 1 ; i < level ; i++) lowcost += cMatrix[cityArrange.get(i)][cityArrange.get(i + 1)];

		//如果已经到达最后一个城市，就要检查这个城市与第一个城市之间有没有边可以走
		//如果可以走通，那么在原本lowcost的基础上增加最后一个城市到第一个城市的cost
		if (level == n && cMatrix[cityArrange.get(level)][1] != -1)
			lowcost += cMatrix[cityArrange.get(level)][1];
			//如果不能走通，那么就直接将lowcost置为MAXVALUE，表示此路不通
		else if (level == n && cMatrix[cityArrange.get(level)][1] == -1)
			lowcost = Integer.MAX_VALUE;
			//如果还不是最后一个城市，从当前城市开始计算下界
		else if (level != n){
			for (int i = level ; i <= n ; i++){
				if(i != n){
					//？
					average = (minEdge[cityArrange.get(i)][0] + minEdge[cityArrange.get(i + 1)][1]) / 2;
					lowcost += average;
				}
				else {
					//？
					lowcost += minEdge[1][1];
				}
			}
		}
		return lowcost;
	}

	/**
	 * 选出cMatrix中的最大值
	 *
	 * @param cMatrix
	 * @return
	 */
	public int selectMax(int[][] cMatrix){
		int max = 0;
		for(int i = 1 ; i < cMatrix.length - 1 ; i++)
			for(int j = 1 ; j <cMatrix.length - 1 ; j++){
				if (cMatrix[i][j] > max)
					max = cMatrix[i][j];
			}

		if(max == -1)
			return Integer.MAX_VALUE;
		return max;
	}

	/**
	 * 求部分解的上界：贪心
	 * @param cMatrix 邻接矩阵[n+1][n+1]:1->n
	 * @return 上界ub
	 */
	public int computeUB(int[][] cMatrix){
		int ub = 0;
		int n = cMatrix.length - 1;
		int max = this.selectMax(cMatrix);
		Vector<Integer> chosed_city = new Vector<>();
		Vector<Integer> res_city = new Vector<>();
		chosed_city.add(1);
		for(int i = 2 ; i < cMatrix.length ; i++) res_city.add(i);

		int i = 1;
		while(!res_city.isEmpty()){
			int minCost = Integer.MAX_VALUE;
			int temp = -1;
			for (int j = 1 ; j <= n ; j++){
				if(i != j && !chosed_city.contains(j)){
					if (cMatrix[i][j] == -1){
						minCost = (max==Integer.MAX_VALUE) ? max : Integer.MAX_VALUE;
						break;
					}
					if (cMatrix[i][j] < minCost && cMatrix[i][j] != -1){
						minCost = cMatrix[i][j];
						temp = j;
					}

				}
			}
			if(temp != -1){
				ub += minCost;
				chosed_city.add(temp);
				res_city.removeElement(temp);
			}
			else{
				ub += max;
				temp = res_city.get(1);
				res_city.remove(1);
				chosed_city.add(temp);
				res_city.removeElement(temp);
			}
			i = temp;
		}
		if(ub != Integer.MAX_VALUE){
			if(cMatrix[i][1] != -1)
				ub += cMatrix[i][1];
			else
				ub += max;
		}

//		System.out.println(ub);
		return ub;
	}

	/**
	 * 检查两个城市之间有没有边
	 *
	 * @param cityArrange 当前city安排
	 * @param i cityArrange(i)
	 * @param j cityArrange(j)
	 * @param cMatrix 邻接矩阵[n+1][n+1]:1->n
	 * @return 两城市是否连通
	 */
	public boolean constraint(Vector<Integer> cityArrange, int i, int j, int[][] cMatrix){
		//如果i - 1 和 j之间有边 返回true
		return cMatrix[cityArrange.get(i - 1)][cityArrange.get(j)] != -1;
	}

	/**
	 * 计算每个城市最小的入边和出边
	 *
	 * @param cMatrix 邻接矩阵[n+1][n+1]:1->n
	 * @return minEdge
	 */
	public int[][] clacuMin(int[][] cMatrix){
		// 保存每个城市的最小入边和出边，用以计算下界
		// minEdge[i][0] 表示第i个城市的出边
		// minEdge[i][1] 表示第i个城市的入边
		int[][] minEdge = new int[cMatrix.length][2];
		for (int i = 1 ; i < cMatrix.length ; i++){
			// minOut 保存城市i的最小出边
			int minOut = Integer.MAX_VALUE;
			// minIn 保存城市i的最小入边
			int minIn = Integer.MAX_VALUE;
			for(int j = 0 ; j < cMatrix.length ; j++){
				// 如果找到比当前出边更小的出边，就保存到minOut
				if (cMatrix[i][j] < minOut && cMatrix[i][j] != -1)
					minOut = cMatrix[i][j];
				// 如果找到比当前入边更小的入边，就保存到minIn
				if (cMatrix[i][j] < minIn && cMatrix[j][i] != -1)
					minIn = cMatrix[j][i];
			}
			// 更新minEdge
			minEdge[i][0] = minOut;
			minEdge[i][1] = minIn;
		}
		// 返回最小入边和出边
		return minEdge;
	}

	/**
	 * 计算TSP问题的最小代价的路径.
	 *
	 * @param cMatrix 邻接矩阵，第0行，0列不算
	 * @param n   城市个数.
	 * @exception IllegalArgumentException exception
	 */
	public int bb4TSP(int[][] cMatrix, int n)
	{
		//构造初始节点
		Vector<Integer> cityArrange = new Vector<Integer>() ;//城市排列
		cityArrange.add(0);//空出一个城市，与cMatrix一致
		for(int i = 1; i<=n; i++) cityArrange.add(i);
		int level = 2;//0-level的城市是已经排好的
//		int lcost = computeLB(cityArrange, level, cMatrix) ; //代价的下界
		this.minEdge = clacuMin(cMatrix);// 算出每个城市的最小入边和出边
		int ub = computeUB(cMatrix);// 上界
		int lb = computeLB(cityArrange, level, cMatrix);// 下界
		HeapNode currentNode = new HeapNode(cityArrange, lb, 1);// 第一个节点
		this.priorHeap.add(currentNode); // 添加第一个节点
		while(level != n) // 如果还没到达最后一个城市
		{
			//从下一个城市开始遍历
			for (int i = level; i <= n ; i++){
				//检查level-1能否到达i
				if (constraint(cityArrange, level, i, cMatrix)){
					Collections.swap(currentNode.cityArrange, level, i);

					// 计算下界
					int temp = computeLB(currentNode.cityArrange, level + 1, cMatrix);
					// 创建新节点
					HeapNode node = new HeapNode(currentNode.cityArrange, temp, level + 1);
//					if(level + 1 == n)
//						node.lcost = computeLB(currentNode.cityArrange, level + 1, cMatrix);
					// 如果大于上界 说明这个节点没有意义 这个节点的潜力太小 剪枝
					if(node.lcost > ub)
						continue;
					this.priorHeap.add(node);

					Collections.swap(currentNode.cityArrange, level, i);
				}
			}
			if(this.priorHeap.isEmpty())  break;
			currentNode = this.priorHeap.poll();
			level = currentNode.level;
		}
		if(level == n){// 到达最后一个城市
			if (currentNode.lcost < this.getMinCost()){
				this.bestH = currentNode.cityArrange;
				this.setMinCost(currentNode.lcost);
			}
		}

		return this.getMinCost();
	}

	public int getMinCost() {
		return minCost;
	}

	public void setMinCost(int minCost) {
		this.minCost = minCost;
	}

	public static void main(String[] args){
		BB4TSP bb4TSP = new BB4TSP();
		int[][] b = { { -1, -1, -1, -1, -1 }, { -1, -1, 9, 19, 13 }, { -1, 21, -1, -1, 14 }, { -1, 1, 40, -1, 17 },
				{ -1, 41, 80, 10, -1 } };
		int n = 4;
		bb4TSP.bb4TSP(b, n);
//		System.out.println(bb4TSP.getMinCost());
	}

}
