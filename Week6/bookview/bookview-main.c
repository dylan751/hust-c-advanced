#include<gtk/gtk.h>

typedef struct {
    const int stt;
    const gchar *title;
    const gchar *content;
} Book;

enum{
    COLUMN_STT,
    COLUMN_TITLE,
    COLUMN_CONTENT,
    NUM_COLUMNS
};

static Book data[] = {
    {1, "C Programming", "Coding"},
    {2, "Databases", "Get information"},
    {3, "Networking", "Co-work with others"}
};

GtkTreeModel *create_model(){
    gint i = 0;
    GtkListStore *store;
    GtkTreeIter iter;
    store = gtk_list_store_new(NUM_COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
    for(i = 0; i < G_N_ELEMENTS(data); ++i){
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, COLUMN_STT, data[i].stt, COLUMN_TITLE, data[i].title, COLUMN_CONTENT, data[i].content, -1);
    }
    return GTK_TREE_MODEL(store);
}

void add_book_columns(GtkTreeView *treeview){
    GtkTreeViewColumn *column1, *column2, *column3;
    GtkCellRenderer *renderer;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    renderer = gtk_cell_renderer_text_new();
    column1 = gtk_tree_view_column_new_with_attributes("STT", renderer, "text", COLUMN_STT, NULL);
    column2 = gtk_tree_view_column_new_with_attributes("Title", renderer, "text", COLUMN_TITLE, NULL);
    column3 = gtk_tree_view_column_new_with_attributes("Content", renderer, "text", COLUMN_CONTENT, NULL);
    gtk_tree_view_append_column(treeview, column1);
    gtk_tree_view_append_column(treeview, column2);
    gtk_tree_view_append_column(treeview, column3);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        g_print("Usage: ./textview textview.glade\n");
        return 1;
    }
    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new_from_file(argv[1]);
    gtk_builder_add_from_file (builder, "Bookview", NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window-main"));
    GtkWidget *mybookview = GTK_WIDGET(gtk_builder_get_object(builder, "my-book-view"));
    gtk_tree_view_set_model(GTK_TREE_VIEW(mybookview), GTK_TREE_MODEL(create_model()));
    add_book_columns(GTK_TREE_VIEW(mybookview));

    g_signal_connect(window, "destroy", gtk_main_quit, NULL);

    gtk_widget_show(window);
    gtk_main();
    g_object_unref(builder);

    return 0;
}