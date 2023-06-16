package com.cochef.mapgen.gen;

import java.util.ArrayList;
import java.util.StringTokenizer;

import com.cochef.mapgen.data.GPSLocation;
import com.cochef.mapgen.data.MapBusLine;
import com.cochef.mapgen.data.MapBusStop;
import com.cochef.mapgen.data.MapIntersection;
import com.cochef.mapgen.data.MapRoadSection;
import com.cochef.mapgen.util.GeometryCalcu;

/**
 * @author mcy
 * 
 */
public class SecBusStopGen {

	private static ArrayList<MapBusStop> secBusStops = null;

	/**
	 * 得到所有的映射站点集合
	 * 
	 * @param lines
	 *            所有的线路的集合
	 * @return 所有的映射站点集合
	 */
	public static ArrayList<MapBusStop> getSecStops(ArrayList<MapBusLine> lines) {
		if (secBusStops == null) {
			secBusStops = new ArrayList<MapBusStop>();
			for (MapBusLine line : lines) { // 取出一条线路进行处理
				ArrayList<MapBusStop[]> stops = line.getBusStops();
				ArrayList<MapIntersection> itscts = line.getItscts();
				int stopsPos = 0;
				int itsctPos = 0;
				Double[] intXys = line.getLineItsctXYS(itscts.get(0));
				GPSLocation curLocation = new GPSLocation(intXys[0], intXys[1]);
				MapRoadSection preRoadSection = null;
				MapRoadSection curRoadSection = null;
				MapRoadSection nextRoadSection = line.getRoadSections().get(0);
				int rdSecSize = line.getRoadSections().size();
				StringTokenizer tokens = new StringTokenizer(line.getXys(), ";");

				// 找到第一个intersection在xys中对应的位置，处理该位置后面的站点
				boolean intsecFound = false;
				boolean hasMoreIntsec = true;
				while (tokens.hasMoreElements()) {
					GPSLocation tempLocation = GPSLocation
							.parseGpsLocation((String) tokens.nextElement());

					// 当前交叉点和当前路段指针后移
					if (curLocation.equals(tempLocation)) {
						itsctPos++;
						if (itsctPos < itscts.size()) {
							intXys = line.getLineItsctXYS(itscts.get(itsctPos));
							curLocation = new GPSLocation(intXys[0], intXys[1]);
							preRoadSection = curRoadSection;
							curRoadSection = nextRoadSection;
							nextRoadSection = itsctPos < rdSecSize ? line
									.getRoadSections().get(itsctPos) : null;
							intsecFound = true;
						} else {
							hasMoreIntsec = false;
						}
					}
					if (stops.get(stopsPos)[0].getLocation().equals(
							tempLocation)) {
						if (intsecFound
								&& stops.get(stopsPos)[0].getLocation().equals(
										tempLocation)) {
							addMappingStop(stops, stopsPos, curRoadSection,
									preRoadSection, nextRoadSection, line);
						}
						stopsPos++;
					}
					if (!hasMoreIntsec) {
						break;
					}
				}
			}
		}

		return secBusStops;
	}

	/**
	 * 对传入的新旧站点集合中的指定元素添加站点映射，并设置车站与路段的链接关系
	 * 
	 * @param stops
	 *            新旧站点集合
	 * @param stopsPos
	 *            指定的要添加映射站点值的站点元素在stops中的位置
	 * @param curRoadSection
	 *            要添加映射站点的对象所在的路段
	 * @param line
	 *            操作所对应的线路，用于输出调试信息
	 */
	public static void addMappingStop(ArrayList<MapBusStop[]> stops,
			int stopsPos, MapRoadSection curRoadSection,
			MapRoadSection preRoadSection, MapRoadSection nextRoadSection,
			MapBusLine line) {
		ArrayList<MapBusStop> secStops = curRoadSection.getSecBusStops();
		MapBusStop[] stopPare = stops.get(stopsPos);
		boolean notFound = true;
		for (MapBusStop mapBusStop : secStops) {
			if (mapBusStop.getStopName().equals(stopPare[0].getStopName())) {
				stopPare[1] = mapBusStop;
				stopPare[0].setRoadSection(stopPare[1].getRoadSection());
				notFound = false;
				break;
			}
		}
		if (notFound) { // 在当前路段中没有该站点的映射置
			MapRoadSection sectionStopIn = curRoadSection;
			MapBusStop tempStop = getMappingStop(stopPare[0], curRoadSection
					.getFirst().getLocation(), curRoadSection.getSecond()
					.getLocation());
			if (tempStop == null && preRoadSection != null) { // 无法映射到当前路段，尝试映射到前一路段
				sectionStopIn = preRoadSection;
				tempStop = getMappingStop(stopPare[0], preRoadSection
						.getFirst().getLocation(), preRoadSection.getSecond()
						.getLocation());
			}
			if (tempStop == null && nextRoadSection != null) { // 无法映射到前一路段，尝试映射到后一路段
				sectionStopIn = nextRoadSection;
				tempStop = getMappingStop(stopPare[0], nextRoadSection
						.getFirst().getLocation(), nextRoadSection.getSecond()
						.getLocation());
			}
			if (tempStop == null) { // 无法映射到当前、前、后三个段，则映射到当前路段的最近的端点
				sectionStopIn = curRoadSection;
				GPSLocation stopLoc = stopPare[0].getLocation();
				if (stopLoc.realDistance(curRoadSection.getFirst()
						.getLocation()) > stopLoc.realDistance(curRoadSection
						.getSecond().getLocation())) {
					tempStop = new MapBusStop(stopPare[0].getStopName(),
							curRoadSection.getSecond().getLocation());
				} else {
					tempStop = new MapBusStop(stopPare[0].getStopName(),
							curRoadSection.getFirst().getLocation());
				}
			}

			// 设置将车站映射加入路段中
			notFound = true;
			secStops = sectionStopIn.getSecBusStops();
			for (MapBusStop mapBusStop : secStops) {
				if (mapBusStop.getStopName().equals(stopPare[0].getStopName())) {
					notFound = false;
					tempStop = mapBusStop;
					break;
				}
			}
			if (notFound) {
				sectionStopIn.addBusStop(tempStop);
			}
			stopPare[1] = tempStop;

			// 车站与路段关联
			stopPare[0].setRoadSection(sectionStopIn);
			stopPare[1].setRoadSection(sectionStopIn);

			if (!secBusStops.contains(tempStop)) {
				secBusStops.add(tempStop);
			}
		}
	}

	/**
	 * 获得站点stop在线段上的映射站点
	 * 
	 * @param stop
	 *            要映射的站点
	 * @param first
	 *            确定线段的第一个点
	 * @param second
	 *            确定线段的第二个点
	 * @return 站点stop在线段上的映射站点
	 */
	private static MapBusStop getMappingStop(MapBusStop stop,
			GPSLocation first, GPSLocation second) {
		MapBusStop tempStop = null;
		Double[] mapping = GeometryCalcu.getSegmentMapPoint(stop.getLocation(),
				first, second);
		if (mapping != null) {
			GPSLocation newLoc = new GPSLocation(mapping[0], mapping[1]);
			tempStop = new MapBusStop(stop.getStopName(), newLoc);
		}

		return tempStop;
	}

	public static void main(String[] args) {
		MapBusStop testStop = getMappingStop(new MapBusStop(null,
				new GPSLocation(108.922634, 34.227066)), new GPSLocation(
				108.945751, 34.198053), new GPSLocation(108.946604, 34.200143));
		System.out.println(testStop);
	}
}
