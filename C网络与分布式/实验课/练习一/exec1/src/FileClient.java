import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

/**
 * 客户端 发送ls cd get bye四种请求
 *
 * @author 楚逸飞
 * @version 1.2
 */

public class FileClient {
    static final int PORT = 2021; // tcp连接端口
    static final String HOST = "127.0.0.1"; // IP
    public static byte[] receiveByte; // 接收数据的缓冲
    public static DatagramPacket dataPacket; // DatagramPacket
    public static DatagramSocket dataSocket; // 用于传输数据
    Socket socket;// 用于传输指令的socket
    /*构造函数*/
    public FileClient() throws UnknownHostException, IOException {
        socket = new Socket();
        socket.connect(new InetSocketAddress(HOST, PORT));
    }
    /*主函数入口*/
    public static void main(String[] args) throws UnknownHostException, IOException {
        new FileClient().send();
    }

    /**
     * send 发送连接请求
     */
    public void send() {
        try {
            // 客户端输出流，用于发送
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            // 客户端输入流，用于接收
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter pw = new PrintWriter(bw, true); // 装饰输出流，及时刷新
            Scanner in = new Scanner(System.in); // 接受用户信息，输入待处理
            String msg = null;
            dataSocket = new DatagramSocket(); // 创建实例
            System.out.println(br.readLine());
            while (true) {// 进入等待指令的循环过程
                System.out.print(">");
                msg = in.nextLine();
                String[] strs = msg.split(" ");
                if (msg.equals("bye")) {
                    pw.println(msg);
                    break; // 退出
                } else if (strs[0].equals("get")) {
                    pw.println(msg + " " + dataSocket.getLocalPort()); // 发送给服务器端
                    String str = br.readLine();
                    if (str.equals("文件不存在")||str.equals("请指定文件")) {
                        System.out.println(str);
                        continue;
                    }
                    System.out.println(str);
                    DataOutputStream fileOut = new DataOutputStream(
                            new BufferedOutputStream(new FileOutputStream("./" + strs[1])));
                    int i = 0;
                    while (i == 0) {// 当没有数据，循环
                        receiveByte = new byte[1024];// 设置缓冲区大小为1024
                        dataPacket = new DatagramPacket(receiveByte, receiveByte.length);
                        dataSocket.receive(dataPacket);
                        i = dataPacket.getLength();
                        // 接收数据
                        if (i > 0) {
                            // 欲正常显示接受数据，需要指定数据的长度
                            fileOut.write(receiveByte, 0, i);
                            fileOut.flush();
                            i = 0;// 循环接收
                        }
                        if (new String(dataPacket.getData(), 0, dataPacket.getLength()).equals("end")) {
                            System.out.println("文件接收完毕");
                            fileOut.close();
                            break;
                        }
                    }
                } else if (strs[0].equals("cd") || strs[0].equals("ls")) {
                    pw.println(msg); // 发送给服务器端
                    String str = null;
                    str = br.readLine();
                    /* 根据输入的命令判断所执行的内容 */
                    if (str.equals("已在根目录下")||str.equals("目录不存在")||str.equals("未指定文件或未正确输入返回命令")) {
                        System.out.println(str);
                        continue;
                    }
                    if (str.equals("")) {
                        System.out.println("空目录");
                        continue;
                    }
                    if (strs[0].equals("ls")) {
                        String[] filenames = str.split("&CYF"); //用&CYF来识别换行
                        String[] names = null;
                        // 输出服务器返回的消息
                        System.out.printf("%-8s%-15s%-25s\n", "TYPE", "NAME", "SIZE");
                        for (int i = 0; i < filenames.length; i++) {
                            names = filenames[i].split("\\s");
                            System.out.printf("%-8s%-15s%-25s\n", names[0], names[1], names[2]);
                        }
                    }
                    if (strs[0].equals("cd")) {
                        System.out.println(str);
                    }
                } else {
                    /* 无法解析输入的命令 */
                    System.out.println("未知命令\n仅支持:cd ls get bye");
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (null != socket) {
                try {
                    socket.close(); // 断开连接
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
