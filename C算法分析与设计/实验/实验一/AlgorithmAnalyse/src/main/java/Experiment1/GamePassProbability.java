package Experiment1;

import java.util.Arrays;
import java.util.Scanner;

public class GamePassProbability {

	public double calculatePassProbability(int[] p, int num) {
		double pass = 0.0d;
		//dp[i][j]表示已经进行了i场，其中有j场胜利的概率
		double[][] dp = new double[num + 1][num + 1];

		//置零
		for (double[] temp : dp) {
			Arrays.fill(temp, 0.0);
		}

		//0场胜利0场->概率为1
		dp[0][0] = 1;

		//动规
		for(int i = 1 ; i <= num ; i ++){
			dp[i][0] = dp[i - 1][0] * (1 - 0.01 * p[i - 1]);
			for(int j = 1 ; j <= i ; j++){
				dp[i][j] = dp[i - 1][j] * (1 - 0.01 * p[i - 1]) + dp[i -1][j - 1] * 0.01 * p[i - 1];
			}
		}

//		//输出dp矩阵查看
//		for(int i = 0 ; i <= num ; i++){
//			for(int j = 0 ; j <= num ; j++){
//				System.out.print(dp[i][j] + "   ");
//			}
//			System.out.println();
//		}

		//计算至少赢下70%场次的概率
		int k = (int) Math.ceil(num * 0.7);
		for (int i = k; i < num + 1; i++) {
			pass += dp[num][i];
		}

		return ((double) Math.round(pass * 100000)) / 100000.0; // 四舍五入


	}

	public static void main(String[] args) {
		GamePassProbability gpp = new GamePassProbability();
		int num;
		Scanner in = new Scanner(System.in);
		num = in.nextInt();
		int[] p = new int[num];
		for(int i = 0; i < num; i++) {
			p[i] = in.nextInt();
		}
		System.out.println(String.format("%.5f",gpp.calculatePassProbability(p, num)));
	}

}
