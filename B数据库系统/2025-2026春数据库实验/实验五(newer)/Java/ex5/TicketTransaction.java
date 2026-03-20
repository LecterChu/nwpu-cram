package ex5;
import java.io.*;
import java.sql.*;

public class TicketTransaction {

    private static BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
    private static PrintWriter stdOut = new PrintWriter(System.out, true);
    private static PrintWriter stdErr = new PrintWriter(System.err, true);
    private final static String FLIGHT_TITLE = "编号\t航班号\t日期\t目的地\t出发地\t机型\t飞机注册号\t起飞时刻\t到达时刻\t头等舱\t公务舱\t经济舱\t超级经济舱";
    private final static String TAB = "\t";

    public static void main(String[] args) {
        String flightDate = null;
        String flightNo = null;
        String seatType = null;
        int numSeats = 0;
        Connection conn = null;
        Statement stmt = null;
        ResultSet rset = null;

        try {
            // 查询航班列表不需要事务
            conn = JdbcUtilSingle.getInstance().getConnection();
            stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);

            stdOut.println("欢迎来到航空售票系统!");
            stdOut.println("请输入需要查询的日期，格式20250101");
            flightDate = stdIn.readLine();

            // 查询指定日期航班
            String SQLQuery = "SELECT * FROM ticket WHERE date = '" + flightDate + "'";
            rset = stmt.executeQuery(SQLQuery);
            if (!rset.next()) {
                stdOut.println("未查询到指定日期的航班，请重新尝试!");
                return;
            }

            displayFlightInfo(rset);
            flightNo = selectFlightNo(rset);
            seatType = selectSeatType();
            numSeats = inputNum(rset, seatType);

            // --- 开始事务边界：查询席位使用读提交 ---
            conn.setAutoCommit(false); // 手动控制事务
            conn.setTransactionIsolation(Connection.TRANSACTION_READ_COMMITTED); // 设置隔离级别为读提交

            // 再次查询剩余席位
            String seatQuery = "SELECT " + seatType + " FROM ticket WHERE date = '" + flightDate + "' AND flight = '" + flightNo + "'";
            stmt = conn.createStatement();
            rset = stmt.executeQuery(seatQuery);
            rset.next();
            int availableSeats = rset.getInt(seatType);

            conn.commit(); // 提交查询事务
            // --- 结束事务边界 ---

            if (availableSeats < numSeats) {
                stdErr.println("所选席位大于剩余数量！请重试");
                return;
            }

            // --- 开始事务边界：订票使用可重复读 ---
            conn.setAutoCommit(false);
            conn.setTransactionIsolation(Connection.TRANSACTION_REPEATABLE_READ); // 设置隔离级别为可重复读

            // 再次查询剩余席位（确保数据一致性）
            rset = stmt.executeQuery(seatQuery);
            rset.next();
            availableSeats = rset.getInt(seatType);

            if (availableSeats < numSeats) {
                stdErr.println("所选席位大于剩余数量！请重试");
                conn.rollback();
                return;
            }

            // 更新座位数
            String updateSQL = "UPDATE ticket SET " + seatType + " = " + (availableSeats - numSeats) +
                    " WHERE date = '" + flightDate + "' AND flight = '" + flightNo + "'";
            stmt.executeUpdate(updateSQL);
            conn.commit(); // 提交订票事务
            stdOut.println("您的机票已购买，祝出行愉快！");
            // --- 结束事务边界 ---

        } catch (SQLException e) {
            handleException("发生SQL异常！", e, conn);
        } catch (Exception e) {
            handleException("发生非数据库错误！", e, conn);
        } finally {
            JdbcUtilSingle.closeConnection(conn, stmt, rset);
        }
    }

    private static void handleException(String message, Exception e, Connection conn) {
        stdErr.println(message);
        e.printStackTrace();
        try {
            if (conn != null) conn.rollback();
        } catch (SQLException rollbackEx) {
            stdErr.println("事务回滚失败！");
            rollbackEx.printStackTrace();
        }
        stdErr.println("交易已回滚！");
    }

    // 其他辅助方法保持不变...
    private static int inputNum(ResultSet rset, String seatType) throws SQLException, IOException {

        int numSeats;
        while (true) {
            stdOut.println("请输入需要购买的数量：");
            try {
                numSeats = Integer.parseInt(stdIn.readLine());
                if (numSeats < 1) {
                    stdErr.println("请输入大于0的数量！");
                    continue;
                } else break;
            } catch (NumberFormatException e) {
                stdOut.println("请输入合法数字！");
            }

        }
        return numSeats;
    }

    private static String selectFlightNo(ResultSet rset) throws SQLException, IOException {
        String flightNo = null;
        int choice;
        while (true) {
            try {
                stdOut.println("请输入需要购买的航班编号:");
                choice = Integer.parseInt(stdIn.readLine());
                //移动游标
                if (rset.absolute(choice)) {
                    flightNo = rset.getString("flight");
                    break;
                } else {
                    stdErr.println("无效的航班编号!");
                }
            } catch (NumberFormatException e) {
                stdErr.println("请输入合法数字！");
            }

        }
        return flightNo;
    }

    private static String selectSeatType() throws IOException {
        String seatType = null;
        while (true) {
            stdOut.println("请输入需要购买的舱位等级，f：头等舱；c：公务舱；y：经济舱；w：超级经济舱：");
            String type = stdIn.readLine();

            switch (type) {
                case "f":
                    seatType = "f_quantity";
                    break;
                case "c":
                    seatType = "c_quantity";
                    break;
                case "y":
                    seatType = "y_quantity";
                    break;
                case "w":
                    seatType = "w_quantity";
                    break;
                default:
                    stdErr.println("无效的舱位等级，请重新输入！");
            }

            if (seatType == null) continue;
            else break;

        }

        return seatType;
    }

    private static void displayFlightInfo(ResultSet rset) throws SQLException {

        rset.beforeFirst(); // 回到最开始的位置
        stdOut.println(FLIGHT_TITLE);
        while (rset.next()) {
            stdOut.print(rset.getRow());
            stdOut.print(TAB);
            stdOut.print(rset.getString("flight"));
            stdOut.print(TAB);
            stdOut.print(rset.getString("date"));
            stdOut.print(TAB);
            stdOut.print(rset.getString("to_location"));
            stdOut.print(TAB);
            stdOut.print(rset.getString("from_location"));
            stdOut.print(TAB);
            stdOut.print(rset.getString("plane_type"));
            stdOut.print(TAB);
            stdOut.print(rset.getString("registered_number"));
            stdOut.print(TAB);
            stdOut.print(rset.getTime("takeoff"));
            stdOut.print(TAB);
            stdOut.print(rset.getTime("landing"));
            stdOut.print(TAB);
            stdOut.print(rset.getInt("f_quantity"));
            stdOut.print(TAB);
            stdOut.print(rset.getInt("c_quantity"));
            stdOut.print(TAB);
            stdOut.print(rset.getInt("y_quantity"));
            stdOut.print(TAB);
            stdOut.println(rset.getInt("w_quantity"));
        }
    }
}