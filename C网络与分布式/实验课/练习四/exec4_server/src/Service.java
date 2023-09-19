import javax.jws.WebMethod;
import javax.jws.WebService;
import javax.xml.ws.Endpoint;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

@WebService(name = "List", portName = "ListPort", targetNamespace = "http://www.list.com", serviceName = "ListService")
public class Service {

    private Vector<User> users;
    private Vector<TODOList> todoLists;
    SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd-HH:mm");
    private static int ID = 0;

    /**
     * 为维护方便，所有返回信息写在此处
     */
    private static final String CRLF = "\r\n";
    private static final String TAB = "\t";
    private static final String REGISTER_SUCCESS = "注册成功！";
    private static final String REGISTER_FAILURE = "用户名已存在，请选择另一个用户名！";
    private static final String ADD_SUCCESS = "添加待办事项成功！";
    private static final String DELETE_SUCCESS = "删除待办事项成功！";
    private static final String DELETE_FAILURE = "查无该待办事项！";
    private static final String CLEAR_SUCCESS = "清除待办事项成功!";

    private static final String INVALID_TIME = "无效时间!";
    private static final String INVALID_USER = "用户名或密码错误";
    private static final String INVALID_TIME_FORMAT = "无效时间格式! (yyyy-MM-dd-HH:mm)";

    public Service() {
        users = new Vector<>();
        todoLists = new Vector<>();
    }

    /**
     * 用户注册
     *
     * @param username 用户名
     * @param password 用户密码
     * @return 注册信息
     */
    @WebMethod
    public String register(String username, String password) {

        /*
        判断用户是否存在
         */
        if (isUserExist(username)) {
            System.out.println(REGISTER_FAILURE);
            return REGISTER_FAILURE;
        }
        User user = new User(username, password);
        users.add(user);
        System.out.println(user.toString() + REGISTER_SUCCESS);
        return REGISTER_SUCCESS;
    }

    /**
     * 添加待办事项
     *
     * @param username 用户名
     * @param password 用户密码
     * @param start    待办事项开始时间
     * @param end      待办事项结束时间
     * @param tag      待办事项标签
     * @return 添加信息
     */
    @WebMethod
    public String add(String username, String password, String start, String end, String tag) {

        /*
        判断用户正确性
         */
        if (!isUserCorrect(username, password)) {
            System.err.println(INVALID_USER);
            return INVALID_USER;
        }

        Date startDate;
        Date endDate;

        /*
        生成格式化日期
         */
        try{
            startDate = simpleDateFormat.parse(start);
            endDate = simpleDateFormat.parse(end);
            if (isReversed(startDate, endDate)){
                System.err.println(INVALID_TIME);
                return INVALID_TIME;
            }
        } catch (ParseException e) {
            e.printStackTrace();
            System.err.println(INVALID_TIME_FORMAT);
            return INVALID_TIME_FORMAT;
        }

        TODOList todoList = new TODOList(ID++, username, tag, startDate, endDate);
        todoLists.add(todoList);
        System.out.println(ADD_SUCCESS);
        return ADD_SUCCESS;
    }

    /**
     * 查询待办事项
     *
     * @param username 用户名
     * @param password 密码
     * @param start    待办事项开始时间
     * @param end      待办事项结束时间
     * @return 查询信息
     */
    @WebMethod
    public String query(String username, String password, String start, String end) {
        /*
        判断用户正确性
         */
        if (!isUserCorrect(username, password)) {
            System.err.println(INVALID_USER);
            return INVALID_USER;
        }

        Date startDate;
        Date endDate;

        /*
        生成格式化日期
         */
        try{
            startDate = simpleDateFormat.parse(start);
            endDate = simpleDateFormat.parse(end);
            if (isReversed(startDate, endDate)){
                System.err.println(INVALID_TIME);
                return INVALID_TIME;
            }
        } catch (ParseException e) {
            e.printStackTrace();
            System.err.println(INVALID_TIME_FORMAT);
            return INVALID_TIME_FORMAT;
        }

        /*
        查询信息
         */
        String info = "";
        for (TODOList todoList : todoLists) {
            if (todoList.getUsername().equals(username) && isBetween(todoList.getStart(), startDate, endDate)
                    && isBetween(todoList.getEnd(), startDate, endDate)){//完全符合条件
                info += "ID: " + todoList.getID() + TAB;
                info += "Start: " + todoList.getStart() + TAB;
                info += "End: " + todoList.getEnd() + TAB;
                info += "Tag: " + todoList.getTag() + TAB;
                info += CRLF;
            }
        }
        return info;
    }

    /**
     * 删除待办事项
     *
     * @param username 用户名
     * @param password 密码
     * @param ID       待办事项ID
     * @return 删除信息
     */
    @WebMethod
    public String delete(String username, String password, int ID) {
        /*
        判断用户正确性
         */
        if (!isUserCorrect(username, password)) {
            System.err.println(INVALID_USER);
            return INVALID_USER;
        }

        /*
        删除待办事项
         */
        for (TODOList todoList : todoLists) {
            if (todoList.getUsername().equals(username) && todoList.getID() == ID) {//有符合条件的待办事项
                todoLists.remove(todoList);
                System.out.println(DELETE_SUCCESS);
                return DELETE_SUCCESS;
            }
        }
        System.err.println(DELETE_FAILURE);
        return DELETE_FAILURE;
    }

    /**
     * 清空待办事项
     *
     * @param username 用户名
     * @param password 密码
     * @return 清空信息
     */
    @WebMethod
    public String clear(String username, String password) {
        /*
        判断用户正确性
         */
        if (!isUserCorrect(username, password)) {
            System.err.println(INVALID_USER);
            return INVALID_USER;
        }

        /*
        清除待办事项
         */
        for (TODOList todoList : todoLists) {
            if (todoList.getUsername().equals(username)){
                todoLists.remove(todoList);
            }
        }
        System.out.println(CLEAR_SUCCESS);
        return CLEAR_SUCCESS;
    }

    public static void main(String[] args) {
        Endpoint.publish("http://127.0.0.1:8001/webservice/todoList", new Service());
        //wsimport -keep http://127.0.0.1:8001/webservice/todoList?wsdl
        System.out.println("服务开始");
    }

    /**
     * 判断时间是否颠倒
     *
     * @param former 开始时间
     * @param latter 结束时间
     * @return 是否颠倒
     */
    private boolean isReversed(Date former, Date latter){
        return former.after(latter);
    }

    /**
     * 判断date是否在时间段[former latter]内
     *
     * @param date   时间
     * @param former 起始时间
     * @param latter 结束时间
     * @return 是否在时间段中
     */
    private boolean isBetween(Date date, Date former, Date latter) {
        boolean isBetween = (date.after(former) && date.before(latter))
                || date.equals(former) || date.equals(latter);
        return isBetween;
    }

    /**
     * 判断用户是否正确
     *
     * @param username 用户名
     * @param password 用户密码
     * @return 用户是否正确
     */
    private boolean isUserCorrect(String username, String password) {
        User currentUser = new User(username, password);
        for (User user : users) {
            if (currentUser.equals(user)) {
                return true;
            }
        }
        return false;
    }

    /**
     * 判断用户是否存在
     *
     * @param username 用户名
     * @return 是否存在
     */
    private boolean isUserExist(String username) {
        for (User user : users) {
            if (user.getName().equals(username)) {
                return true;
            }
        }
        return false;
    }
}
