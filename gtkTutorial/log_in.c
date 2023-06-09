#include <gtk/gtk.h>
#include "after.h"
#include "create_account.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *title;
    GtkWidget *subtitle;
    PangoAttrList *attr_list;
    PangoAttribute *attr;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    fixed = gtk_fixed_new();

    entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Username");
    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);

    button1 = gtk_button_new_with_label("LOG IN");
    gtk_widget_set_size_request(button1, 165, 20);

    button2 = gtk_button_new_with_label("SIGN UP");
    gtk_widget_set_size_request(button2, 165, 20);

    title = gtk_label_new("PLAYER DATA");
    attr_list = pango_attr_list_new();
    attr = pango_attr_foreground_new(65535, 32768, 0);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(title), attr_list);
    attr = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    pango_attr_list_insert(attr_list, attr);
    attr = pango_attr_size_new(24 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(title), attr_list);
    pango_attr_list_unref(attr_list);

    subtitle = gtk_label_new("LOG IN");
    attr_list = pango_attr_list_new();
    attr = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    pango_attr_list_insert(attr_list, attr);
    attr = pango_attr_size_new(18 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(subtitle), attr_list);
    pango_attr_list_unref(attr_list);

    gtk_fixed_put(GTK_FIXED(fixed), title, 225, 150);
    gtk_fixed_put(GTK_FIXED(fixed), subtitle, 275, 200);
    gtk_fixed_put(GTK_FIXED(fixed), entry1, 225, 250);
    gtk_fixed_put(GTK_FIXED(fixed), entry2, 225, 300);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 225, 350);
    gtk_fixed_put(GTK_FIXED(fixed), button1, 225, 400);

    gtk_widget_show(title);
    gtk_widget_show(subtitle);

    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);
    /*g_signal_connect(button2, "clicked", G_CALLBACK(on_button2_clicked), NULL);*/
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}