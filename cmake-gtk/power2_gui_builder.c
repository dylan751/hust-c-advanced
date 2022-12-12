#include <gtk/gtk.h>

double x;
const char* ui_path = NULL;

void button_clicked (GtkWidget *widget,
             gpointer   data) {
  x = g_ascii_strtod(gtk_entry_get_text(GTK_ENTRY(data)), NULL);
}

void readX() {
  gtk_init(0, NULL);
  GtkBuilder *builder = gtk_builder_new_from_file(ui_path);
  gtk_builder_connect_signals(builder, NULL);
  GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
  GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
  GtkWidget *entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry"));
  g_signal_connect (button, "clicked", G_CALLBACK (button_clicked), entry);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
  gtk_widget_show_all (window);
  gtk_main();
  g_object_unref(builder);
}

double display(double value) {
  printf("%lf\n", value);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: ./power2_gui_builder input_x.glade\n");
    return 1;
  }
  ui_path = argv[1];
  readX();
  display(x * x);
  return 0;
}