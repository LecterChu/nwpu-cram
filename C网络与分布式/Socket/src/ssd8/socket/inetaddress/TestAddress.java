package ssd8.socket.inetaddress;

import java.net.InetAddress;

public class TestAddress {
	public static void main(String[] args) throws Exception {
		InetAddress ia = InetAddress.getLocalHost(); //获得本机IP地址情况
		System.out.println(ia.getHostName()); //得到主机名
		System.out.println(ia.getHostAddress()); //得到主机地址

		InetAddress ia2 = InetAddress.getByName("wben-T420s"); //通过主机名获得信息
		System.out.println(ia2.getHostAddress());

		InetAddress ia3 = InetAddress.getByName("www.nwpu.edu.cn"); //根据域名到DNS查询IP
		System.out.println("163 IP:" + ia3.getHostAddress());

		InetAddress ia4 = InetAddress.getByAddress(new byte[] { (byte) 192,
				(byte) 168, 0, 86 }); //通过主机IP获得信息
		System.out.println(ia4.getHostName());

	}
}
