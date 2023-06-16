// Multiple interfaces.


interface CanFight {
	
	void fight();
}

interface CanSwim {
	
	void swim();
}

interface CanFly {
	
	void fly();
}

/*
interface Animal extends CanFight,CanSwim,CanFly {
	
	void run();
}
*/
class ActionCharacter {
	
	public void fight() {
		
		System.out.println("ActionCharacter.fight()");
	}
}

class Hero extends ActionCharacter 
    implements CanFight, CanSwim, CanFly {
    	
	public void swim() {
		
		System.out.println("Hero.swim()");
	}
  
	public void fly() {
		
		System.out.println("Hero.fly()");
	}
}

public class Adventure {
	
	static void t(CanFight x) {
		
		x.fight(); 
	}
	  
	static void u(CanSwim x) { 
		
		x.swim();
	}
	  
	static void v(CanFly x) {
		
		x.fly();
	}
	  
	static void w(ActionCharacter x) {
		
		x.fight(); 
	}
	  
	public static void main(String[] args) {
		
			
		Hero h = new Hero();
		    
		t(h); // Treat it as a CanFight
		u(h); // Treat it as a CanSwim
		v(h); // Treat it as a CanFly
		w(h); // Treat it as an ActionCharacter
	}
} ///:~