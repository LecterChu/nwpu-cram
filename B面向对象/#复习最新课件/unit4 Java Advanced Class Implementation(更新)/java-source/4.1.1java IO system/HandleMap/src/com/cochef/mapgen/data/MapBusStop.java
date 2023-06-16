package com.cochef.mapgen.data;

/**
 * 站点数据模型的抽象
 * 
 * @author zhengzhen
 */
public class MapBusStop {
	private String stopName;
	private GPSLocation location;
	private MapRoadSection roadSection;

	/**
	 * 构造函数
	 * 
	 * @param initStopID
	 *            站点ID要设置的初值
	 * @param initStopName
	 *            站点名称要设置的初值
	 */
	public MapBusStop(String initStopName, GPSLocation initGpsLocation) {
		stopName = initStopName;
		location = initGpsLocation;
	}

	/**
	 * 构造函数
	 * 
	 * @param initStopID
	 *            站点ID要设置的初值
	 * @param initStopName
	 *            站点名称要设置的初值
	 * @param initCoordX
	 *            站点经度
	 * @param initCoordY
	 *            站点纬度
	 * @param initBusLines
	 *            站点所在的路线的列表
	 */
	public MapBusStop(int initStopID, String initStopName, float initCoordX,
			float initCoordY) {
		stopName = initStopName;
		location = new GPSLocation(initCoordX, initCoordY);
	}

	/**
	 * 获得站点名称
	 * 
	 * @return 站点名称
	 */
	public String getStopName() {
		return stopName;
	}

	/**
	 * 设置站点名称
	 * 
	 * @param stopName
	 *            要设置的站点名称
	 */
	public void setStopName(String stopName) {
		this.stopName = stopName;
	}

	/**
	 * 获得站点经度
	 * 
	 * @return 站点经度
	 */
	public double getCoordX() {
		return this.location.getGPSX();
	}

	/**
	 * 设置站点经度
	 * 
	 * @param coordX
	 *            要设置的站点经度
	 */
	public void setCoordX(float coordX) {
		this.location.setGPSX(coordX);
	}

	/**
	 * 获得站点纬度
	 * 
	 * @return 站点纬度
	 */
	public double getCoordY() {
		return this.location.getGPSY();
	}

	/**
	 * 设置站点纬度
	 * 
	 * @param coordY
	 *            要设置的站点纬度
	 */
	public void setCoordY(float coordY) {
		this.location.setGPSY(coordY);
	}

	/**
	 * 
	 * 获得站点位置
	 * 
	 * @return 站点所在的位置
	 */
	public GPSLocation getLocation() {
		return location;
	}

	/**
	 * 
	 * 设置站点位置
	 * 
	 * @param 设置站点所在的位置
	 */
	public void setLocation(GPSLocation location) {
		this.location = location;
	}

	/**
	 * @return the roadSection
	 */
	public MapRoadSection getRoadSection() {
		return roadSection;
	}

	/**
	 * @param roadSection
	 *            the roadSection to set
	 */
	public void setRoadSection(MapRoadSection roadSection) {
		this.roadSection = roadSection;
	}

	public String toString() {
		return stopName + "-" + location;
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
		result = prime * result
				+ ((stopName == null) ? 0 : stopName.hashCode());
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
		MapBusStop other = (MapBusStop) obj;
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
