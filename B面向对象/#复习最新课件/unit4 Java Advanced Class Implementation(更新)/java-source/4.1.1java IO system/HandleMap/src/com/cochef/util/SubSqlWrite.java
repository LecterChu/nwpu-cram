package com.cochef.util;

import java.io.OutputStreamWriter;
import java.util.ArrayList;

import com.cochef.mapgen.data.GPSLocation;
import com.cochef.mapgen.data.MapBusStop;
import com.cochef.mapgen.data.MapDataCollection;
import com.cochef.mapgen.data.MapIntersection;
import com.cochef.mapgen.data.MapRoadSection;
import com.cochef.mapgen.util.GeometryCalcu;

public class SubSqlWrite {

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
	public void insertIntosubway_stop(String stop_name, String stop_coord_x,
			String stop_coord_y, OutputStreamWriter writer) throws Exception {
		writer.write("INSERT INTO cochefdb.subway_stop(stop_name, stop_coord_x, stop_coord_y) VALUES ('"
				+ stop_name + "', " + stop_coord_x + ", " + stop_coord_y + ");");
		writer.write("\n");
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
	public void insertIntosubway_line(String firstStopX, String firstStopY,
			String line_id, boolean direction, boolean pay_way,
			String total_price, String start_time, String end_time, String xys,
			OutputStreamWriter writer) throws Exception {
		String first_stop_id = "(SELECT substop_id FROM cochefdb.subway_stop WHERE stop_coord_x = "
				+ firstStopX + " AND stop_coord_y = " + firstStopY + ")";
		xys = xys.replace(" ", ";");
		xys = xys.substring(0, xys.length() - 1);
		writer.write("INSERT INTO cochefdb.subway_line(sub_line_id, sub_direction, pay_way, price, first_stop_id, summer_begin, winter_begin, summer_first, summer_last, winter_first, winter_last, subway_interval, xys) VALUES ('"
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
				+ BusSqlWrite.formateTime(start_time, "0000", "+")
				+ "', '"
				+ BusSqlWrite.formateTime(end_time, "0000", "+")
				+ "', '"
				+ BusSqlWrite.formateTime(start_time, "0030", "+")
				+ "', '"
				+ BusSqlWrite.formateTime(end_time, "0030", "-")
				+ "', "
				+ 10
				+ ", '" + xys + "');");
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
	public void insertIntosubstop_in_line(String stopXYs, String line_id,
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
			id = "(SELECT substop_id FROM cochefdb.subway_stop WHERE stop_coord_x = "
					+ x + " AND stop_coord_y = " + y + ")";
			if (i > 0)
				idPre = "(SELECT substop_id FROM cochefdb.subway_stop WHERE stop_coord_x = "
						+ xPre + " AND stop_coord_y = " + yPre + ")";
			else
				idPre = "null";
			if (i < stopxy.length - 1)
				idSuc = "(SELECT substop_id FROM cochefdb.subway_stop WHERE stop_coord_x = "
						+ xSuc + " AND stop_coord_y = " + ySuc + ")";
			else
				idSuc = "null";
			writer.write("INSERT INTO cochefdb.substop_in_line(substop_id, sub_line_id, sub_direction, pre_stop_id, next_stop_id) VALUES ("
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

	private ArrayList<String> stopXysStr = new ArrayList<String>();

	/**
	 * 在每条上行路线或下行路线解析完之后调用，将站点与路段的映射关系插入数据库中substop_in_rdsection表
	 * 
	 * @param stopxys
	 * @param writer
	 * @throws Exception
	 */
	public void insertIntosubstop_in_rdsection(String stopxys[],
			OutputStreamWriter writer) throws Exception {

		for (String stopxy : stopxys) {
			if (stopXysStr.contains(stopxy)) {
				continue;
			} else {
				stopXysStr.add(stopxy);
			}
			double x = Double.parseDouble(stopxy.split(",")[0]);
			double y = Double.parseDouble(stopxy.split(",")[1]);
			String oriStopID = "(SELECT substop_id FROM cochefdb.subway_stop WHERE stop_coord_x = "
					+ x + " AND stop_coord_y = " + y + ")";
			MapRoadSection mapRS = MapDataCollection.getSubMapSec(x, y, 150);
			if (mapRS == null) {
				System.err.println("hehe!");
				continue;
			}
			double x1 = mapRS.getFirst().getLocation().getGPSX();
			double y1 = mapRS.getFirst().getLocation().getGPSY();
			double x2 = mapRS.getSecond().getLocation().getGPSX();
			double y2 = mapRS.getSecond().getLocation().getGPSY();
			String idStart = "(SELECT itsct_id FROM cochefdb.intersection WHERE itsct_coord_x = "
					+ x1 + " AND itsct_coord_y = " + y1 + ")";
			String idEnd = "(SELECT itsct_id FROM cochefdb.intersection WHERE itsct_coord_x = "
					+ x2 + " AND itsct_coord_y = " + y2 + ")";
			String rdSecID = "(SELECT road_section_id FROM cochefdb.road_section WHERE itsct_id_start = "
					+ idStart + " AND itsct_id_end = " + idEnd + ")";
			Double[] mapxy = GeometryCalcu.getSegmentMapPoint(new GPSLocation(
					x, y), mapRS.getFirst().getLocation(), mapRS.getSecond()
					.getLocation());
			writer.write("INSERT INTO cochefdb.substop_in_rdsection(substop_id, road_section_id, stop_mapping_x, stop_mapping_y) VALUES ("
					+ oriStopID
					+ ", "
					+ rdSecID
					+ ", "
					+ mapxy[0]
					+ ", "
					+ mapxy[1] + ");");
			writer.write("\n");
		}

	}
}
