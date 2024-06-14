#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"

// Fungsi Dummy untuk Membuat Linked List Tindakan
Tindakan* createDummyTindakanList() {
    Tindakan* head = (Tindakan*) malloc(sizeof(Tindakan));
    head->id = 1;
    strcpy(head->Tindakan, "Operasi Jantung");
    head->biaya = 50000000;
    head->next = (Tindakan*) malloc(sizeof(Tindakan));
    head->next->id = 2;
    strcpy(head->next->Tindakan, "Kemoterapi");
    head->next->biaya = 20000000;
    head->next->next = (Tindakan*) malloc(sizeof(Tindakan));
    head->next->next->id = 3;
    strcpy(head->next->next->Tindakan, "Cek Darah");
    head->next->next->biaya = 150000;
    head->next->next->next = NULL;
    return head;
}

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

        tindakanList = tindakanList->next;
        row++;
    }
}

// Fungsi untuk Membangun Tab Finance
void buildFinanceTab(GtkWidget* financeTab, Tindakan* tindakanList) {
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