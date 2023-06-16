/*
Violet - A program for editing UML diagrams.

Copyright (C) 2002 Cay S. Horstmann (http://horstmann.com)

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

package com.horstmann.violet;

import java.awt.BasicStroke;
import java.awt.Graphics2D;
import java.awt.Shape;
import java.awt.geom.GeneralPath;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

/**
   A class that assumes that an edge can yield its shape
   as a general path, and then takes advantage of the fact
   that containment testing can be done by fattening the
   general path.
*/
abstract class GeneralPathEdge extends AbstractEdge
{  
   /**
      Returns the path that should be stroked to
      draw this edge. The path does not include
      arrow tips or labels.
      @return a path along the edge
   */
   public abstract GeneralPath getPath();

   public Rectangle2D getBounds(Graphics2D g2)
   {
      return getPath().getBounds();
   }

   public boolean contains(Point2D aPoint)
   {
      final double MAX_DIST = 3;

      // the end points may contain small nodes, so don't
      // match them
      Line2D conn = getConnectionPoints();
      if (aPoint.distance(conn.getP1()) <= MAX_DIST 
         || aPoint.distance(conn.getP2()) <= MAX_DIST)
         return false;

      GeneralPath p = getPath();
      BasicStroke fatStroke = new BasicStroke(
         (float)(2 * MAX_DIST));
      Shape fatPath = fatStroke.createStrokedShape(p);
      return fatPath.contains(aPoint);
   }
}
