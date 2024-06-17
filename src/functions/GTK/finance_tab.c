#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"

// Fungsi untuk Menambahkan Data Tindakan ke Tabel
void addTindakanToTable(GtkWidget* table, Tindakan* tindakanList) {
    int row = 1;
    while (tindakanList != NULL) {
        char id_text[10];
        sprintf(id_text, "%d", tindakanList->id);
        GtkWidget* label_id = gtk_label_new(id_text);
        
        GtkWidget* label_tindakan = gtk_label_new(tindakanList->Tindakan);

        char biaya_text[20];
        sprintf(biaya_text, "Rp %d", tindakanList->biaya);
        GtkWidget* label_biaya = gtk_label_new(biaya_text);

        gtk_grid_attach(GTK_GRID(table), label_id, 0, row, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label_tindakan, 1, row, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label_biaya, 2, row, 1, 1);

        // Set header width height and alignment
        gtk_widget_set_size_request(label_id, 50, 30);
        gtk_widget_set_size_request(label_tindakan, 200, 30);
        gtk_widget_set_size_request(label_biaya, 100, 30);

        tindakanList = tindakanList->next;
        row++;
    }
}

// Fungsi untuk Membangun Tab Finance
void buildFinanceTab(GtkWidget* financeTab, Tindakan* tindakanList) {

     // TOOLBAR
    // Create the toolbar
    GtkWidget* financeToolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(financeToolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(financeTab), financeToolbar, FALSE, FALSE, 0);

    // Create the "Add Data" button
    GtkToolItem *addPriceButton = gtk_tool_button_new(NULL, "Add Data");
    GtkWidget *addPriceButtonWidget = gtk_bin_get_child(GTK_BIN(addPriceButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *addPriceContext = gtk_widget_get_style_context(addPriceButtonWidget);
    gtk_style_context_add_class(addPriceContext, "add-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(financeToolbar), addPriceButton, -1);

    // Create the "edit Data" button
    GtkToolItem *editPriceButton = gtk_tool_button_new(NULL, "Edit Data");
    GtkWidget *editPriceButtonWidget = gtk_bin_get_child(GTK_BIN(editPriceButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *editPriceContext = gtk_widget_get_style_context(editPriceButtonWidget);
    gtk_style_context_add_class(editPriceContext, "edit-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(financeToolbar), editPriceButton, -1);
    // g_signal_connect(addPriceButton, "clicked", G_CALLBACK(addDataPatientButtonHandler), operatedData);

    // Create the "delete Data" button
    GtkToolItem *deletePriceButton = gtk_tool_button_new(NULL, "Delete Data");
    GtkWidget *deletePriceButtonWidget = gtk_bin_get_child(GTK_BIN(deletePriceButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *deletePriceContext = gtk_widget_get_style_context(deletePriceButtonWidget);
    gtk_style_context_add_class(deletePriceContext, "delete-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(financeToolbar), deletePriceButton, -1);
    

    // Set the button border
    gtk_container_set_border_width(GTK_CONTAINER(addPriceButton), 5);
    gtk_container_set_border_width(GTK_CONTAINER(editPriceButton), 5);
    gtk_container_set_border_width(GTK_CONTAINER(deletePriceButton), 5);




    // Create the scrollable table
    GtkWidget* scrollableFinance = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollableFinance), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(financeTab), scrollableFinance, TRUE, TRUE, 0);

    // Create the table
    GtkWidget* tableFinance = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(scrollableFinance), tableFinance);

    // Add table headers
    GtkWidget* header_id = gtk_label_new("ID");
    GtkWidget* header_tindakan = gtk_label_new("Tindakan");
    GtkWidget* header_biaya = gtk_label_new("Biaya");

    gtk_grid_attach(GTK_GRID(tableFinance), header_id, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableFinance), header_tindakan, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableFinance), header_biaya, 2, 0, 1, 1);

    // Add data to the table
    addTindakanToTable(tableFinance, tindakanList);

    // Set table properties
    gtk_widget_set_hexpand(tableFinance, TRUE);
    gtk_widget_set_halign(tableFinance, GTK_ALIGN_FILL);
    gtk_grid_set_row_spacing(GTK_GRID(tableFinance), 7);
    gtk_grid_set_column_spacing(GTK_GRID(tableFinance), 15);
}