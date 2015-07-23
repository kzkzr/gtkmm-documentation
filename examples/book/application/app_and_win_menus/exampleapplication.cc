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

#include "exampleapplication.h"
#include "examplewindow.h"
#include <iostream>

ExampleApplication::ExampleApplication()
: Gtk::Application("org.gtkmm.examples.application")
{
  Glib::set_application_name("Gtk::Application Example");
}

Glib::RefPtr<ExampleApplication> ExampleApplication::create()
{
  return Glib::RefPtr<ExampleApplication>( new ExampleApplication() );
}

void ExampleApplication::on_startup()
{
  //Call the base class's implementation:
  Gtk::Application::on_startup();

  //Create the Application menu:
  //We can use add_action because Gtk::Application derives from ActionMap:
  add_action("something",
    sigc::mem_fun(*this, &ExampleApplication::on_action_something) );
  add_action("quit",
    sigc::mem_fun(*this, &ExampleApplication::on_action_quit) );

  
  auto app_menu = Gio::Menu::create();
  app_menu->append("_Something", "app.something");
  app_menu->append("_Quit", "app.quit");

  set_app_menu(app_menu);


  //Create the per-Window menu:
  auto win_menu = Gio::Menu::create();

  auto submenu_file = Gio::Menu::create();
  submenu_file->append("_New", "win.new");
  submenu_file->append("_Close", "win.close");
  win_menu->append_submenu("File", submenu_file);

  auto submenu_edit = Gio::Menu::create();
  submenu_edit->append("_Cut", "win.cut");
  auto item = Gio::MenuItem::create("_Copy", "win.copy");
  //Setting "accel" works, but might be deprecated soon: See https://bugzilla.gnome.org/show_bug.cgi?id=708908
  //When it is deprecated, use Gtk::Application::set_accel_for_action() instead.
  item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>c"));
  submenu_edit->append_item(item);
  item = Gio::MenuItem::create("_Paste", "win.paste");
  item->set_attribute_value("accel", Glib::Variant<Glib::ustring>::create("<Primary>v"));
  submenu_edit->append_item(item);
  win_menu->append_submenu("Edit", submenu_edit);

  auto submenu_notification = Gio::Menu::create();
  submenu_notification->append("_Send", "win.send-note");
  submenu_notification->append("_Withdraw", "win.withdraw-note");
  win_menu->append_submenu("Notification", submenu_notification);

  set_menubar(win_menu);

  //Create an action with a parameter. This action can be activated from
  //a Gio::Notification, sent by the Notification/win.send-note menu selection.
  auto action_print =
    Gio::SimpleAction::create("print", Glib::VARIANT_TYPE_STRING);
  action_print->signal_activate().connect(
    sigc::mem_fun(*this, &ExampleApplication::on_action_print));
  add_action(action_print);
}

void ExampleApplication::create_window()
{
  auto window = new ExampleWindow();
  window->set_default_size(300, 100);

  //Make sure that the application runs for as long this window is still open:
  add_window(*window);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  window->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(*this,
    &ExampleApplication::on_window_hide), window));

  window->show();
}

void ExampleApplication::on_window_hide(Gtk::Window* window)
{
  delete window;
}

void ExampleApplication::on_activate()
{
  //std::cout << "debug1: " << G_STRFUNC << std::endl;
  // The application has been started, so let's show a window.
  // A real application might want to reuse this "empty" window in on_open(),
  // when asked to open a file, if no changes have been made yet.
  create_window();
}

void ExampleApplication::on_action_something()
{
  std::cout << G_STRFUNC << std::endl;
}

void ExampleApplication::on_action_quit()
{
  std::cout << G_STRFUNC << std::endl;
  quit(); // Not really necessary, when Gtk::Widget::hide() is called.

  // Gio::Application::quit() will make Gio::Application::run() return,
  // but it's a crude way of ending the program. The window is not removed
  // from the application. Neither the window's nor the application's
  // destructors will be called, because there will be remaining reference
  // counts in both of them. If we want the destructors to be called, we
  // must remove the window from the application. One way of doing this
  // is to hide the window.
  auto windows = get_windows();
  if (windows.size() > 0)
    windows[0]->hide(); // In this simple case, we know there is only one window.
}

void ExampleApplication::on_action_print(const Glib::VariantBase& parameter)
{
  std::cout << G_STRFUNC << " Parameter=" << parameter.print() << std::endl;
}
