package com.cochef.util;

import java.io.OutputStreamWriter;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;

import com.cochef.mapgen.data.GPSLocation;
import com.cochef.mapgen.data.MapBusLine;
import com.cochef.mapgen.data.MapBusStop;
import com.cochef.mapgen.data.MapDataCollection;
import com.cochef.mapgen.data.MapIntersection;
import com.cochef.mapgen.data.MapRoadSection;
import com.cochef.mapgen.data.MapStopSection;

//import com.cochef.rtbus.data.GPSLocation;
//import com.cochef.rtbus.data.RelativeLocation;

public class BusSqlWrite {

	/**
	 * 向数据库stop表插入真实站点，可以在解析过程中调用
	 * 
	 * @param stop_name
	 *            站点名
	 * @param stop_coord_x
	 *            站点经度
	 * @param stop_coord_y
	 *            站点纬度
	 * @param writer
	 *            文件输出流sqls.sql
	 * @throws Exception
	 */
	public void insertIntoStop(String stop_name, String stop_coord_x,
			String stop_coord_y, OutputStreamWriter writer) throws Exception {
		writer.write("INSERT INTO cochefdb.stop(stop_name, stop_coord_x, stop_coord_y) VALUES ('"
				+ stop_name + "', " + stop_coord_x + ", " + stop_coord_y + ");");
		writer.write("\n");
	}

	/**
	 * 向数据库intersection表插入交叉口，解析完成后，中间数据集合生成之后，才能调用
	 * 
	 * @param data
	 *            中间数据集合，存储交叉口、虚拟站点及他们与线路、路段（交叉口之间）的映射关系
	 * @param writer
	 *            文件输出流sqls.sql
	 * @throws Exception
	 */
	public void insertIntoIntersection(MapDataCollection data,
			OutputStreamWriter writer) throws Exception {
		ArrayList<MapIntersection> intersections = data.getItscts();
		for (MapIntersection mapIntersection : intersections) {
			GPSLocation itsLoc = mapIntersection.getLocation();
			writer.write("INSERT INTO cochefdb.intersection(itsct_coord_x, itsct_coord_y) VALUES ("
					+ itsLoc.getGPSX() + ", " + itsLoc.getGPSY() + ");");
			writer.write("\n");
		}
	}

	/**
	 * 向数据库street表插入道路，解析完成后，中间数据集合生成之后，才能调用
	 * 
	 * @param data
	 *            中间数据集合，存储交叉口、虚拟站点及他们与线路、路段（交叉口之间）的映射关系
	 * @param writer
	 *            文件输出流sqls.sql
	 * @throws Exception
	 */
	public void insertIntoStreet(MapDataCollection data,
			OutputStreamWriter writer) throws Exception {
		ArrayList<String> streets = data.getStreets(data.getRdSections());
		for (String street : streets) {
			writer.write("INSERT INTO cochefdb.street(street_name) VALUES ('"
					+ street + "');");
			writer.write("\n");
		}
	}

	/**
	 * 向数据库road_section表插入路段，解析完成后，中间数据集合生成之后，才能调用
	 * 
	 * @param data
	 *            中间数据集合，存储交叉口、虚拟站点及他们与线路、路段（交叉口之间）的映射关系
	 * @param writer
	 *            文件输出流sqls.sql
	 * @throws Exception
	 */
	public void insertIntoRoadsection(MapDataCollection data,
			OutputStreamWriter writer) throws Exception {

		ArrayList<MapRoadSection> roadSecs = data.getRdSections();
		double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		for (MapRoadSection mapRoadSection : roadSecs) {

			x1 = mapRoadSection.getFirst().getLocation().getGPSX();
			y1 = mapRoadSection.getFirst().getLocation().getGPSY();
			x2 = mapRoadSection.getSecond().getLocation().getGPSX();
			y2 = mapRoadSection.getSecond().getLocation().getGPSY();
			double length = mapRoadSection.getLength();
			length = round(length, 2);
			String streetName = mapRoadSection.getStreetName();

			//length = round(length, 2);
			String idFrom = "(SELECT itsct_id FROM cochefdb.intersection WHERE itsct_coord_x = "
					+ x1 + " AND itsct_coord_y = " + y1 + ")";
			String idTo = "(SELECT itsct_id FROM cochefdb.intersection WHERE itsct_coord_x = "
					+ x2 + " AND itsct_coord_y = " + y2 + ")";
			String streetID = "(SELECT street_id FROM cochefdb.street WHERE street_name = '"
					+ streetName + "')";
			writer.write("INSERT INTO cochefdb.road_section(itsct_id_start, itsct_id_end, street_id, section_length) VALUES ("
					+ idFrom
					+ ", "
					+ idTo
					+ ", "
					+ streetID
					+ ", "
					+ length
					+ ");");
			writer.write("\n");

		}
	}

	/**
	 * 在每条上行路线或下行路线解析完之后调用，（上行是一条busline，下行是一条busline），将busline信息插入数据库中busline表
	 * 
	 * @param firstStopX
	 *            上行或下行第一站的经度
	 * @param firstStopY
	 *            上行或下行第一站的经度
	 * @param line_id
	 *            路线名，如40路(火车站--外事学院北校区)，40路(外事学院北校区--火车站)
	 * @param direction
	 * @param pay_way
	 * @param total_price
	 * @param start_time
	 * @param end_time
	 * @param xys
	 * @param writer
	 * @throws Exception
	 */
	public void insertIntoBusline(String firstStopX, String firstStopY,
			String line_id, boolean direction, boolean pay_way,
			String total_price, String start_time, String end_time, String xys,
			OutputStreamWriter writer) throws Exception {
		String first_stop_id = "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = "
				+ firstStopX + " AND stop_coord_y = " + firstStopY + ")";
		xys = xys.replace(" ", ";");
		xys = xys.substring(0, xys.length() - 1);
		writer.write("INSERT INTO cochefdb.busline(line_id, direction, pay_way, price, first_stop_id, summer_begin, winter_begin, summer_first, summer_last, winter_first, winter_last, bus_interval, xys) VALUES ('"
				+ line_id
				+ "', "
				+ direction
				+ ", "
				+ pay_way
				+ ", "
				+ total_price
				+ ", "
				+ first_stop_id
				+ ", '"
				+ "1949-05-01"
				+ "', '"
				+ "1949-11-01"
				+ "', '"
				+ formateTime(start_time, "0000", "+")
				+ "', '"
				+ formateTime(end_time, "0000", "+")
				+ "', '"
				+ formateTime(start_time, "0030", "+")
				+ "', '"
				+ formateTime(end_time, "0030", "-")
				+ "', "
				+ 10
				+ ", '"
				+ xys
				+ "');");
		// + formateTime("0010", "0000", "-") + "', '" + xys + "');");
		writer.write("\n");
		start_time = "";
	}

	/**
	 * 在每条上行路线或下行路线解析完之后调用，将站点和线路的绑定信息插入数据库中stop_in_line表
	 * 
	 * @param stopXYs
	 * @param line_id
	 * @param direction
	 * @param writer
	 * @throws Exception
	 */
	public void insertIntostop_in_line(String stopXYs, String line_id,
			boolean direction, OutputStreamWriter writer) throws Exception {

		String x = "", y = "";
		String xPre = "", yPre = "", xSuc = "", ySuc = "";
		String id = "", idPre = "", idSuc = "";

		String[] stopxy = stopXYs.split(" ");

		// 首站无前驱站点,末站无后继站点
		for (int i = 0; i < stopxy.length; i++) {
			x = stopxy[i].split(",")[0];
			y = stopxy[i].split(",")[1];
			if (i > 0) {
				xPre = stopxy[i - 1].split(",")[0];
				yPre = stopxy[i - 1].split(",")[1];
			}
			if (i < stopxy.length - 1) {
				xSuc = stopxy[i + 1].split(",")[0];
				ySuc = stopxy[i + 1].split(",")[1];
			}
			id = "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = " + x
					+ " AND stop_coord_y = " + y + ")";
			if (i > 0)
				idPre = "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = "
						+ xPre + " AND stop_coord_y = " + yPre + ")";
			else
				idPre = "null";
			if (i < stopxy.length - 1)
				idSuc = "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = "
						+ xSuc + " AND stop_coord_y = " + ySuc + ")";
			else
				idSuc = "null";
			writer.write("INSERT INTO cochefdb.stop_in_line(stop_id, line_id, direction, pre_stop_id, next_stop_id) VALUES ("
					+ id
					+ ", '"
					+ line_id
					+ "', "
					+ direction
					+ ", "
					+ idPre
					+ ", " + idSuc + ");");
			writer.write("\n");
		}

	}

	/**
	 * 向数据库stop_in_rdsection表插入站点和路段的绑定及映射关系，解析完成后，中间数据集合生成之后，才能调用
	 * 
	 * @param data
	 *            中间数据集合，存储交叉口、虚拟站点及他们与线路、路段（交叉口之间）的映射关系
	 * @throws Exception
	 */
	public void insertIntostop_in_rdsection(MapDataCollection data,
			OutputStreamWriter writer) throws Exception {
		
		ArrayList<MapBusLine> mapBuslines = data.getBusLines();
		ArrayList<MapBusStop> stops = new ArrayList<MapBusStop>();
		for (MapBusLine mapBusline : mapBuslines) {
			ArrayList<MapBusStop[]> stopOriAbsPairs = mapBusline
					.getBusLoction();
			for (MapBusStop[] stopOriAbsPair : stopOriAbsPairs) {
				if (stops.contains(stopOriAbsPair[0])) {
					continue;
				}
				stops.add(stopOriAbsPair[0]);
				MapRoadSection rsec = stopOriAbsPair[0].getRoadSection();
				double x1 = rsec.getFirst().getLocation().getGPSX();
				double y1 = rsec.getFirst().getLocation().getGPSY();
				double x2 = rsec.getSecond().getLocation().getGPSX();
				double y2 = rsec.getSecond().getLocation().getGPSY();
				String idStart = "(SELECT itsct_id FROM cochefdb.intersection WHERE itsct_coord_x = "
						+ x1 + " AND itsct_coord_y = " + y1 + ")";
				String idEnd = "(SELECT itsct_id FROM cochefdb.intersection WHERE itsct_coord_x = "
						+ x2 + " AND itsct_coord_y = " + y2 + ")";
				String rdSecID = "(SELECT road_section_id FROM cochefdb.road_section WHERE itsct_id_start = "
						+ idStart + " AND itsct_id_end = " + idEnd + ")";

				double absX = round(stopOriAbsPair[1].getCoordX(),6);
				double absY = round(stopOriAbsPair[1].getCoordY(),6);
				double oriX = stopOriAbsPair[0].getCoordX();
				double oriY = stopOriAbsPair[0].getCoordY();

				String oriStopID = "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = "
						+ oriX + " AND stop_coord_y = " + oriY + ")";
				writer.write("INSERT INTO cochefdb.stop_in_rdsection(stop_id, road_section_id, stop_mapping_x, stop_mapping_y) VALUES ("
						+ oriStopID
						+ ", "
						+ rdSecID
						+ ", "
						+ absX
						+ ", "
						+ absY + ");");
				writer.write("\n");
			}

		}
	}

	/**
	 * 向数据库stop_section表插入站点段，解析完成后，中间数据集合生成之后，才能调用
	 * 
	 * @param data
	 *            中间数据集合，存储交叉口、虚拟站点及他们与线路、路段（交叉口之间）的映射关系
	 * @throws Exception
	 */
	public void insertIntostop_section(MapDataCollection data,
			OutputStreamWriter writer) throws Exception {

		ArrayList<MapStopSection> stopSecs = data.getStopSections();
		double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
		String lineID;
		boolean direction;
		for (MapStopSection stopSec : stopSecs) {

			x1 = stopSec.getFirstStop().getCoordX();
			y1 = stopSec.getFirstStop().getCoordY();
			x2 = stopSec.getSecondStop().getCoordX();
			y2 = stopSec.getSecondStop().getCoordY();
			lineID = stopSec.getLine().getLineName();
			direction = stopSec.getLine().isDirection();
			String idFrom = "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = "
					+ x1 + " AND stop_coord_y = " + y1 + ")";
			String idTo = "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = "
					+ x2 + " AND stop_coord_y = " + y2 + ")";
			double length = stopSec.getLength();
			length = round(length, 2);
			writer.write("INSERT INTO cochefdb.stop_section(stop_id_1st, stop_id_2nd, line_id, direction, section_length) VALUES ("
					+ idFrom
					+ ", "
					+ idTo
					+ ", '"
					+ lineID
					+ "', "
					+ direction
					+ ", " + length + ");");
			writer.write("\n");
		}
	}

	// /**
	// * 在每条上行路线或下行路线解析完之后调用，将站点段和线路的绑定信息插入数据库中stop_sec_line表
	// * @param stopXYs
	// * @param line_id
	// * @param direction
	// * @param writer
	// * @throws Exception
	// */
	// public void insertIntostop_sec_line(String stopXYs, String line_id,
	// boolean direction, OutputStreamWriter writer) throws Exception{
	// String[] stopXYss = stopXYs.split(" ");
	// for(int i = 0; i < stopXYss.length - 1; i++){
	// String x1 = stopXYss[i].split(",")[0];
	// String y1 = stopXYss[i].split(",")[1];
	// String x2 = stopXYss[i + 1].split(",")[0];
	// String y2 = stopXYss[i + 1].split(",")[1];
	// String idFrom =
	// "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = '"
	// + x1 + "' AND stop_coord_y = '" + y1 + "')";
	// String idTo = "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = '"
	// + x2 + "' AND stop_coord_y = '" + y2 + "')";
	// String stopSecID =
	// "(SELECT stop_section_id FROM cochefdb.stop_section WHERE stop_id_1st = '"
	// + idFrom + "' AND stop_id_2nd = '" + idTo + "')";
	//
	// writer.write("INSERT INTO cochefdb.stop_sec_line(stop_section_id, line_id, direction) VALUES ("
	// + stopSecID
	// + ", '"
	// + line_id
	// + "', "
	// + direction
	// + ");");
	// writer.write("\n");
	// }
	// }

	/**
	 * 在每条上行路线或下行路线解析完之后调用，将站点段和线路的绑定信息插入数据库中stop_sec_line表
	 * 
	 * @param stopXYs
	 * @param line_id
	 * @param direction
	 * @param writer
	 * @throws Exception
	 */
	public void insertIntostop_sec_line(MapDataCollection data,
			OutputStreamWriter writer) throws Exception {

		ArrayList<MapBusLine> mapBuslines = data.getBusLines();
		for (MapBusLine mapBusline : mapBuslines) {
			String lineID = mapBusline.getLineName();
			boolean direction = mapBusline.isDirection();
			ArrayList<MapStopSection> mapStopSections = mapBusline
					.getStopSections();
			for (MapStopSection mapStopSection : mapStopSections) {
				String idFrom = "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = "
						+ mapStopSection.getFirstStop().getCoordX()
						+ " AND stop_coord_y = "
						+ mapStopSection.getFirstStop().getCoordY() + ")";
				String idTo = "(SELECT stop_id FROM cochefdb.stop WHERE stop_coord_x = "
						+ mapStopSection.getSecondStop().getCoordX()
						+ " AND stop_coord_y = "
						+ mapStopSection.getSecondStop().getCoordY() + ")";
				String stopSecID = "(SELECT stop_section_id FROM cochefdb.stop_section WHERE stop_id_1st = "
						+ idFrom + " AND stop_id_2nd = " + idTo + ")";
				writer.write("INSERT INTO cochefdb.stop_sec_line(stop_section_id, line_id, direction) VALUES ("
						+ stopSecID + ", '" + lineID + "', " + direction + ");");
				writer.write("\n");
			}
		}
	}

	/**
	 * 向数据库itsct_in_line表插入交叉口和线路的绑定关系，解析完成后，中间数据集合生成之后，才能调用
	 * 
	 * @param data
	 *            中间数据集合，存储交叉口、虚拟站点及他们与线路、路段（交叉口之间）的映射关系
	 * @param writer
	 *            文件输出流sqls.sql
	 * @throws Exception
	 */
	public void insertIntoitsct_in_line(MapDataCollection data,
			OutputStreamWriter writer) throws Exception {

		ArrayList<MapBusLine> mapBuslines = data.getBusLines();
		for (MapBusLine mapBusline : mapBuslines) {
			String lineID = mapBusline.getLineName();
			boolean direction = mapBusline.isDirection();
			ArrayList<MapIntersection> its = mapBusline.getItscts();
			for (int i = 0; i < its.size(); i++) {
				MapIntersection pre = null;
				MapIntersection it = null;
				MapIntersection suc = null;

				if (i > 0) {
					pre = its.get(i - 1);
				}
				it = its.get(i);
				if (i < its.size() - 1) {
					suc = its.get(i + 1);
				}

				String xPre = "null", yPre = "null", xSuc = "null", ySuc = "null";
				String currentX = "", currentY = "";

				currentX = it.getLocation().getGPSX() + "";
				currentY = it.getLocation().getGPSY() + "";
				if (pre != null) {
					xPre = pre.getLocation().getGPSX() + "";
					yPre = pre.getLocation().getGPSY() + "";
				}
				if (suc != null) {
					xSuc = suc.getLocation().getGPSX() + "";
					ySuc = suc.getLocation().getGPSY() + "";
				}

				String id = "", idPre = "null", idSuc = "null";
				id = "(SELECT itsct_id FROM cochefdb.intersection WHERE itsct_coord_x = "
						+ currentX + " AND itsct_coord_y = " + currentY + ")";
				if (pre != null) {
					idPre = "(SELECT itsct_id FROM cochefdb.intersection WHERE itsct_coord_x = "
							+ xPre + " AND itsct_coord_y = " + yPre + ")";
				}
				if (suc != null) {
					idSuc = "(SELECT itsct_id FROM cochefdb.intersection WHERE itsct_coord_x = "
							+ xSuc + " AND itsct_coord_y = " + ySuc + ")";
				}
				writer.write("INSERT INTO cochefdb.itsct_in_line(itsct_id, line_id, direction, pre_itsct_id, next_itsct_id) VALUES ("
						+ id
						+ ", '"
						+ lineID
						+ "', "
						+ direction
						+ ", "
						+ idPre + ", " + idSuc + ");");
				writer.write("\n");
			}
		}
	}

	public void InsertAbs(MapDataCollection data, OutputStreamWriter writer)
			throws Exception {
		insertIntoIntersection(data, writer);
		insertIntoStreet(data, writer);
		insertIntoRoadsection(data, writer);
		insertIntostop_in_rdsection(data, writer);
		insertIntostop_section(data, writer);
		// insertIntostop_sec_line(data, writer);
		insertIntoitsct_in_line(data, writer);
	}

	/**
	 * 对double数据进行取精度.
	 * 
	 * @param value
	 *            double数据.
	 * @param scale
	 *            精度位数(保留的小数位数).
	 * @return 精度计算后的数据.
	 */
	public static double round(double value, int scale) {
		BigDecimal bd = new BigDecimal(value);
		bd = bd.setScale(scale, RoundingMode.HALF_UP);
		double d = bd.doubleValue();
		bd = null;
		return d;
	}

	/**
	 * 本方法处理字符串表示的时间偏移并返回格式化时间，特别地，当offsetString为“0000”时，用于格式化时间
	 * 
	 * @param timeString
	 *            表示时间的字符串，形如“0600”表示6时0分
	 * @param offsetString
	 *            表示时间偏移的字符串，形如“0030”表示0时30分
	 * @param direction
	 *            表示偏移方向的字符串，取值“+”和“-”
	 * @return 格式化时间字符串，形如“05:10:09”表示5时10分9秒
	 */
	public static String formateTime(String timeString, String offsetString,
			String direction) {

		String returnTime = "";
		int t = 0;
		int time = Integer.parseInt(timeString.substring(0, 2)) * 60
				+ Integer.parseInt(timeString.substring(2, 4));

		int offset = Integer.parseInt(offsetString.substring(0, 2)) * 60
				+ Integer.parseInt(offsetString.substring(2, 4));

		if (direction.equals("+")) {
			t = time + offset;
		} else {
			if (time < offset)
				t = time - offset + 24 * 60;
			else
				t = time - offset;
		}
		String part1 = "" + (t / 60) % 24, part2 = t % 60 + "";
		if (part1.length() < 2) {
			part1 = "0" + part1;
		}
		if (part2.length() < 2) {
			part2 = "0" + part2;
		}
		returnTime = part1 + part2;
		returnTime = returnTime.substring(0, 2) + ":"
				+ returnTime.substring(2, 4) + ":00";
		return returnTime;
	}

	// /**
	// * 获得参数线路的最后一个路段索引
	// *
	// * @param rdses
	// * 路段集合
	// * @param lineID
	// * 某线路ID
	// * @return 参数线路的最后一个路段索引
	// */
	// public int getLineLastSection(ArrayList<RDSection> rdses,
	// String lineID) {
	//
	// for (int i = 0; i < rdses.size(); i++) {
	// int index = 0;
	// if (((index = rdses.get(i).getLines().indexOf(lineID)) != -1)
	// && (rdses.get(i).getNextSectionIndex().get(index) == -1)) {
	// return i;
	// }
	// }
	// return -1;
	// }

	// /**
	// * 获得某个路段在指定线路上的前驱索引，若返回值为-1，表示该路段为线路的第一个路段
	// *
	// * @param rdses
	// * 路段集合
	// * @param rdsIndex
	// * 某路段的索引
	// * @param lineID
	// * 指定线路ID
	// * @return
	// */
	// public int getSameLinePre(ArrayList<RDSection> rdses, int rdsIndex,
	// String lineID) {
	//
	// int i = 0;
	// for (RDSection s : rdses) {
	// if (s.getNextSectionIndex().contains(rdsIndex)
	// && s.getLines().contains(lineID)) {
	// return i;
	// }
	// i++;
	// }
	// return -1;
	// }

	// public String getLineIDDown(String line_idUp) {
	// String s = line_idUp.substring(line_idUp.indexOf("(") + 1,
	// line_idUp.indexOf(")"));
	// return line_idUp.substring(0, line_idUp.indexOf("(")) + "("
	// + s.split("--")[1] + "--" + s.split("--")[0] + ")";
	// }

}
