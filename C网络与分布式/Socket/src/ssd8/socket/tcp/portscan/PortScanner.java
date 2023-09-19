package ssd8.socket.tcp.portscan;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

public class PortScanner {
	public static void main(String[] args) {
		String host = "127.0.0.1"; //要扫描的主机
		int scope = 1024; //要扫描的端口范围
		PortScanner.scan(host, scope); //开始扫描
	}

	public static void scan(String host, int scope) {
		if (scope <= 0 || scope > 65535) {
			System.out.println("端口必须在0-65536之间");
			return;
		}
		Socket socket = null;
		for (int port = 1; port < scope; port++) {
			try {
				socket = new Socket(host, port);
				System.out.println("端口：" + port + "，被占用。");
			} catch (UnknownHostException e) {
				System.out.println("主机无法识别！");
			} catch (IOException e) {
				System.out.println("端口：" + port + "不能连接！");
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

}
