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

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.font.FontRenderContext;
import java.awt.geom.GeneralPath;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;

/**
   An edge that is composed of multiple line segments
*/
public abstract class SegmentedLineEdge extends GeneralPathEdge
{
   /**
      Costructs an edge with no adornments.
   */
   public SegmentedLineEdge()
   {
      lineStyle = LineStyle.SOLID;
      startArrowHead = ArrowHead.NONE;
      endArrowHead = ArrowHead.NONE;
      startLabel = "";
      middleLabel = "";
      endLabel = "";
   }

   /**
      Sets the line style property.
      @param newValue the new value
   */
   public void setLineStyle(LineStyle newValue) { lineStyle = newValue; }

   /**
      Gets the line style property.
      @return the line style
   */
   public LineStyle getLineStyle() { return lineStyle; }

   /**
      Sets the start arrow head property
      @param newValue the new value
   */
   public void setStartArrowHead(ArrowHead newValue) { startArrowHead = newValue; }

   /**
      Gets the start arrow head property
      @return the start arrow head style
   */
   public ArrowHead getStartArrowHead() { return startArrowHead; }

   /**
      Sets the end arrow head property
      @param newValue the new value
   */
   public void setEndArrowHead(ArrowHead newValue) { endArrowHead = newValue; }

   /**
      Gets the end arrow head property
      @return the end arrow head style
   */
   public ArrowHead getEndArrowHead() { return endArrowHead; }

   /**
      Sets the start label property
      @param newValue the new value
   */
   public void setStartLabel(String newValue) { startLabel = newValue; }

   /**
      Gets the start label property
      @return the label at the start of the edge
   */
   public String getStartLabel() { return startLabel; }

   /**
      Sets the middle label property
      @param newValue the new value
   */
   public void setMiddleLabel(String newValue) { middleLabel = newValue; }

   /**
      Gets the middle label property
      @return the label at the middle of the edge
   */
   public String getMiddleLabel() { return middleLabel; }

   /**
      Sets the end label property
      @param newValue the new value
   */
   public void setEndLabel(String newValue) { endLabel = newValue; }

   /**
      Gets the end label property
      @return the label at the end of the edge
   */
   public String getEndLabel() { return endLabel; }

   /**
      Draws the edge.
      @param g2 the graphics context
   */
   public void draw(Graphics2D g2)
   {
      Stroke oldStroke = g2.getStroke();
      g2.setStroke(lineStyle.getStroke());
      g2.draw(getPath());
      g2.setStroke(oldStroke);
      ArrayList points = getPoints();
      startArrowHead.draw(g2, (Point2D)points.get(1),
         (Point2D)points.get(0));
      endArrowHead.draw(g2, (Point2D)points.get(points.size() - 2),
         (Point2D)points.get(points.size() - 1));

      drawString(g2, (Point2D)points.get(1), (Point2D)points.get(0), 
         startLabel, false);
      drawString(g2, (Point2D)points.get(points.size() / 2 - 1),
         (Point2D)points.get(points.size() / 2), 
         middleLabel, true);
      drawString(g2, (Point2D)points.get(points.size() - 2),
         (Point2D)points.get(points.size() - 1), 
         endLabel, false);
   }

   /**
      Draws a string.
      @param g2 the graphics context
      @param p an endpoint of the segment along which to
      draw the string
      @param q the other endpoint of the segment along which to
      draw the string
      @param s the string to draw
      @param center true if the string should be centered
      along the segment
   */

   public static void drawString(Graphics2D g2, 
      Point2D p, Point2D q, String s, boolean center)
   {
      Point2D a = getAttachmentPoint(g2, p, q, s, center);
      Font font = g2.getFont();
      FontRenderContext frc = g2.getFontRenderContext();
      Rectangle2D b = font.getStringBounds(s, frc);      
      Rectangle2D background = new Rectangle2D.Double(
         b.getX() + a.getX(), b.getY() + a.getY(),
         b.getWidth(), b.getHeight());
      Color oldColor = g2.getColor();
      g2.setColor(Color.WHITE);
      g2.fill(background);
      g2.setColor(oldColor);
      g2.drawString(s, (float)a.getX(), (float)a.getY());
   }

   /**
      Computes the attachment point for drawing a string.
      @param g2 the graphics context
      @param p an endpoint of the segment along which to
      draw the string
      @param q the other endpoint of the segment along which to
      draw the string
      @param s the string to draw
      @param center true if the string should be centered
      along the segment
      @return the point at which to draw the string
   */
   private static Point2D getAttachmentPoint(Graphics2D g2, 
      Point2D p, Point2D q, String s, boolean center)
   {
      if (s == null) s = "";
      Font font = g2.getFont();
      FontRenderContext frc = g2.getFontRenderContext();
      Rectangle2D b = font.getStringBounds(s, frc);      
      final int GAP = 3;
      double xoff = GAP;
      double yoff = -GAP;
      Point2D attach = q;
      if (center)
      {
         if (p.getX() > q.getX()) 
         { 
            return getAttachmentPoint(g2, q, p, s, center); 
         }
         attach = new Point2D.Double((p.getX() + q.getX()) / 2, 
            (p.getY() + q.getY()) / 2);
         if (p.getY() < q.getY())
            yoff = b.getY() + b.getHeight() - GAP;
         else if (p.getY() == q.getY())
            xoff = -b.getWidth() / 2;
         else
            yoff = -b.getY() + GAP;
      }
      else 
      {
         if (p.getX() < q.getX())
         {
            xoff = -GAP - b.getWidth();
         }
         if (p.getY() > q.getY())
         {
            yoff = -b.getY() + GAP;
         }
      }
      return new Point2D.Double(attach.getX() + xoff, attach.getY() + yoff);
   }

   /**
      Computes the extent of a string that is drawn along a line segment.
      @param g2 the graphics context
      @param p an endpoint of the segment along which to
      draw the string
      @param q the other endpoint of the segment along which to
      draw the string
      @param s the string to draw
      @param center true if the string should be centered
      along the segment
      @return the rectangle enclosing the string
   */
   public static Rectangle2D getStringBounds(Graphics2D g2, 
      Point2D p, Point2D q, String s, boolean center)
   {
      if (g2 == null) return new Rectangle2D.Double();
      Font font = g2.getFont();
      FontRenderContext frc = g2.getFontRenderContext();
      Rectangle2D b = font.getStringBounds(s, frc);      
      Point2D a = getAttachmentPoint(g2, p, q, s, center);
      return new Rectangle2D.Double(b.getX() + a.getX(),
         b.getY() + a.getY(), b.getWidth(), b.getHeight());
   }

   public Rectangle2D getBounds(Graphics2D g2)
   {
      ArrayList points = getPoints();
      Rectangle2D r = super.getBounds(g2);
      r.add(getStringBounds(g2, 
               (Point2D)points.get(1), (Point2D)points.get(0), 
               startLabel, false));
      r.add(getStringBounds(g2, 
               (Point2D)points.get(points.size() / 2 - 1),
               (Point2D)points.get(points.size() / 2), 
               middleLabel, true));
      r.add(getStringBounds(g2, 
               (Point2D)points.get(points.size() - 2),
               (Point2D)points.get(points.size() - 1), 
               endLabel, false));
      return r;
   }

   public GeneralPath getPath()
   {
      ArrayList points = getPoints();
      GeneralPath path = new GeneralPath();
      Point2D p = (Point2D)points.get(points.size() - 1);
      path.moveTo((float)p.getX(), (float)p.getY());
      for (int i = points.size() - 2; i >= 0; i--)
      {
         p = (Point2D)points.get(i);
         path.lineTo((float)p.getX(), (float)p.getY());
      }
      return path;
   }

   public Line2D getConnectionPoints()
   {
      ArrayList points = getPoints();
      return new Line2D.Double((Point2D)points.get(0),
         (Point2D)points.get(points.size() - 1));
   }

   /**
      Gets the corner points of this segmented line edge
      @return an array list of Point2D objects, containing
      the corner points
   */
   public abstract ArrayList getPoints();

   private LineStyle lineStyle;
   private ArrowHead startArrowHead;
   private ArrowHead endArrowHead;
   private String startLabel;
   private String middleLabel;
   private String endLabel;
}
