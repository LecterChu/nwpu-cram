import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class MathClient {
    public static void main(String[] args){
        try{
            Registry registry = LocateRegistry.getRegistry("localhost");
            IRemoteMath remoteMath = (IRemoteMath) registry.lookup("Compute");
            double res = remoteMath.add(5.0, 3.0);
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
