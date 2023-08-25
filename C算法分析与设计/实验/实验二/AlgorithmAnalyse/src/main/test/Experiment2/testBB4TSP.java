package Experiment2;

import org.junit.Assert;
import org.junit.Test;

import java.util.Random;

public class testBB4TSP {

	public int NoEdge = -1;

	@Test
	public void testbb4TSP() {

		BB4TSP bb4TSP = new BB4TSP();
		int[][] b = { { -1, -1, -1, -1, -1 },
				{ -1, -1, 9, 19, 13 },
				{ -1, 21, -1, -1, 14 },
				{ -1, 1, 40, -1, 17 },
				{ -1, 41, 80, 10, -1 } };
		int n = 4;
		int ans = bb4TSP.bb4TSP(b, n);
		Assert.assertTrue(ans == 34);

		/**
		 * 测试不同规模下算法的执行效率
		 */

		/**
		 * n=5
		 */
		Random random = new Random();

		long startTime=System.currentTimeMillis();
		int [][] a1=new int [6][];
		for(int i = 0; i<6; i++) {
			a1[i]=new int[6];
			for(int j=0;j<6;j++) {
				if(i==0||j==0) {
					a1[i][j]=NoEdge;
				}else if(i==j){
					a1[i][j]=NoEdge;
				}else {
					a1[i][j]=random.nextInt(10)+1;
				}
			}
		}
		System.out.println("n=5时的执行结果：" + ans);
		ans = bb4TSP.bb4TSP(a1, 5);
		long endTime=System.currentTimeMillis();
		System.out.println("n=5时的执行时间："+(endTime-startTime)+"ms");
		System.out.println();


		/**
		 * n=10
		 */

		long startTime1=System.currentTimeMillis();
		int [][] a2=new int [11][];
		for(int i=0;i<11;i++) {
			a2[i]=new int[11];
			for(int j=0;j<11;j++) {
				if(i==0||j==0) {
					a2[i][j]=NoEdge;
				}else if(i==j){
					a2[i][j]=NoEdge;
				}else {
					a2[i][j]=random.nextInt(10)+1;
				}
			}
		}
		BB4TSP bb4TSP1 = new BB4TSP();
		ans = bb4TSP1.bb4TSP(a2, 10);
		System.out.println("n=10时的执行结果：" + ans);
		long endTime1=System.currentTimeMillis();
		System.out.println("n=10时的执行时间："+(endTime1-startTime1)+"ms");
		System.out.println();

		/**
		 * n=15
		 */

		long startTime2=System.currentTimeMillis();
		int [][] a3=new int [16][];
		for(int i=0;i<16;i++) {
			a3[i]=new int[16];
			for(int j=0;j<16;j++) {
				if(i==0||j==0) {
					a3[i][j]=NoEdge;
				}else if(i==j){
					a3[i][j]=NoEdge;
				}else {
					a3[i][j]=random.nextInt(10)+1;
				}
			}
		}
		BB4TSP bb4TSP2 = new BB4TSP();
		ans = bb4TSP2.bb4TSP(a3, 15);
		System.out.println("n=15时的执行结果：" + ans);
		long endTime2=System.currentTimeMillis();
		System.out.println("n=15时的执行时间："+(endTime2-startTime2)+"ms");
		System.out.println();

		/**
		 * n=20
		 */

		long startTime3=System.currentTimeMillis();
		int [][] a4=new int [21][];
		for(int i=0;i<21;i++) {
			a4[i]=new int[21];
			for(int j=0;j<21;j++) {
				if(i==0||j==0) {
					a4[i][j]=NoEdge;
				}else if(i==j){
					a4[i][j]=NoEdge;
				}else {
					a4[i][j]=random.nextInt(10)+1;
				}
			}
		}
		BB4TSP bb4TSP3 = new BB4TSP();
		ans = bb4TSP3.bb4TSP(a4, 20);
		System.out.println("n=20时的执行结果：" + ans);
		long endTime3=System.currentTimeMillis();
		System.out.println("n=20时的执行时间："+(endTime3-startTime3)+"ms");
		System.out.println();

		/**
		 * n=25
		 */

		long startTime4=System.currentTimeMillis();
		int [][] a5=new int [26][];
		for(int i=0;i<26;i++) {
			a5[i]=new int[26];
			for(int j=0;j<26;j++) {
				if(i==0||j==0) {
					a5[i][j]=NoEdge;
				}else if(i==j){
					a5[i][j]=NoEdge;
				}else {
					a5[i][j]=random.nextInt(10)+1;
				}
			}
		}
		BB4TSP bb4TSP4 = new BB4TSP();
		ans = bb4TSP4.bb4TSP(a5, 25);
		System.out.println("n=25时的执行结果：" + ans);
		long endTime4=System.currentTimeMillis();
		System.out.println("n=25时的执行时间："+(endTime4-startTime4)+"ms");
		System.out.println();

		/**
		 * n=30
		 */

		long startTime5=System.currentTimeMillis();
		int [][] a6=new int [31][];
		for(int i=0;i<31;i++) {
			a6[i]=new int[31];
			for(int j=0;j<31;j++) {
				if(i==0||j==0) {
					a6[i][j]=NoEdge;
				}else if(i==j){
					a6[i][j]=NoEdge;
				}else {
					a6[i][j]=random.nextInt(10)+1;
				}
			}
		}
		BB4TSP bb4TSP5 = new BB4TSP();
		ans = bb4TSP5.bb4TSP(a6, 30);
		System.out.println("n=30时的执行结果：" + ans);
		long endTime5=System.currentTimeMillis();
		System.out.println("n=30时的执行时间："+(endTime5-startTime5)+"ms");
		System.out.println();
	}

}
