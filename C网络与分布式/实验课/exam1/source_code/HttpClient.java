import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.net.Socket;

/**
 * Class <em>HttpClient</em> is a class representing a simple HTTP client.
 *
 * @author Yifei Chu
 * @version 1.0
 */

public class HttpClient {

    /**
     * Response is stored in a byte array.
     */
    private byte[] buffer;

    /**
     * My socket to the world.
     */
    Socket socket = null;

    /**
     * Output stream to the socket.
     */
    BufferedOutputStream ostream = null;

    /**
     * Input stream from the socket.
     */
    BufferedInputStream istream = null;

    /**
     * StringBuffer storing the header
     */
    private StringBuffer header = null;

    /**
     * StringBuffer storing the response.
     */
    private StringBuffer response = null;

    /**
     * String to represent the Carriage Return and Line Feed character sequence.
     */
    static private String CRLF = "\r\n";

    String myMail = "YifeiChu@qq.com";
    /**
     * HttpClient constructor;
     */
    public HttpClient() {
        buffer = new byte[Constant.BUFFERT_SIZE];
        header = new StringBuffer();
        response = new StringBuffer();
    }

    /**
     * <em>connect</em> connects to the input host on the default http port -- port
     * 80. This function opens the socket and creates the input and output streams
     * used for communication.
     */
    public void connect(String host) throws Exception {

        /**
         * Open my socket to the specified host at the default port.
         */
        socket = new Socket(host, Constant.WEB_PORT);

        /**
         * Create the output stream.
         */
        ostream = new BufferedOutputStream(socket.getOutputStream());

        /**
         * Create the input stream.
         */
        istream = new BufferedInputStream(socket.getInputStream());
    }

    /**
     * <em>processGetRequest</em> process the input GET request.
     */
    public void processGetRequest(String request, String host) throws Exception {
        /**
         * Send the request to the server.
         */
        request += Constant.SEQUENCE;

        request += "Host: " + host + Constant.SEQUENCE;
        request += "From: " + myMail + Constant.SEQUENCE;
        request += "Connection: Close" + Constant.SEQUENCE + Constant.SEQUENCE;
        buffer = request.getBytes();
        ostream.write(buffer, 0, request.length());
        ostream.flush();
        /**
         * waiting for the response.
         */
        processResponse();
    }

//	/**
//	 * <em>processPutRequest</em> process the input PUT request.
//	 */
//	public void processPutRequest(String request, String host) throws Exception {
//		// =======start your job here============//
//		String[] reqs = request.split("[\\s+]");
//		File file = null;
//
//		request += CRLF;
//		request += "Host: " + host + CRLF;
//
//		if (reqs.length == 3) {
//			String fileDir = reqs[1];
//			file = new File(pathname + fileDir);
//			if (file.exists()) {
//				request += "Content-length: " + file.length() + CRLF + CRLF;
//			} else {
//				request += "Content-length: 0" + CRLF + CRLF;
//			}
//		} else {
//			request += "Content-length: 0" + CRLF + CRLF;
//		}
//
//		buffer = request.getBytes();
//		ostream.write(buffer, 0, request.length());
//
//		if (file != null && file.exists()) {
//			getFileContent(file);
//		}
//
//		ostream.flush();
//		processResponse();
//		// =======end of your job============//
//	}
//
//	/**
//	 * 获取文件内容
//	 *
//	 * @param file 来自服务器的文件
//	 * @throws Exception
//	 */
//	private void getFileContent(File file) throws Exception {
//		BufferedInputStream bufferedInputStream = new BufferedInputStream(new FileInputStream(file));
//		while ((bufferedInputStream.read(buffer)) > 0) {
//			ostream.write(buffer, 0, buffer.length);
//			buffer = new byte[buffer_size];
//		}
//		bufferedInputStream.close();
//	}

    /**
     * <em>processResponse</em> process the server response.
     *
     */
    public void processResponse() throws Exception {
        int last = 0, c = 0;
        /**
         * Process the header and add it to the header StringBuffer.
         */
        boolean inHeader = true; // loop control
        while (inHeader && ((c = istream.read()) != -1)) {
            switch (c) {
                case '\r':
                    break;
                case '\n':
                    if (c == last) {
                        inHeader = false;
                        break;
                    }
                    last = c;
                    header.append("\n");
                    break;
                default:
                    last = c;
                    header.append((char) c);
            }
        }

        /**
         * Read the contents and add it to the response StringBuffer.
         */
        while (istream.read(buffer) != -1) {
            response.append(new String(buffer, Constant.FORMAT));
        }
    }

    /**
     * Get the response header.
     */
    public String getHeader() {
        return header.toString();
    }

    /**
     * Get the server's response.
     */
    public String getResponse() {
        return response.toString();
    }

    /**
     * Close all open connections -- sockets and streams.
     */
    public void close() throws Exception {
        socket.close();
        istream.close();
        ostream.close();
    }
}

