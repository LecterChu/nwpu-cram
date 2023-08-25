package Experiment3;

import org.junit.Assert;
import org.junit.Test;

import java.util.Random;

public class GATest {
	int popNum = 10;
	int length = 5;
	int codeNum = 5;
	int[] codes = {1, 2, 3, 4, 5};
	int[] codeCount = {1, 1, 1, 1, 1};
	int[][] a = {
			{100, 3, 1, 5, 8},
			{3, 100, 6, 7, 9},
			{1, 6, 100, 4, 2},
			{5, 7, 4, 100, 3},
			{8, 9, 2, 3, 100}
	};
	int[][] iniPop = new int[popNum][length];
	GAOperations gaOperations = new GAOperations();
	
	@Test
	public void TestRandomInitialiation()
	{		
		gaOperations.RandomInitialiation(popNum, length, codes, codeNum, codeCount, iniPop);
		int i, j;
		int[] nJs = new int[codeNum];//统计每个编码产生的数量
		for(i = 0; i < popNum; i++)
		{
			for(j = 0; j < codeNum; j++)
			{
				nJs[j] = 0;
			}
			for(j = 0; j < length; j++) //统计每个code的数量
			{
				int pos = GAOperations.getCodePos(iniPop[i][j], codeNum, codes);//获取code 在codes中的位置
				nJs[pos]++;
			}
			for(j = 0; j < codeNum; j++)
			{
				Assert.assertEquals(nJs[j], codeCount[j]);
			}
		}
	}
	
	@Test
	public void TestComputeFitness()
	{
		int[] pop = {1, 3, 5, 4, 2};
		double fit = GAOperations.computeFitness(pop, length, a);
		Assert.assertTrue(Math.abs(fit-1/16.0) < 0.0001);
	}
	
	@Test
	public void TestRoundBet()
	{
		gaOperations.RandomInitialiation(popNum, length, codes, codeNum, codeCount, iniPop);
		int i, j;
		int[] nJs = new int[codeNum];//统计每个编码产生的数量
		double[] fitness = new double[popNum];
		for(i = 0; i < popNum; i++)
		{
			fitness[i] = GAOperations.computeFitness(iniPop[i], length, a);
		}
		GAOperations.roundBet(popNum, length, iniPop, fitness);
		for(i = 0; i < popNum; i++)
		{
			for(j = 0; j < codeNum; j++)
			{
				nJs[j] = 0;
			}
			for(j = 0; j < length; j++) //统计每个code的数量
			{
				int pos = GAOperations.getCodePos(iniPop[i][j], codeNum, codes);//获取code 在codes中的位置
				nJs[pos]++;
			}
			for(j = 0; j < codeNum; j++)
			{
				Assert.assertEquals(nJs[j], codeCount[j]);
			}
		}
	}

	@Test
	public void TestDisturbance()
	{
		gaOperations.RandomInitialiation(popNum, length, codes, codeNum, codeCount, iniPop);
		int i, j;
		int[] nJs = new int[codeNum];//统计每个编码产生的数量
		GAOperations.Disturbance(iniPop, popNum, length, 5);
		for(i = 0; i < popNum; i++)
		{
			for(j = 0; j < codeNum; j++)
			{
				nJs[j] = 0;
			}
			for(j = 0; j < length; j++) //统计每个code的数量
			{
				int pos = GAOperations.getCodePos(iniPop[i][j], codeNum, codes);//获取code 在codes中的位置
				nJs[pos]++;
			}
			for(j = 0; j < codeNum; j++)
			{
				Assert.assertEquals(nJs[j], codeCount[j]);
			}
		}
	}


	@Test
	public void TimeTest(){
		Random random = new Random();
		System.out.println("GATest:");
		int n;
		int popNum = 100;
		int length;
		int codeNum;
		double bestRes;
		int[] codes;
		int[] bestCodes;
		int[][] a;
		int[][] iniPop;
		double[] fitness;
		GAOperations gaOperations = new GAOperations();

		for (int iter = 1 ; iter <= 15 ; iter++){
			n = iter;
			length = n;
			codeNum = n;
			a = new int[n][n];
			fitness = new double[popNum];
			codes = new int[n];
			bestCodes = new int[n];
			iniPop = new int[popNum][n];
			for (int i = 0; i < n; i++) {
				bestCodes[i] = i + 1;
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					a[i][j] = random.nextInt(10) + 1;
				}
			}
			long tt= System.currentTimeMillis();
			bestRes = GAOperations.computeFitness(bestCodes, length, a);
			gaOperations.RandomInitialiation(popNum, length, bestCodes, codeNum, codes, iniPop);
			int T = 100000, cgf = 0;
			for (int t = 1; t <= T; t++) {
				if (cgf > 2000) break;
				cgf++;
				for (int i = 0; i < popNum; i++) {
					fitness[i] = GAOperations.computeFitness(iniPop[i], length, a);
					if (fitness[i] > bestRes) {
						cgf = 0;
						bestRes = fitness[i];
						System.arraycopy(iniPop[i], 0, bestCodes, 0, length);
					}
				}
				GAOperations.Disturbance(iniPop, popNum, length, 5);
				GAOperations.roundBet(popNum, length, iniPop, fitness);
			}
			System.out.println("time of n=" + iter + " :" + (System.currentTimeMillis() - tt) +"ms");
		}

//		// n = 5;
//		n = 5;
//		length = n;
//		codeNum = n;
//		a = new int[n][n];
//		fitness = new double[popNum];
//		codes = new int[n];
//		bestCodes = new int[n];
//		iniPop = new int[popNum][n];
//		for (int i = 0; i < n; i++) {
//			bestCodes[i] = i + 1;
//		}
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				a[i][j] = random.nextInt(10) + 1;
//			}
//		}
//		long tt= System.currentTimeMillis();
//		bestRes = GAOperations.computeFitness(bestCodes, length, a);
//		gaOperations.RandomInitialiation(popNum, length, bestCodes, codeNum, codes, iniPop);
//		int T = 100000, cgf = 0;
//		for (int t = 1; t <= T; t++) {
//			if (cgf > 2000) break;
//			cgf++;
//			for (int i = 0; i < popNum; i++) {
//				fitness[i] = GAOperations.computeFitness(iniPop[i], length, a);
//				if (fitness[i] > bestRes) {
//					cgf = 0;
//					bestRes = fitness[i];
//					System.arraycopy(iniPop[i], 0, bestCodes, 0, length);
//				}
//			}
//			GAOperations.Disturbance(iniPop, popNum, length, 5);
//			GAOperations.roundBet(popNum, length, iniPop, fitness);
//		}
//		System.out.println("time of n=5 :" + (System.currentTimeMillis() - tt) +"ms");
//
//
//		// n = 10;
//		n = 10;
//		length = n;
//		codeNum = n;
//		a = new int[n][n];
//		fitness = new double[popNum];
//		codes = new int[n];
//		bestCodes = new int[n];
//		iniPop = new int[popNum][n];
//		for (int i = 0; i < n; i++) {
//			bestCodes[i] = i + 1;
//		}
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				a[i][j] = random.nextInt(10) + 1;
//			}
//		}
//		tt= System.currentTimeMillis();
//		bestRes = GAOperations.computeFitness(bestCodes, length, a);
//		gaOperations.RandomInitialiation(popNum, length, bestCodes, codeNum, codes, iniPop);
//		T = 100000;
//		cgf = 0;
//		for (int t = 1; t <= T; t++) {
//			if (cgf > 2000) break;
//			cgf++;
//			for (int i = 0; i < popNum; i++) {
//				fitness[i] = GAOperations.computeFitness(iniPop[i], length, a);
//				if (fitness[i] > bestRes) {
//					cgf = 0;
//					bestRes = fitness[i];
//					System.arraycopy(iniPop[i], 0, bestCodes, 0, length);
//				}
//			}
//			GAOperations.Disturbance(iniPop, popNum, length, 10);
//			GAOperations.roundBet(popNum, length, iniPop, fitness);
//		}
//		System.out.println("time of n=10 :" + (System.currentTimeMillis() - tt) +"ms");
//
//
//		// n = 15;
//		n = 15;
//		length = n;
//		codeNum = n;
//		a = new int[n][n];
//		fitness = new double[popNum];
//		codes = new int[n];
//		bestCodes = new int[n];
//		iniPop = new int[popNum][n];
//		for (int i = 0; i < n; i++) {
//			bestCodes[i] = i + 1;
//		}
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				a[i][j] = random.nextInt(10) + 1;
//			}
//		}
//		tt= System.currentTimeMillis();
//		bestRes = GAOperations.computeFitness(bestCodes, length, a);
//		gaOperations.RandomInitialiation(popNum, length, bestCodes, codeNum, codes, iniPop);
//		T = 100000;
//		cgf = 0;
//		for (int t = 1; t <= T; t++) {
//			if (cgf > 2000) break;
//			cgf++;
//			for (int i = 0; i < popNum; i++) {
//				fitness[i] = GAOperations.computeFitness(iniPop[i], length, a);
//				if (fitness[i] > bestRes) {
//					cgf = 0;
//					bestRes = fitness[i];
//					System.arraycopy(iniPop[i], 0, bestCodes, 0, length);
//				}
//			}
//			GAOperations.Disturbance(iniPop, popNum, length, 15);
//			GAOperations.roundBet(popNum, length, iniPop, fitness);
//		}
//		System.out.println("time of n=15 :" + (System.currentTimeMillis() - tt) +"ms");
//
//
//		// n = 20;
//		n = 20;
//		length = n;
//		codeNum = n;
//		a = new int[n][n];
//		fitness = new double[popNum];
//		codes = new int[n];
//		bestCodes = new int[n];
//		iniPop = new int[popNum][n];
//		for (int i = 0; i < n; i++) {
//			bestCodes[i] = i + 1;
//		}
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				a[i][j] = random.nextInt(10) + 1;
//			}
//		}
//		tt= System.currentTimeMillis();
//		bestRes = GAOperations.computeFitness(bestCodes, length, a);
//		gaOperations.RandomInitialiation(popNum, length, bestCodes, codeNum, codes, iniPop);
//		T = 100000;
//		cgf = 0;
//		for (int t = 1; t <= T; t++) {
//			if (cgf > 2000) break;
//			cgf++;
//			for (int i = 0; i < popNum; i++) {
//				fitness[i] = GAOperations.computeFitness(iniPop[i], length, a);
//				if (fitness[i] > bestRes) {
//					cgf = 0;
//					bestRes = fitness[i];
//					System.arraycopy(iniPop[i], 0, bestCodes, 0, length);
//				}
//			}
//			GAOperations.Disturbance(iniPop, popNum, length, 20);
//			GAOperations.roundBet(popNum, length, iniPop, fitness);
//		}
//		System.out.println("time of n=20 :" + (System.currentTimeMillis() - tt) +"ms");

		// n = 30;
		n = 30;
		length = n;
		codeNum = n;
		a = new int[n][n];
		fitness = new double[popNum];
		codes = new int[n];
		bestCodes = new int[n];
		iniPop = new int[popNum][n];
		for (int i = 0; i < n; i++) {
			bestCodes[i] = i + 1;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = random.nextInt(10) + 1;
			}
		}
		long tt= System.currentTimeMillis();
		bestRes = GAOperations.computeFitness(bestCodes, length, a);
		gaOperations.RandomInitialiation(popNum, length, bestCodes, codeNum, codes, iniPop);
		int T = 100000;
		int cgf = 0;
		for (int t = 1; t <= T; t++) {
			if (cgf > 2000) break;
			cgf++;
			for (int i = 0; i < popNum; i++) {
				fitness[i] = GAOperations.computeFitness(iniPop[i], length, a);
				if (fitness[i] > bestRes) {
					cgf = 0;
					bestRes = fitness[i];
					System.arraycopy(iniPop[i], 0, bestCodes, 0, length);
				}
			}
			GAOperations.Disturbance(iniPop, popNum, length, 20);
			GAOperations.roundBet(popNum, length, iniPop, fitness);
		}
		System.out.println("time of n=30 :" + (System.currentTimeMillis() - tt) +"ms");

		// n = 40;
		n = 40;
		length = n;
		codeNum = n;
		a = new int[n][n];
		fitness = new double[popNum];
		codes = new int[n];
		bestCodes = new int[n];
		iniPop = new int[popNum][n];
		for (int i = 0; i < n; i++) {
			bestCodes[i] = i + 1;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = random.nextInt(10) + 1;
			}
		}
		tt= System.currentTimeMillis();
		bestRes = GAOperations.computeFitness(bestCodes, length, a);
		gaOperations.RandomInitialiation(popNum, length, bestCodes, codeNum, codes, iniPop);
		T = 100000;
		cgf = 0;
		for (int t = 1; t <= T; t++) {
			if (cgf > 2000) break;
			cgf++;
			for (int i = 0; i < popNum; i++) {
				fitness[i] = GAOperations.computeFitness(iniPop[i], length, a);
				if (fitness[i] > bestRes) {
					cgf = 0;
					bestRes = fitness[i];
					System.arraycopy(iniPop[i], 0, bestCodes, 0, length);
				}
			}
			GAOperations.Disturbance(iniPop, popNum, length, 20);
			GAOperations.roundBet(popNum, length, iniPop, fitness);
		}
		System.out.println("time of n=40 :" + (System.currentTimeMillis() - tt) +"ms");

	}
}

