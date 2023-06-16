/**
 * 
 */
package com.cochef.mapgen.data;

import java.util.ArrayList;

/**
 * @author mcy
 * 
 */
public class MapStopSection {

	private MapBusStop firstStop;
	private MapBusStop secondStop;
	private MapBusLine line;
	private double length;

	public MapStopSection(MapBusStop initFirst, MapBusStop initSecond,
			MapBusLine initLine, double initLen) {
		firstStop = initFirst;
		secondStop = initSecond;
		line = initLine;
		length = initLen;
	}

	/**
	 * @return the firstStop
	 */
	public MapBusStop getFirstStop() {
		return firstStop;
	}

	/**
	 * @return the secondStop
	 */
	public MapBusStop getSecondStop() {
		return secondStop;
	}

	/**
	 * @return the length
	 */
	public double getLength() {
		return length;
	}

	/**
	 * @return the line
	 */
	public MapBusLine getLine() {
		return line;
	}

	/**
	 * @param line
	 *            the line to set
	 */
	public void setLine(MapBusLine line) {
		this.line = line;
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
				+ ((firstStop == null) ? 0 : firstStop.hashCode());
		result = prime * result + ((line == null) ? 0 : line.hashCode());
		result = prime * result
				+ ((secondStop == null) ? 0 : secondStop.hashCode());
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
		MapStopSection other = (MapStopSection) obj;
		if (firstStop == null) {
			if (other.firstStop != null) {
				return false;
			}
		} else if (!firstStop.equals(other.firstStop)) {
			return false;
		}
		if (line == null) {
			if (other.line != null) {
				return false;
			}
		} else if (!line.equals(other.line)) {
			return false;
		}
		if (secondStop == null) {
			if (other.secondStop != null) {
				return false;
			}
		} else if (!secondStop.equals(other.secondStop)) {
			return false;
		}
		return true;
	}

}
