package ssd8.socket.udp.echo;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.SocketException;
import java.util.Scanner;

/**
 * udp test, echo client
 * 
 * @author wben
 *
 */
public class EchoClient {
	int remotePort = 8888; // 服务器端口
	String remoteIp = "127.0.0.1"; // 服务器IP
	DatagramSocket socket; // 客户端DatagramSocket

	public EchoClient() throws SocketException {
		socket = new DatagramSocket(); // 随机可用端口，又称匿名端口
	}
	
	public static void main(String[] args) throws SocketException, IOException {
		new EchoClient().send();
	}

	public void send() throws IOException {
		Scanner in = new Scanner(System.in);
		SocketAddress socketAddres = new InetSocketAddress(remoteIp, remotePort);
		// 服务器端地址
		while (true) {
			String s = in.next(); // 获取用户输入
			byte[] info = s.getBytes();
			// 创建数据包，指定服务器地址
			DatagramPacket dp = new DatagramPacket(info, info.length,
					socketAddres);
			socket.send(dp); // 向服务器端发送数据包
			DatagramPacket inputDp = new DatagramPacket(new byte[512], 512);
			socket.receive(inputDp); // 接受服务器返回的信息
			String msg = new String(inputDp.getData(), 0, inputDp.getLength());
			System.out.println(msg);
			if (s.equals("quit")) {
				break;
			}
		}
		socket.close();
	}
}
