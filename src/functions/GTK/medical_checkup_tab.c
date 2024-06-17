#include   <gtk/gtk.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <time.h>
#include   "dataStructure.h"
#include   "search.h"
#include   "logger.h"
#include   "dataOperator.h"

// Define an "empty" Date
Date emptyDate = {0, 0, 0};

void clearMedCheckDataTable(GtkWidget* table) {
    GList *children, *iter;

    printf("Clearing the table\n");
    children = gtk_container_get_children(GTK_CONTAINER(table));

    printf("Destroying the children\n");
    for(iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }

    printf("Freeing the list\n");
    g_list_free(children);
}

void addDataMedCheckToTable(GtkWidget* table, Patient** operatedData, Tindakan* allTindakanList, Date startDate, Date endDate) {
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
    setDate(&currentDate, 1, 7, 2023);           // Untuk testing

    Patient* patientList = *operatedData;
    char label1_text[10];
    char tanggal_text[20];
    char kontrol_text[20];
    char biaya_text[20];
    char tindakan_text[50];
    int biaya;
    int i = 1;

    printf("Start Algorithm\n");
    // Print compare date between emptyDate
    printf("Compare Date Start Date: %d End Date: %d\n", compareDate(startDate, emptyDate), compareDate(endDate, emptyDate));

    if(compareDate(startDate, emptyDate) == 0 && compareDate(endDate, emptyDate) == 0) {
        printf("Start Date and End Date is empty\n");
    } else {
        setDate(&currentDate, 1, 7, 2023);
    }

    while (patientList != NULL) {
        History* history = patientList->history;
        while (history != NULL) {

            // Jika tanggal kontrol lebih dari tanggal sekarang, maka tampilkan

            if (compareDate(startDate, emptyDate) == 0 && compareDate(endDate, emptyDate) == 0) {
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
                } 
            } else {
                // Jika tanggal kontrol berada di antara start date dan end date, maka tampilkan
                if (compareDate(history->kontrol, startDate) >= 0 && compareDate(history->kontrol, endDate) <= 0) {
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
                    // gtk_grid_attach(GTK_GRID(table), label7, 6, i, 1);
                    gtk_grid_attach(GTK_GRID(table), checkbox, 7, i, 1, 1);
                    
                    i++;
                }
            }

            history = history->next;
        } patientList = patientList->next;
    }
}

// Callback function for toolbar buttons add patient data
void confirmDateEntry(GtkWidget* button, gpointer data) {
    AddDateParams* params = (AddDateParams*) data;

    // Ubah tanggal start dan end ke dalam string biasa
    char* startDateText = strdup(gtk_entry_get_text(GTK_ENTRY(params->datePointer->startDate)));
    char* endDateText = strdup(gtk_entry_get_text(GTK_ENTRY(params->datePointer->endDate)));

    // Cek apakah format tanggal benar
    int startDateChecking = stringDateFormatVerify(startDateText);
    int endDateChecking = stringDateFormatVerify(endDateText);

    int isError = 0;
    if (startDateChecking == 1 && endDateChecking == 1){
        isError = 0;
    } else {
        isError = 1;
    }

    // JIka TIdak ada Error
    if (isError == 0){
        // Display addDataMedCheckToTable dengan tanggal yang diinput
        Date startDate = convertStringToDate(startDateText);
        Date endDate = convertStringToDate(endDateText);

        // Print the date
        printDate(startDate);
        printDate(endDate);

        Patient** tempData = malloc(sizeof(Patient*));
        *tempData = NULL; // Initialize the result pointer to NULL

        copyPatient(*params->patientParams->allPatientData, tempData);

        freePatientList(*params->patientParams->operatedData);
        *params->patientParams->operatedData = *tempData;

        // Update the table
        addDataMedCheckToTable(params->patientParams->table, params->patientParams->operatedData, params->patientParams->allTindakanData, startDate, endDate);

        // Show the updated table
        gtk_widget_show_all(params->patientParams->table);

        // tutup jendela setelah data berhasil ditambahkan
        gtk_widget_destroy(params->window);

    } else {
        char* pesanError;
        switch (isError)
        {
        case 1:
            pesanError = "Format Start Date / End Date tidak valid, gunakan format 'DD MMM YYYY' (Contoh: 15 Mei 2024)";
            break;
        default:
            break;
        }

        // tampilkan pesan error
        GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, pesanError);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}


void RefreshMedCheckButtonHandler(GtkWidget* button, gpointer data)
{   
    // Get the patient list
    PatientParams* params = (PatientParams*) data;

    //uji tampilkan nama pertama pada data pasien
    // printf("Nama Pasien Pertama: %s\n", (*operatedData)->namaLengkap);
    // Create the new window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Add Patient Data");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Create the main container
    GtkWidget* mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), mainBox);

    // Create the input fields
    GtkWidget* startLabel = gtk_label_new("Start Date:");
    GtkWidget* startEntry = gtk_entry_new();
    GtkWidget* endLabel = gtk_label_new("End Date:");
    GtkWidget* endEntry = gtk_entry_new();

    // Styling label
    gtk_widget_set_margin_top(startLabel, 20);

    // Create the add button
    GtkWidget* submitButton = gtk_button_new_with_label("Submit");
    gtk_widget_set_margin_bottom(submitButton, 20);

    GtkStyleContext *context = gtk_widget_get_style_context(submitButton);
    gtk_style_context_add_class(context, "add-data-button-dialog");

    // Create the parameter for the add button
    DatePointer* DatePointerData = malloc(sizeof(DatePointer));
    DatePointerData->startDate = startEntry;
    DatePointerData->endDate = endEntry;

    // // Create the parameter for the add button
    AddDateParams* addDateParams = malloc(sizeof(AddDateParams));
    addDateParams->datePointer = DatePointerData;
    addDateParams->window = window;
    addDateParams->patientParams = params;

    g_signal_connect(submitButton, "clicked", G_CALLBACK(confirmDateEntry), addDateParams);


    // Add the input fields and button to the main container
    gtk_box_pack_start(GTK_BOX(mainBox), startLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), startEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), endLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), endEntry, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(mainBox), submitButton, FALSE, FALSE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);

    gtk_widget_show_all(params->table);
}

// Function to build the patient data tab (Callable from activate.c)
void buildMedicalCheckUpTab(GtkWidget* userDataTab, Patient** operatedData, Patient** allPatientData, Tindakan* tindakanList) {
    Patient* patientList = *operatedData;
    // TOOLBAR
    // Create the toolbar
    GtkWidget* medCheckToolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(medCheckToolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(userDataTab), medCheckToolbar, FALSE, FALSE, 0);

    // Create the "Add Data" button
    GtkToolItem *addPatientDataButton = gtk_tool_button_new(NULL, "Refresh");
    GtkWidget *addPatientDataButtonWidget = gtk_bin_get_child(GTK_BIN(addPatientDataButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *addPatientContext = gtk_widget_get_style_context(addPatientDataButtonWidget);
    gtk_style_context_add_class(addPatientContext, "add-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(medCheckToolbar), addPatientDataButton, -1);

    // PATIENT DATA DISPLAY
    // Create the scrollable table
    GtkWidget* scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollable), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(userDataTab), scrollable, TRUE, TRUE, 0);

    // Create the table
    GtkWidget* table = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(scrollable), table);

    // Adddata to the table
    addDataMedCheckToTable(table, operatedData, tindakanList, emptyDate, emptyDate);

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
    PatientParameter->allTindakanData = tindakanList;

    // linking semua data ke dalam parameter
    g_signal_connect(addPatientDataButton, "clicked", G_CALLBACK(RefreshMedCheckButtonHandler), PatientParameter);
}