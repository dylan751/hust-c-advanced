#include <gtk/gtk.h>

void btn_show_clicked_cb(GtkButton *button,
                         gpointer   user_data) {
    GtkTextBuffer * buffer = gtk_text_view_get_buffer(user_data);
    GtkTextIter iter;
    char* markup = "Text sizes: <span size=\"xx-small\">tiny</span> <span size=\"x-small\">very small</span> <span size=\"small\">small</span> <span size=\"medium\">normal</span> <span size=\"large\">large</span> <span size=\"x-large\">very large</span> <span size=\"xx-large\">huge</span>\n\n"
                    "Text <span color=\"gray\">c<span color=\"green\">o</span>l<span color=\"tomato\">o</span>rs</span> and <span background=\"pink\">backgrounds</span>\n\n"
                    "Colorful <span underline=\"low\" underline-color=\"blue\"><span underline=\"double\" underline-color=\"red\">under</span>lines</span> and <span background=\"pink\"><span underline=\"error\">mo</span><span underline=\"error\" underline-color=\"green\">re</span></span>\n";
    gtk_text_buffer_get_start_iter(buffer, &iter);
    gtk_text_buffer_insert_markup(buffer, &iter, markup, -1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        g_print("Usage: ./textview textview.glade\n");
        return 1;
    }
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file(argv[1]);
    gtk_builder_add_from_file (builder, "Textview", NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    GtkWidget *textview = GTK_WIDGET(gtk_builder_get_object(builder, "textview"));
    GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));

    g_signal_connect(window, "destroy", gtk_main_quit, NULL);
    g_signal_connect (button, "clicked", G_CALLBACK(btn_show_clicked_cb), textview);
    gtk_widget_show(window);
    gtk_main();
    g_object_unref(builder);

    return 0;
}
