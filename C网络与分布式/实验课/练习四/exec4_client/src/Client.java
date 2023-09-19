import com.list.List;
import com.list.ListService;

import java.util.Scanner;

/**
 * WebService 客户端
 *
 * @author 楚逸飞
 * @version 1.0
 */
public class Client {

    private static Scanner scanner = new Scanner(System.in);

    /**
     * 为维护方便，所有操作结果信息写在此处
     */
    private static final String WRONG_PARAMETER = "参数错误!";
    private static final String TIME_FORMAT = "时间格式：yyyy-MM-dd-HH:mm";

    private static ListService listService = new ListService();
    private static List service = listService.getListPort();

    public static void main(String[] args) {
        helpMenu();

        while (true) {
            String line = scanner.nextLine();
            int choice = Integer.parseInt(line);
            service(choice);
            System.out.println("请输入一个操作：");
        }
    }

    private static void service(int choice) {
        switch (choice) {
            case 1:
                register();
                break;
            case 2:
                add();
                break;
            case 3:
                query();
                break;
            case 4:
                delete();
                break;
            case 5:
                clear();
                break;
            case 6:
                helpMenu();
                break;
            case 7:
                System.exit(0);
            default:
                System.err.println(WRONG_PARAMETER);
        }
    }

    private static void helpMenu() {
        System.out.println("帮助菜单:");
        System.out.println(TIME_FORMAT);
        System.out.println("\t 1.用户注册");
        System.out.println("\t\t 参数: <username> <password>");
        System.out.println("\t 2.添加待办事项");
        System.out.println("\t\t 参数: <username> <password> <start> <end> <tag>");
        System.out.println("\t 3.查询待办事项");
        System.out.println("\t\t 参数: <username> <password> <start> <end>");
        System.out.println("\t 4.删除待办事项");
        System.out.println("\t\t 参数: <username> <password> <ID>");
        System.out.println("\t 5.清空待办事项");
        System.out.println("\t\t 参数: <username> <password>");
        System.out.println("\t 6.帮助菜单");
        System.out.println("\t\t 参数: no args");
        System.out.println("\t 7.退出");
        System.out.println("\t\t 参数: no args");
        System.out.println("请输入一个操作：");
    }

    private static void register() {
        System.out.println("请输入参数：<username> <password>");
        String line = scanner.nextLine();
        String[] cmds = line.split(" ");

        if (cmds.length != 2) {
            System.out.println(WRONG_PARAMETER);
        } else {
            System.out.println(service.register(cmds[0], cmds[1]));
        }
    }

    private static void add() {
        System.out.println("请输入参数：<username> <password> <start> <end> <tag>");
        String line = scanner.nextLine();
        String[] cmds = line.split(" ");

        if (cmds.length != 5) {
            System.out.println(WRONG_PARAMETER);
        } else {
            System.out.println(service.add(cmds[0], cmds[1], cmds[2], cmds[3], cmds[4]));
        }
    }

    private static void query() {
        System.out.println("请输入参数：<username> <password> <start> <end>");
        String line = scanner.nextLine();
        String[] cmds = line.split(" ");

        if (cmds.length != 4) {
            System.out.println(WRONG_PARAMETER);
        } else {
            System.out.println(service.query(cmds[0], cmds[1], cmds[2], cmds[3]));
        }
    }

    private static void delete() {
        System.out.println("请输入参数：<username> <password> <ID>");
        String line = scanner.nextLine();
        String[] cmds = line.split(" ");

        if (cmds.length != 3) {
            System.out.println(WRONG_PARAMETER);
        } else {
            System.out.println(service.delete(cmds[0], cmds[1], Integer.parseInt(cmds[2])));
        }
    }

    private static void clear() {
        System.out.println("请输入参数：<username> <password>");
        String line = scanner.nextLine();
        String[] cmds = line.split(" ");

        if (cmds.length != 2) {
            System.out.println(WRONG_PARAMETER);
        } else {
            System.out.println(service.clear(cmds[0], cmds[1]));
        }
    }
}
