package Experiment3;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class GAOperations {
	/**
	 * 随机产生初始解，思路：先产生，后修复（也可以边产生边修复，如产生的位置的代码计数过多，则重新随机产生）.
	 * 
	 * @param popNum 种群大小       
	 * @param length  每一个个体长度.
	 * @param iniPop  产生的初始种群.
	 * @param codes   编码序列.
	 * @param codeNum   编码的数量.
	 * @param codeCount  每一个编码的计数.
	 */
	public void RandomInitialiation(int popNum, int length, int[] codes, int codeNum, int[] codeCount, int[][] iniPop) {
		int i, j;
		int[] nJs = new int[codeNum];//统计每个编码产生的数量
		Random random = new Random();
		//随机产生编码，并去重，修复
		for (int k = 0 ; k < popNum ; k++){
			//给元素赋值1-codeNum的数
			iniPop[k][0] = random.nextInt(codeNum) + 1;
			for (i = 1 ; i < codeNum ;){
				iniPop[k][i] = random.nextInt(codeNum) + 1;
				for (j = 0 ; j < i ; j++){
					//若有相同元素则重新赋值
					if (iniPop[k][i] == iniPop[k][j])
						break;
				}
				//只有i之前的元素全部不相同，才进行i++，对下一个元素赋值
				if (j == i)
					i++;
			}
		}
		
	}
	
	/**
	 * 
	 * @param pop 个体       
	 * @param length  个体长度.
	 * @param a 邻接矩阵
	 */
	public static double computeFitness(int[] pop, int length, int[][] a)
	{
		//计算个体适应度
		double fitness = 0.0;
		for (int i = 1 ; i < length ; i++)
			fitness += a[pop[i - 1] - 1][pop[i] - 1];
		fitness += a[pop[length - 1] - 1][pop[0] - 1];

		//适应度函数
		return 1 / fitness;
	}

	/**
	 * 复制染色体
	 */
	public static void copyGh(int k, int kk, int length, int[][] iniPop1) {
		//父代种群
		int[][] iniPop = iniPop1;
		for (int i = 0 ; i < length ; i++)
			iniPop1[k][i] = iniPop[kk][i];
	}
	
	/**
	 * 
	 * @param popNum 个体 个数      
	 * @param length  个体长度.
	 * @param iniPop1  种群
	 * @param fitness 每一个个体的适应度
	 */
	public static void roundBet(int popNum, int length, int[][] iniPop1, double[] fitness)
	{
		//楼盘赌
		Random random = new Random();
		int selectId;
		double ran1;
		for (int k = 0 ; k < length ; k++){
			ran1 = random.nextDouble();
			int i;
			for(i = 0 ; i < length ; i++){
				if (ran1 <= fitness[i])
					break;
			}
			if (i == length)
				i--;
			selectId = i;
			copyGh(k, selectId, length, iniPop1);
		}

	}
	

	/**
	 * 
	 * @param iniPop  种群
	 * @param popNum 个体 个数      
	 * @param length  个体长度.
	 * @param disPos  随机交换的位置数
	 */
	public static void Disturbance(int [][] iniPop, int popNum, int length, int disPos)
	{
		//扰动
		// 交叉概率
		double pCross = 0.8;
		// 变异概率
		double pMutate = 0.9;
		Random random = new Random();

		// 交叉
		for (int i = 0 ; i < popNum ; i += 2){
			if (random.nextDouble() <= pCross){
				for (int j = 0 ; j < disPos ; j++){
					int t = iniPop[i][j];
					iniPop[i][j] = iniPop[i + 1][j];
					iniPop[i + 1][j] = t;
				}
				// 对交叉过后的重复数组进行修复
				int re = i - 1;
				while (++re <= i + 1){
					// 统计每个编码产生的数量
					int[] njs = new int[length];
					for (int j = 0 ; j < length ; j++)
						// 初始是=时均为出现，置为0
						njs[j] = 0;
					for (int j = 0 ; j < length ; j++){
						// 获取位置
						int pos = iniPop[re][j] - 1;
						// 统计出现次数
						njs[pos]++;
						if (njs[pos] > 1)
							// 次数大于1需要修复
							iniPop[re][j] = 0;
					}
					// 未出现数字的数组
					List<Integer> intList = new ArrayList<Integer>();
					for (int j = 0 ; j < length ; j++)
						if (njs[j] == 0)
							// 将未出现的数添加至数组中
							intList.add(j + 1);
					// 乱序
					Collections.shuffle(intList);
					int k = 0;
					for (int j = 0 ; j < length ; j++)
						if (iniPop[re][j] == 0)
							// 填入
							iniPop[re][j] = intList.get(k++);
				}

			}
		}

		// 变异
		for (int i = 0 ; i < popNum ; i++)
			// 按变异概率，交换两个基因
			if (random.nextDouble() <= pMutate){
				// 位置1的基因
				int pos1 = random.nextInt(length);
				// 位置2的基因
				int pos2 = random.nextInt(length);
				while (pos1 == pos2)
					// 位置相同，重新获取位置
					pos2 = random.nextInt(length);
				// 交换基因
				int t = iniPop[i][pos1];
				iniPop[i][pos1] = iniPop[i][pos2];
				iniPop[i][pos2] = t;
			}
	}
	
	/**
	 * 获取code在codes中的位置
	 * @param code  编码
	 * @param codeNum 总编码数 
	 * @param codes  编码矩阵.
	 */
	public static int getCodePos(int code, int codeNum, int[] codes)
	{
		int pos = 0;
		for(; pos < codeNum; pos++)
		{
			if(code == codes[pos])
			{
				return pos;
			}
		}
		return -1;
	}
}
