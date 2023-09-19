import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;

/**
 *
 * @author Yifei Chu
 * @version 1.0
 */
public class Handler implements Runnable {

    /**
     * My socket to the world.
     */
    private Socket socket;
    private ProxyClient proxyClient;

    /**
     * Response is stored in a byte array.
     */
    private byte[] buffer;


    BufferedReader br = null;
    /**
     * Output stream to the socket.
     */
    BufferedOutputStream ostream = null;

    /**
     * 初始化输入输出流
     *
     * @throws IOException
     */
    public void initStream() throws IOException {
        br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        ostream = new BufferedOutputStream(socket.getOutputStream());
    }

    /**
     * 构造函数
     * 单线程用于处理客户端的请求链接
     *
     * @param socket 套接字
     */
    public Handler(Socket socket) {
        this.socket = socket;

        buffer = new byte[Constant.BUFFERT_SIZE];
        this.proxyClient = new ProxyClient();
    }

    @Override
    public void run() {
        try {
            initStream();
            String info = null;

            URL url = null;

            while ((info = br.readLine()) != null) {
                System.out.println("获取Header: " + info);
                if (info.toLowerCase().startsWith("get")) {
                    doGet(info);
                    break;
                } else if (info.toLowerCase().startsWith("from") || info.toLowerCase().startsWith("user-agent")) {
                    continue;
                } else {
                    badRequest();
                    break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (socket != null) {
                try {
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    /**
     * 返回错误400
     *
     * @throws IOException
     */
    private void badRequest() throws IOException {
        String response = "HTTP/1.0 400 Bad Request" + Constant.SEQUENCE + Constant.SEQUENCE;
        buffer = response.getBytes();
        ostream.write(buffer, 0, response.length());
        ostream.flush();
    }

    /**
     * 返回错误404
     *
     * @throws IOException
     */
    private void notFoundRequest() throws IOException {
        String response = "HTTP/1.0 404 Not Found" + Constant.SEQUENCE + Constant.SEQUENCE;
        buffer = response.getBytes();
        ostream.write(buffer, 0, response.length());
        ostream.flush();
    }

    /**
     * 根据请求信息处理get请求
     *
     * @param info 请求报文信息
     * @return doGet执行是否成功
     * @throws Exception
     */
    private boolean doGet(String info) throws Exception {
        URL url = null;

        try{
            String[] orders = info.split("[\\s+]");
//			String[] orders = info.split("/");//相较于“ ”更好的分割方式
            if (!(orders.length == 3)) {
                badRequest();
                return false;
            } else {
                url = new URL(orders[1]);
//				url = new URL('/' + orders[1] + '/' + orders[2]);
                requestGet(url);
                System.out.println("GET:" + url.getHost());
                responseGet();
            }
        } catch (MalformedURLException e){
            badRequest();
        } catch (ConnectException e){
            badRequest();
        } catch (UnknownHostException e){
            notFoundRequest();
        } catch (Exception e) {
            badRequest();
        }

        return true;
    }

    /**
     * 发送get请求
     *
     * @param url 目的url
     * @throws Exception
     */
    private void requestGet(URL url) throws Exception {
        proxyClient.connect(url.getHost(), url.getPort() == -1 ? 80 : url.getPort());
        String request = "GET " + url.getFile() + " HTTP/1.0";
        proxyClient.processGetRequest(request, url.getHost());
    }

    /**
     * 处理get响应报文
     *
     * @throws IOException
     */
    private void responseGet() throws IOException {
        String header = proxyClient.getHeader() + "\n";
        String body = proxyClient.getResponse();

        buffer = header.getBytes();
        ostream.write(buffer, 0, header.length());
        ostream.write(body.getBytes());

        ostream.flush();
    }

}
