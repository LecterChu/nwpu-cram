
public class DecoratorPattern

{

       private Component door = new Door();//创建一个扇门(向下转型)

       

       private Component lock = new Lock(door);//添加一把锁(向下转型)

       private Component knob = new Knob(lock);//再添加一个把手(向下转型)

       

       public void showDecorator()

       {
              knob.sampleOperation();

       }//end showDecorator()

       

       public static void main(String[] args)

       {

              System.out.println("Decorator Pattern!\n");         

              DecoratorPattern dp = new DecoratorPattern();

              dp.showDecorator();

       }//end main(...)

   

}//end class DecoratorPattern

