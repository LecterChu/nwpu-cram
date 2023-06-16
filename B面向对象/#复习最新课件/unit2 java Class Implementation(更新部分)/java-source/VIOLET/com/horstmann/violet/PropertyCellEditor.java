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

import java.awt.Component;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.beans.PropertyEditor;
import java.util.EventObject;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.event.CellEditorListener;
import javax.swing.event.ChangeEvent;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.EventListenerList;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableCellRenderer;

/**
   A cell editor and renderer that can invoke a given
   property editor (which is the cell value)
*/
public class PropertyCellEditor 
   implements TableCellRenderer, 
   TableCellEditor
{
   public PropertyCellEditor()
   {
      label = new JLabel();
      textField = new JTextField();
      textField.getDocument().addDocumentListener(new
         DocumentListener()
         {
            public void insertUpdate(DocumentEvent e) 
            {
               currentEditor.setAsText(textField.getText());
            }
            public void removeUpdate(DocumentEvent e) 
            {
               currentEditor.setAsText(textField.getText());
            }
            public void changedUpdate(DocumentEvent e) 
            {
            }
         });

      comboBox = new JComboBox();
      comboBox.addItemListener(new
         ItemListener()
         {
            public void itemStateChanged(ItemEvent event)
            {
               if (event.getStateChange() == ItemEvent.SELECTED)
               {
                  currentEditor.setAsText(
                     (String)comboBox.getSelectedItem());
               }
            }
         });
   }

   public Component getTableCellRendererComponent(JTable table,
      Object value, boolean isSelected, boolean hasFocus, 
      int row, int column)
   {
      final PropertyEditor editor = (PropertyEditor)value;
      if (editor.isPaintable())
      {
         return new 
            Component()
            {
               public void paint(Graphics g)
               {
                  Rectangle r = new Rectangle(getSize());
                  editor.paintValue(g, r);
               }
            };
      } 
      else 
      {
         label.setText(editor.getAsText());
         return label;
      }      
   }
  
   public Component getTableCellEditorComponent(JTable table,
      Object value, boolean isSelected, int row, int column)
   {      
      currentEditor = (PropertyEditor)value;
      String[] tags = currentEditor.getTags();
      String text = currentEditor.getAsText();
      if (currentEditor.supportsCustomEditor())
      {
         currentType = CUSTOM;
         JOptionPane.showInternalMessageDialog(table, 
            currentEditor.getCustomEditor(), "Property", 
            JOptionPane.QUESTION_MESSAGE);
         return null;
      }
      else if (tags != null)
      {
         currentType = COMBO;
         comboBox.removeAllItems();
         for (int i = 0; i < tags.length; i++)
         {
            comboBox.addItem(tags[i]);
         }
         comboBox.setSelectedItem(text);
         return comboBox;
      }
      else 
      {
         currentType = TEXT;
         textField.setText(text);
         return textField;
      }
   }

   public boolean isCellEditable(EventObject event)
   {
      return true;
   }

   public boolean shouldSelectCell(EventObject event)
   {
      return true;
   }

   public void cancelCellEditing()
   {
      if (currentType == CUSTOM)
      {
         dialog.setVisible(false);
      }
      currentType = NONE;     
   }

   public boolean stopCellEditing()
   {
      if (currentType == CUSTOM)
      {
         dialog.setVisible(false);
      }
      if (currentType == TEXT)
      {
         currentEditor.setAsText(textField.getText());
      }
      
      currentType = NONE;

      return true;
   }

   public Object getCellEditorValue()
   {
      return currentEditor;
   }

   public void addCellEditorListener(CellEditorListener listener)
   {
      listenerList.add(CellEditorListener.class, listener);
   }

   public void removeCellEditorListener(CellEditorListener listener)
   {
      listenerList.remove(CellEditorListener.class, listener);
   }

   protected void fireEditingStopped()
   {
      Object[] listeners = listenerList.getListeners(
         CellEditorListener.class);
      for (int i = 0; i < listeners.length; i++)
         ((CellEditorListener)listeners[i]).editingStopped(
            new ChangeEvent(this));
   }

   protected void fireEditingCanceled()
   {
      Object[] listeners = listenerList.getListeners(
         CellEditorListener.class);
      for (int i = 0; i < listeners.length; i++)
         ((CellEditorListener)listeners[i]).editingCanceled(
            new ChangeEvent(this));
   }

   private EventListenerList listenerList 
      = new EventListenerList();

   private JLabel label;
   private JTextField textField;
   private JComboBox comboBox;
   private PropertyEditor currentEditor;
   private int currentType;
   private JDialog dialog;

   private static final int NONE = 0;
   private static final int COMBO = 1;
   private static final int TEXT = 2;
   private static final int CUSTOM = 3;
}






