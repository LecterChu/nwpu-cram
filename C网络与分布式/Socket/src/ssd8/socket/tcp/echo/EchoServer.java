package ssd8.socket.tcp.echo;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * tcp echo test, server side
 * 
 * @author wben
 *
 */
public class EchoServer {
	ServerSocket serverSocket;
	private final int PORT = 8080; //端口

	public EchoServer() throws IOException {
		serverSocket = new ServerSocket(PORT, 2); // 创建服务器端套接字
		serverSocket.setSoTimeout(3000);
		System.out.println("服务器启动。");
	}

	public static void main(String[] args) throws IOException {
		new EchoServer().servic(); // 启动服务
	}
	
	/**
	 * service implements
	 */
	public void servic() {
		Socket socket = null;
		while (true) {
			try {
				socket = serverSocket.accept(); //等待并取出用户连接，并创建套接字
				System.out.println("新连接，连接地址：" + socket.getInetAddress() + "："
						+ socket.getPort()); //客户端信息
				//输入流，读取客户端信息
				BufferedReader br = new BufferedReader(new InputStreamReader(
						socket.getInputStream()));
				//输出流，向客户端写信息
				BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(
						socket.getOutputStream()));
				PrintWriter pw = new PrintWriter(bw, true); //装饰输出流，true,每写一行就刷新输出缓冲区，不用flush
				String info = null; //接收用户输入的信息
				while ((info = br.readLine()) != null) {
					System.out.println(info); //输出用户发送的消息
					pw.println("you said:" + info); //向客户端返回用户发送的消息，println输出完后会自动刷新缓冲区
					if (info.equals("quit")) { //如果用户输入“quit”就退出
						break;
					}
				}
			} //如果客户端断开连接，则应捕获该异常，但不应中断整个while循环，使得服务器能继续与其他客户端通信 
			catch (IOException e) {
				e.printStackTrace();
			} finally {
				if (null != socket) {
					try {
						socket.close(); //断开连接
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
		}
	}
}
