package com.cochef.util;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Vector;

import com.cochef.mapgen.data.GPSLocation;
import com.cochef.mapgen.data.MapDataCollection;
import com.cochef.mapgen.data.MapRoadSection;
import com.cochef.mapgen.util.GeometryCalcu;

/**
 * @author mcy
 * 
 */
public class Parser {

	private static BusSqlWrite busSqlWriter;
	private static SubSqlWrite subSqlWriter;
	private static ArrayList<GPSLocation> stopLocations;

	public static void main(String[] args) {
		try {
			Parser parser = new Parser();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public Parser() throws Exception {
		busSqlWriter = new BusSqlWrite();
		subSqlWriter = new SubSqlWrite();
		stopLocations = new ArrayList<GPSLocation>();
		String busFolder = "buslineInfo/";// 公交线路信息文件路径
		String subFolder = "sublineInfo/";// 地铁线路信息文件路径
		OutputStreamWriter writerSQL = new OutputStreamWriter(
				new FileOutputStream(new File("insert.sql")), "UTF-8");// 写到sqls——数据库插入文件
		busAssociate(busFolder, writerSQL);
		subAssociate(subFolder, writerSQL);
		writerSQL.close();
	}

	private void subAssociate(String subFolder, OutputStreamWriter writerSQL)
			throws Exception {

		OutputStreamWriter writerHanSub = new OutputStreamWriter(
				new FileOutputStream(new File("HanjingliSub.txt")), "UTF-8");// 写到hanjingli——生成地图用的文件
		OutputStreamWriter writerHan2Sub = new OutputStreamWriter(
				new FileOutputStream(new File("Hanjingli2Sub.txt")), "UTF-8");// 写到hanjingli2——生成地图用的文件
		OutputStreamWriter writerZhengSub = new OutputStreamWriter(
				new FileOutputStream(new File("subline.txt")), "UTF-8");// 写到busline——生成虚拟站点的数据来源文件

		String subFileNames[] = new File(subFolder).list();
		for (int i = 0; i < subFileNames.length; i++) {
			subSqlGen(subFolder + subFileNames[i], writerHanSub, writerHan2Sub,
					writerZhengSub, writerSQL);
		}
		writerHanSub.close();
		writerHan2Sub.close();
		writerZhengSub.close();

		// MapDataCollection data = new MapDataCollection();??
		// subSqlWriter.insertIntosubstop_in_rdsection(data,writerSQL);
	}

	private void busAssociate(String busFolder, OutputStreamWriter writerSQL)
			throws Exception {

		OutputStreamWriter writerHanBus = new OutputStreamWriter(
				new FileOutputStream(new File("HanjingliBus.txt")), "UTF-8");// 写到hanjingli——生成地图用的文件
		OutputStreamWriter writerHan2Bus = new OutputStreamWriter(
				new FileOutputStream(new File("Hanjingli2Bus.txt")), "UTF-8");// 写到hanjingli2——生成地图用的文件
		OutputStreamWriter writerZhengBus = new OutputStreamWriter(
				new FileOutputStream(new File("busline.txt")), "UTF-8");// 写到busline——生成虚拟站点的数据来源文件

		String busFileNames[] = new File(busFolder).list();
		for (int i = 0; i < busFileNames.length; i++) {
			busSqlGen(busFolder + busFileNames[i], writerHanBus, writerHan2Bus,
					writerZhengBus, writerSQL);
		}
		writerHanBus.close();
		writerHan2Bus.close();
		writerZhengBus.close();

		MapDataCollection data = new MapDataCollection();
		busSqlWriter.InsertAbs(data, writerSQL);
	}

	private void subSqlGen(String sourcePath,
			OutputStreamWriter writerHanjingli,
			OutputStreamWriter writerHanjingli2,
			OutputStreamWriter writerZheng, OutputStreamWriter writerSQL)
			throws Exception {

		InputStreamReader read = new InputStreamReader(new FileInputStream(
				new File(sourcePath)), "UTF-8");
		BufferedReader reader = new BufferedReader(read);// 从原始信息文件读取信息的流
		OutputStreamWriter writer = new OutputStreamWriter(
				new FileOutputStream(
						new File("tempfiles/sub/"
								+ sourcePath.substring(sourcePath
										.lastIndexOf("/") + 1))), "UTF-8");// 写到解析用的中间文件

		InputStreamReader read2 = new InputStreamReader(
				new FileInputStream(
						new File("tempfiles/sub/"
								+ sourcePath.substring(sourcePath
										.lastIndexOf("/") + 1))), "UTF-8");// 从中间文件读取信息的流
		BufferedReader reader2 = new BufferedReader(read2);

		String temp = "";

		// 初步规范化内容格式
		if ((temp = reader.readLine()) != null) {

			temp = temp.replace("\",", "\"\n").replace("},", "}\n")
					.replace("],", "]\n").replace(":[", ":\n[")
					.replace("\"xys\":\"", "\"xys\":\"\n").replace(";", "\n");
			writer.write(temp);
		}
		reader.close();
		writer.close();

		boolean xysPassed = false;// 行"xys":"已读标记，用于指示进入拐角xy区域或用于区分都由“name”指示的线路名和站点名
		int xysCounter = 0;
		boolean direction = true;// 上下行，true上行
		boolean pay_way = true;// 能否刷卡,true能刷
		boolean uppay_way = true;
		String total_price = "";// 最大票价，总票价
		String uptotal_price = "";
		String basic_price = "";// 起步价
		String line_id = "";// 线路名称，如916路(东大汽车站--草阳村)
		String line_idUp = "";// 上行线路名称
		String stop_name = "", stop_coord_x = "", stop_coord_y = "";// 站名，坐标
		String stopXYs = "";// 站坐标集合字符串
		String stopNames = "";
		String itsctXYs = "";// 拐角坐标集合字符串
		String itsct_coord_x = "", itsct_coord_y = "";// 拐角坐标
		String start_time = "", end_time = "";// 首末班发车时间
		String firstStopX = "";
		String firstStopY = "";
		String itsctXYsUp = "";// 上行itsctXYs清空时保存上行itsctXYs
		String itsctXYsDown = "";
		String savedDownStopXYs = "";// stopXYs清空时保存stopXYs
		String savedUpStopXYs = "";
		String upStartTime = "", downStartTime = "";// 上下行首班发车时间
		String upEndTime = "", downEndTime = "";// 上下行末班发车时间
		String savedUpStopNames = "";

		while ((temp = reader2.readLine()) != null) {
			// 获取stop.stop_name值
			if (temp.startsWith("\"name\"") && !xysPassed) {
				stop_name = temp.substring(8, temp.length() - 1);
				stopNames += stop_name + " ";
			}
			// 获取stop.stop_coord_x,stop.stop_coord_y值
			if (temp.startsWith("\"xy\"") && !temp.contains("s")) {
				temp = temp.substring(6, temp.length() - 2);
				if (temp.endsWith("\""))// 最后一个站点以"}]结尾，与其他站点的"}结尾相比，从后面截去两个字符后，还多余一个"
					temp = temp.substring(0, temp.length() - 1);
				stop_coord_x = temp.split(",")[0];
				stop_coord_y = temp.split(",")[1];
				stopXYs += stop_coord_x + "," + stop_coord_y + " ";
			}
			if (!stop_name.equals("") && !stop_coord_x.equals("")
					&& !stop_coord_y.equals("")) {
				stop_name = "";// 重置
				stop_coord_x = "";
				stop_coord_y = "";
			}
			if (temp.contains("ic_card")) {
				if (temp.endsWith("0\""))
					pay_way = false;
				else
					pay_way = true;
			}
			if (temp.contains("basic_price")) {
				String s = temp.split(":")[1];
				basic_price = s.substring(1, s.length() - 1);
			}
			if (temp.contains("total_price")) {
				String s = temp.split(":")[1];
				total_price = s.substring(1, s.length() - 1);
			}
			// 进入拐角xy区域
			if (temp.equals("\"xys\":\"")) {
				xysPassed = true;
				xysCounter++;
			}
			// 获取intersection.itsct_coord_x，intersection.itsct_coord_y值
			if (xysPassed && temp.contains(",") && !temp.startsWith("\"xy\"")) {

				itsct_coord_x = temp.split(",")[0];
				itsct_coord_y = temp.split(",")[1];
				if (itsct_coord_y.endsWith("\"")) {
					itsct_coord_y = itsct_coord_y.substring(0,
							itsct_coord_y.length() - 1);
				}
				itsctXYs += itsct_coord_x + "," + itsct_coord_y + " ";
			}
			if (temp.contains("end_time")) {
				end_time = temp.substring(12, temp.length() - 1);
				if (direction) {
					upEndTime = end_time;
				} else {
					downEndTime = end_time;
				}
			}
			// 获取busline.line_id值
			if (temp.startsWith("\"name\"") && xysPassed) {
				line_id = temp.substring(8, temp.length() - 1);
			}
			// 获取busline.summer_first，busline.summer_last,busline.winter_first，busline.winter_last值
			if (temp.contains("start_time")) {
				start_time = temp.substring(14, temp.length() - 1);
				if (direction) {
					upStartTime = start_time;
				} else {
					downStartTime = start_time;
				}
			}
			if (temp.contains("commutation_ticket") && xysPassed) {// 表明这是出现的第二个commutation_ticket,就是上下行转换的时机

				itsctXYsUp += itsctXYs;
				savedUpStopXYs = stopXYs;
				// System.out.println(savedUpStopXYs);
				stopXYs = stopXYs.substring(0, stopXYs.length() - 1);
				savedUpStopNames = stopNames;
				// System.out.println(savedUpStopNames);
				line_idUp = line_id;
				itsctXYsUp = itsctXYs;
				uppay_way = pay_way;
				uptotal_price = total_price;
				direction = false;
				stopXYs = "";
				itsctXYs = "";
				xysPassed = false;
				end_time = "";
				stopNames = "";
			}
			if (temp.contains("version")) {// 表明这是文件的结尾，下行读取完毕
				itsctXYsDown = itsctXYs;
				savedDownStopXYs = stopXYs;
				direction = true;
				start_time = "";
				stopXYs = "";
				itsctXYs = "";
				xysPassed = false;
			}
		}

		// 向Hanjingli.txt中输出上下行原始拐点信息，向Hanjingli2中输出上下行线路名信息
		String up = itsctXYsUp.replace(" ", ";");
		up = up.substring(0, up.length() - 1);
		String down = itsctXYsDown.replace(" ", ";");
		down = down.substring(0, down.length() - 1);
		writerHanjingli.write("\"" + up + "\",\n");
		writerHanjingli.write("\"" + down + "\",\n");
		writerHanjingli2.write(line_idUp + "," + line_id + ",");

		// 向busline.txt中输出上行路线名、初始拐点、初始站点信息
		writerZheng.write(line_idUp + "\n");
		writerZheng.write(up + "\n");
		String stopnames[] = savedUpStopNames.split(" ");
		String stopxys[] = savedUpStopXYs.split(" ");
		for (int i = 0; i < 2 * stopxys.length; i++) {
			if (i % 2 == 0) {
				writerZheng.write(stopnames[i / 2] + ";");
			} else {
				writerZheng.write(stopxys[i / 2] + ";");
			}
		}
		writerZheng.write("\n");

		// 向busline.txt中输出下行路线名、初始拐点、初始站点信息
		writerZheng.write(line_id + "\n");
		writerZheng.write(down + "\n");
		String dstopnames[] = stopNames.split(" ");
		String dstopxys[] = savedDownStopXYs.split(" ");
		for (int i = 0; i < 2 * dstopxys.length; i++) {
			if (i % 2 == 0) {
				writerZheng.write(dstopnames[i / 2] + ";");
			} else {
				writerZheng.write(dstopxys[i / 2] + ";");
			}
		}
		writerZheng.write("\n");

		line_idUp = getLineName(line_idUp);// 截去line_id括号部分
		line_id = getLineName(line_id);// 截去line_id括号部分

		// 向stop表插入上行站点
		String[] stopxy;
		// System.out.println("stopnames size: " + stopnames.length);
		// System.out.println("stopxys size: " + stopxys.length);
		for (int i = 0; i < stopnames.length; i++) {
			stopxy = stopxys[i].split(",");
			GPSLocation newStopLoc = GPSLocation.parseGpsLocation(stopxys[i]);
			if (!stopLocations.contains(newStopLoc)) {
				stopLocations.add(newStopLoc);
				subSqlWriter.insertIntosubway_stop(stopnames[i],
						String.valueOf(newStopLoc.getGPSX()),
						String.valueOf(newStopLoc.getGPSY()), writerSQL);
				writerSQL.flush();
			}
		}
		// 向stop表插入下行站点
		String[] dstopxy;
		for (int i = 0; i < dstopnames.length; i++) {
			dstopxy = dstopxys[i].split(",");
			GPSLocation newStopLoc = GPSLocation.parseGpsLocation(dstopxys[i]);
			if (!stopLocations.contains(newStopLoc)) {
				stopLocations.add(newStopLoc);
				subSqlWriter.insertIntosubway_stop(dstopnames[i],
						String.valueOf(newStopLoc.getGPSX()),
						String.valueOf(newStopLoc.getGPSY()), writerSQL);
				writerSQL.flush();
			}
		}

		// 向busline表插入上行线路
		String[] first = stopxys[0].split(",");
		firstStopX = first[0];
		firstStopY = first[1];
		if (uptotal_price.equals("")) {
			uptotal_price = "1";
		}
		subSqlWriter.insertIntosubway_line(firstStopX, firstStopY, line_idUp,
				true, uppay_way, uptotal_price, upStartTime, upEndTime, up,
				writerSQL);
		writerSQL.flush();
		// 向busline表插入下行线路
		String[] dfirst = dstopxys[0].split(",");
		firstStopX = dfirst[0];
		firstStopY = dfirst[1];
		if (total_price.equals("")) {
			total_price = "1";
		}
		subSqlWriter.insertIntosubway_line(firstStopX, firstStopY, line_id,
				false, pay_way, total_price, downStartTime, downEndTime, down,
				writerSQL);
		writerSQL.flush();

		// 向stop_in_line表插入上行站点（真实站点）与线路的绑定关系
		subSqlWriter.insertIntosubstop_in_line(savedUpStopXYs, line_idUp, true,
				writerSQL);
		writerSQL.flush();
		// 向stop_in_line表插入下行站点（真实站点）与线路的绑定关系
		subSqlWriter.insertIntosubstop_in_line(savedDownStopXYs, line_id,
				false, writerSQL);

		// 向substop_in_rdsection表插入上行站点与路段的映射关系
		subSqlWriter.insertIntosubstop_in_rdsection(stopxys, writerSQL);
		// 向substop_in_rdsection表插入下行站点与路段的映射关系
		subSqlWriter.insertIntosubstop_in_rdsection(dstopxys, writerSQL);

		// 向substop_in_rdsection插入手动点出来的数据

		// 地铁一号线下行与上行
		String subway_1_0 = "108.816737,34.298547;108.83997,34.288376;108.852035,34.284542;"
				+ "108.863198,34.278407;108.871803,34.274121;108.891721,34.269324;108.912642,34.269466;"
				+ "108.92144,34.269581;108.933375,34.269706;108.947141,34.269901;108.962933,34.270025;"
				+ "108.972922,34.27002;108.984246,34.269466;108.995528,34.269502;109.013772,34.269604;"
				+ "109.029173,34.271966;109.044129,34.27393;109.056306,34.275309;109.069433,34.279258";
		String subway_1_1 = "109.069433,34.279258;109.056306,34.275309;109.044129,34.27393;"
				+ "109.029173,34.271966;109.013772,34.269604;108.995528,34.269502;108.984246,34.269466;"
				+ "108.972922,34.27002;108.962933,34.270025;108.947141,34.269901;108.933375,34.269706;"
				+ "108.92144,34.269581;108.912642,34.269466;108.891721,34.269324;108.871803,34.274121;"
				+ "108.863198,34.278407;108.852035,34.284542;108.83997,34.288376;108.816737,34.298547";

		// 地铁三号线下行与上行
		String subway_3_0 = "109.068859,34.399191;109.070029,34.382674;109.065367,34.360208;"
				+ "109.055352,34.340406;109.049612,34.328406;109.03258,34.311061;109.006938,34.310751;"
				+ "108.995576,34.303076;108.995587,34.291323;108.995592,34.277481;108.995528,34.269502;"
				+ "108.996681,34.251155;108.996729,34.242703;108.99395,34.230907;108.976656,34.223628;"
				+ "108.964012,34.222887;108.946685,34.222794;108.931895,34.222892;108.917314,34.225345;"
				+ "108.904327,34.231168;108.888754,34.237249;108.872243,34.237497;108.851547,34.237914";
		String subway_3_1 = "108.851547,34.237914;108.872243,34.237497;108.888754,34.237249;"
				+ "108.904327,34.231168;108.917314,34.225345;108.931895,34.222892;108.946685,34.222794;"
				+ "108.964012,34.222887;108.976656,34.223628;108.99395,34.230907;108.996729,34.242703;"
				+ "108.996681,34.251155;108.995528,34.269502;108.995592,34.277481;108.995587,34.291323;"
				+ "108.995576,34.303076;109.006938,34.310751;109.03258,34.311061;109.049612,34.328406;"
				+ "109.055352,34.340406;109.065367,34.360208;109.070029,34.382674;109.068859,34.399191";
		subSqlWriter.insertIntosubstop_in_rdsection(subway_1_0.split(";"), writerSQL);
		subSqlWriter.insertIntosubstop_in_rdsection(subway_1_1.split(";"), writerSQL);
		subSqlWriter.insertIntosubstop_in_rdsection(subway_3_0.split(";"), writerSQL);
		subSqlWriter.insertIntosubstop_in_rdsection(subway_3_1.split(";"), writerSQL);
		
		writerSQL.flush();

		reader2.close();

		if (xysCounter > 2)
			System.out.println("输入文件" + sourcePath + "的格式不对，xysNum:"
					+ xysCounter);

	}

	/**
	 * 针对线路数据信息文件夹路径下的每个文件，预处理成temp.txt并逐行解析，使用传入的文件输出流输出到sqls.sql
	 * 
	 * @param sourcePath
	 *            单个线路信息文件，如staticGen/prims/916.txt
	 * @param writer2
	 *            输出到sqls.sql的输出流
	 */
	private static void busSqlGen(String sourcePath,
			OutputStreamWriter writerHanjingli,
			OutputStreamWriter writerHanjingli2,
			OutputStreamWriter writerZheng, OutputStreamWriter writerSQL)
			throws Exception {

		InputStreamReader read = new InputStreamReader(new FileInputStream(
				new File(sourcePath)), "UTF-8");
		BufferedReader reader = new BufferedReader(read);// 从原始信息文件读取信息的流
		OutputStreamWriter writer = new OutputStreamWriter(
				new FileOutputStream(
						new File("tempfiles/bus/"
								+ sourcePath.substring(sourcePath
										.lastIndexOf("/") + 1))), "UTF-8");// 写到解析用的中间文件

		InputStreamReader read2 = new InputStreamReader(
				new FileInputStream(
						new File("tempfiles/bus/"
								+ sourcePath.substring(sourcePath
										.lastIndexOf("/") + 1))), "UTF-8");// 从中间文件读取信息的流
		BufferedReader reader2 = new BufferedReader(read2);

		String temp = "";

		// 初步规范化内容格式
		if ((temp = reader.readLine()) != null) {

			temp = temp.replace("\",", "\"\n").replace("},", "}\n")
					.replace("],", "]\n").replace(":[", ":\n[")
					.replace("\"xys\":\"", "\"xys\":\"\n").replace(";", "\n");
			writer.write(temp);
		}
		reader.close();
		writer.close();

		boolean xysPassed = false;// 行"xys":"已读标记，用于指示进入拐角xy区域或用于区分都由“name”指示的线路名和站点名
		int xysCounter = 0;
		boolean direction = true;// 上下行，true上行
		boolean pay_way = true;// 能否刷卡,true能刷
		boolean uppay_way = true;
		String total_price = "";// 最大票价，总票价
		String uptotal_price = "";
		String basic_price = "";// 起步价
		String line_id = "";// 线路名称，如916路(东大汽车站--草阳村)
		String line_idUp = "";// 上行线路名称
		String stop_name = "", stop_coord_x = "", stop_coord_y = "";// 站名，坐标
		String stopXYs = "";// 站坐标集合字符串
		String stopNames = "";
		String itsctXYs = "";// 拐角坐标集合字符串
		String itsct_coord_x = "", itsct_coord_y = "";// 拐角坐标
		String start_time = "", end_time = "";// 首末班发车时间
		String firstStopX = "";
		String firstStopY = "";
		String itsctXYsUp = "";// 上行itsctXYs清空时保存上行itsctXYs
		String itsctXYsDown = "";
		String savedDownStopXYs = "";// stopXYs清空时保存stopXYs
		String savedUpStopXYs = "";
		String upStartTime = "", downStartTime = "";// 上下行首班发车时间
		String upEndTime = "", downEndTime = "";// 上下行末班发车时间
		String savedUpStopNames = "";

		while ((temp = reader2.readLine()) != null) {
			// 获取stop.stop_name值
			if (temp.startsWith("\"name\"") && !xysPassed) {
				stop_name = temp.substring(8, temp.length() - 1);
				stopNames += stop_name + " ";
			}
			// 获取stop.stop_coord_x,stop.stop_coord_y值
			if (temp.startsWith("\"xy\"") && !temp.contains("s")) {
				temp = temp.substring(6, temp.length() - 2);
				if (temp.endsWith("\""))// 最后一个站点以"}]结尾，与其他站点的"}结尾相比，从后面截去两个字符后，还多余一个"
					temp = temp.substring(0, temp.length() - 1);
				stop_coord_x = temp.split(",")[0];
				stop_coord_y = temp.split(",")[1];
				stopXYs += stop_coord_x + "," + stop_coord_y + " ";
			}
			if (!stop_name.equals("") && !stop_coord_x.equals("")
					&& !stop_coord_y.equals("")) {
				stop_name = "";// 重置
				stop_coord_x = "";
				stop_coord_y = "";
			}
			if (temp.contains("ic_card")) {
				if (temp.endsWith("0\""))
					pay_way = false;
				else
					pay_way = true;
			}
			if (temp.contains("basic_price")) {
				String s = temp.split(":")[1];
				basic_price = s.substring(1, s.length() - 1);
			}
			if (temp.contains("total_price")) {
				String s = temp.split(":")[1];
				total_price = s.substring(1, s.length() - 1);
			}
			// 进入拐角xy区域
			if (temp.equals("\"xys\":\"")) {
				xysPassed = true;
				xysCounter++;
			}
			// 获取intersection.itsct_coord_x，intersection.itsct_coord_y值
			if (xysPassed && temp.contains(",") && !temp.startsWith("\"xy\"")) {

				itsct_coord_x = temp.split(",")[0];
				itsct_coord_y = temp.split(",")[1];
				if (itsct_coord_y.endsWith("\"")) {
					itsct_coord_y = itsct_coord_y.substring(0,
							itsct_coord_y.length() - 1);
				}
				itsctXYs += itsct_coord_x + "," + itsct_coord_y + " ";
			}
			if (temp.contains("end_time")) {
				end_time = temp.substring(12, temp.length() - 1);
				if (direction) {
					upEndTime = end_time;
				} else {
					downEndTime = end_time;
				}
			}
			// 获取busline.line_id值
			if (temp.startsWith("\"name\"") && xysPassed) {
				line_id = temp.substring(8, temp.length() - 1);
			}
			// 获取busline.summer_first，busline.summer_last,busline.winter_first，busline.winter_last值
			if (temp.contains("start_time")) {
				start_time = temp.substring(14, temp.length() - 1);
				if (direction) {
					upStartTime = start_time;
				} else {
					downStartTime = start_time;
				}
			}
			if (temp.contains("commutation_ticket") && xysPassed) {// 表明这是出现的第二个commutation_ticket,就是上下行转换的时机

				itsctXYsUp += itsctXYs;
				savedUpStopXYs = stopXYs;
				// System.out.println(savedUpStopXYs);
				stopXYs = stopXYs.substring(0, stopXYs.length() - 1);
				savedUpStopNames = stopNames;
				// System.out.println(savedUpStopNames);
				line_idUp = line_id;
				itsctXYsUp = itsctXYs;
				uppay_way = pay_way;
				uptotal_price = total_price;
				direction = false;
				stopXYs = "";
				itsctXYs = "";
				xysPassed = false;
				end_time = "";
				stopNames = "";
			}
			if (temp.contains("version")) {// 表明这是文件的结尾，下行读取完毕
				itsctXYsDown = itsctXYs;
				savedDownStopXYs = stopXYs;
				direction = true;
				start_time = "";
				stopXYs = "";
				itsctXYs = "";
				xysPassed = false;
			}
		}

		// 向Hanjingli.txt中输出上下行原始拐点信息，向Hanjingli2中输出上下行线路名信息
		String up = itsctXYsUp.replace(" ", ";");
		up = up.substring(0, up.length() - 1);
		String down = itsctXYsDown.replace(" ", ";");
		down = down.substring(0, down.length() - 1);
		writerHanjingli.write("\"" + up + "\",\n");
		writerHanjingli.write("\"" + down + "\",\n");
		writerHanjingli2.write(line_idUp + "," + line_id + ",");

		// 向busline.txt中输出上行路线名、初始拐点、初始站点信息
		writerZheng.write(line_idUp + "\n");
		writerZheng.write(up + "\n");
		String stopnames[] = savedUpStopNames.split(" ");
		String stopxys[] = savedUpStopXYs.split(" ");
		for (int i = 0; i < 2 * stopxys.length; i++) {
			if (i % 2 == 0) {
				writerZheng.write(stopnames[i / 2] + ";");
			} else {
				writerZheng.write(stopxys[i / 2] + ";");
			}
		}
		writerZheng.write("\n");

		// 向busline.txt中输出下行路线名、初始拐点、初始站点信息
		writerZheng.write(line_id + "\n");
		writerZheng.write(down + "\n");
		String dstopnames[] = stopNames.split(" ");
		String dstopxys[] = savedDownStopXYs.split(" ");
		for (int i = 0; i < 2 * dstopxys.length; i++) {
			if (i % 2 == 0) {
				writerZheng.write(dstopnames[i / 2] + ";");
			} else {
				writerZheng.write(dstopxys[i / 2] + ";");
			}
		}
		writerZheng.write("\n");

		line_idUp = getLineName(line_idUp);// 截去line_id括号部分
		line_id = getLineName(line_id);// 截去line_id括号部分

		// 向stop表插入上行站点
		String[] stopxy;
		// System.out.println("stopnames size: " + stopnames.length);
		// System.out.println("stopxys size: " + stopxys.length);
		for (int i = 0; i < stopnames.length; i++) {
			stopxy = stopxys[i].split(",");
			GPSLocation newStopLoc = GPSLocation.parseGpsLocation(stopxys[i]);
			if (!stopLocations.contains(newStopLoc)) {
				stopLocations.add(newStopLoc);
				busSqlWriter.insertIntoStop(stopnames[i],
						String.valueOf(newStopLoc.getGPSX()),
						String.valueOf(newStopLoc.getGPSY()), writerSQL);
				writerSQL.flush();
			}
		}
		// 向stop表插入下行站点
		String[] dstopxy;
		for (int i = 0; i < dstopnames.length; i++) {
			dstopxy = dstopxys[i].split(",");
			GPSLocation newStopLoc = GPSLocation.parseGpsLocation(dstopxys[i]);
			if (!stopLocations.contains(newStopLoc)) {
				stopLocations.add(newStopLoc);
				busSqlWriter.insertIntoStop(dstopnames[i],
						String.valueOf(newStopLoc.getGPSX()),
						String.valueOf(newStopLoc.getGPSY()), writerSQL);
				writerSQL.flush();
			}
		}

		// 向busline表插入上行线路
		String[] first = stopxys[0].split(",");
		firstStopX = first[0];
		firstStopY = first[1];
		if (uptotal_price.equals("")) {
			uptotal_price = "1";
		}
		busSqlWriter
				.insertIntoBusline(firstStopX, firstStopY, line_idUp, true,
						uppay_way, uptotal_price, upStartTime, upEndTime, up,
						writerSQL);
		writerSQL.flush();
		// 向busline表插入下行线路
		String[] dfirst = dstopxys[0].split(",");
		firstStopX = dfirst[0];
		firstStopY = dfirst[1];
		if (total_price.equals("")) {
			total_price = "1";
		}
		busSqlWriter.insertIntoBusline(firstStopX, firstStopY, line_id, false,
				pay_way, total_price, downStartTime, downEndTime, down,
				writerSQL);
		writerSQL.flush();

		// 向stop_in_line表插入上行站点（真实站点）与线路的绑定关系
		busSqlWriter.insertIntostop_in_line(savedUpStopXYs, line_idUp, true,
				writerSQL);
		writerSQL.flush();
		// 向stop_in_line表插入下行站点（真实站点）与线路的绑定关系
		busSqlWriter.insertIntostop_in_line(savedDownStopXYs, line_id, false,
				writerSQL);
		writerSQL.flush();

		reader2.close();

		if (xysCounter > 2)
			System.out.println("输入文件" + sourcePath + "的格式不对，xysNum:"
					+ xysCounter);

	}

	private static String getLineName(String lineName) {
		int indexEnd = lineName.indexOf("(");
		if (indexEnd >= 0) {
			lineName = lineName.substring(0, indexEnd);
		}
		return lineName;
	}

}
