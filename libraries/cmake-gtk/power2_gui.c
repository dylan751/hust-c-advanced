#include <gtk/gtk.h>

double x;

void button_clicked (GtkWidget *widget,
             gpointer   data) {
  x = g_ascii_strtod(gtk_entry_get_text(GTK_ENTRY(data)), NULL);
}

void activate (GtkApplication *app,
               gpointer        user_data) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title (GTK_WINDOW (window), "Hello GTK3");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_add(GTK_CONTAINER(window), box);
  GtkWidget *entry = gtk_entry_new();
  gtk_box_pack_start(box, entry, 1, 1, 0);
  GtkWidget *button = gtk_button_new_with_label("Enter");
  g_signal_connect (button, "clicked", G_CALLBACK (button_clicked), entry);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_box_pack_start(box, button, 1, 1, 0);
  gtk_widget_show_all (window);
}

void readX() {
  GtkApplication *app = gtk_application_new("hello.gtk", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  int status = g_application_run (G_APPLICATION (app), 0, NULL);
  g_object_unref(app);
}

double display(double value) {
  printf("%lf\n", value);
}

int main(int argc, char *argv[]) {
  readX();
  display(x * x);
  return 0;
}