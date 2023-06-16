package com.cochef.mapgen.data;

import java.util.ArrayList;

/**
 * @author zhengzhen
 * 
 */
public class MapRoadSection {

	private MapIntersection first;
	private MapIntersection second;
	private String streetName;
	private double length;
	private ArrayList<MapBusStop> secBusStops; // 映射后的站点的集合

	// private long roadSectionNo;

	public MapRoadSection(MapIntersection initFirst, MapIntersection initSecond) {
		first = initFirst;
		second = initSecond;
		streetName = null;
		length = -1;
		secBusStops = new ArrayList<MapBusStop>();
	}

	/**
	 * @return the first
	 */
	public MapIntersection getFirst() {
		return first;
	}

	/**
	 * @param first
	 *            the first to set
	 */
	public void setFirst(MapIntersection first) {
		this.first = first;
	}

	/**
	 * @return the second
	 */
	public MapIntersection getSecond() {
		return second;
	}

	/**
	 * @param second
	 *            the second to set
	 */
	public void setSecond(MapIntersection second) {
		this.second = second;
	}

	/**
	 * @return the streetName
	 */
	public String getStreetName() {
		return streetName;
	}

	/**
	 * @param streetName
	 *            the streetName to set
	 */
	public void setStreetName(String streetName) {
		this.streetName = streetName;
	}

	/**
	 * @return the length
	 */
	public double getLength() {
		return length;
	}

	/**
	 * @param length
	 *            the length to set
	 */
	public void setLength(double length) {
		this.length = length;
	}

	/**
	 * @return the secBusStops
	 */
	public ArrayList<MapBusStop> getSecBusStops() {
		return secBusStops;
	}

	/**
	 * 向映射站点集合中添加站点
	 * 
	 * @param mapBusStop
	 */
	public void addBusStop(MapBusStop mapBusStop) {
		if (mapBusStop != null && !secBusStops.contains(mapBusStop)) {
			secBusStops.add(mapBusStop);
		}
	}

	public void initStreetName() {
		boolean found = false;
		if (first.getNameList() == null || second.getNameList() == null) {
//			System.out.println("哎，这个路段还没有道路的名字，恐怕得手动加了"
//					+ "\n\t位置：MapRoadSection.initStreetName");
			return;
		}
		for (String name1 : first.getNameList()) {
			for (String name2 : second.getNameList()) {
				if (name1.equals(name2)) {
					this.streetName = name1;
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}
	}

	public String toString() {
		return first.toString() + "," + second.toString();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((first == null) ? 0 : first.hashCode());
		result = prime * result + ((second == null) ? 0 : second.hashCode());
		return result;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (obj == null) {
			return false;
		}
		if (getClass() != obj.getClass()) {
			return false;
		}
		MapRoadSection other = (MapRoadSection) obj;
		if (first == null) {
			if (other.first != null) {
				return false;
			}
		} else if (!first.equals(other.first)) {
			return false;
		}
		if (second == null) {
			if (other.second != null) {
				return false;
			}
		} else if (!second.equals(other.second)) {
			return false;
		}
		return true;
	}

}
