#include   <gtk/gtk.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <time.h>
#include   "dataStructure.h"
#include   "search.h"
#include   "logger.h"
#include   "dataOperator.h"

void clearMedCheckDataTable(GtkWidget* table) {
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(table));
    for(iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}

void addDataMedCheckToTable(GtkWidget* table, Patient** operatedData, Tindakan* allTindakanList) {
    // Clear the table first
    clearMedCheckDataTable(table);
    
    // Add table headers, Hanya menampilkan No, Nama Lengkap, ID Pasien, Diagnosis, Tindakan, Kontrol
    GtkWidget* header1 = gtk_label_new("No");
    GtkWidget* header2 = gtk_label_new("Nama Lengkap");
    GtkWidget* header3 = gtk_label_new("ID Pasien");
    GtkWidget* header4 = gtk_label_new("Diagnosis");
    GtkWidget* header5 = gtk_label_new("Tindakan");
    GtkWidget* header6 = gtk_label_new("Kontrol");
    
    
    gtk_grid_attach(GTK_GRID(table), header1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header3, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header4, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header5, 4, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(table), header6, 5, 0, 1, 1);

    // Set the width of header
    gtk_widget_set_size_request(header1, 50, 30);
    gtk_widget_set_size_request(header2, 200, 30);
    gtk_widget_set_size_request(header3, 100, 30);
    gtk_widget_set_size_request(header4, 200, 30);
    gtk_widget_set_size_request(header5, 200, 30);
    gtk_widget_set_size_request(header6, 200, 30);

    // tambahkan margin kiri pada tabel
    gtk_widget_set_margin_start(header1, 10);

    /* Lakukan Operasi Pada patientList */

    // Dapatkan Date sekarang
    Date currentDate = getCurrentDate();
    // setDate(&currentDate, 1, 7, 2023);           // Untuk testing

    Patient* patientList = *operatedData;
    char label1_text[10];
    char tanggal_text[20];
    char kontrol_text[20];
    char biaya_text[20];
    char tindakan_text[50];
    int biaya;
    int i = 1;

    while (patientList != NULL) {
        History* history = patientList->history;
        while (history != NULL) {

            // Jika tanggal kontrol lebih dari tanggal sekarang, maka tampilkan
            if (compareDate(history->kontrol, currentDate) > 0) {
                sprintf(label1_text, "%d", i);
                GtkWidget* label1 = gtk_label_new(label1_text);

                GtkWidget* label2 = gtk_label_new(patientList->namaLengkap);

                GtkWidget* label3 = gtk_label_new(history->idPasien);
                GtkWidget* label4 = gtk_label_new(history->diagnosis);

                idToTindakan(allTindakanList, history->tindakanID, tindakan_text, &biaya);
                GtkWidget* label5 = gtk_label_new(tindakan_text);

                convertDateToString(history->kontrol, kontrol_text);
                GtkWidget* label6 = gtk_label_new(kontrol_text);

                // sprintf(biaya_text, "Rp %d", biaya);
                // GtkWidget* label7 = gtk_label_new(biaya_text);
                
                GtkWidget* checkbox = gtk_check_button_new();

                // set alignment
                gtk_widget_set_halign(label1, GTK_ALIGN_START);
                gtk_widget_set_halign(label2, GTK_ALIGN_START);
                gtk_widget_set_halign(label3, GTK_ALIGN_START);
                gtk_widget_set_halign(label4, GTK_ALIGN_START);
                gtk_widget_set_halign(label5, GTK_ALIGN_START);
                gtk_widget_set_halign(label6, GTK_ALIGN_START);
                // gtk_widget_set_halign(label7, GTK_ALIGN_START);

                gtk_grid_attach(GTK_GRID(table), label1, 0, i, 1, 1);
                gtk_grid_attach(GTK_GRID(table), label2, 1, i, 1, 1);
                gtk_grid_attach(GTK_GRID(table), label3, 2, i, 1, 1);
                gtk_grid_attach(GTK_GRID(table), label4, 3, i, 1, 1);
                gtk_grid_attach(GTK_GRID(table), label5, 4, i, 1, 1);
                gtk_grid_attach(GTK_GRID(table), label6, 5, i, 1, 1);
                // gtk_grid_attach(GTK_GRID(table), label7, 6, i, 1, 1);
                gtk_grid_attach(GTK_GRID(table), checkbox, 7, i, 1, 1);
                
                i++;
            } history = history->next;
        } patientList = patientList->next;
    }
}

// Function to build the patient data tab (Callable from activate.c)
void buildMedicalCheckUpTab(GtkWidget* userDataTab, Patient** operatedData, Patient** allPatientData, Tindakan* tindakanList) {
    Patient* patientList = *operatedData;
    // TOOLBAR
    // Create the toolbar
    GtkWidget* patientDataToolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(patientDataToolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(userDataTab), patientDataToolbar, FALSE, FALSE, 0);

    // PATIENT DATA DISPLAY
    // Create the scrollable table
    GtkWidget* scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollable), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(userDataTab), scrollable, TRUE, TRUE, 0);

    // Create the table
    GtkWidget* table = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(scrollable), table);

    // Adddata to the table
    addDataMedCheckToTable(table, operatedData, tindakanList);

    // Set table properties
    gtk_widget_set_hexpand(table, TRUE);
    gtk_widget_set_halign(table, GTK_ALIGN_FILL);
    gtk_grid_set_row_spacing(GTK_GRID(table), 7);
    gtk_grid_set_column_spacing(GTK_GRID(table), 15); 

    // Hubungkan sinyal 'changed' ke fungsi callback
    // buat parameter PatientParams
    PatientParams* PatientParameter = malloc(sizeof(PatientParams));
    PatientParameter->table = table;
    PatientParameter->operatedData = operatedData;
    PatientParameter->allPatientData = allPatientData;


    // linking semua data ke dalam parameter

    // // print data pasien pertama
    // printf("Nama Pasien Pertama 1: %s\n", *operatedData->namaLengkap);
}