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
import java.beans.PropertyEditorSupport;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

/**
   A property editor for the MultiLineString type.
*/
public class MultiLineStringEditor extends PropertyEditorSupport
{
   public boolean supportsCustomEditor()
   {
      return true;
   }

   public Component getCustomEditor()
   {
      final MultiLineString value = (MultiLineString)getValue();
      final JTextArea textArea = new JTextArea(10, 40);
      textArea.setText(value.getText());
      textArea.getDocument().addDocumentListener(new
         DocumentListener()
         {
            public void insertUpdate(DocumentEvent e) 
            {
               value.setText(textArea.getText());
               firePropertyChange();
            }
            public void removeUpdate(DocumentEvent e) 
            {
               value.setText(textArea.getText());
               firePropertyChange();
            }
            public void changedUpdate(DocumentEvent e) 
            {
            }
         });
      return new JScrollPane(textArea);
   }
}
