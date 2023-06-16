package com.cochef.mapgen.gen;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.StringTokenizer;

import com.cochef.mapgen.data.GPSLocation;
import com.cochef.mapgen.data.MapIntersection;

/**
 * @author lyw 得到newIntersections列表
 */
public class LoadIntsecs {

	private static ArrayList<MapIntersection> mapIntersections = null;

	/**
	 * 往屏幕打印信息
	 * 
	 * @param list
	 */
	// private static void printNewIntersections(ArrayList<MapIntersection>
	// list) {
	// // TODO Auto-generated method stub
	// int i = 0, j = 0;
	// for (; i < list.size(); i++) {
	// System.out.println(list.get(i).getLocation().getGPSX() + ","
	// + list.get(i).getLocation().getGPSY() + ":");
	// for (j=0; j < list.get(i).getNameList().size(); j++) {
	// System.out.println(list.get(i).getNameList().get(j) + " ");
	// }
	// }
	// }

	/**
	 * @param str
	 *            与路口关联的路段名称 ，例如：雁塔西路-长安中路-长安南路
	 * @return 名称列表，即去除"-"
	 */
	private static ArrayList<String> handleNames(String str) {
		ArrayList<String> list = new ArrayList<String>();
		StringTokenizer token1 = new StringTokenizer(str, "=");
		String temp;
		while (token1.hasMoreTokens()) {
			temp = token1.nextToken();
			list.add(temp);
		}
		return list;
	}

	/**
	 * @return the mapIntersections
	 */
	public static ArrayList<MapIntersection> getMapIntersections() {
		if (mapIntersections == null) {
			mapIntersections = new ArrayList<MapIntersection>();
			InputStreamReader read;
			try {
				read = new InputStreamReader(new FileInputStream(new File(
						"intersection.txt")), "UTF-8");
				BufferedReader input = new BufferedReader(read);
				StringTokenizer tokens;
				GPSLocation location;
				ArrayList<String> names;
				double x, y;
				String msg = input.readLine();
				while (msg != null) {
					tokens = new StringTokenizer(msg, ",");
					if (tokens.countTokens() == 3) {
						x = Double.parseDouble(tokens.nextToken());
						y = Double.parseDouble(tokens.nextToken());
						names = new ArrayList<String>();
						names = handleNames(tokens.nextToken());
						location = new GPSLocation(x, y);
						MapIntersection newIntersection = new MapIntersection(
								location, names);
						if (!mapIntersections.contains(newIntersection)) {
							mapIntersections.add(newIntersection);
						}
					}
					msg = input.readLine();
				}
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return mapIntersections;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		getMapIntersections();
		double min = Double.MAX_VALUE;
		int minI = -1, minJ = -1;
		ArrayList<Double> dists = new ArrayList<Double>();
		for (int i = 0; i < mapIntersections.size(); i++) {
			for (int j = i + 1; j < mapIntersections.size(); j++) {
				double newDist = mapIntersections.get(i).getLocation()
						.realDistance(mapIntersections.get(j).getLocation());
				dists.add(newDist);
				if (newDist < 90 && newDist > 80) {
					min = newDist;
					minI = i;
					minJ = j;
					break;
				}
			}
		}
		System.out.println(min + " == "
				+ mapIntersections.get(minI).getLocation() + ";"
				+ mapIntersections.get(minJ).getLocation());
//		Collections.sort(dists);
//		int i = 0;
//		for (Double double1 : dists) {
//			System.out.print(double1 + "\t\t");
//			if (i % 5 == 0) {
//				System.out.println();
//			}
//			i++;
//		}
	}

}
