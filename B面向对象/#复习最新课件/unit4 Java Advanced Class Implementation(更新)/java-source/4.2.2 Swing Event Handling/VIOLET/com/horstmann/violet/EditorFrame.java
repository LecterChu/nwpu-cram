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
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.beans.DefaultPersistenceDelegate;
import java.beans.Encoder;
import java.beans.ExceptionListener;
import java.beans.Expression;
import java.beans.PersistenceDelegate;
import java.beans.PropertyVetoException;
import java.beans.XMLDecoder;
import java.beans.XMLEncoder;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.text.MessageFormat;
import java.util.ResourceBundle;
import javax.imageio.ImageIO;
import javax.print.DocFlavor;
import javax.print.DocPrintJob;
import javax.print.PrintException;
import javax.print.SimpleDoc;
import javax.print.StreamPrintService;
import javax.print.StreamPrintServiceFactory;
import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;
import javax.swing.ImageIcon;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JDesktopPane;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JInternalFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.event.InternalFrameAdapter;
import javax.swing.event.InternalFrameEvent;

/**
   This desktop frame contains panes that show graphs.
*/
public class EditorFrame extends JFrame
{
   /**
      Constructs a blank frame with a desktop pane
      but no graph windows.
      @param appResourcesName the application-specific resources
   */
   public EditorFrame(String appResourcesName)
   {  
      ResourceBundle appResources = 
         ResourceBundle.getBundle(appResourcesName);



      appFactory = new ResourceFactory(appResources);
      setTitle(appResources.getString("app.name"));
      Dimension screenSize 
         = Toolkit.getDefaultToolkit().getScreenSize();
  
      int screenWidth = (int)screenSize.getWidth();
      int screenHeight = (int)screenSize.getHeight();

      setBounds(screenWidth / 16, screenHeight / 16,
         screenWidth * 7 / 8, screenHeight * 7 / 8);

      setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
      addWindowListener(new
         WindowAdapter()
         {
            public void windowClosing(WindowEvent event)
            {
               exit();
            }
         });

      desktop = new JDesktopPane();
      setContentPane(desktop);

      editorResources = 
         ResourceBundle.getBundle("com.horstmann.violet.EditorStrings");

      try
      {
         fileChooser = new JFileChooser();
         fileChooser.setCurrentDirectory(new File("."));
      }
      catch (SecurityException exception)
      {
         // that happens when we run under Web Start
      }
      
      defaultExtension = appResources.getString("files.extension");

      violetFilter = new ExtensionFilter(
         appResources.getString("files.name"), 
         new String[] { defaultExtension });
      psFilter = new ExtensionFilter(
         editorResources.getString("files.postscript.name"), 
         editorResources.getString("files.postscript.extension"));
      exportFilter = new ExtensionFilter(
         editorResources.getString("files.image.name"), 
         editorResources.getString("files.image.extension"));

      // set up menus

      ResourceFactory factory = new ResourceFactory(editorResources);
      
      JMenuBar menuBar = new JMenuBar();
      setJMenuBar(menuBar);
      JMenu fileMenu = factory.createMenu("file");
      menuBar.add(fileMenu);

      newMenu = factory.createMenu("file.new");
      fileMenu.add(newMenu);

      fileMenu.add(factory.createMenuItem(
         "file.open", this, "openFile")).setEnabled(fileChooser != null);

      fileMenu.add(factory.createMenuItem("file.save", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               File file = frame.getFile();
               if (file == null)
                  saveAs();
               else
                  saveFile(file);
            }
         })).setEnabled(fileChooser != null);

      fileMenu.add(factory.createMenuItem(
         "file.save_as", this, "saveAs")).setEnabled(fileChooser != null);

      fileMenu.add(factory.createMenuItem(
         "file.export_image", this, "exportImage")).setEnabled(fileChooser != null);

      fileMenu.add(factory.createMenuItem(
         "file.print_postscript", this, "exportPostScript")).setEnabled(fileChooser != null);

      fileMenu.add(factory.createMenuItem(
         "file.exit", this, "exit"));

      JMenu editMenu = factory.createMenu("edit");
      menuBar.add(editMenu);

      editMenu.add(factory.createMenuItem(
         "edit.properties", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               final GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               GraphPanel panel = frame.getGraphPanel();
               panel.editSelected();
            }
         }));

      editMenu.add(factory.createMenuItem("edit.delete", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               GraphPanel panel = frame.getGraphPanel();
               panel.removeSelected();
            }
         }));

      editMenu.add(factory.createMenuItem(
         "edit.select_next", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               GraphPanel panel = frame.getGraphPanel();
               panel.selectNext(1);
            }
         }));

      editMenu.add(factory.createMenuItem(
         "edit.select_previous", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               Graph graph = frame.getGraph();
               GraphPanel panel = frame.getGraphPanel();
               panel.selectNext(-1);
            }
         }));

      JMenu viewMenu = factory.createMenu("view");
      menuBar.add(viewMenu);

      viewMenu.add(factory.createMenuItem(
         "view.zoom_out", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               GraphPanel panel = frame.getGraphPanel();
               panel.changeZoom(-1);
            }
         }));

      viewMenu.add(factory.createMenuItem(
         "view.zoom_in", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               GraphPanel panel = frame.getGraphPanel();
               panel.changeZoom(1);
            }
         }));

      viewMenu.add(factory.createMenuItem(
         "view.smaller_grid", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               GraphPanel panel = frame.getGraphPanel();
               panel.changeGridSize(-1);
            }
         }));

      viewMenu.add(factory.createMenuItem(
         "view.larger_grid", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               GraphPanel panel = frame.getGraphPanel();
               panel.changeGridSize(1);
            }
         }));

      viewMenu.add(factory.createCheckBoxMenuItem(
         "view.hide_grid", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               GraphPanel panel = frame.getGraphPanel();
               JCheckBoxMenuItem menuItem = (JCheckBoxMenuItem)event.getSource();               
               panel.setHideGrid(menuItem.isSelected());
            }
         }));


      JMenu lafMenu = factory.createMenu("view.change_laf");
      viewMenu.add(lafMenu);
      
      UIManager.LookAndFeelInfo[] infos =
         UIManager.getInstalledLookAndFeels();
      for (int i = 0; i < infos.length; i++)
      {
         final UIManager.LookAndFeelInfo info = infos[i];
         JMenuItem item = new JMenuItem(info.getName());
         lafMenu.add(item);
         item.addActionListener(new
            ActionListener()
            {
               public void actionPerformed(ActionEvent event)
               {               
                  try
                  {
                     UIManager.setLookAndFeel(info.getClassName());
                     SwingUtilities.updateComponentTreeUI(EditorFrame.this);
                  }
                  catch (ClassNotFoundException ex) {}
                  catch (InstantiationException ex) {}
                  catch (IllegalAccessException ex) {}
                  catch (UnsupportedLookAndFeelException ex) {}
               }
            });
      }

      JMenu windowMenu = factory.createMenu("window");
      menuBar.add(windowMenu);

      windowMenu.add(factory.createMenuItem(
         "window.next", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               JInternalFrame[] frames = desktop.getAllFrames();
               for (int i = 0; i < frames.length; i++)
               {
                  if (frames[i] == desktop.getSelectedFrame())
                  {
                     i++; 
                     if (i == frames.length) i = 0;
                     try
                     {
                        frames[i].toFront();
                        frames[i].setSelected(true); 
                     }
                     catch (PropertyVetoException exception)
                     {
                     }
                     return;
                  }
               }
            }
         }));

      windowMenu.add(factory.createMenuItem(
         "window.previous", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               JInternalFrame[] frames = desktop.getAllFrames();
               for (int i = 0; i < frames.length; i++)
               {
                  if (frames[i] == desktop.getSelectedFrame())
                  {
                     if (i == 0) i = frames.length;
                     i--; 
                     try
                     {
                        frames[i].toFront();
                        frames[i].setSelected(true); 
                     }
                     catch (PropertyVetoException exception)
                     {
                     }
                     return;
                  }
               }
            }
         }));

      windowMenu.add(factory.createMenuItem(
         "window.maximize", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               try
               {
                  frame.setMaximum(true);
               }
               catch (PropertyVetoException exception)
               {
               }
            }
         }));

      windowMenu.add(factory.createMenuItem(
         "window.restore", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               try
               {
                  frame.setMaximum(false);
               }
               catch (PropertyVetoException exception)
               {
               }
            }
         }));

      windowMenu.add(factory.createMenuItem(
         "window.close", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               GraphFrame frame 
                  = (GraphFrame)desktop.getSelectedFrame();
               if (frame == null) return;
               try
               {
                  frame.setClosed(true);
               }
               catch (PropertyVetoException exception)
               {
               }
            }
         }));

      JMenu helpMenu = factory.createMenu("help");
      menuBar.add(helpMenu);

      helpMenu.add(factory.createMenuItem(
         "help.about", this, "showAboutDialog"));

      helpMenu.add(factory.createMenuItem(
         "help.license", new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               try
               {
                  BufferedReader reader 
                     = new BufferedReader(
                        new InputStreamReader(
                           getClass().getResourceAsStream(
                              "license.txt")));
                  JTextArea text = new JTextArea(10, 50);
                  String line;
                  while ((line = reader.readLine()) != null)
                  {
                     text.append(line);
                     text.append("\n");
                  }   
                  text.setCaretPosition(0);
                  JOptionPane.showInternalMessageDialog(
                     desktop, 
                     new JScrollPane(text),
                     null, 
                     JOptionPane.INFORMATION_MESSAGE);
               }
               catch (IOException exception) {}
            }
         }));
   }

   /**
      Adds a graph type to the File->New menu.
      @param resourceName the name of the menu item resource
      @param graphClass the class object for the graph
   */
   public void addGraphType(String resourceName,
      final Class graphClass)
   {
      newMenu.add(appFactory.createMenuItem(resourceName, new
         ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               try
               {
                  GraphFrame frame = new GraphFrame(
                     (Graph)graphClass.newInstance());
                  addInternalFrame(frame);
               }
               catch (Exception exception)
               {
               }
            }
         }));
   }

   /**
      Reads the command line arguments.
      @param args the command line arguments
   */
   public void readArgs(String[] args)
   {
      if (args.length == 0)
         showAboutDialog();
      else
      {
         for (int i = 0; i < args.length; i++)
         {
            File file = new File(args[i]);
            read(file);
         }
      }
   }

   /**
      Creates an internal frame on the desktop.
      @param c the component to display in the internal frame
      @param t the title of the internal frame.
   */
   private void addInternalFrame(final JInternalFrame iframe)
   {  
      iframe.setResizable(true);
      iframe.setClosable(true);
      iframe.setMaximizable(true);
      iframe.setIconifiable(true);
      int frameCount = desktop.getAllFrames().length;      
      desktop.add(iframe);
      // position frame
      int emptySpace 
         = FRAME_GAP * Math.max(ESTIMATED_FRAMES, frameCount);
      int width = Math.max(desktop.getWidth() / 2, 
            desktop.getWidth() - emptySpace);            
      int height = Math.max(desktop.getHeight() / 2, 
         desktop.getHeight() - emptySpace);

      iframe.reshape(frameCount * FRAME_GAP, 
         frameCount * FRAME_GAP, width, height);
      iframe.show();

      iframe.addInternalFrameListener(new
         InternalFrameAdapter()
         {
            public void internalFrameActivated(InternalFrameEvent event)
            {
               setTitle();
            }
            public void internalFrameDeactivated(InternalFrameEvent event)
            {
               setTitle();
            }
         });

      // select the frame--might be vetoed
      try
      {  
         iframe.setSelected(true);
      }
      catch(PropertyVetoException e)
      {
      }
   }

   /**
      Sets the frame title.
   */
   private void setTitle()
   {
      GraphFrame frame 
         = (GraphFrame)desktop.getSelectedFrame();
      if (frame == null) 
         setTitle("");
      else
      {
         File file = frame.getFile();
         if (file == null)
            setTitle("");
         else
            setTitle("" + file);
      }
   }

   /**
      Asks the user to open a graph file.
   */
   public void openFile()
   {  
      // let user select file

      fileChooser.resetChoosableFileFilters();
      fileChooser.setFileFilter(violetFilter);
      fileChooser.setSelectedFile(null);
      int r = fileChooser.showOpenDialog(this);
      if (r == JFileChooser.APPROVE_OPTION)
      {  
         File file = fileChooser.getSelectedFile();
         read(file);
      }
   }

   /**
      Reads a grap file and opens a new frame.
      @param file the file to read
   */
   public void read(File file)
   {
      try
      {
         XMLDecoder reader 
            = new XMLDecoder(new FileInputStream(file));
         Graph graph = (Graph)reader.readObject();
         reader.close();
         GraphFrame frame = new GraphFrame(graph);
         addInternalFrame(frame);
         frame.setFile(file);
         setTitle();
      }
      catch (IOException exception)
      {
         JOptionPane.showInternalMessageDialog(desktop, 
            exception);
      }
   }

   /**
      Saves the current graph as a new file.
   */
   public void saveAs()
   {
      GraphFrame frame 
         = (GraphFrame)desktop.getSelectedFrame();
      if (frame == null) return;
      fileChooser.resetChoosableFileFilters();
      fileChooser.setFileFilter(violetFilter);
      fileChooser.setSelectedFile(frame.getFile());
      if (fileChooser.showSaveDialog(this) 
         != JFileChooser.APPROVE_OPTION) return;
      File file = fileChooser.getSelectedFile();
      file = editExtension(file, null, defaultExtension);
      frame.setFile(file);      
      setTitle();
      saveFile(file);
   }


   /**
      Saves the current graph in a file. We use long-term
      bean persistence to save the program data. See
      http://java.sun.com/products/jfc/tsc/articles/persistence4/index.html
      for an overview.
      @param file the file for saving
   */
   private void saveFile(File file)
   {
      GraphFrame frame 
         = (GraphFrame)desktop.getSelectedFrame();
      if (frame == null) return;
      try
      {
         XMLEncoder encoder = new XMLEncoder(
            new FileOutputStream(file));
         
         encoder.setExceptionListener(new 
            ExceptionListener() 
            {
               public void exceptionThrown(Exception ex) 
               {
                  ex.printStackTrace();
               }
            });
         
         encoder.setPersistenceDelegate(
            Point2D.Double.class,
            new DefaultPersistenceDelegate(
               new String[]{ "x", "y" }) );
         
         encoder.setPersistenceDelegate(BentStyle.class,
            staticFieldDelegate);
         encoder.setPersistenceDelegate(LineStyle.class,
            staticFieldDelegate);
         encoder.setPersistenceDelegate(ArrowHead.class,
            staticFieldDelegate);
         
         Graph.setPersistenceDelegate(encoder);
         AbstractNode.setPersistenceDelegate(encoder);
         
         Graph graph = frame.getGraph();
         
         encoder.writeObject(graph);
         encoder.close();
         
         frame.getGraphPanel().setModified(false);
      }
      catch (IOException exception)
      {
         JOptionPane.showInternalMessageDialog(desktop, 
            exception);
      }
   }

   /**
      Exports the current graph to an image file.
   */
   public void exportImage()
   {
      GraphFrame frame 
         = (GraphFrame)desktop.getSelectedFrame();
      if (frame == null) return;
      fileChooser.resetChoosableFileFilters();
      fileChooser.setFileFilter(exportFilter);
      fileChooser.setSelectedFile(editExtension(
         frame.getFile(),
         defaultExtension, 
         editorResources.getString("files.image.extension")));
      if (fileChooser.showSaveDialog(this) 
         == JFileChooser.APPROVE_OPTION)
      {
         try
         {
            File file = fileChooser.getSelectedFile();
            String format = file.getName()
               .substring(file.getName().lastIndexOf(".") + 1);
            if (!ImageIO.getImageWritersByFormatName(format)
               .hasNext())
            {
               MessageFormat formatter = new MessageFormat(
                  editorResources.getString("error.unsupported_image"));
               JOptionPane.showInternalMessageDialog(desktop, 
                  formatter.format(new Object[] { format }));
               return;
            }
            Graph graph = frame.getGraph();
            BufferedImage dummy = new BufferedImage(1, 1,
               BufferedImage.TYPE_INT_RGB);
            // need a dummy image to get a Graphics to
            // measure the size
            Rectangle2D bounds = graph.getBounds(
               (Graphics2D)dummy.getGraphics());
            BufferedImage image 
               = new BufferedImage((int)bounds.getWidth() + 1,
                  (int)bounds.getHeight() + 1, 
                  BufferedImage.TYPE_INT_RGB);
            Graphics2D g2 = (Graphics2D)image.getGraphics();
            g2.translate(-bounds.getX(), -bounds.getY());
            g2.setColor(Color.WHITE);
            g2.fill(new Rectangle2D.Double(
               bounds.getX(),
               bounds.getY(), 
               bounds.getWidth() + 1,
               bounds.getHeight() + 1));
            g2.setColor(Color.BLACK);
            graph.draw(g2, null);
            ImageIO.write(image, format, file);
         }
         catch (IOException exception)
         {
            JOptionPane.showInternalMessageDialog(desktop, 
               exception);
         }
      }
   }

   /**
      Exports the current graph in a PostScript file.
   */
   public void exportPostScript()
   {
      GraphFrame frame 
         = (GraphFrame)desktop.getSelectedFrame();
      if (frame == null) return;
      fileChooser.resetChoosableFileFilters();
      fileChooser.setFileFilter(psFilter);
      fileChooser.setSelectedFile(editExtension(frame.getFile(),
         defaultExtension, editorResources.getString("files.postscript.extension")));
      if (fileChooser.showSaveDialog(this) 
         == JFileChooser.APPROVE_OPTION)
      {
         try
         {
            File file = fileChooser.getSelectedFile();
            final Graph graph = frame.getGraph();

            DocFlavor flavor = 
               DocFlavor.SERVICE_FORMATTED.PRINTABLE;
            String mimeType = "application/postscript";
            StreamPrintServiceFactory[] factories = 
               StreamPrintServiceFactory
               .lookupStreamPrintServiceFactories(flavor, 
                  mimeType);
            FileOutputStream out = new FileOutputStream(file);
            if (factories.length == 0) return;
            StreamPrintService service 
               = factories[0].getPrintService(out);
            DocPrintJob job = service.createPrintJob();
            PrintRequestAttributeSet attributes = new
               HashPrintRequestAttributeSet();
            job.print(new SimpleDoc(new
               Printable()
               {
                  public int print(Graphics g, PageFormat pf,
                     int page) throws PrinterException
                  {
                     if (page >= 1) 
                        return Printable.NO_SUCH_PAGE;
                     Graphics2D g2 = (Graphics2D)g;
                     Rectangle2D bounds = graph.getBounds(g2);
                     g2.translate(pf.getImageableX(),
                        pf.getImageableY());
                     double scale = 1;
                     while (scale * bounds.getWidth() 
                        > pf.getImageableWidth() || 
                        scale * bounds.getHeight()
                        > pf.getImageableHeight())
                        scale = scale / Math.sqrt(2);
                     g2.scale(scale, scale);
                     g2.translate(-bounds.getX(), 
                        -bounds.getY());
                     g2.setColor(Color.BLACK);
                     graph.draw(g2, null);
                     return Printable.PAGE_EXISTS;
                  }
               }, flavor, null), attributes);
         }
         catch (IOException exception)
         {
            JOptionPane.showInternalMessageDialog(desktop, 
               exception);
         }
         catch (PrintException exception)
         {
            JOptionPane.showInternalMessageDialog(desktop, 
               exception);
         }
      }
   }

   /**
      Edits the file path so that it ends in the desired 
      extension.
      @param original the file to use as a starting point
      @param toBeRemoved the extension that is to be
      removed before adding the desired extension. Use
      null if nothing needs to be removed. 
      @param desired the desired extension (e.g. ".png"),
      or a | separated list of extensions
      @return original if it already has the desired 
      extension, or a new file with the edited file path
   */
   private static File editExtension(File original,
      String toBeRemoved, String desired)
   {
      if (original == null) return null;
      File edited;
      int n = desired.indexOf('|');
      if (n >= 0) desired = desired.substring(0, n);
      String path = original.getPath();
      if (path.toLowerCase().endsWith(desired.toLowerCase()))
         return original;
      if (toBeRemoved != null && path.toLowerCase().endsWith(
             toBeRemoved.toLowerCase()))
         path = path.substring(0, path.length() - toBeRemoved.length());
      return new File(path + desired);      
   }

   /**
      Displays the About dialog box.
   */
   public void showAboutDialog()
   {
      ResourceBundle appResources = appFactory.getBundle();
      JOptionPane.showInternalMessageDialog(desktop, 
         appResources.getString("app.name") + " " 
         + appResources.getString("app.version") + "\n"
         + appResources.getString("app.copyright") + "\n"
         + editorResources.getString("dialog.about.license"),
         null, 
         JOptionPane.INFORMATION_MESSAGE,
         new ImageIcon(
            getClass().getResource(appResources.getString("app.icon"))));  
   }

   /**
      Exits the program if no graphs have been modified
      or if the user agrees to abandon modified graphs.
   */
   public void exit()
   {
      boolean modified = false;
      JInternalFrame[] frames = desktop.getAllFrames();
      for (int i = 0; i < frames.length; i++)
      {
         if (frames[i] instanceof GraphFrame)
         {
            GraphFrame frame = (GraphFrame)frames[i];
            if (frame.getGraphPanel().isModified()) modified = true;
         }
      }
      if (modified)
      {
         // ask user if it is ok to close
         int result
            = JOptionPane.showInternalConfirmDialog(
               desktop, 
               editorResources.getString("dialog.exit.ok"), 
               null, 
               JOptionPane.YES_NO_OPTION);
         
         // if the user doesn't agree, veto the close
         if (result != JOptionPane.YES_OPTION)
            return;
      }
      
      System.exit(0);
   }

   private ResourceFactory appFactory;
   private ResourceBundle editorResources;
   private JDesktopPane desktop;
   private JFileChooser fileChooser;
   private JMenu newMenu;
   private String defaultExtension;

   private javax.swing.filechooser.FileFilter violetFilter;
   private javax.swing.filechooser.FileFilter psFilter;
   private javax.swing.filechooser.FileFilter exportFilter;

   private static final int FRAME_GAP = 20;
   private static final int ESTIMATED_FRAMES = 5;

   private static PersistenceDelegate staticFieldDelegate 
      = new 
         DefaultPersistenceDelegate()
         {
            protected Expression instantiate(Object 
               oldInstance, Encoder out)
            {
               try
               {
                  Class cl = oldInstance.getClass();
                  Field[] fields = cl.getFields();
                  for (int i = 0; i < fields.length; i++)
                  {
                     if (Modifier.isStatic(
                            fields[i].getModifiers()) &&
                        fields[i].get(null) == oldInstance)
                     {
                        return new Expression(fields[i], 
                           "get",
                           new Object[] { null });
                     }
                  }
               }
               catch (IllegalAccessException ex) 
               {
                  ex.printStackTrace();
               }
               return null;
            }
            
            protected boolean mutatesTo(
               Object oldInstance, Object newInstance)
            {
               return oldInstance == newInstance;
            }
         };

   
   // workaround for bug #4646747 in J2SE SDK 1.4.0
   private static java.util.HashMap beanInfos;
   static
   {
      beanInfos = new java.util.HashMap();
      Class[] cls = new Class[]
         {
            Point2D.Double.class,
            BentStyle.class,
            ArrowHead.class,
            LineStyle.class,
            Graph.class,
            AbstractNode.class,
         };
      for (int i = 0; i < cls.length; i++)
      {
         try
         {
            beanInfos.put(cls[i], 
               java.beans.Introspector.getBeanInfo(cls[i]));
         }         
         catch (java.beans.IntrospectionException ex)
         {
         }
      }
   }
}
