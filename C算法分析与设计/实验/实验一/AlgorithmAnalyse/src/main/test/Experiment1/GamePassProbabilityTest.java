package Experiment1;

import org.junit.Assert;
import org.junit.Test;

import Experiment1.GamePassProbability;


public class GamePassProbabilityTest {
	
	@Test
	public void testCalculateProbability(){
		GamePassProbability gamePassProbability = new GamePassProbability();
    	int[] p1 = {50, 50, 50, 50};
    	int[] p2 = {80, 80, 90, 90, 99};
    	int[] p3 = {};
        double result1 = gamePassProbability.calculatePassProbability(p1, 4);
        double result2 = gamePassProbability.calculatePassProbability(p2, 5);
        double result3 = gamePassProbability.calculatePassProbability(p3, 0);
        Assert.assertTrue(result1 == 0.31250);
        Assert.assertTrue(result2 == 0.88906);  
        Assert.assertTrue(result3 == 1);   
    }

}
