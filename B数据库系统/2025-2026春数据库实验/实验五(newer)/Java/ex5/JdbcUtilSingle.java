package ex5;

import java.sql.*;

public class JdbcUtilSingle {
	private static final String URL = "jdbc:postgresql://localhost:5432/Five";
	private static final String USER = "postgres";
	private static final String PASSWORD = "postgres";
	private static Connection connection;
	private static boolean closed = false;

	public static synchronized JdbcUtilSingle getInstance() throws SQLException {
		if ((connection == null) || closed) {
			connection = DriverManager.getConnection(URL, USER, PASSWORD);
			closed = false;
		}
		return new JdbcUtilSingle();
	}

	public Connection getConnection() {
		return connection;
	}

	public static void closeConnection(Connection conn, Statement stmt, ResultSet rset) {
		try {
			if (rset != null) {
				rset.close();
			}
			if (stmt != null) {
				stmt.close();
			}
			if (conn != null) {
				conn.close();
				closed = true;
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
}