package com.cochef.mapgen.gen;

import java.util.ArrayList;

import com.cochef.mapgen.data.MapBusLine;
import com.cochef.mapgen.data.MapBusStop;
import com.cochef.mapgen.data.MapStopSection;

/**
 * @author mcy
 * 
 */
public class StopSectionGen {

	private static ArrayList<MapStopSection> stopSections;

	/**
	 * 获取站点段集合,站点段由直接连通的原始站点对组成
	 * 
	 * @param lines
	 *            所有线路的集合
	 * @return 站点段集合
	 */
	public static ArrayList<MapStopSection> getMapStopSections(
			ArrayList<MapBusLine> lines) {
		if (stopSections == null) {
			stopSections = new ArrayList<MapStopSection>();
			for (MapBusLine mapBusLine : lines) {
				ArrayList<MapBusStop[]> stopPares = mapBusLine.getBusStops();
				MapBusStop[] preStopPare = stopPares.get(0);
				MapBusStop[] curStopPare = null;
				int stopSize = stopPares.size();
				for (int i = 1; i < stopSize; i++) {
					curStopPare = stopPares.get(i);
					double secLength = getStopSecLen(preStopPare[0],
							curStopPare[0], mapBusLine);
					MapStopSection newMapStopSection = new MapStopSection(
							preStopPare[0], stopPares.get(i)[0], mapBusLine,
							secLength);
					newMapStopSection.setLine(mapBusLine);
					mapBusLine.addStopSection(newMapStopSection);
					stopSections.add(newMapStopSection);
					preStopPare = curStopPare;
				}
			}
		}

		return stopSections;
	}

	/**
	 * 得到两个站点之间的距离
	 * 
	 * @param first
	 *            第一个站点
	 * @param second
	 *            第二个站点
	 * @param theLine
	 *            站点所在的线路
	 * @return 两个站点之间的距离
	 */
	private static double getStopSecLen(MapBusStop first, MapBusStop second,
			MapBusLine theLine) {
		return theLine.getLength(first.getLocation(), second.getLocation());
	}

}
