package com.cochef.mapgen.data;

import java.util.ArrayList;
import java.util.StringTokenizer;

public class MapIntersection {

	private GPSLocation location;
	private ArrayList<String> nameList;

	public MapIntersection(GPSLocation location, ArrayList<String> nameList) {
		this.location = location;
		this.nameList = nameList;
	}

	/**
	 * @return the location
	 */
	public GPSLocation getLocation() {
		return location;
	}

	/**
	 * @param location
	 *            the location to set
	 */
	public void setLocation(GPSLocation location) {
		this.location = location;
	}

	/**
	 * @return the nameList
	 */
	public ArrayList<String> getNameList() {
		return nameList;
	}

	/**
	 * @param nameList
	 *            the nameList to set
	 */
	public void setNameList(ArrayList<String> nameList) {
		this.nameList = nameList;
	}

	public String toString() {
		return location.toString();
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
		result = prime * result
				+ ((location == null) ? 0 : location.hashCode());
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
		MapIntersection other = (MapIntersection) obj;
		if (location == null) {
			if (other.location != null) {
				return false;
			}
		} else if (!location.equals(other.location)) {
			return false;
		}
		return true;
	}

}
