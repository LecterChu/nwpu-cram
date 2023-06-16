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
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Point2D;
import java.awt.event.InputEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;
import javax.swing.JPanel;
import javax.swing.JOptionPane;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.util.ArrayList;

/**
   A panel to draw a graph
*/
public class GraphPanel extends JPanel
{
   /**
      Constructs a graph.
      @param aToolBar the tool bar with the node and edge tools
   */
   public GraphPanel(ToolBar aToolBar)
   {
      grid = new Grid();
      gridSize = GRID;
      grid.setGrid((int)gridSize, (int)gridSize);
      zoom = 1;
      toolBar = aToolBar;
      setBackground(Color.WHITE);

      addMouseListener(new
         MouseAdapter()
         {
            public void mousePressed(MouseEvent event)
            {
               requestFocus();
               Point2D mousePoint = new Point2D.Double(
                  event.getX() / zoom, event.getY() / zoom);
               Node n = graph.findNode(mousePoint); 
               Edge e = graph.findEdge(mousePoint);
               Object tool = toolBar.getSelectedTool();
               if (event.getClickCount() > 1 
                  || (event.getModifiers() 
                     & InputEvent.BUTTON1_MASK) == 0) 
                  // double/right-click
               {
                  if (e != null)
                  {
                     selected = e;
                     editSelected();
                  }
                  else if (n != null)
                  {
                     selected = n;
                     editSelected();
                  }
               }
               else if (tool == null) // select
               {
                  if (e != null)
                  {
                     selected = e;
                  }
                  else if (n != null)
                  {
                     selected = n;
                     dragStartBounds = n.getBounds();
                     dragStartPoint = mousePoint;
                  }
                  else 
                  {
                     selected = null;
                  }
               }
               else if (tool instanceof Node)
               {
                  Node prototype = (Node)tool;
                  Node newNode = (Node)prototype.clone();
                  boolean added = graph.add(newNode, mousePoint);
                  if (added)
                  {
                     modified = true;
                     selected = newNode;
                     dragStartBounds = newNode.getBounds();
                     dragStartPoint = mousePoint;
                  }
                  else if (n != null)
                  {
                     selected = n;
                     dragStartBounds = n.getBounds();
                     dragStartPoint = mousePoint;
                  }
               }
               else if (tool instanceof Edge)
               {
                  if (n != null) rubberBandStart = mousePoint;
               }
               lastMousePoint = mousePoint;
               repaint();
            }

            public void mouseReleased(MouseEvent event)
            {
               Object tool = toolBar.getSelectedTool();
               if (rubberBandStart != null)
               {
                  Point2D mousePoint = new Point2D.Double(
                     event.getX() / zoom, event.getY() / zoom);
                  Edge prototype = (Edge)tool;
                  Edge newEdge = (Edge)prototype.clone();
                  if (mousePoint.distance(rubberBandStart) > CONNECT_THRESHOLD &&
                     graph.connect(newEdge, 
                         rubberBandStart, mousePoint))
                  {
                     modified = true;
                     selected = newEdge;
                  }
               }

               revalidate();
               repaint();

               lastMousePoint = null;
               dragStartBounds = null;
               rubberBandStart = null;
            }
         });

      addMouseMotionListener(new
         MouseMotionAdapter()
         {
            public void mouseDragged(MouseEvent event)
            {
               Point2D mousePoint = new Point2D.Double(
                  event.getX() / zoom, event.getY() / zoom);
               if (dragStartBounds != null)
               {
                  if (selected instanceof Node)
                  {
                     Node n = (Node)selected;
                     Rectangle2D bounds = n.getBounds();
                     n.translate(
                        dragStartBounds.getX() - bounds.getX() 
                        + mousePoint.getX() - dragStartPoint.getX(),
                        dragStartBounds.getY() - bounds.getY() 
                        + mousePoint.getY() - dragStartPoint.getY());
                     graph.layout();
                  }
               }
               lastMousePoint = mousePoint;
               repaint();
            }
         });
  }



   /**
      Edits the properties of the selected graph element.
   */
   public void editSelected()
   {
      if (selected == null) return;
      PropertySheet sheet = new PropertySheet(selected, this);
      sheet.addChangeListener(new
         ChangeListener()
         {
            public void stateChanged(ChangeEvent event)
            {
               graph.layout();
               repaint();
            }
         });
      JOptionPane.showInternalMessageDialog(this, sheet, 
         "Properties", 
         JOptionPane.QUESTION_MESSAGE);        
      modified = true;
   }

   /**
      Removes the selected node or edge.
   */
   public void removeSelected()
   {
      if (selected instanceof Node)
      {
         graph.removeNode((Node)selected);
      }
      else if (selected instanceof Edge)
      {
         graph.removeEdge((Edge)selected);
      }          
      modified = true;
      repaint();               
   }

   /**
      Set the graph in the panel
      @param aGraph the graph to be displayed and edited
   */
   public void setGraph(Graph aGraph)
   {
      graph = aGraph;
      modified = false;
      revalidate();
      repaint();
   }

   public void paintComponent(Graphics g)
   {
      super.paintComponent(g);
      Graphics2D g2 = (Graphics2D) g;
      g2.scale(zoom, zoom);
      Rectangle2D bounds = getBounds();
      Rectangle2D graphBounds = graph.getBounds(g2);
      if (!hideGrid)
         grid.draw(g2, new Rectangle2D.Double(0, 0, Math.max(bounds.getMaxX() / zoom, graphBounds.getMaxX()), Math.max(bounds.getMaxY() / zoom, graphBounds.getMaxY())));
      //      graph.draw(g2, lastMousePoint != null ? new Grid() : grid);
      graph.draw(g2, grid);

      if (!graph.getNodes().contains(selected)
         && !graph.getEdges().contains(selected))
         selected = null;

      if (selected instanceof Node)
      {
         Rectangle2D grabberBounds = ((Node)selected).getBounds();
         drawGrabber(g2, grabberBounds.getMinX(), grabberBounds.getMinY());
         drawGrabber(g2, grabberBounds.getMinX(), grabberBounds.getMaxY());
         drawGrabber(g2, grabberBounds.getMaxX(), grabberBounds.getMinY());
         drawGrabber(g2, grabberBounds.getMaxX(), grabberBounds.getMaxY());
      }

      if (selected instanceof Edge)
      {
         Line2D line = ((Edge)selected).getConnectionPoints();
         drawGrabber(g2, line.getX1(), line.getY1());
         drawGrabber(g2, line.getX2(), line.getY2());
      }

      if (rubberBandStart != null)
      {
         Color oldColor = g2.getColor();
         g2.setColor(PURPLE);
         g2.draw(new Line2D.Double(rubberBandStart, lastMousePoint));
         g2.setColor(oldColor);
      }
   }

   /**
      Draws a single "grabber", a filled square
      @param g2 the graphics context
      @param x the x coordinate of the center of the grabber
      @param y the y coordinate of the center of the grabber
   */
   public static void drawGrabber(Graphics2D g2, double x, double y)
   {
      final int SIZE = 5;
      Color oldColor = g2.getColor();
      g2.setColor(PURPLE);
      g2.fill(new Rectangle2D.Double(x - SIZE / 2,
         y - SIZE / 2, SIZE, SIZE));      
      g2.setColor(oldColor);
   }

   public Dimension getPreferredSize()
   {
      Rectangle2D bounds 
         = graph.getBounds((Graphics2D)getGraphics());
      return new Dimension(
         (int)(zoom * bounds.getMaxX()), 
         (int)(zoom * bounds.getMaxY()));
   }

   /**
      Changes the zoom of this panel. The zoom is 1 by
      default and is multiplied by sqrt(2) for each positive
      stem or divided by sqrt(2) for each negative step.
      @param steps the number of steps by which to change
      the zoom. A positive value zooms in, a negative value
      zooms out.
   */
   public void changeZoom(int steps)
   {
      final double FACTOR = Math.sqrt(2);
      for (int i = 1; i <= steps; i++)
         zoom *= FACTOR;
      for (int i = 1; i <= -steps; i++)
         zoom /= FACTOR;
      revalidate();
      repaint();
   }

   /**
      Changes the grid size of this panel. The zoom is 10 by
      default and is multiplied by sqrt(2) for each positive
      stem or divided by sqrt(2) for each negative step.
      @param steps the number of steps by which to change
      the zoom. A positive value zooms in, a negative value
      zooms out.
   */
   public void changeGridSize(int steps)
   {
      final double FACTOR = Math.sqrt(2);
      for (int i = 1; i <= steps; i++)
         gridSize *= FACTOR;
      for (int i = 1; i <= -steps; i++)
         gridSize /= FACTOR;
      grid.setGrid((int)gridSize, (int)gridSize);      
      graph.layout();
      repaint();
   }

   public void selectNext(int n)
   {
      ArrayList selectables = new ArrayList();
      selectables.addAll(graph.getNodes());
      selectables.addAll(graph.getEdges());
      if (selectables.size() == 0) return;
      java.util.Collections.sort(selectables, new
         java.util.Comparator()
         {
            public int compare(Object obj1, Object obj2)
            {
               double x1;
               double y1;
               if (obj1 instanceof Node)
               {
                  Rectangle2D bounds = ((Node)obj1).getBounds();
                  x1 = bounds.getX();
                  y1 = bounds.getY();
               }
               else
               {
                  Point2D start = ((Edge)obj1).getConnectionPoints().getP1();
                  x1 = start.getX();
                  y1 = start.getY();                  
               }
               double x2;
               double y2;
               if (obj2 instanceof Node)
               {
                  Rectangle2D bounds = ((Node)obj2).getBounds();
                  x2 = bounds.getX();
                  y2 = bounds.getY();
               }
               else
               {
                  Point2D start = ((Edge)obj2).getConnectionPoints().getP1();
                  x2 = start.getX();
                  y2 = start.getY();                  
               }
               if (y1 < y2) return -1;
               if (y1 > y2) return 1;
               if (x1 < x2) return -1;
               if (x1 > x2) return 1;
               return 0;
            }
         });
      int index;
      if (selected == null) 
         index = 0;
      else index = selectables.indexOf(selected) + n;
      while (index < 0) index += selectables.size();
      index %= selectables.size();
      selected = selectables.get(index);
      repaint();
   }

   /**
      Checks whether this graph has been modified since it 
      was last saved.
      @return true if the graph has been modified
   */
   public boolean isModified()
   {
      return modified;
   }

   /**
      Sets or resets the modified flag for this graph
      @param newValue true to indicate that the graph has
      been modified
   */
   public void setModified(boolean newValue)
   {
      modified = newValue;
   }

   /**
      Sets the value of the hideGrid property
      @param newValue true if the grid is being hidden
   */
   public void setHideGrid(boolean newValue)
   {
      hideGrid = newValue;
      repaint();
   }

   private Graph graph;
   private Object selected;
   private ToolBar toolBar;
   private Point2D lastMousePoint;
   private Point2D rubberBandStart;
   private Point2D dragStartPoint;
   private Rectangle2D dragStartBounds;
   private Grid grid;
   private double zoom;
   private double gridSize;
   private boolean hideGrid;
   private boolean modified;
   private static final int GRID = 10;
   private static final int CONNECT_THRESHOLD = 8;
   private static final Color PURPLE = new Color(0.7f, 0.4f, 0.7f);   
}                               
