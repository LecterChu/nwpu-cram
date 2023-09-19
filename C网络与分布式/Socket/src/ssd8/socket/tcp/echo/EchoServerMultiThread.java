package ssd8.socket.tcp.echo;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * tcp echo test, server side with mutil threaad
 * 
 * @author wben
 *
 */
public class EchoServerMultiThread {
	ServerSocket serverSocket;
	private final int PORT = 8080; // 端口

	public EchoServerMultiThread() throws IOException {
		serverSocket = new ServerSocket(PORT); // 创建服务器端套接字
		System.out.println("服务器启动。");
	}

	public static void main(String[] args) throws IOException {
		new EchoServerMultiThread().servic(); // 启动服务
	}

	/**
	 * service implements
	 */
	public void servic() {
		while (true) {
			Socket socket = null;
			try {
				socket = serverSocket.accept();
				Thread work = new Thread(new Handler(socket));
				// 为客户连接创建工作线程
				work.start();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}
}
