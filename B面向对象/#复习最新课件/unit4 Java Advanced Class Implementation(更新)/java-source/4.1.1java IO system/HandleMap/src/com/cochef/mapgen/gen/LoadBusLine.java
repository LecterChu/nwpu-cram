package com.cochef.mapgen.gen;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.StringTokenizer;

import javax.management.loading.MLet;

import com.cochef.mapgen.data.GPSLocation;
import com.cochef.mapgen.data.MapBusLine;
import com.cochef.mapgen.data.MapBusStop;
import com.cochef.mapgen.data.MapDataCollection;
import com.cochef.mapgen.data.MapIntersection;
import com.cochef.mapgen.data.MapRoadSection;
import com.cochef.mapgen.util.GeometryCalcu;

public class LoadBusLine {

	private static ArrayList<MapBusLine> mapBusLines = null;
	private static ArrayList<MapBusStop> mapBusStops = null;

	/**
	 * 获取所有的线路对象，给线路对象中的xys和站点集合赋值
	 * 
	 * @return the newIntersections
	 */
	public static ArrayList<MapBusLine> getMapBusLines() {
		if (mapBusLines == null) {
			mapBusLines = new ArrayList<MapBusLine>();
			mapBusStops = new ArrayList<MapBusStop>();
			InputStreamReader read;
			try {
				read = new InputStreamReader(new FileInputStream(new File(
						"busline.txt")), "UTF-8");
				BufferedReader input = new BufferedReader(read);
				StringTokenizer tokens;

				String msg = input.readLine();
				MapBusLine bs;
				MapBusStop busStop;

				while (msg != null) {
					msg = getLineName(msg);
					bs = new MapBusLine(msg, input.readLine());
					msg = input.readLine();

					tokens = new StringTokenizer(msg, ";");
					while (tokens.hasMoreTokens()) {

						String name = tokens.nextToken();
						String xys = tokens.nextToken();
						busStop = new MapBusStop(name, new GPSLocation(
								Double.parseDouble(xys.substring(0,
										xys.indexOf(","))),
								Double.parseDouble(xys.substring(xys
										.indexOf(",") + 1))));
						// 将站点对象添加到公共集合中，保证站点对象的无冗余
						if (!mapBusStops.contains(busStop)) {
							mapBusStops.add(busStop);
						}
						// 获取站点与映射站点组成的数组
						MapBusStop[] nbs = new MapBusStop[2];
						nbs[0] = mapBusStops.get(mapBusStops.indexOf(busStop));
						nbs[1] = null;
						bs.addBusLocation(nbs);
					}
					initDirection(bs);
					mapBusLines.add(bs);
					msg = input.readLine();
				}
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return mapBusLines;
	}

	private static void initDirection(MapBusLine mbl) {
		boolean notContained = true;
		for (MapBusLine blIt : mapBusLines) {
			if (blIt.getLineName().equals(mbl.getLineName())) {
				notContained = false;
				break;
			}
		}
		mbl.setDirection(notContained);
	}

	public static ArrayList<MapBusStop> getOrigStops() {
		return mapBusStops;
	}

	/**
	 * 对传入的线路初始化其direction值，并去掉线路名称中的起始点和终止点
	 * 
	 * @param lines
	 *            要初始化direction并修改lineName的线路集合
	 */
	public static void initAllLineName(ArrayList<MapBusLine> lines) {
		for (int i = 0; i < lines.size(); i++) {
			MapBusLine lineI = lines.get(i);
			lineI.setLineName(getLineName(lineI.getLineName()));
		}
	}

	private static String getLineName(String lineName) {
		int indexEnd = lineName.indexOf("(");
		if (indexEnd >= 0) {
			lineName = lineName.substring(0, indexEnd);
		}
		return lineName;
	}

	/**
	 * 添加线路首尾的初次没有添加的路段，并将没有映射到该路段的相应站点进行映射
	 * 
	 * @param lines
	 *            要处理的线路的集合
	 * @param rdSecs
	 *            所有路段的集合
	 */
	public static void addHeadRearSectionStops(ArrayList<MapBusLine> lines,
			ArrayList<MapRoadSection> rdSecs) {
		for (MapBusLine mbline : lines) {
			ArrayList<MapBusStop[]> stops = mbline.getBusStops();
			MapBusStop[] firstStop = stops.get(0);
			MapBusStop[] lastStop = stops.get(stops.size() - 1);
			if (firstStop[1] == null) { // 没有相应的映射，说明没有该路段
				// TODO 查找该添加的路段，然后添加到首尾，并对站点进行映射
				addSecStop(mbline, 1, rdSecs);
			}
			if (lastStop[1] == null) {
				addSecStop(mbline, -1, rdSecs);
			}
		}
	}

	/**
	 * 根据传入的参数，正向或反向地添加传入的线路缺少的RoadSection和相应站点的映射
	 * 
	 * @param mbline
	 *            要添加路段和站点映射的线路
	 * @param step
	 *            遍历的方向，1是正向，-1是方向
	 * @param rdSecs
	 *            整个路网中所有路段的集合
	 */
	private static void addSecStop(MapBusLine mbline, int step,
			ArrayList<MapRoadSection> rdSecs) {
		ArrayList<MapBusStop[]> stops = mbline.getBusStops();
		MapBusStop[] firstStop = null;
		MapRoadSection firstSec = null;
		MapIntersection outsideEnd = null;
		if (step == 1) {
			firstStop = stops.get(0);
			firstSec = mbline.getRoadSections().get(0);
			outsideEnd = firstSec.getFirst();
		} else if (step == -1) {
			firstStop = stops.get(stops.size() - 1);
			firstSec = mbline.getRoadSections().get(
					mbline.getRoadSections().size() - 1);
			outsideEnd = firstSec.getSecond();
		} else {
			// TODO 抛出异常，表示参数传入错误
			System.out.println("参数传入错误，LoadBusLine.addSecStop");
			return;
		}
		double minDistSame = Double.MAX_VALUE, minDistOps = Double.MAX_VALUE;
		MapRoadSection closeSecSame = null, closeSecOps = null;

		for (MapRoadSection mrs : rdSecs) {
			boolean equ2ndEnd = mrs.getSecond().equals(outsideEnd);
			boolean equ1stEnd = mrs.getFirst().equals(outsideEnd);
			if (equ2ndEnd || equ1stEnd) {
				double dist = GeometryCalcu.distP2Sec(firstStop[0]
						.getLocation(), mrs.getFirst().getLocation(), mrs
						.getSecond().getLocation());
				if (dist < minDistSame) { // 同方向路段
					if (step == 1 && equ2ndEnd || step == -1 && equ1stEnd) {
						minDistSame = dist;
						closeSecSame = mrs;
					}
				}
				if (dist < minDistOps) { // 反方向路段
					if (step == 1 && equ1stEnd || step == -1 && equ2ndEnd) {
						minDistOps = dist;
						closeSecOps = mrs;
					}
				}
			}
		}
		MapRoadSection newSection = null;
		MapIntersection intsec = null;
		if (minDistSame < 50) {
			newSection = closeSecSame;
			// System.out.println("相近的路段");
			intsec = (step == 1) ? newSection.getFirst() : newSection
					.getSecond();
		} else if (minDistOps < 50) { // 构造一个新路段，将找到的路段反向
			newSection = new MapRoadSection(closeSecOps.getSecond(),
					closeSecOps.getFirst());
			intsec = (step == 1) ? newSection.getFirst() : newSection
					.getSecond();
			// System.out.println("反向相近的路段");
		} else { // 端点为本站点与已有第一路段的第一端点
			// 添加一个新的Intersection
			// 无法找到该intersection所在的路的名字，设为null
			intsec = new MapIntersection(firstStop[0].getLocation(), null);
//			System.out
//					.println("无法找到该intersection所在的路的名字，设为null，之后手动解决。在LoadBusLine中");

			// 向DataCollection中添加新的intersection
			if (!MapDataCollection.getItscts().contains(intsec)) {
				MapDataCollection.getItscts().add(intsec); // 添加新的intersection
			} else {
				intsec = MapDataCollection.getItscts().get(
						MapDataCollection.getItscts().indexOf(intsec));
			}

			newSection = (step == 1) ? new MapRoadSection(intsec,
					firstSec.getFirst()) : new MapRoadSection(
					firstSec.getSecond(), intsec);
		}

		// 在datacollection中添加该新路段
		if (!MapDataCollection.getRdSections().contains(newSection)) {
			MapDataCollection.getRdSections().add(newSection);
		}

		if (step == 1) {
			if (!mbline.getItscts().contains(intsec)) {
				mbline.getItscts().add(0, intsec);
			}
			mbline.getRoadSections().add(0, newSection);
		} else {
			if (!mbline.getItscts().contains(intsec)) {
				mbline.getItscts().add(intsec);
			}
			mbline.addRoadSection(newSection);
		}
		// 将开始的若干个未映射的站点映射到该路段
		int pos = (step == 1) ? 0 : stops.size() - 1;
		MapRoadSection preSection = (step == 1) ? null : mbline
				.getRoadSections().get(mbline.getRoadSections().size() - 2);
		MapRoadSection nextSection = (step == 1) ? mbline.getRoadSections()
				.get(1) : null;
		for (int i = pos; stops.get(i)[1] == null; i += step) {
			SecBusStopGen.addMappingStop(stops, i, newSection, preSection,
					nextSection, mbline);
		}
	}
}
