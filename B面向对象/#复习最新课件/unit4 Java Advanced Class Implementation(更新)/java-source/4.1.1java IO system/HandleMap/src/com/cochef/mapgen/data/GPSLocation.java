package com.cochef.mapgen.data;

import com.cochef.mapgen.util.GPST;

/**
 * 
 */

/**
 * 经纬度位置
 * 
 * @author zhengzhen
 */
public class GPSLocation {

	/**
	 * 经度
	 */
	private double locationX;

	/**
	 * 纬度
	 */
	private double locationY;

	/**
	 * 构造函数，构造GPSLocation对象
	 * 
	 * @param initLocationX
	 *            经度
	 * @param initLocationY
	 *            纬度
	 */
	public GPSLocation(double initLocationX, double initLocationY) {
		locationX = initLocationX;
		locationY = initLocationY;
	}
	
	public GPSLocation(Double[] xy) {
		locationX = xy[0];
		locationY = xy[1];
	}

	/**
	 * 得到经度
	 * 
	 * @return 经度
	 */
	public double getGPSX() {
		return locationX;
	}

	/**
	 * 设置经度
	 * 
	 * @param newLocationX
	 *            要设置的经度值
	 */
	public void setGPSX(double newLocationX) {
		this.locationX = newLocationX;
	}

	/**
	 * 得到纬度
	 * 
	 * @return 纬度
	 */
	public double getGPSY() {
		return locationY;
	}

	/**
	 * 设置纬度
	 * 
	 * @param newLocationY
	 *            要设置的纬度值
	 */
	public void setGPSY(double newLocationY) {
		this.locationY = newLocationY;
	}

	/**
	 * 给出点（包含经纬度信息），求两个点之间的距离
	 * 
	 * @param point1
	 *            第一个点
	 * @param point2
	 *            第二个点
	 * @return 传入的两个点之间的距离
	 */
	public static double realDistance(GPSLocation point1, GPSLocation point2) {
		double lon1 = point1.getGPSX();
		double lat1 = point1.getGPSY();
		double lon2 = point2.getGPSX();
		double lat2 = point2.getGPSY();

		return getDistance(lon1, lat1, lon2, lat2);
	}

	/**
	 * 求调用对象和传入参数之间的距离
	 * 
	 * @param point
	 *            传入的点
	 * @return 传入的点与调用者的距离
	 */
	public double realDistance(GPSLocation point) {
		double lon = point.getGPSX();
		double lat = point.getGPSY();

		return getDistance(locationX, locationY, lon, lat);
	}

	/**
	 * 给出两组经纬度，求它们之间的距离
	 * 
	 * @param lon1
	 *            第一个点的经度
	 * @param lat1
	 *            第一个点的纬度
	 * @param lon2
	 *            第二个点的经度
	 * @param lat2
	 *            第二个点的纬度
	 * @return 两个点之间的距离
	 */
	private static double getDistance(double lon1, double lat1, double lon2,
			double lat2) {
		// TODO Auto-generated method stub
		double[] xy1 = GPST.BLToGauss(lon1, lat1);
		double[] xy2 = GPST.BLToGauss(lon2, lat2);
		return Math.sqrt((xy2[0] - xy1[0]) * (xy2[0] - xy1[0])
				+ (xy2[1] - xy1[1]) * (xy2[1] - xy1[1]));
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
		long temp;
		temp = Double.doubleToLongBits(locationX);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(locationY);
		result = prime * result + (int) (temp ^ (temp >>> 32));
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
		GPSLocation other = (GPSLocation) obj;
		if (Double.doubleToLongBits(locationX) != Double
				.doubleToLongBits(other.locationX)) {
			return false;
		}
		if (Double.doubleToLongBits(locationY) != Double
				.doubleToLongBits(other.locationY)) {
			return false;
		}
		return true;
	}

	public String toString() {
		return locationX + "," + locationY;
	}

	public static GPSLocation parseGpsLocation(String gpsString) {
		String[] strXY = gpsString.split(",");
		GPSLocation tempLocation = new GPSLocation(
				Double.parseDouble(strXY[0]), Double.parseDouble(strXY[1]));
		return tempLocation;
	}
	
	public static void main(String[] args) {
		GPSLocation loc1 = GPSLocation.parseGpsLocation("108.86276,34.278769");
		GPSLocation loc2 = GPSLocation.parseGpsLocation("108.858407,34.273071");
		System.err.println(loc1.realDistance(loc2));
		
	}

}
