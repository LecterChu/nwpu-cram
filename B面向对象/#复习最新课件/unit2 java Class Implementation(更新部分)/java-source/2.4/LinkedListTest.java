import java.util.LinkedList;

public class GenericTest {
    public static void main(String[] args) {
        LinkedList<Integer> linkedList = new LinkedList<Integer>();
        // 假设有集合 [10,56,24,7,29,100]
        linkedList.add(10);
        linkedList.add(56);
        linkedList.add(24);
        linkedList.add(7);
        linkedList.add(29);
        linkedList.add(100);
        int min = linkedList.getFirst();
        for(int i = 1;i<linkedList.size();i++){
            if(linkedList.get(i)<min)min=linkedList.get(i);
        }
        System.out.println(min);
    }
}
