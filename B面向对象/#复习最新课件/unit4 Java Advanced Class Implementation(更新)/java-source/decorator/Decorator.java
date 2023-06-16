public abstract class Decorator extends Component

{

       private Component component;

       

       public  Decorator(Component component)

       {

              this.component = component;

       }//end Decorator

       

       public void sampleOperation()

       {

              this.component.sampleOperation();

       }//end sampleOperation()

       

}//end abctract class Decorator


