#include   <gtk/gtk.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <time.h>
#include   "dataStructure.h"
#include   "search.h"
#include   "logger.h"
#include   "dataOperator.h"


// Fungsi untuk menambahkan data rekam medis ke tabel dan gunakan loadMedicalCheckup() untuk mengisi data MedicalCheckup
void addMedicalCheckUpToTable(GtkWidget* tableMedicalCheckUp, MedicalCheckup* medicalCheckupList, Patient** operatedData, Patient** allPatientData, Tindakan* tindakanList) {
    // Load data rekam medis
    loadMedicalCheckup(&medicalCheckupList, *operatedData);

    // Penampung Sementara
    char tindakan_text[50];
    char kontrol_text[20];

    // Add data to the table
    MedicalCheckup* current = medicalCheckupList;
    int i = 1;
    while (current != NULL) {
        // Create the labels
        GtkWidget* label_nama = gtk_label_new(current->namaLengkap);
        GtkWidget* label_id = gtk_label_new(current->idPasien);
        GtkWidget* label_diagnosis = gtk_label_new(current->diagnosis);

        idToTindakan(tindakanList, current->tindakanID, tindakan_text, NULL);
        GtkWidget* label_tindakan = gtk_label_new(tindakan_text);

        convertDateToString(current->kontrol, kontrol_text);
        GtkWidget* label_kontrol = gtk_label_new(kontrol_text);

        // Attach the labels to the table
        gtk_grid_attach(GTK_GRID(tableMedicalCheckUp), label_nama, 0, i, 1, 1);
        gtk_grid_attach(GTK_GRID(tableMedicalCheckUp), label_id, 1, i, 1, 1);
        gtk_grid_attach(GTK_GRID(tableMedicalCheckUp), label_diagnosis, 2, i, 1, 1);
        gtk_grid_attach(GTK_GRID(tableMedicalCheckUp), label_tindakan, 3, i, 1, 1);
        gtk_grid_attach(GTK_GRID(tableMedicalCheckUp), label_kontrol, 4, i, 1, 1);

        // Set the width of the labels
        gtk_widget_set_size_request(label_nama, 150, -1);
        gtk_widget_set_size_request(label_id, 100, -1);
        gtk_widget_set_size_request(label_diagnosis, 150, -1);
        gtk_widget_set_size_request(label_tindakan, 150, -1);
        gtk_widget_set_size_request(label_kontrol, 150, -1);

        // Increment the counter
        i++;
        current = current->next;
    }
}

// Fungsi untuk Membangun Tab Finance
void buildMedicalCheckUpTab(GtkWidget* medicalCheckUpTab, Patient** operatedData, Patient** allPatientData, Tindakan* tindakanList, MedicalCheckup* medicalCheckupList) {
    // Create the scrollable table
    GtkWidget* scrollableMedicalCheckUp = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollableMedicalCheckUp), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(medicalCheckUpTab), scrollableMedicalCheckUp, TRUE, TRUE, 0);

    // Create the table
    GtkWidget* tableMedicalCheckUp = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(scrollableMedicalCheckUp), tableMedicalCheckUp);

    // Add table headers
    GtkWidget* header_nama = gtk_label_new("Nama Pasien");
    GtkWidget* header_id = gtk_label_new("ID Pasien");
    GtkWidget* header_diagnosis = gtk_label_new("Diagnosis");
    GtkWidget* header_tindakan = gtk_label_new("Tindakan");
    GtkWidget* header_kontrol = gtk_label_new("Kontrol");

    gtk_grid_attach(GTK_GRID(tableMedicalCheckUp), header_nama, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableMedicalCheckUp), header_id, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableMedicalCheckUp), header_diagnosis, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableMedicalCheckUp), header_tindakan, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableMedicalCheckUp), header_kontrol, 4, 0, 1, 1);

    // Set the width of header
    gtk_widget_set_size_request(header_nama, 150, -1);
    gtk_widget_set_size_request(header_id, 100, -1);
    gtk_widget_set_size_request(header_diagnosis, 150, -1);
    gtk_widget_set_size_request(header_tindakan, 150, -1);
    gtk_widget_set_size_request(header_kontrol, 150, -1);

    // Add data to the table
    addMedicalCheckUpToTable(tableMedicalCheckUp, medicalCheckupList, operatedData, allPatientData, tindakanList);

    // Set table properties
    gtk_widget_set_hexpand(tableMedicalCheckUp, TRUE);
    gtk_widget_set_halign(tableMedicalCheckUp, GTK_ALIGN_FILL);
    gtk_grid_set_row_spacing(GTK_GRID(tableMedicalCheckUp), 7);
}
