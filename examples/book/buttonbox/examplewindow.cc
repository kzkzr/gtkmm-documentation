/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "examplewindow.h"
#include "examplebuttonbox.h"

ExampleWindow::ExampleWindow()
: m_VBox_Main(Gtk::Orientation::VERTICAL),
  m_VBox(Gtk::Orientation::VERTICAL),
  m_Frame_Horizontal("Horizontal Button Boxes"),
  m_Frame_Vertical("Vertical Button Boxes")
{
  set_title("Gtk::ButtonBox");
  m_VBox_Main.set_margin(10);
  m_VBox_Main.set_spacing(10);
  add(m_VBox_Main);

  m_VBox_Main.pack_start(m_Frame_Horizontal, Gtk::PackOptions::EXPAND_WIDGET);
  m_VBox_Main.set_margin_start(10);

  //The horizontal ButtonBoxes:
  m_VBox.set_margin(10);
  m_Frame_Horizontal.add(m_VBox);

  m_VBox.set_spacing(5);
  m_VBox.pack_start(*Gtk::manage(
              new ExampleButtonBox(true, "Spread (spacing 40)", 40,
                  Gtk::ButtonBoxStyle::SPREAD)),
          Gtk::PackOptions::EXPAND_WIDGET);

  m_VBox.pack_start(*Gtk::manage(
              new ExampleButtonBox(true, "Edge (spacing 30)", 30,
                  Gtk::ButtonBoxStyle::EDGE)),
          Gtk::PackOptions::EXPAND_WIDGET);

  m_VBox.pack_start(*Gtk::manage(
              new ExampleButtonBox(true, "Start (spacing 20)", 20,
                  Gtk::ButtonBoxStyle::START)),
          Gtk::PackOptions::EXPAND_WIDGET);

  m_VBox.pack_start(*Gtk::manage(
              new ExampleButtonBox(true, "End (spacing 10)", 10,
                  Gtk::ButtonBoxStyle::END)),
          Gtk::PackOptions::EXPAND_WIDGET);


  //The vertical ButtonBoxes:
  m_VBox_Main.pack_start(m_Frame_Vertical, Gtk::PackOptions::EXPAND_WIDGET);

  m_HBox.set_margin(10);
  m_Frame_Vertical.add(m_HBox);

  m_HBox.set_spacing(5);
  m_HBox.pack_start(*Gtk::manage(
              new ExampleButtonBox(false, "Spread (spacing 5)", 5,
                  Gtk::ButtonBoxStyle::SPREAD)),
          Gtk::PackOptions::EXPAND_WIDGET);

  m_HBox.pack_start(*Gtk::manage(
              new ExampleButtonBox(false, "Edge (spacing 30)", 30,
                  Gtk::ButtonBoxStyle::EDGE)),
          Gtk::PackOptions::EXPAND_WIDGET);

  m_HBox.pack_start(*Gtk::manage(
              new ExampleButtonBox(false, "Start (spacing 20)", 20,
                  Gtk::ButtonBoxStyle::START)),
          Gtk::PackOptions::EXPAND_WIDGET);

  m_HBox.pack_start(*Gtk::manage(new ExampleButtonBox(false, "End (spacing 10)",
                  10, Gtk::ButtonBoxStyle::END)),
          Gtk::PackOptions::EXPAND_WIDGET);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_clicked()
{
  hide();
}
