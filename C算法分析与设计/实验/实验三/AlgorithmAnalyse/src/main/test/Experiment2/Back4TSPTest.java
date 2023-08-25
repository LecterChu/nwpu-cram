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

        int NoEdge = -1;
        Random random =new Random();

        System.out.println("Back4TSPTest:");

        for (int iter = 5 ; iter <= 15 ; iter++){
            long startTime = System.currentTimeMillis();
            int[][] a = new int[iter+1][iter+1];
            for (int i = 0 ; i <= iter ; i++){
                for(int j=0;j<6;j++) {
                    if(i==0||j==0) {
                        a[i][j]=NoEdge;
                    }else if(i==j){
                        a[i][j]=NoEdge;
                    }else {
                        a[i][j]=random.nextInt(10)+1;
                    }
                }
            }
            back4TSP.backtrack4TSP(a, iter);
            long endTime=System.currentTimeMillis();
            System.out.println("time of n=" + iter + " :"+(endTime-startTime)+"ms");
        }

    }

}
