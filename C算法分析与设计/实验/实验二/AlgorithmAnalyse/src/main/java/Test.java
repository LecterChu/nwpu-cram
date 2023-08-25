import java.util.Vector;

public class Test {

    public static void main(String[] args){
        int n = 5;
        Vector<Integer> res = new Vector<>();

        for(int i = n ; i >= 1 ; i--)
            res.add(i);
        System.out.print(res.toString());

        res.remove(1);
        System.out.print(res.toString());

        res.removeElement(1);
        System.out.print(res.toString());
    }
}
