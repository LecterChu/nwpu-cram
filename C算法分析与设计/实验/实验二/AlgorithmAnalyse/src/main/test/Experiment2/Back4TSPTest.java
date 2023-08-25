package Experiment2;

import org.junit.Assert;
import org.junit.Test;

import java.util.Random;

public class Back4TSPTest {

	@Test
	public void testBacktrack4TSP() {
		Back4TSP back4TSP = new Back4TSP();
		int[][] b = { { -1, -1, -1, -1, -1 }, { -1, -1, 9, 19, 13 }, { -1, 21, -1, -1, 14 }, { -1, 1, 40, -1, 17 },
				{ -1, 41, 80, 10, -1 } };
		int n = 4;
		back4TSP.backtrack4TSP(b, n);
		Assert.assertTrue(back4TSP.bestc == 34);

		int NoEdge = -1; //涓嶅彲杈�
		Random random =new Random();

		/**
		 * n=5
		 */
		long startTime=System.currentTimeMillis();
		int [][] a1=new int [6][];
		for(int i=0;i<6;i++) {
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
//		Back4TSP back4TSP = new Back4TSP();
		back4TSP.backtrack4TSP(a1, 5);
		long endTime=System.currentTimeMillis();
		System.out.println("time of n=5 :"+(endTime-startTime)+"ms");

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
		Back4TSP back4TSP1 = new Back4TSP();
		back4TSP1.backtrack4TSP(a2, 10);
		long endTime1=System.currentTimeMillis();
		System.out.println("time of n=10 :"+(endTime1-startTime1)+"ms");

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
		Back4TSP back4TSP2 = new Back4TSP();
		back4TSP2.backtrack4TSP(a3, 15);
		long endTime2=System.currentTimeMillis();
		System.out.println("time of n=15 :"+(endTime2-startTime2)+"ms");

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
		Back4TSP back4TSP3 = new Back4TSP();
		back4TSP3.backtrack4TSP(a4, 20);
		long endTime3=System.currentTimeMillis();
		System.out.println("time of n=20 :"+(endTime3-startTime3)+"ms");

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
		Back4TSP back4TSP4 = new Back4TSP();
		back4TSP4.backtrack4TSP(a5, 25);
		long endTime4=System.currentTimeMillis();
		System.out.println("time of n=25 :"+(endTime4-startTime4)+"ms");

	}


}
