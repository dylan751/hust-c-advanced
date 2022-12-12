import sys
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

x = 0.0
ui_path = ''

def display(value):
  print(value)

def button_clicked(widget, data):
  global x
  x = float(data.get_text())
  Gtk.main_quit()

def readX():
  builder = Gtk.Builder()
  builder.add_from_file(ui_path)
  window = builder.get_object("window_main")
  button = builder.get_object("button")
  entry = builder.get_object("entry")
  button.connect("clicked", button_clicked, entry)
  window.show_all()
  Gtk.main()

if __name__ == "__main__":
  argv = len(sys.argv)
  if argv < 2:
    print("Usage: python power2_gui_builder.py input_x.glade")
    exit(1)
  ui_path = sys.argv[1]
  readX()
  display(x * x)