#include <gtk/gtk.h>

// GTK4 Functions
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Health Admin Medika Karya");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800);
    gtk_window_present(GTK_WINDOW(window));

    // create menu tabs
    GtkWidget *notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // Membuat box vertikal untuk PatientTab
    GtkWidget *PatientTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Membuat toolbar horizontal
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_margin_top(toolbar, 10);    // tambahkan jeda 10 pixel di sisi atas

    // Membuat tombol "Tambah Data"
    GtkWidget *add_icon = gtk_image_new_from_icon_name("list-add-symbolic");
    GtkWidget *add_button = gtk_button_new();
    gtk_button_set_child(GTK_BUTTON(add_button), add_icon);
    gtk_widget_set_margin_start(add_button, 10);  // tambahkan jeda 10 pixel di sisi kiri
    gtk_widget_set_margin_end(add_button, 3);    // tambahkan jeda 10 pixel di sisi kanan
    gtk_box_append(GTK_BOX(toolbar), add_button);

    // Membuat tombol "Edit Data"
    GtkWidget *edit_icon = gtk_image_new_from_icon_name("document-edit-symbolic");
    GtkWidget *edit_button = gtk_button_new();
    gtk_button_set_child(GTK_BUTTON(edit_button), edit_icon);
    gtk_widget_set_margin_start(edit_button, 3);  // tambahkan jeda 10 pixel di sisi kiri
    gtk_widget_set_margin_end(edit_button, 3);    // tambahkan jeda 10 pixel di sisi kanan
    gtk_box_append(GTK_BOX(toolbar), edit_button);

    // Membuat tombol "Hapus Data"
    GtkWidget *delete_icon = gtk_image_new_from_icon_name("edit-delete-symbolic");
    GtkWidget *delete_button = gtk_button_new();
    gtk_button_set_child(GTK_BUTTON(delete_button), delete_icon);
    gtk_widget_set_margin_start(delete_button, 3);  // tambahkan jeda 10 pixel di sisi kiri
    gtk_widget_set_margin_end(delete_button, 3);    // tambahkan jeda 10 pixel di sisi kanan
    gtk_box_append(GTK_BOX(toolbar), delete_button);

    // Membuat kotak pencarian dan menambahkannya ke toolbar
    GtkWidget *search_entry = gtk_search_entry_new();
    gtk_widget_set_margin_start(search_entry, 10);  // tambahkan jeda 10 pixel di sisi kiri
    gtk_widget_set_margin_end(search_entry, 10);    // tambahkan jeda 10 pixel di sisi kanan
    gtk_box_append(GTK_BOX(toolbar), search_entry);

    // ============================================================================================

    

    // ====================================================================


    gtk_box_append(GTK_BOX(PatientTab), toolbar);

    GtkWidget *HistoryTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *PriceTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *AboutTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), PatientTab, gtk_label_new("Patient Data"));
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), HistoryTab, gtk_label_new("Medical Record"));
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), PriceTab, gtk_label_new("Fee Management"));
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), AboutTab, gtk_label_new("About"));

    

    gtk_widget_set_visible(window, TRUE);
}
