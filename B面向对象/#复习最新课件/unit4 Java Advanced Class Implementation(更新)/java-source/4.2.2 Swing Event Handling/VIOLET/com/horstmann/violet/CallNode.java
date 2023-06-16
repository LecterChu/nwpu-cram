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
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.List;

/**
   A method call node in a scenario diagram.
*/
public class CallNode extends RectangularNode
{
   /**
      Construct a call node with a default size
   */
   public CallNode()
   {
      setBounds(new Rectangle2D.Double(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT));
   }

   public void draw(Graphics2D g2)
   {
      Color oldColor = g2.getColor();
      g2.setColor(Color.WHITE);
      g2.fill(getBounds());
      g2.setColor(oldColor);
      if (openBottom)
      {
         Rectangle2D b = getBounds();
         double x1 = b.getX();
         double x2 = x1 + b.getWidth();
         double y1 = b.getY();
         double y3 = y1 + b.getHeight();
         double y2 = y3 - CALL_YGAP;
         g2.draw(new Line2D.Double(x1, y1, x2, y1));
         g2.draw(new Line2D.Double(x1, y1, x1, y2));
         g2.draw(new Line2D.Double(x2, y1, x2, y2));
         Stroke oldStroke = g2.getStroke();
         g2.setStroke(new BasicStroke(1.0f, 
                         BasicStroke.CAP_ROUND, 
                         BasicStroke.JOIN_ROUND, 
                         0.0f, 
                         new float[] { 5.0f, 5.0f }, 0.0f));
         g2.draw(new Line2D.Double(x1, y2, x1, y3));
         g2.draw(new Line2D.Double(x2, y2, x2, y3));
         g2.setStroke(oldStroke);
      }
      else
         g2.draw(getBounds());
   }

   /**
      Gets the implicit parameter of this call.
      @return the implicit parameter node
   */
   public ImplicitParameterNode getImplicitParameter()
   {
      return implicitParameter;
   }

   /**
      Sets the implicit parameter of this call.
      @param newValue the implicit parameter node
   */
   public void setImplicitParameter(ImplicitParameterNode newValue)
   {
      implicitParameter = newValue;
   }

   public Point2D getConnectionPoint(Direction d)
   {
      if (d.getX() > 0)
         return new Point2D.Double(getBounds().getMaxX(),
            getBounds().getMinY());
      else
         return new Point2D.Double(getBounds().getX(),
            getBounds().getMinY());
   }

   public boolean addEdge(Edge e, Point2D p1, Point2D p2)
   {
      if (!(e instanceof CallEdge)) return false;
      Node end = e.getEnd();
      if (end == null) return false;
      Node n = null;
      if (end instanceof CallNode) 
      {
         // check for cycles
         Node parent = this; 
         while (parent != null && end != parent) 
            parent = parent.getParent();
         
         if (end.getParent() == null && end != parent)
         {
            n = end;
         }
         else
         {
            CallNode c = new CallNode();
            c.implicitParameter = ((CallNode)end).implicitParameter;
            e.connect(this, c);
            n = c;
         }
      }
      else if (end instanceof ImplicitParameterNode)
      {
         if (((ImplicitParameterNode)end).getTopRectangle().contains(p2))
         {
            n = end;
            ((CallEdge)e).setMiddleLabel("\u00ABcreate\u00BB");
         }
         else
         {
            CallNode c = new CallNode();
            c.implicitParameter = (ImplicitParameterNode)end;
            e.connect(this, c);
            n = c;
         }
      }
      else return false;

      int i = 0;
      List calls = getChildren();
      while (i < calls.size() && ((Node)calls.get(i)).getBounds().getY() <= p1.getY()) 
         i++;
      addChild(i, n);
      return true;
   }

   public void removeEdge(Graph g, Edge e)
   {
      if (e.getStart() == this)
         removeChild(e.getEnd());
   }

   public void removeNode(Graph g, Node n)
   {
      if (n == getParent() || n == implicitParameter)
         g.removeNode(this);
   }

   public void layout(Graph g, Graphics2D g2, Grid grid)
   {
      if (implicitParameter == null) return;
      double xmid = implicitParameter.getBounds().getCenterX();

      for (CallNode c = (CallNode)getParent(); 
           c != null; c = (CallNode)c.getParent())
         if (c.implicitParameter == implicitParameter)
            xmid += getBounds().getWidth() / 2;

      translate(xmid - getBounds().getCenterX(), 0);
      double ytop = getBounds().getY() + CALL_YGAP;

      List calls = getChildren();
      for (int i = 0; i < calls.size(); i++)
      {
         Node n = (Node)calls.get(i);
         if (n instanceof ImplicitParameterNode) // <<create>>
         {
            n.translate(0, ytop - ((ImplicitParameterNode)n).getTopRectangle().getCenterY());
            ytop += ((ImplicitParameterNode)n).getTopRectangle().getHeight() / 2 + CALL_YGAP;
         }
         else if (n instanceof CallNode)
         {
            Rectangle2D bounds = n.getBounds();
            n.translate(0, ytop - bounds.getY());
            n.layout(g, g2, grid);
            if (((CallNode)n).signaled)
               ytop += CALL_YGAP;
            else
               ytop += n.getBounds().getHeight() + CALL_YGAP;
         }
      }
      if (openBottom) ytop += 2 * CALL_YGAP;
      Rectangle2D b = getBounds();
      setBounds(new Rectangle2D.Double(b.getX(), b.getY(), b.getWidth(), Math.max(DEFAULT_HEIGHT, ytop - b.getY())));
   }

   public boolean addNode(Node n, Point2D p)
   {
      return n instanceof PointNode;
   }

   /**
      Sets the signaled property.
      @param newValue true if this node is the target of a signal edge
   */      
   public void setSignaled(boolean newValue) { signaled = newValue; }

   /**
      Gets the openBottom property.
      @return true if this node is the target of a signal edge
   */
   public boolean isOpenBottom() { return openBottom; }

   /**
      Sets the openBottom property.
      @param newValue true if this node is the target of a signal edge
   */      
   public void setOpenBottom(boolean newValue) { openBottom = newValue; }


   private ImplicitParameterNode implicitParameter;
   private boolean signaled;
   private boolean openBottom;

   private static int DEFAULT_WIDTH = 16;
   private static int DEFAULT_HEIGHT = 30;
   public static int CALL_YGAP = 20;
}
