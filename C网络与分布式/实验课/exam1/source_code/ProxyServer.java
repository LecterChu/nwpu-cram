import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 *
 * @author Yifei Chu
 * @version 1.0
 */
public class ProxyServer {

    ServerSocket serverSocket;
    ExecutorService executorService; //线程池

    public ProxyServer() throws IOException {
        serverSocket = new ServerSocket(Constant.WEB_PORT);
        executorService = Executors.newFixedThreadPool(Runtime.getRuntime().
                availableProcessors() * Constant.POOLSIZE);
        System.out.println("服务器启动，端口号"+Constant.WEB_PORT);
    }

    /**
     * service 函数实现
     *
     * @return void
     */
    public void service(){
        while (true) {
            try {
                Socket socket = serverSocket.accept();
                executorService.execute(new Handler(socket));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String args[]) throws IOException{
        new ProxyServer().service();
    }
}

