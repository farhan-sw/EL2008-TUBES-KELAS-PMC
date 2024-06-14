#include   <gtk/gtk.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <time.h>
#include   "dataStructure.h"

void on_search_entry_changed(GtkSearchEntry *entry, gpointer user_data) {
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Search entry changed: %s\n", text);

    // Implementasikan logika lain di sini
}

// Callback function for toolbar buttons add patient data
void addPatientData(GtkWidget* button, gpointer data) {
    // Handle the add button click event here
    printf("Adding Data and close the window\n");
}

void addDataPatientButtonHandler(GtkWidget* button, gpointer data)
{   
    // Get the patient list
    Patient* patientList = (Patient*)data;
    //uji tampilkan nama pertama pada data pasien
    printf("Nama Pasien Pertama: %s\n", patientList->namaLengkap);
    // Create the new window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Add Patient Data");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Create the main container
    GtkWidget* mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), mainBox);

    // Create the input fields
    GtkWidget* namaLabel = gtk_label_new("Nama Lengkap:");
    GtkWidget* namaEntry = gtk_entry_new();
    GtkWidget* alamatLabel = gtk_label_new("Alamat:");
    GtkWidget* alamatEntry = gtk_entry_new();
    GtkWidget* kotaLabel = gtk_label_new("Kota:");
    GtkWidget* kotaEntry = gtk_entry_new();
    GtkWidget* kotaKelahiranLabel = gtk_label_new("Tempat Lahir:");
    GtkWidget* kotaKelahiranEntry = gtk_entry_new();
    GtkWidget* umurLabel = gtk_label_new("Umur:");
    GtkWidget* umurEntry = gtk_entry_new();
    GtkWidget* noBPJSLabel = gtk_label_new("Nomor BPJS:");
    GtkWidget* noBPJSEntry = gtk_entry_new();
    GtkWidget* idPasienLabel = gtk_label_new("ID Pasien:");
    GtkWidget* idPasienEntry = gtk_entry_new();

    // Styling label
    gtk_widget_set_margin_top(namaLabel, 20);

    // Create the add button
    GtkWidget* addButton = gtk_button_new_with_label("Add Data");
    gtk_widget_set_margin_bottom(addButton, 20);

    GtkStyleContext *context = gtk_widget_get_style_context(addButton);
    gtk_style_context_add_class(context, "add-data-button-dialog");

    g_signal_connect(addButton, "clicked", G_CALLBACK(addPatientData), NULL);

    // Close the window when button clicked
    g_signal_connect_swapped(addButton, "clicked", G_CALLBACK(gtk_widget_destroy), window);


    // Add the input fields and button to the main container
    gtk_box_pack_start(GTK_BOX(mainBox), namaLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), namaEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), alamatLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), alamatEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaKelahiranLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaKelahiranEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), umurLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), umurEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), noBPJSLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), noBPJSEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), idPasienLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), idPasienEntry, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(mainBox), addButton, FALSE, FALSE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);
}

void clearPatientDataTable(GtkWidget* table) {
    GList* children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(table));
    iter = children;
    for (int i = 0; i < 8 && iter != NULL; i++){
        iter = g_list_next(iter); // Benar-benar melewati baris pertama
    }
    //baca isi data itter
    while (iter != NULL) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
        iter = g_list_next(iter);
    }
    g_list_free(children);
}

void addDataPatientToTable(GtkWidget* table, Patient* patientsList) {
    // Clear the table first
    clearPatientDataTable(table);
    // cari panjang linkedlist
    Patient* patientstemp = patientsList;
    int count = 0;
    while (patientstemp != NULL) {
        count++;
        patientstemp = patientstemp->next;
    }

    patientstemp = patientsList;
    char umur_text[10];
    char noBPJS_text[20];
    char tanggalLahir_text[20];
    // cetak data ke dalam tabel
    for (int i = 0; i < count; i++) {
        char label1_text[10];
        sprintf(label1_text, "%d", i+1);
        GtkWidget* label1 = gtk_label_new(label1_text);
        GtkWidget* label2 = gtk_label_new(patientstemp->namaLengkap);
        GtkWidget* label3 = gtk_label_new(patientstemp->alamat);
        GtkWidget* label4 = gtk_label_new(patientstemp->kota);
        GtkWidget* label5 = gtk_label_new(patientstemp->tempatLahir);
        convertDateToString(patientstemp->tanggalLahir, tanggalLahir_text);
        GtkWidget* label6 = gtk_label_new(tanggalLahir_text);
        
        sprintf(umur_text, "%d", patientstemp->umur);
        GtkWidget* label7 = gtk_label_new(umur_text);

        sprintf(noBPJS_text, "%d", patientstemp->noBPJS);
        GtkWidget* label8 = gtk_label_new(noBPJS_text);
        GtkWidget* label9 = gtk_label_new(patientstemp->idPasien);
        GtkWidget* checkbox = gtk_check_button_new();
        gtk_grid_attach(GTK_GRID(table), label1, 0, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label2, 1, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label3, 2, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label4, 3, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label5, 4, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label6, 5, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label7, 6, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label8, 7, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label9, 8, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), checkbox, 9, i+1, 1, 1);
        patientstemp = patientstemp->next;
    }

    // //tampilkan data pasien pertama
    // printf("Nama Pasien Pertama 2: %s\n", patientsList->namaLengkap);
}

// Function to build the patient data tab (Callable from activate.c)
void buildPatientDataTab(GtkWidget* userDataTab, Patient* patientList){
    // TOOLBAR
    // Create the toolbar
    GtkWidget* patientDataToolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(patientDataToolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(userDataTab), patientDataToolbar, FALSE, FALSE, 0);

    // Create the "Add Data" button
    GtkToolItem *addPatientDataButton = gtk_tool_button_new(NULL, "Add Data");
    GtkWidget *addPatientDataButtonWidget = gtk_bin_get_child(GTK_BIN(addPatientDataButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *context = gtk_widget_get_style_context(addPatientDataButtonWidget);
    gtk_style_context_add_class(context, "add-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(patientDataToolbar), addPatientDataButton, -1);
    g_signal_connect(addPatientDataButton, "clicked", G_CALLBACK(addDataPatientButtonHandler), patientList);

    // Set the button border
    gtk_container_set_border_width(GTK_CONTAINER(addPatientDataButton), 5);

    // Create the search box
    GtkWidget* searchBox = gtk_search_entry_new();
    gtk_box_pack_start(GTK_BOX(userDataTab), searchBox, FALSE, FALSE, 0);
    // Hubungkan sinyal 'changed' ke fungsi callback
    g_signal_connect(searchBox, "changed", G_CALLBACK(on_search_entry_changed), NULL);

    // PATIENT DATA DISPLAY
    // Create the scrollable table
    GtkWidget* scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollable), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(userDataTab), scrollable, TRUE, TRUE, 0);

    // Create the table
    GtkWidget* table = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(scrollable), table);

    // Add table headers
    GtkWidget* header1 = gtk_label_new("No");
    GtkWidget* header2 = gtk_label_new("Nama Lengkap");
    GtkWidget* header3 = gtk_label_new("Alamat");
    GtkWidget* header4 = gtk_label_new("Kota");
    GtkWidget* header5 = gtk_label_new("Tempat Lahir");
    GtkWidget* header6 = gtk_label_new("Tanggal Lahir");
    GtkWidget* header7 = gtk_label_new("Umur");
    GtkWidget* header8 = gtk_label_new("No BPJS");
    GtkWidget* header9 = gtk_label_new("ID Pasien");
    
    gtk_grid_attach(GTK_GRID(table), header1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header3, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header4, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header5, 4, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header6, 5, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header7, 6, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header8, 7, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header9, 8, 0, 1, 1);

    // Set the width of header
    gtk_widget_set_size_request(header2, 150, -1);
    gtk_widget_set_size_request(header3, 200, -1);

    // tambahkan margin kiri pada tabel
    gtk_widget_set_margin_start(header1, 10);

    // Add dummy data to the table
    addDataPatientToTable(table, patientList);

    // Set table properties
    gtk_widget_set_hexpand(table, TRUE);
    gtk_widget_set_halign(table, GTK_ALIGN_FILL);
    gtk_grid_set_row_spacing(GTK_GRID(table), 7);
    gtk_grid_set_column_spacing(GTK_GRID(table), 15); 

    // // print data pasien pertama
    // printf("Nama Pasien Pertama 1: %s\n", patientList->namaLengkap);
}