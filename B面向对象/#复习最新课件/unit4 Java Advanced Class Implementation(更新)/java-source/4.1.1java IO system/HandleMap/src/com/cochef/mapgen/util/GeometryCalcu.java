package com.cochef.mapgen.util;

import com.cochef.mapgen.data.GPSLocation;

/**
 * 
 */

/**
 * @author mcy
 * 
 */
public class GeometryCalcu {

	/**
	 * 返回两个点所确定的直线的方程 ax + by + c = 0 的三个参数，传入的两个点的经纬度在计算时会转换为相应的大地坐标
	 * 
	 * @param loc1st
	 *            第一个点的经纬度
	 * @param loc2nd
	 *            第二个点的经纬度
	 * 
	 * @return 含有三个元素的Double型数组，分别是方程中的a、b、c
	 */
	public static Double[] getEquPara(GPSLocation loc1st, GPSLocation loc2nd) {
		Double[] equPara = new Double[3];
		double[] xy1 = GPST.BLToGauss(loc1st.getGPSX(), loc1st.getGPSY());
		double[] xy2 = GPST.BLToGauss(loc2nd.getGPSX(), loc2nd.getGPSY());

		if (Math.abs(xy1[1] - xy2[1]) < 0.00001) {
			equPara[0] = 0.0;
			equPara[1] = 1.0;
			equPara[2] = -xy1[1];
		} else {
			equPara[0] = 1.0;
			equPara[1] = (xy2[0] - xy1[0]) / (xy1[1] - xy2[1]);
			equPara[2] = -xy1[0] - equPara[1] * xy1[1];
		}
		return equPara;
	}

	/**
	 * 判断点是否在线段的一定线段距离内（以线段为中轴线的一个矩形区域内，矩形长为线段长度，宽为传入的阈值的2倍）
	 * 
	 * @param point
	 *            点
	 * @param endpoint1st
	 *            线段的第一个端点
	 * @param endpoint2nd
	 *            线段的第二个端点
	 * @param radio
	 *            判断是否临近的阈值
	 * @return true, 如果点到线段的距离在一定的阈值内; false, 不在一定范围内
	 */
	public static boolean isNearRDLine(GPSLocation point,
			GPSLocation endpoint1st, GPSLocation endpoint2nd, double radio) {
		// 经纬度转大地坐标
		double[] xy = GPST.BLToGauss(point.getGPSX(), point.getGPSY());
		double[] xy2 = GPST.BLToGauss(endpoint1st.getGPSX(),
				endpoint1st.getGPSY());
		double[] xy3 = GPST.BLToGauss(endpoint2nd.getGPSX(),
				endpoint2nd.getGPSY());
		double x = xy[0];
		double y = xy[1];
		double x2 = xy2[0];
		double x3 = xy3[0];

		if (distP2L(point, endpoint1st, endpoint2nd) < radio) { // 到直线的距离在阈值内
			Double[] abc = getEquPara(endpoint1st, endpoint2nd);
			double a1 = abc[0];
			double b1 = abc[1];
			double c1 = abc[2];

			// 找线段所在直线的经过点point的垂线
			double a2 = b1;
			double b2 = -a1;
			double c2 = a1 * y - b1 * x;

			// 两直线的交点
			Double[] newXY = getIntSect(a1, b1, c1, a2, b2, c2);
			if ((newXY[0] - x2) * (newXY[0] - x3) <= 1e-6) { // 在线段范围内
				return true;
			}
		}
		return false;
	}

	/**
	 * 得到点在直线上的映射点
	 * 
	 * @param point
	 *            点
	 * @param endpoint1st
	 *            确定直线的第一个点
	 * @param endpoint2nd
	 *            确定直线的第二个点
	 * @return 点在直线上的映射点的经纬度
	 */
	public static Double[] getLineMapPoint(GPSLocation point,
			GPSLocation endpoint1st, GPSLocation endpoint2nd) {
		// 经纬度转大地坐标
		double[] xy = GPST.BLToGauss(point.getGPSX(), point.getGPSY());
		double x = xy[0];
		double y = xy[1];

		Double[] abc = getEquPara(endpoint1st, endpoint2nd);
		double a1 = abc[0];
		double b1 = abc[1];
		double c1 = abc[2];

		// 找线段所在直线的经过点point的垂线
		double a2 = b1;
		double b2 = -a1;
		double c2 = a1 * y - b1 * x;

		// 两直线的交点
		Double[] newXY = getIntSect(a1, b1, c1, a2, b2, c2);
		double[] _x = GPST.GaussToBL(newXY[0], newXY[1]);
		newXY[0] = _x[0];
		newXY[1] = _x[1];

		return newXY;
	}

	/**
	 * 得到点在线段上的映射点
	 * 
	 * @param point
	 *            点
	 * @param endpoint1st
	 *            确定线段的第一个点
	 * @param endpoint2nd
	 *            确定线段的第二个点
	 * @return 点在线段上的映射点的经纬度，如映射点不在线段上，则返回null
	 */
	public static Double[] getSegmentMapPoint(GPSLocation point,
			GPSLocation endpoint1st, GPSLocation endpoint2nd) {
		// 两直线的交点
		Double[] newXY = getLineMapPoint(point, endpoint1st, endpoint2nd);
		// 经纬度转大地坐标
		double x = GPST.BLToGauss(newXY[0], newXY[1])[0];

		double x2 = GPST
				.BLToGauss(endpoint1st.getGPSX(), endpoint1st.getGPSY())[0];
		double x3 = GPST
				.BLToGauss(endpoint2nd.getGPSX(), endpoint2nd.getGPSY())[0];
		if ((x - x2) * (x - x3) > 1e-6) {
			newXY = null;
		}

		return newXY;
	}

	/**
	 * 求点到直线的距离，直线由另外两点确定
	 * 
	 * @param point
	 *            点
	 * @param endpoint1st
	 *            确定直线的第一个点
	 * @param endpoint2nd
	 *            确定直线的第二个点
	 * @return 点到直线的距离，单位为m
	 */
	public static double distP2L(GPSLocation point, GPSLocation endpoint1st,
			GPSLocation endpoint2nd) {
		Double[] abc = getEquPara(endpoint1st, endpoint2nd);
		double[] xy = GPST.BLToGauss(point.getGPSX(), point.getGPSY());
		double x = xy[0];
		double y = xy[1];
		double dist = Math.abs(abc[0] * x + abc[1] * y + abc[2])
				/ Math.sqrt(abc[0] * abc[0] + abc[1] * abc[1]);
		return dist;
	}

	/**
	 * 点到线段的距离，线段
	 * 
	 * @param point
	 *            点
	 * @param endpoint1st
	 *            确定直线的第一个点
	 * @param endpoint2nd
	 *            确定直线的第二个点
	 * @return 点到线段的距离，单位为m，如果点不在线段为中轴线的矩形内则返回Double.MAX_VALUE
	 */
	public static double distP2Sec(GPSLocation point, GPSLocation endpoint1st,
			GPSLocation endpoint2nd) {
		Double[] mapPoint = getLineMapPoint(point, endpoint1st, endpoint2nd);
		double mapX = GPST.BLToGauss(mapPoint[0], mapPoint[1])[0];
		double x2 = GPST
				.BLToGauss(endpoint1st.getGPSX(), endpoint1st.getGPSY())[0];
		double x3 = GPST
				.BLToGauss(endpoint2nd.getGPSX(), endpoint2nd.getGPSY())[0];
		if ((mapX - x2) * (mapX - x3) < 1e-6) { // 在线段范围内
			return distP2L(point, endpoint1st, endpoint2nd);
		} else {
			return Double.MAX_VALUE;
		}

	}

	/**
	 * 根据两直线标准方程求两直线交点
	 * 
	 * @param a1
	 *            第一直线标准方程第一参数
	 * @param b1
	 *            第一直线标准方程第二参数
	 * @param c1
	 *            第一直线标准方程第三参数
	 * @param a2
	 *            第二直线标准方程第一参数
	 * @param b2
	 *            第二直线标准方程第二参数
	 * @param c2
	 *            第二直线标准方程第三参数
	 * @return 两个路段所在直线交叉点的坐标；若两路段平行，则返回null
	 */
	public static Double[] getIntSect(double a1, double b1, double c1,
			double a2, double b2, double c2) {
		Double[] itsct = null;
		double fenmu = a1 * b2 - a2 * b1;
		if (!(Math.abs(fenmu) < 1e-6)) {
			itsct = new Double[2];
			itsct[0] = (b1 * c2 - b2 * c1) / fenmu;
			itsct[1] = (c1 * a2 - c2 * a1) / fenmu;
		}
		return itsct;
	}

}
