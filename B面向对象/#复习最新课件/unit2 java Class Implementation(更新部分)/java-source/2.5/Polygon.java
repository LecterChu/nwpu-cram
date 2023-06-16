import java.util.ArrayList;
import java.util.List;

import Point.*;
public class Polygon {
	public static  List<Point2D> makePolygon(Point2D...points) {
		List<Point2D> result = new ArrayList<Point2D>();
		for(Point2D item:points)
			result.add(item);
		return result;
		
	}
	public static void main(String[] args) {
		List<Point2D> ls = makePolygon(new Point2D(23,23));
		List<Point2D> lt = makePolygon(new Point2D(23,23),new Point2D(23,23));
		System.out.println(ls +"\n"+lt);
	}
	

}
