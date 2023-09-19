package ssd8.socket.thread;

/**
 * java多线程
 * 
 * @author wben
 *
 */
public class ThreadTest extends Thread {
	public ThreadTest(String str) {
		super(str);
	}

	@Override
	public void run() {
		synchronized (this) {
			for (int i = 0; i < 10; i++) {
				System.out.println(getName() + "-" + i);
				try {
					sleep((long) (Math.random() * 1000));
				} catch (InterruptedException e) {
					e.printStackTrace();
				}

			}
			// for循环结束
			System.out.println(getName() + "-for循环结束");
		}
		super.run();
	}

	public static void main(String args[]) {
		new ThreadTest("TA").run();
		new ThreadTest("TB").run();
		System.out.println("===Main Thread===");
	}

}
