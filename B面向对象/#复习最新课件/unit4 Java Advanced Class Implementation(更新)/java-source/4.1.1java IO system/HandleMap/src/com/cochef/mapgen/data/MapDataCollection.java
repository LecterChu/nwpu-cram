package com.cochef.mapgen.data;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

import com.cochef.mapgen.gen.LoadBusLine;
import com.cochef.mapgen.gen.LoadIntsecs;
import com.cochef.mapgen.gen.RoadSectionGen;
import com.cochef.mapgen.gen.SecBusStopGen;
import com.cochef.mapgen.gen.StopSectionGen;
import com.cochef.mapgen.util.GeometryCalcu;

/**
 * 
 */

/**
 * @author mcy
 * 
 */
public class MapDataCollection {

	private static ArrayList<MapIntersection> itscts;
	private static ArrayList<MapBusLine> busLines;
	private static ArrayList<MapBusStop> origStops;
	private static ArrayList<MapRoadSection> rdSections;
	private static ArrayList<MapBusStop> newStops;
	private static ArrayList<MapStopSection> stopSections;

	public MapDataCollection() {
		// TODO Auto-generated constructor stub
		itscts = LoadIntsecs.getMapIntersections();
		busLines = LoadBusLine.getMapBusLines();
		origStops = LoadBusLine.getOrigStops();
		rdSections = RoadSectionGen.getMapRoadSections(itscts, busLines);
		// //// LoadBusLine.initAllLineName(busLines);
		stopSections = StopSectionGen.getMapStopSections(busLines);
		newStops = SecBusStopGen.getSecStops(busLines);

		LoadBusLine.addHeadRearSectionStops(busLines, rdSections);

		RoadSectionGen.initAllStreetNames(rdSections);
		RoadSectionGen.initAllRoadLength(busLines);
	}

	/**
	 * @return the itscts
	 */
	public static ArrayList<MapIntersection> getItscts() {
		return itscts;
	}

	/**
	 * @return the busLines
	 */
	public static ArrayList<MapBusLine> getBusLines() {
		return busLines;
	}

	/**
	 * @return the origStops
	 */
	public static ArrayList<MapBusStop> getOrigStops() {
		return origStops;
	}

	/**
	 * @return the rdSections
	 */
	public static ArrayList<MapRoadSection> getRdSections() {
		return rdSections;
	}

	/**
	 * @return the newStops
	 */
	public static ArrayList<MapBusStop> getNewStops() {
		return newStops;
	}

	/**
	 * @return the stopSections
	 */
	public static ArrayList<MapStopSection> getStopSections() {
		return stopSections;
	}

	/**
	 * 得到所有的街道名字
	 * 
	 * @param secs
	 *            路段集合
	 * @return 所有的街道的名字
	 */
	public static ArrayList<String> getStreets(ArrayList<MapRoadSection> secs) {
		ArrayList<String> streets = new ArrayList<String>();
		for (MapRoadSection mrs : secs) {
			String aStreet = mrs.getStreetName();
			if (!streets.contains(aStreet)) {
				streets.add(aStreet);
			}
		}
		return streets;
	}

	/**
	 * 得到某一坐标能够映射到的最近的路段
	 * 
	 * @param stop_x
	 *            坐标经度
	 * @param stop_y
	 *            坐标纬度
	 * @param radio
	 *            到能够映射的路段点的最大距离，超过此距离不做映射
	 * @return 某一坐标能够映射到的最近的路段，若无法映射则返回null
	 */
	public static MapRoadSection getSubMapSec(double stop_x, double stop_y,
			double radio) {
		MapRoadSection theRDSec = null;
		double minDist = Double.MAX_VALUE;
		ArrayList<MapRoadSection> rdSecs = rdSections;
		for (MapRoadSection mapRoadSection : rdSecs) {
			double dist = GeometryCalcu.distP2Sec(new GPSLocation(stop_x,
					stop_y), mapRoadSection.getFirst().getLocation(),
					mapRoadSection.getSecond().getLocation());
			if (dist < minDist) {
				minDist = dist;
				theRDSec = mapRoadSection;
			}
		}
		System.out.println("min dist: " + minDist);
		if (minDist < radio) {
			return theRDSec;
		} else {
			return null;
		}

	}
	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Start");
		MapDataCollection mdc = new MapDataCollection();

		double max = 0;
		MapRoadSection theSection = null;
		ArrayList<Double> lens = new ArrayList<Double>();
		for (MapRoadSection rdSec : mdc.getRdSections()) {
			double temp = rdSec.getFirst().getLocation()
					.realDistance(rdSec.getSecond().getLocation());
			double sub = Math.abs(rdSec.getLength() - temp);
			if (sub > max) {
				max = sub;
				theSection = rdSec;
			}
			lens.add(sub);
		}

		System.out.println(max + " - " + theSection.getFirst().getLocation()
				+ ";" + theSection.getSecond().getLocation());
		
		for (MapBusLine line : mdc.getBusLines()) {
			if (line.getRoadSections().contains(theSection)) {
				System.out.println(line.getLineName() + ": " + line.getXys());
			}
		}

		Collections.sort(lens);
		System.out
				.println("==============================================================");
		for (Double double1 : lens) {
			System.out.println(double1);
		}

		System.out.println("End");
	}

}
