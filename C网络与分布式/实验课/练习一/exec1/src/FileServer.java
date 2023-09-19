import java.io.File;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 *服务器 使用工厂类Executors里的FixedThreadPools实现ExecutorService这一API接口建立一个线程池管理线程
 *
 * @author 楚逸飞
 * @version 1.2
 */

public class FileServer {
    ServerSocket serverSocket;//ServerSocket
    private final int PORT = 2021; // TCP端口 负责与用户链接
    int port = 2020; // UDP端口号 负责传送文件
    public static DatagramPacket dataPacket;
    public static DatagramSocket dataSocket;
    public static byte[] sendDataByte; // 发送缓存
    static final String HOST = "127.0.0.1"; // 服务器地址
    String filePath;// 根目录路径
    final int POOL_SIZE = 4;
    ExecutorService executorService;

    public FileServer(String filePath) throws IOException {
        serverSocket = new ServerSocket(PORT);
        this.filePath = filePath;
        executorService = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors()*POOL_SIZE);
        System.out.println("服务器启动。");
    }

    /* main函数入口 */
    public static void main(String[] args) throws IOException, InterruptedException {
        if (args.length != 1) {
            System.out.println("usage: java FileServer <dir>");// 没有输入路径信息则会提示用法
            return;
        }
        String filePath = args[0];
        File file = new File(filePath);
        /* 校验该目录是否有效 */
        if (!file.isDirectory()) {
            System.out.println("无效路径");
            return;
        }
        new FileServer(filePath).servic(); // 启动服务
        return;
    }

    /**
     * service 函数实现
     *
     * @return void
     * @throws InterruptedException 线程异常
     */
    public void servic() throws InterruptedException {
        Socket socket = null;
        while (true) {
            try {
                socket = serverSocket.accept(); // 等待并取出用户连接，并创建套接字
                executorService.execute((new Handler(socket, filePath)));
            } // 如果客户端断开连接，则应捕获该异常，但不应中断整个while循环，使得服务器能继续与其他客户端通信
            catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
