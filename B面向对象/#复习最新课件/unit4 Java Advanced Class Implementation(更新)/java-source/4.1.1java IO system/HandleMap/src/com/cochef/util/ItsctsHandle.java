package com.cochef.util;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

import com.cochef.mapgen.data.GPSLocation;

public class ItsctsHandle {

	private static BufferedReader reader = new BufferedReader(
			new InputStreamReader(System.in));

	public static void handleFile(String filename, double distance)
			throws IOException, FileNotFoundException {
		InputStreamReader read = new InputStreamReader(new FileInputStream(
				new File(filename)), "UTF-8");
		BufferedReader input = new BufferedReader(read);
		OutputStreamWriter output = new OutputStreamWriter(
				new FileOutputStream(
						new File("intersections_after_handled.txt")), "UTF-8");

		ArrayList<String> contents = new ArrayList<String>();
		ArrayList<GPSLocation> locations = new ArrayList<GPSLocation>();
		int i = 0, j = 0;
		int index = 0;

		String str = input.readLine();
		boolean p[] = new boolean[1000];
		for (i = 0; i < 1000; i++) {
			p[i] = true;
		}
		while (str != null) {
			contents.add(str);
			locations.add(loadLocation(str));
			str = input.readLine();
		}
		System.err.println(locations.size());
		for (i = 0; i < locations.size() - 1; i++) {
			for (j = i + 1; j < locations.size(); j++) {
				if (locations.get(i).realDistance(locations.get(j)) < distance) {
					p[j] = false;
				}
			}
		}

		for (i = 0; i < contents.size(); i++) {
			if (p[i]) {
				output.write(contents.get(i) + "\n");
				System.err.println(i);
			}
		}

		output.flush();
		output.close();
	}

	private static GPSLocation loadLocation(String str) {
		StringTokenizer tokens = new StringTokenizer(str, ",");
		double x = Double.parseDouble(tokens.nextToken());
		double y = Double.parseDouble(tokens.nextToken());
		return new GPSLocation(x, y);
	}

	public static void main(String[] args) throws Exception {
		System.out.println("两路口之间距离的阈值：");
		int num = Integer.parseInt(reader.readLine());
		ItsctsHandle.handleFile("intersection.txt", num);
		System.err.println("finished~.~");
	}

}
