#include   <gtk/gtk.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <time.h>
#include   "dataStructure.h"
#include   "search.h"
#include   "logger.h"
#include   "dataOperator.h"

void clearMedicalHistoryDataTable(GtkWidget* table) {
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(table));
    for(iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}

void addMedicalRecordToTable(GtkWidget* table) {
    for (int i = 0; i < sizeof(medRec) / sizeof(medRec[0]); i++) {
        char label1_text[10];
        sprintf(label1_text, "%d", i+1);
        GtkWidget* label1 = gtk_label_new(label1_text);
        GtkWidget* label2 = gtk_label_new(medRec[i][0]);
        GtkWidget* label3 = gtk_label_new(medRec[i][1]);
        GtkWidget* label4 = gtk_label_new(medRec[i][2]);
        GtkWidget* label5 = gtk_label_new(medRec[i][3]);
        GtkWidget* label6 = gtk_label_new(medRec[i][4]);
        GtkWidget* label7 = gtk_label_new(medRec[i][5]);
        GtkWidget* checkbox = gtk_check_button_new();

        gtk_grid_attach(GTK_GRID(table), label1, 0, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label2, 1, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label3, 2, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label4, 3, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label5, 4, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label6, 5, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), label7, 6, i+1, 1, 1);
        gtk_grid_attach(GTK_GRID(table), checkbox, 7, i+1, 1, 1);
    }
}

// Function to add history data to the table
void addHistoryToTable(GtkWidget* table, Patient* patientList, Tindakan* allTindakanList) {
    // Clear the table
    clearMedicalHistoryDataTable(table);

    int i = 1;

    // Penampung Sementara
    char tanggal_text[20];
    char kontrol_text[20];
    char biaya_text[20];
    char tindakan_text[50];
    int biaya;

    while (patientList != NULL) {
        History* history = patientList->history;
        while (history != NULL) {
            char label1_text[10];
            sprintf(label1_text, "%d", i);
            GtkWidget* label1 = gtk_label_new(label1_text);

            convertDateToString(history->tanggal, tanggal_text);
            GtkWidget* label2 = gtk_label_new(tanggal_text);

            GtkWidget* label3 = gtk_label_new(history->idPasien);
            GtkWidget* label4 = gtk_label_new(history->diagnosis);

            idToTindakan(allTindakanList, history->tindakanID, tindakan_text, &biaya);
            GtkWidget* label5 = gtk_label_new(tindakan_text);

            convertDateToString(history->kontrol, kontrol_text);
            GtkWidget* label6 = gtk_label_new(kontrol_text);

            sprintf(biaya_text, "Rp %d", biaya);
            GtkWidget* label7 = gtk_label_new(biaya_text);
            
            GtkWidget* checkbox = gtk_check_button_new();

            // set alignment
            gtk_widget_set_halign(label2, GTK_ALIGN_START);
            gtk_widget_set_halign(label3, GTK_ALIGN_START);
            gtk_widget_set_halign(label4, GTK_ALIGN_START);
            gtk_widget_set_halign(label5, GTK_ALIGN_START);
            gtk_widget_set_halign(label6, GTK_ALIGN_START);
            gtk_widget_set_halign(label7, GTK_ALIGN_START);

            gtk_grid_attach(GTK_GRID(table), label1, 0, i, 1, 1);
            gtk_grid_attach(GTK_GRID(table), label2, 1, i, 1, 1);
            gtk_grid_attach(GTK_GRID(table), label3, 2, i, 1, 1);
            gtk_grid_attach(GTK_GRID(table), label4, 3, i, 1, 1);
            gtk_grid_attach(GTK_GRID(table), label5, 4, i, 1, 1);
            gtk_grid_attach(GTK_GRID(table), label6, 5, i, 1, 1);
            gtk_grid_attach(GTK_GRID(table), label7, 6, i, 1, 1);
            gtk_grid_attach(GTK_GRID(table), checkbox, 7, i, 1, 1);
            history = history->next;
            i++;
        }
        patientList = patientList->next;
    }
}

// Callback function for search box
void on_searchMedRecordBox_changed(GtkSearchEntry* entry, gpointer user_data)
{

}

void addHistoryData(GtkWidget* button, gpointer data)
{
    AddHistoryParams* addHistoryParams = (AddHistoryParams*)data;

    // Ubah Tanggal dari Entry ke char biasa dan kontrol
    char* tanggal = strdup(gtk_entry_get_text(GTK_ENTRY(addHistoryParams->newHistoryFormPointer->tanggal)));
    char* kontrol = strdup(gtk_entry_get_text(GTK_ENTRY(addHistoryParams->newHistoryFormPointer->kontrol)));
    char* diagnosis = strdup(gtk_entry_get_text(GTK_ENTRY(addHistoryParams->newHistoryFormPointer->diagnosis)));
    char* idPasien = strdup(gtk_entry_get_text(GTK_ENTRY(addHistoryParams->newHistoryFormPointer->idPasien)));
    char* tindakan = strdup(gtk_entry_get_text(GTK_ENTRY(addHistoryParams->newHistoryFormPointer->tindakan)));

    // Validasi Tanggal
    int tanggalValid = stringDateFormatVerify(tanggal);
    int kontrolValid = stringDateFormatVerify(kontrol);

    // Validasi hanya nomer untuk ID
    // Cek apakah ID Pasien sudah ada
    int isIDExist = isIdPatientExist(*addHistoryParams->patientParams->operatedData, idPasien);
    
    // Validasi TIndakan ada
    int istindakanExist = isTindakanExist(addHistoryParams->patientParams->allTindakanData, tindakan);
    
    // Cek Validasi Semua jawaban haru berisi
    int isError = 0;
    if(strcmp(tanggal, "") == 0){
        isError = 1;
    } else if (strcmp(idPasien, "") == 0){
        isError = 2;
    } else if (strcmp(diagnosis, "") == 0){
        isError = 3;
    } else if (strcmp(tindakan, "") == 0){
        isError = 4;
    } else if (strcmp(kontrol, "") == 0){
        isError = 5;
    } else if (isIDExist == 0){
        isError = 6;
    } else if (istindakanExist == 0){
        isError = 7;
    }

    // Jika tidak ada error
    if(isError == 0){
        // Create new history
        History* newHistory = malloc(sizeof(History));

        // Isi Nama Lengkap dan ID Pasien
        Patient* patient = findPatient(*addHistoryParams->patientParams->allPatientData, idPasien);

        // Isi ID Pasien
        strcpy(newHistory->idPasien, idPasien);

        // Isi Diagnosis
        strcpy(newHistory->diagnosis, diagnosis);

        // Isi Tanggal
        Date tanggalDate;
        tanggalDate = convertStringToDate(tanggal);
        newHistory->tanggal = tanggalDate;

        // Isi Kontrol
        Date kontrolDate;
        kontrolDate = convertStringToDate(kontrol);
        newHistory->kontrol = kontrolDate;

        // Isi Tindakan
        newHistory->tindakanID = TindakanToID(addHistoryParams->patientParams->allTindakanData, tindakan);

        // Isi Biaya
        newHistory->biaya = idToBiaya(addHistoryParams->patientParams->allTindakanData, newHistory->tindakanID);


        // Print SIngle History
        // printHistory(newHistory);

        Patient** tempData = malloc(sizeof(Patient*));
        *tempData = NULL; // Initialize the result pointer to NULL

        // Add History to allPatientData
        addHistory(&patient->history, newHistory);

        // Copy allPatientData to tempData
        copyPatient(*addHistoryParams->patientParams->allPatientData, tempData);

        freePatientList(*addHistoryParams->patientParams->operatedData);
        *addHistoryParams->patientParams->operatedData = *tempData;

        // Update Table
        addHistoryToTable(addHistoryParams->patientParams->table, *addHistoryParams->patientParams->operatedData, addHistoryParams->patientParams->allTindakanData);

        // Show updated table
        gtk_widget_show_all(addHistoryParams->patientParams->table);

        // Close the window
        gtk_widget_destroy(addHistoryParams->window);
        

    } else {
        // Show error message
        GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(addHistoryParams->window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error: ");
        switch (isError)
        {
        case 1:
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Tanggal tidak boleh kosong");
            break;
        case 2:
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "ID Pasien tidak boleh kosong");
            break;
        case 3:
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Diagnosis tidak boleh kosong");
            break;
        case 4:
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Tindakan tidak boleh kosong");
            break;
        case 5:
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Kontrol tidak boleh kosong");
            break;
        case 6:
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "ID Pasien tidak ditemukan");
            break;
        case 7:
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Tindakan tidak ditemukan");
            break;
        default:
            break;
        }

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

// Callback function for "Add Data" button
void on_addHistoryData_button_clicked(GtkWidget* button, gpointer data)
{
    // Get patient data
    PatientParams* PatientParameter = (PatientParams*)data;

    // Create New Window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Add Medical Record");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    // Create Main Container
    GtkWidget* mainContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), mainContainer);

    // Create Input Field
    GtkWidget* tanggalLabel = gtk_label_new("Tanggal");
    GtkWidget* tanggalEntry = gtk_entry_new();
    GtkWidget* idPasienLabel = gtk_label_new("ID Pasien");
    GtkWidget* idPasienEntry = gtk_entry_new();
    GtkWidget* diagnosisLabel = gtk_label_new("Diagnosis");
    GtkWidget* diagnosisEntry = gtk_entry_new();
    GtkWidget* tindakanLabel = gtk_label_new("Tindakan");
    GtkWidget* tindakanEntry = gtk_entry_new();
    GtkWidget* kontrolLabel = gtk_label_new("Kontrol");
    GtkWidget* kontrolEntry = gtk_entry_new();

    // Style Label
    gtk_widget_set_halign(tanggalLabel, GTK_ALIGN_START);
    gtk_widget_set_halign(idPasienLabel, GTK_ALIGN_START);
    gtk_widget_set_halign(diagnosisLabel, GTK_ALIGN_START);
    gtk_widget_set_halign(tindakanLabel, GTK_ALIGN_START);
    gtk_widget_set_halign(kontrolLabel, GTK_ALIGN_START);

    // Create Add Button
    GtkWidget* addButton = gtk_button_new_with_label("Add");
    gtk_widget_set_margin_bottom(addButton, 20);
    gtk_widget_set_halign(addButton, GTK_ALIGN_CENTER);
    GtkStyleContext *context = gtk_widget_get_style_context(addButton);
    gtk_style_context_add_class(context, "add-data-button-dialog");

    // Create the parameter for the add button
    NewHistoryFormPointer* newHistoryFormPointer = malloc(sizeof(NewHistoryFormPointer));
    newHistoryFormPointer->tanggal = tanggalEntry;
    newHistoryFormPointer->idPasien = idPasienEntry;
    newHistoryFormPointer->diagnosis = diagnosisEntry;
    newHistoryFormPointer->tindakan = tindakanEntry;
    newHistoryFormPointer->kontrol = kontrolEntry;

    // Create the parameter for the add button
    AddHistoryParams* addHistoryParams = malloc(sizeof(AddHistoryParams));
    addHistoryParams->patientParams = PatientParameter;
    addHistoryParams->window = window;
    addHistoryParams->newHistoryFormPointer = newHistoryFormPointer;

    // Linking the signal with the callback
    g_signal_connect(addButton, "clicked", G_CALLBACK(addHistoryData), addHistoryParams);


    // Add the input fields and button to the main container
    gtk_box_pack_start(GTK_BOX(mainContainer), tanggalLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainContainer), tanggalEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainContainer), idPasienLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainContainer), idPasienEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainContainer), diagnosisLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainContainer), diagnosisEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainContainer), tindakanLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainContainer), tindakanEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainContainer), kontrolLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainContainer), kontrolEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainContainer), addButton, FALSE, FALSE, 0);

    // Show the window
    gtk_widget_show_all(window);
}

// Callback function for "Edit Data" button
void on_editHistoryData_button_clicked(GtkWidget* button, gpointer data)
{
    PatientParams* PatientParameter = (PatientParams*)data;
    Patient** operatedData = PatientParameter->operatedData;
    Patient** allPatientData = PatientParameter->allPatientData;
    GtkWidget* table = PatientParameter->table;

    // Edit data in the table
    // addHistoryToTable(table, *operatedData, *allPatientData);
}

// Callback function for "Delete Data" button
void on_deleteHistoryData_button_clicked(GtkWidget* button, gpointer data)
{
    PatientParams* PatientParameter = (PatientParams*)data;
    Patient** operatedData = PatientParameter->operatedData;
    Patient** allPatientData = PatientParameter->allPatientData;
    GtkWidget* table = PatientParameter->table;

    // Delete data in the table
    // addHistoryToTable(table, *operatedData, *allPatientData);
}

// Function to build the medical record tab (Callable from main.c)
void buildMedicalRecordTab(GtkWidget* medicalRecordsTab, Patient** operatedData, Patient** allPatientData, Tindakan* allTindakanList) {
    Patient* patientList = *operatedData;

    // Creating Tabs for Medical Records
    // TOOLBAR
    // Create the toolbar
    GtkWidget* HistoryDataToolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(HistoryDataToolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(medicalRecordsTab), HistoryDataToolbar, FALSE, FALSE, 0);

    // Create the "Add Data" button
    GtkToolItem *addHistoryDataButton = gtk_tool_button_new(NULL, "Add Data");
    GtkWidget *addHistoryDataButtonWidget = gtk_bin_get_child(GTK_BIN(addHistoryDataButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *addHistoryContext = gtk_widget_get_style_context(addHistoryDataButtonWidget);
    gtk_style_context_add_class(addHistoryContext, "add-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(HistoryDataToolbar), addHistoryDataButton, -1);

    // Create the "edit Data" button
    GtkToolItem *editHistoryDataButton = gtk_tool_button_new(NULL, "Edit Data");
    GtkWidget *editHistoryDataButtonWidget = gtk_bin_get_child(GTK_BIN(editHistoryDataButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *editHistoryContext = gtk_widget_get_style_context(editHistoryDataButtonWidget);
    gtk_style_context_add_class(editHistoryContext, "edit-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(HistoryDataToolbar), editHistoryDataButton, -1);

    // Create the "delete Data" button
    GtkToolItem *deleteHistoryDataButton = gtk_tool_button_new(NULL, "Delete Data");
    GtkWidget *deleteHistoryDataButtonWidget = gtk_bin_get_child(GTK_BIN(deleteHistoryDataButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *deleteHistoryContext = gtk_widget_get_style_context(deleteHistoryDataButtonWidget);
    gtk_style_context_add_class(deleteHistoryContext, "delete-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(HistoryDataToolbar), deleteHistoryDataButton, -1);

    // Set the button border
    gtk_container_set_border_width(GTK_CONTAINER(addHistoryDataButton), 5);
    gtk_container_set_border_width(GTK_CONTAINER(editHistoryDataButton), 5);
    gtk_container_set_border_width(GTK_CONTAINER(deleteHistoryDataButton), 5);

    // Create the search box
    GtkWidget* searchMedRecordBox = gtk_search_entry_new();
    gtk_box_pack_start(GTK_BOX(medicalRecordsTab), searchMedRecordBox, FALSE, FALSE, 0);

    // ==================================================================================================

    // MEDICAL RECORDS DATA DISPLAY
    // Create the scrollable table
    GtkWidget* scrollableMedRec = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollableMedRec), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(medicalRecordsTab), scrollableMedRec, TRUE, TRUE, 0);

    // Create the table
    GtkWidget* tableMedRec = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(scrollableMedRec), tableMedRec);

    // Add table headers
    GtkWidget* header1MedRec = gtk_label_new("No");
    GtkWidget* header2MedRec = gtk_label_new("Tanggal");
    GtkWidget* header3MedRec = gtk_label_new("ID Pasien");
    GtkWidget* header4MedRec = gtk_label_new("Diagnosis");
    GtkWidget* header5MedRec = gtk_label_new("Tindakan");
    GtkWidget* header6MedRec = gtk_label_new("Kontrol");
    GtkWidget* header7MedRec = gtk_label_new("Biaya");
    
    gtk_grid_attach(GTK_GRID(tableMedRec), header1MedRec, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableMedRec), header2MedRec, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableMedRec), header3MedRec, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableMedRec), header4MedRec, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableMedRec), header5MedRec, 4, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableMedRec), header6MedRec, 5, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(tableMedRec), header7MedRec, 6, 0, 1, 1);

    // Set the width of header
    gtk_widget_set_size_request(header4MedRec, 200, -1);
    gtk_widget_set_size_request(header5MedRec, 200, -1);

    // tambahkan margin kiri pada tabel
    gtk_widget_set_margin_start(header1MedRec, 10);

    // Input data rekam medis dari patientList
    addHistoryToTable(tableMedRec, patientList, allTindakanList);

    // Set table properties
    gtk_widget_set_hexpand(tableMedRec, TRUE);
    gtk_widget_set_halign(tableMedRec, GTK_ALIGN_FILL);
    gtk_grid_set_row_spacing(GTK_GRID(tableMedRec), 7);
    gtk_grid_set_column_spacing(GTK_GRID(tableMedRec), 15); 


    /* ----------------------- HUBUNGKAN SINYAL DENGAN CALLBACK ----------------------- */
    // buat parameter PatientParams
    PatientParams* PatientParameter = malloc(sizeof(PatientParams));
    PatientParameter->table = tableMedRec;
    PatientParameter->operatedData = operatedData;
    PatientParameter->allPatientData = allPatientData;
    PatientParameter->allTindakanData = allTindakanList;

    // Linking the signal with the callback
    g_signal_connect(searchMedRecordBox, "changed", G_CALLBACK(on_searchMedRecordBox_changed), PatientParameter);
    g_signal_connect(addHistoryDataButton, "clicked", G_CALLBACK(on_addHistoryData_button_clicked), PatientParameter);
    g_signal_connect(editHistoryDataButton, "clicked", G_CALLBACK(on_editHistoryData_button_clicked), PatientParameter);
    g_signal_connect(deleteHistoryDataButton, "clicked", G_CALLBACK(on_deleteHistoryData_button_clicked), PatientParameter); 
}

