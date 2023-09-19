package ssd8.socket.tcp.echo;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * work thread
 * 
 * @author wben
 *
 */
public class Handler implements Runnable { // 负责与单个客户通信的线程
	private Socket socket;
	BufferedReader br;
	BufferedWriter bw;
	PrintWriter pw;

	public Handler(Socket socket) {
		this.socket = socket;
	}

	public void initStream() throws IOException { // 初始化输入输出流对象方法
		br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		bw = new BufferedWriter(
				new OutputStreamWriter(socket.getOutputStream()));
		pw = new PrintWriter(bw, true);
	}

	public void run() { // 执行的内容
		try {
			System.out.println("新连接，连接地址：" + socket.getInetAddress() + "："
					+ socket.getPort()); //客户端信息
			initStream(); // 初始化输入输出流对象
			String info = null;
			while (null != (info = br.readLine())) {
				System.out.println(info);
				pw.println("you said:" + info); // 返回用户发送的消息
				if (info.equals("quit")) { // 如果用户输入“quit”就退出
					break;
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (null != socket) {
				try {
					socket.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}
}
