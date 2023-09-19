import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Inet4Address;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Date;
import java.util.concurrent.TimeUnit;

/**
 * 服务器端的对于四种请求的处理方式 实现Runnable
 *
 * @author 楚逸飞
 * @version 1.2
 */

public class Handler implements Runnable {
    ServerSocket serverSocket;// ServerSocket
    private Socket socket;// Socket
    public static DatagramPacket dataPacket;// DatagramPacket
    public static DatagramSocket dataSocket;// DatagramSocket用于传输数据
    public static byte[] sendDataByte;// 发送数据的缓冲区
    static final String HOST = "127.0.0.1"; // 连接地址
    String filePath;// 目录地址

    /**
     * 构造函数
     * 单线程用于处理客户端的请求链接
     *
     * @param socket 套接字
     * @param filePath 根目录位置
     */
    public Handler(Socket socket, String filePath) {
        this.socket = socket;
        this.filePath = filePath;
    }

    /**
     * 单个线程处理的内容
     */
    public void run() {
        try {
            String filePath = this.filePath;
            String reInfo = socket.getInetAddress() + ":" + socket.getPort() + ">连接成功 ";
            System.out.println(reInfo);// 输出连接成功的信息
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            // 输出流，向客户端写信息
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            PrintWriter pw = new PrintWriter(bw, true); // 装饰输出流，true,每写一行就刷新输出缓冲区，不用flush
            pw.println(reInfo);
            String[] strArray = null;// 用于存放信息
            dataSocket = new DatagramSocket();// 用于处理文件传输
            while ((strArray = br.readLine().split(" ")) != null) {
                System.out.println(strArray[0]); // 输出用户发送的消息
                if (strArray[0].equals("ls")) {
                    System.out.println(filePath);
                    pw.println(getFiles(filePath)); // 向客户端返回用户发送的消息，println输出完后会自动刷新缓冲区
                }
                // 处理cd命令
                if (strArray[0].equals("cd")) {
                    if (strArray.length < 2) {
                        pw.println("未指定文件或未正确输入返回命令");
                        continue;
                    }
                    // 处理返回上级目录
                    if (strArray[1].equals("..")) {
                        if (filePath.equals(this.filePath)) {
                            pw.println("已经在根目录下 >  OK");
                            //pw.println(filePath + " >  OK");
                            continue;
                        } else {
                            System.out.println("退回上一级");
                            filePath = filePath.substring(0, filePath.lastIndexOf("\\"));
                            filePath = filePath.substring(0, filePath.lastIndexOf("\\")) + "\\";
                            pw.println(filePath + " >  OK");
                        }
                    } else {
                        int flag = 0;
                        File root = new File(filePath);
                        File[] files = root.listFiles();
                        for (int i = 0; i < files.length; i++) {
                            if (strArray[1].equals(files[i].getName()) && files[i].isDirectory())
                                flag = 1;
                        }
                        if (flag == 1) {
                            System.out.println("进入" + strArray[1]);
                            filePath = filePath + strArray[1] + "\\";
                            System.out.println(filePath);
                            pw.println(filePath + " >  OK");
                        } else {
                            System.out.println("不存在");
                            pw.println("目录不存在");
                        }
                    }
                }
                // 处理get命令
                if (strArray[0].equals("get")) {
                    if (strArray.length < 3) {
                        pw.println("请指定文件");
                        continue;
                    }
                    int flag = 0;
                    File root = new File(filePath);
                    File[] files = root.listFiles();
                    for (int i = 0; i < files.length; i++) {
                        if (strArray[1].equals(files[i].getName()) && !files[i].isDirectory())
                            flag = 1;
                    }
                    String filename = strArray[1];
                    if (flag != 1) {
                        System.out.println("不存在");
                        pw.println("文件不存在");
                        continue;
                    } else {
                        pw.println("开始传输" + filename);// 开始传输
                        // 获取端口号
                        int port = Integer.parseInt(strArray[2]);
                        String sendfilePath = filePath + "\\" + filename;
                        // 传输文件
                        DataInputStream fis = new DataInputStream(
                                new BufferedInputStream(new FileInputStream(sendfilePath)));
                        sendDataByte = new byte[1024];//缓冲区大小设置为1024
                        int read = 0;
                        long a = new Date().getTime();
                        while (true) {
                            if (fis != null) {
                                read = fis.read(sendDataByte);
                            }
                            if (read == -1) {// 传输结束
                                sendDataByte = "end".getBytes();
                                DatagramPacket endPkg = new DatagramPacket(sendDataByte, sendDataByte.length,
                                        (Inet4Address) Inet4Address.getByName("localhost"), port);
                                System.out.print("用时：");
                                System.out.println(new Date().getTime() - a);
                                dataSocket.send(endPkg);
                                break;
                            }
                            dataPacket = new DatagramPacket(sendDataByte, sendDataByte.length,
                                    (Inet4Address) Inet4Address.getByName("localhost"), port);
                            dataSocket.send(dataPacket);
                            TimeUnit.MICROSECONDS.sleep(1);// 限制传输速度
                        }
                    }
                }
                if (strArray[0].equals("bye")) { // 如果用户输入“bye”就退出
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
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

    /* 存放文件目录信息 */
    private static ArrayList<String> filelist = new ArrayList<String>();

    /**
     * 获取指定路径下的文件
     *
     * @param filePath 指定的文件夹目录
     * @return 返回指定文件夹下的信息
     */
    static String getFiles(String filePath) {
        String str = "";
        File root = new File(filePath);
        File[] files = root.listFiles();
        for (File file : files) {
            if (file.isDirectory()) {// 判断是否为文件还是文件目录
                /*
                 * 递归调用
                 */
                getFiles(file.getPath());
                filelist.add(file.getPath());
                str = str + "<dir> " + file.getName() + " " + file.length() + "&CYF";
            } else {
                str = str + "<file> " + file.getName() + " " + file.length() + "&CYF";
            }
        }
        return str;
    }
}
