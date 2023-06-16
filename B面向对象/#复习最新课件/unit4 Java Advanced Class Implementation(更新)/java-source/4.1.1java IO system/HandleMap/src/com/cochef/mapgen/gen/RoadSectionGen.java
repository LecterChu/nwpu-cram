package com.cochef.mapgen.gen;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.StringTokenizer;

import com.cochef.mapgen.data.GPSLocation;
import com.cochef.mapgen.data.MapBusLine;
import com.cochef.mapgen.data.MapIntersection;
import com.cochef.mapgen.data.MapRoadSection;

/**
 * @author mcy
 * 
 */
public class RoadSectionGen {

	private static ArrayList<MapRoadSection> newRSs = null;

	/**
	 * 从传入的路口集合和线路集合得到路段集合列表，并对线路集合中各个线路对象的路口集合和路段集合进行初始化操作
	 * 
	 * @param newIntsecs
	 * @param mapBusLines
	 * @return 得到路段集合列表
	 */
	public static ArrayList<MapRoadSection> getMapRoadSections(
			ArrayList<MapIntersection> newIntsecs,
			ArrayList<MapBusLine> mapBusLines) {
		if (newRSs == null) {
			newRSs = new ArrayList<MapRoadSection>();
			for (MapBusLine line : mapBusLines) {
				// 先对比xys中各个点和newIntsecs中各个路口的距离，如果小于阈值，则认为该路口在该线路中
				// LinkedHashMap用来暂存站点序列
				LinkedHashMap<MapIntersection, Double> itsctsMap = new LinkedHashMap<MapIntersection, Double>();
				StringTokenizer tokens = new StringTokenizer(line.getXys(), ";");
				while (tokens.hasMoreElements()) {
					String xyToken = (String) tokens.nextElement();
					GPSLocation tempGPS = GPSLocation.parseGpsLocation(xyToken);
					// 和所有NewIntersection比距离
					for (MapIntersection intSec : newIntsecs) {
						double dist = tempGPS
								.realDistance(intSec.getLocation());
						if (dist < 80) { // 暂时以80为界限
							if (itsctsMap.containsKey(intSec)) {
								// 已包含该路口
								// 若当前的距离比之前插入的距离小，删掉之前的，将当前值插入最后
								if (dist < itsctsMap.get(intSec)) {
									itsctsMap.remove(intSec);
									if (!isTooClose(itsctsMap, intSec, line)) {
										itsctsMap.put(intSec, dist);
									}
								}
							} else {
								if (!isTooClose(itsctsMap, intSec, line)) {
									itsctsMap.put(intSec, dist);
								}
							}
						}
					}
				}

				Iterator<Entry<MapIntersection, Double>> iter = itsctsMap
						.entrySet().iterator();
				while (iter.hasNext()) {
					Map.Entry<MapIntersection, Double> entry = (Map.Entry<MapIntersection, Double>) iter
							.next();
					line.addItsct(entry.getKey());
				}

				// 对线路得到的路口列表操作，得到路段列表，加入相应的List中
				ArrayList<MapIntersection> lineIntsecs = line.getItscts();
				MapIntersection preIntsec = lineIntsecs.get(0);
				MapIntersection curIntsec = null;
				for (int i = 1; i < lineIntsecs.size(); i++) {
					curIntsec = lineIntsecs.get(i);
					MapRoadSection tempNewRoadSection = new MapRoadSection(
							preIntsec, curIntsec);
					// 先存入newRSs，再从newRSs中得到并存入相应的line中，保证各个line中NewRoadSection对象的一致
					addMapRS(tempNewRoadSection);
					int tempIndex = newRSs.indexOf(tempNewRoadSection);
					line.addRoadSection(newRSs.get(tempIndex));
					preIntsec = curIntsec;
				}
			}
		}

		return newRSs;
	}

	private static boolean isTooClose(
			LinkedHashMap<MapIntersection, Double> itsctsMap,
			MapIntersection intSec, MapBusLine line) {
		boolean isTooClose = false;
		GPSLocation gps = new GPSLocation(line.getXYSWithItsct(intSec));
		Iterator<Entry<MapIntersection, Double>> iter = itsctsMap.entrySet()
				.iterator();
		while (iter.hasNext()) {
			Map.Entry<MapIntersection, Double> entry = (Map.Entry<MapIntersection, Double>) iter
					.next();
			GPSLocation temp = new GPSLocation(line.getXYSWithItsct(entry
					.getKey()));
			if (gps.equals(temp)) {
				isTooClose = true;
				break;
			}
		}
		return isTooClose;
	}

	/**
	 * 不重复地添加路段
	 * 
	 * @param nrs
	 */
	private static void addMapRS(MapRoadSection nrs) {
		if (!newRSs.contains(nrs)) {
			newRSs.add(nrs);
		}
	}

	public static void initAllStreetNames(ArrayList<MapRoadSection> mpSecs) {
		for (MapRoadSection mapRoadSection : mpSecs) {
			mapRoadSection.initStreetName();
		}
	}

	/**
	 * 初始化所有路段的长度
	 * 
	 * @param lines
	 *            所有线路的集合
	 */
	public static void initAllRoadLength(ArrayList<MapBusLine> lines) {
		// 初始化所有不在线路两个端点处的路段
		for (MapBusLine mbl : lines) {
			for (MapRoadSection mrs : mbl.getRoadSections()) {
				if (mrs.getLength() > 0) {
					continue;
				} else if (!mrs.getFirst().equals(mbl.getItscts().get(0))
						&& !mrs.getSecond()
								.equals(mbl.getItscts().get(
										mbl.getItscts().size() - 1))) {
					mrs.setLength(getRoadSecLen(mrs, mbl, true));
				}
			}
		}
		// 初始化所有在线路端点处的路段
		for (MapBusLine mbl : lines) {
			for (MapRoadSection mrs : mbl.getRoadSections()) {
				if (mrs.getLength() > 0) {
					continue;
				} else if (mrs.getFirst().equals(mbl.getItscts().get(0))
						|| mrs.getSecond()
								.equals(mbl.getItscts().get(
										mbl.getItscts().size() - 1))) {
					mrs.setLength(getRoadSecLen(mrs, mbl, false));
				}
			}
		}
	}

	/**
	 * 得到路段的长度
	 * 
	 * @param roadSec
	 *            路段
	 * @param theLine
	 *            路段所在线路
	 * @param isInside
	 *            该路段是否是在线路的内部。true，在路段内部；false，在路段端点处
	 * @return 路段的长度
	 */
	public static double getRoadSecLen(MapRoadSection roadSec,
			MapBusLine theLine, boolean isInside) {
		GPSLocation firstLoc = null;
		GPSLocation secondLoc = null;
		Double[] firstXY = null;
		Double[] secondXY = null;
		if (isInside) {
			firstXY = theLine.getLineItsctXYS(roadSec.getFirst());
			secondXY = theLine.getLineItsctXYS(roadSec.getSecond());
		} else {
			String[] xysLoc = theLine.getXys().split(";");
			if (roadSec.getFirst().equals(theLine.getItscts().get(0))) { // 在路段开始端点处
				String[] xyStr = xysLoc[0].split(",");
				firstXY = new Double[2];
				firstXY[0] = Double.parseDouble(xyStr[0]);
				firstXY[1] = Double.parseDouble(xyStr[1]);
				secondXY = theLine.getLineItsctXYS(roadSec.getSecond());
			} else if (roadSec.getSecond().equals(
					theLine.getItscts().get(theLine.getItscts().size() - 1))) { // 在路段结尾端点处
				firstXY = theLine.getLineItsctXYS(roadSec.getFirst());
				String[] xyStr = xysLoc[xysLoc.length - 1].split(",");
				secondXY = new Double[2];
				secondXY[0] = Double.parseDouble(xyStr[0]);
				secondXY[1] = Double.parseDouble(xyStr[1]);
			}
		}

		firstLoc = new GPSLocation(firstXY[0], firstXY[1]);
		secondLoc = new GPSLocation(secondXY[0], secondXY[1]);

		return theLine.getLength(firstLoc, secondLoc);
	}
}
