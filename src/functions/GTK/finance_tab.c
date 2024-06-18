#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"
#include "dataOperator.h"

void clearFinanceDataTable(GtkWidget* table) {
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(table));
    for(iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}

// Fungsi untuk Menambahkan Data Tindakan ke Tabel
void addTindakanToTable(GtkWidget* table, Tindakan* tindakanList) {

    // Clear the table
    clearFinanceDataTable(table);

    // Add table headers
    GtkWidget* header_id = gtk_label_new("No");
    GtkWidget* header_tindakan = gtk_label_new("Tindakan");
    GtkWidget* header_biaya = gtk_label_new("Biaya");

    gtk_grid_attach(GTK_GRID(table), header_id, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header_tindakan, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header_biaya, 2, 0, 1, 1);

    int row = 1;

    while (tindakanList != NULL) {
        char id_text[10];
        sprintf(id_text, "%d", row);
        GtkWidget* label_id = gtk_label_new(id_text);
        
        GtkWidget* label_tindakan = gtk_label_new(tindakanList->Tindakan);

        char biaya_text[20];
        sprintf(biaya_text, "Rp %d", tindakanList->biaya);
        GtkWidget* label_biaya = gtk_label_new(biaya_text);

        // tambahkan checkbox
        GtkWidget* checkbox = gtk_check_button_new();

        gtk_grid_attach(GTK_GRID(table), label_id, 0, row, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label_tindakan, 1, row, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label_biaya, 2, row, 1, 1);
        gtk_grid_attach(GTK_GRID(table), checkbox, 3, row, 1, 1);

        // Set header width height and alignment
        gtk_widget_set_size_request(label_id, 50, 30);
        gtk_widget_set_size_request(label_tindakan, 200, 30);
        gtk_widget_set_size_request(label_biaya, 100, 30);

        tindakanList = tindakanList->next;
        row++;
    }
}

// Callback function for "Add Data" button
void addDatahandler(GtkWidget* button, gpointer data) {
    TindakanFormPointer* params = (TindakanFormPointer*) data;
    Tindakan* tindakanList = *(params->financialTabParams->allTindakanData);

    // Get the input values
    const char* layanan = strdup(gtk_entry_get_text(GTK_ENTRY(params->tindakan)));
    const char* harga = strdup(gtk_entry_get_text(GTK_ENTRY(params->biaya)));

    // cek apakah harga hanya angka
    int isNumber = 1;
    for (int i = 0; i < strlen(harga); i++) {
        if (harga[i] < '0' || harga[i] > '9') {
            isNumber = 0;
            break;
        }
    }

    // cek error
    int error = 0;
    if (strlen(layanan) == 0) {
        error = 1;
    } else if (strlen(harga) == 0) {
        error = 2;
    } else if (isNumber == 0) {
        error = 3;
    }

    if (error == 0){
        // Create the new Tindakan
        Tindakan* newTindakan = malloc(sizeof(Tindakan));
        newTindakan->id = 0;
        strcpy(newTindakan->Tindakan, layanan);
        newTindakan->biaya = atoi(harga);
        newTindakan->next = NULL;

        // Add the new Tindakan to the list
        if (tindakanList == NULL) {
            tindakanList = newTindakan;
        } else {
            Tindakan* current = tindakanList;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newTindakan;
        }

        // Update the table
        addTindakanToTable(params->financialTabParams->table, *(params->financialTabParams->allTindakanData));


        // show table
        gtk_widget_show_all(params->financialTabParams->table);

        // Close the window
        gtk_widget_destroy(params->window);

    } else {
        // Show error message
        GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error: ");
        if (error == 1) {
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Layanan tidak boleh kosong");
        } else if (error == 2) {
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Harga tidak boleh kosong");
        } else if (error == 3) {
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Harga harus berupa angka");
        }
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    
}

void addDataFinanceButtonHandler(GtkWidget* button, gpointer data) {
    FinancialTabParams* FinanceParams = (FinancialTabParams*) data;

    printf("Add Data Button Clicked\n");
    // Create the new window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Add Pricelist Data");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    // Create the main container
    GtkWidget* mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), mainBox);

    // Create the input fields
    GtkWidget* layananLabel = gtk_label_new("Layanan");
    GtkWidget* layananEntry = gtk_entry_new();
    GtkWidget* hargaLabel = gtk_label_new("Biaya:");
    GtkWidget* hargaEntry = gtk_entry_new();

    // Styling label
    gtk_widget_set_margin_top(layananLabel, 20);

    // Create the add button
    GtkWidget* addButton = gtk_button_new_with_label("Add Pricelist");
    gtk_widget_set_margin_top(addButton, 20);
    gtk_widget_set_margin_bottom(addButton, 20);

    GtkStyleContext *context = gtk_widget_get_style_context(addButton);
    gtk_style_context_add_class(context, "add-data-button-dialog");

    //buat params
    TindakanFormPointer* params = malloc(sizeof(TindakanFormPointer));
    params->tindakan = layananEntry;
    params->biaya = hargaEntry;
    params->financialTabParams =  FinanceParams;
    params->window = window;

    // Connect the button to the callback function
    g_signal_connect(addButton, "clicked", G_CALLBACK(addDatahandler), params);


    // Add the input fields and button to the main container
    gtk_box_pack_start(GTK_BOX(mainBox), layananLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), layananEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), hargaLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), hargaEntry, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(mainBox), addButton, FALSE, FALSE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);
}

// Callback function for "Edit Data" button
void editDataFinanceButtonHandler(GtkWidget* button, gpointer data) {
    FinancialTabParams* FinanceParams = (FinancialTabParams*) data;

    printf("Edit Data Button Clicked\n");
}

// Callback function for "Delete Data" button
void deleteDataFinanceButtonHandler(GtkWidget* button, gpointer data) {
    FinancialTabParams* FinanceParams = (FinancialTabParams*) data;

    // cari berapa data yang di check
    int count = 0;
    Tindakan* current = *(FinanceParams->allTindakanData);

    int row = 0;

    GtkWidget* checkbox;

    while(current != NULL){
        checkbox = gtk_grid_get_child_at(GTK_GRID(FinanceParams->table), 3, row+1);
        if (checkbox != NULL && GTK_IS_TOGGLE_BUTTON(checkbox)){
            if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox))) {
                count++;
            }
        }
        current = current->next;
        row++;
    }

    if(count == 0){
        GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Tidak ada data yang dipilih untuk dihapus");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    } else {
        // tampilkan dialog konfirmasi
        GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, "Apakah Anda yakin ingin menghapus data pasien yang dipilih?");
        int response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        if (response == GTK_RESPONSE_YES) {
            // hapus data yang dipilih
            current = *(FinanceParams->allTindakanData);
            Tindakan* prev = NULL;
            row = 0;
            while(current != NULL){
                checkbox = gtk_grid_get_child_at(GTK_GRID(FinanceParams->table), 3, row+1);
                if (checkbox != NULL && GTK_IS_TOGGLE_BUTTON(checkbox)){
                    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox))) {
                        if (prev == NULL) {
                            *(FinanceParams->allTindakanData) = current->next;
                            free(current);
                            current = *(FinanceParams->allTindakanData);
                        } else {
                            prev->next = current->next;
                            free(current);
                            current = prev->next;
                        }
                    } else {
                        prev = current;
                        current = current->next;
                    }
                }
                row++;
            }

            // Update the table
            addTindakanToTable(FinanceParams->table, *(FinanceParams->allTindakanData));
            gtk_widget_show_all(FinanceParams->table);

            // Show success message
            GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Data berhasil dihapus");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }

    printf("Delete Data Button Clicked\n");
}


// Fungsi untuk Membangun Tab Finance
void buildFinanceTab(GtkWidget* financeTab, Tindakan** allTindakanList) {
    Tindakan* tindakanList = *allTindakanList;

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

    // Add data to the table
    addTindakanToTable(tableFinance, tindakanList);

    // Set table properties
    gtk_widget_set_hexpand(tableFinance, TRUE);
    gtk_widget_set_halign(tableFinance, GTK_ALIGN_FILL);
    gtk_grid_set_row_spacing(GTK_GRID(tableFinance), 7);
    gtk_grid_set_column_spacing(GTK_GRID(tableFinance), 15);

    // Create params
    FinancialTabParams* params = malloc(sizeof(FinancialTabParams));
    params->table = tableFinance;
    params->allTindakanData = allTindakanList;

    // Connect the button to the callback function
    g_signal_connect(addPriceButton, "clicked", G_CALLBACK(addDataFinanceButtonHandler), params);
    g_signal_connect(editPriceButton, "clicked", G_CALLBACK(editDataFinanceButtonHandler), params);
    g_signal_connect(deletePriceButton, "clicked", G_CALLBACK(deleteDataFinanceButtonHandler), params);
}