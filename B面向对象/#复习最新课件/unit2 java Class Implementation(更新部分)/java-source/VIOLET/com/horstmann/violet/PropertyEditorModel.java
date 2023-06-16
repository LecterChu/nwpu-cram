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

import java.beans.BeanInfo;
import java.beans.IntrospectionException;
import java.beans.Introspector;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyDescriptor;
import java.beans.PropertyEditor;
import java.beans.PropertyEditorManager;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import javax.swing.table.AbstractTableModel;

/**
   A table model for a property sheet table.
   The first column lists the names of all editable properties.
   The second column contains editors to change the property
   values.
*/
public class PropertyEditorModel extends AbstractTableModel
{
   /**
      Constructs a property editor model.
      @param bean the object whose properties are being edited
   */
   public PropertyEditorModel(Object bean) 
   {      
      names = new ArrayList();
      editors = new ArrayList();
      
      try
      {
         BeanInfo info = Introspector.getBeanInfo(bean.getClass());
         PropertyDescriptor[] descriptors = info.getPropertyDescriptors();      

         for (int i = 0; i < descriptors.length; i++)
         {
            PropertyEditor editor = getEditor(bean, descriptors[i]);
            if (editor != null)
            {
               names.add(descriptors[i].getName());
               editors.add(editor);
            }
         }
      }
      catch (IntrospectionException exception)
      {
         exception.printStackTrace();
      }
   }

   /**
      Constructs an editor for this type, using either
      a custom editor or one of the system editors.
      @param bean the object whose properties are being
      edited
      @param descriptor the descriptor of the property to edit
      @return a property editor for the described property,
      or null if none is available
   */
   private PropertyEditor getEditor(final Object bean,
      PropertyDescriptor descriptor)
   {
      try
      {
         Method getter = descriptor.getReadMethod();
         if (getter == null) return null;
         final Method setter = descriptor.getWriteMethod();
         if (setter == null) return null;
         final PropertyEditor editor;
         Class editorClass = descriptor.getPropertyEditorClass();
         if (editorClass != null)            
            editor = (PropertyEditor)editorClass.newInstance();
         else
            editor = PropertyEditorManager.findEditor(descriptor.getPropertyType());
         if (editor == null) return null;
         Object value = getter.invoke(bean, new Object[] {});
         editor.setValue(value);
         editor.addPropertyChangeListener(new
            PropertyChangeListener()
            {
               public void propertyChange(PropertyChangeEvent event)
               {
                  try
                  {
                     setter.invoke(bean, new Object[] { 
                        editor.getValue() });
                     fireTableDataChanged();
                  }
                  catch (IllegalAccessException exception)
                  {
                  }
                  catch (InvocationTargetException exception)
                  {
                  }
               }
            });
         return editor;
      }
      catch (InstantiationException exception)
      {
         return null;
      }
      catch (IllegalAccessException exception)
      {
         return null;
      }
      catch (InvocationTargetException exception)
      {
         return null;
      }
   }

   public int getRowCount()
   {
      return names.size();
   }

   public int getColumnCount()
   {
      return 2;
   }

   public boolean isCellEditable(int row, int column)
   {
      return column == 1;
   }

   public Class getColumnClass(int column)
   {
      if (column == 0)
         return String.class;
      else
         return PropertyEditor.class;
   }

   public Object getValueAt(int row, int column)
   {
      if (column == 0)
         return (String)names.get(row);
      else
         return (PropertyEditor)editors.get(row);
   }
   
   private ArrayList names;
   private ArrayList editors;
}
