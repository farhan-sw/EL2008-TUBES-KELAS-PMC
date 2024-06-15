#include   <gtk/gtk.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <time.h>
#include   "dataStructure.h"
#include   "search.h"
#include   "logger.h"
#include   "dataOperator.h"


void clearPatientDataTable(GtkWidget* table) {
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(table));
    for(iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}

void addDataPatientToTable(GtkWidget* table, Patient** operatedData) {
    // Clear the table first
    clearPatientDataTable(table);
    
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

    // cari panjang linkedlist
    Patient* patientstemp = *operatedData;
    int count = 0;
    while (patientstemp != NULL) {
        count++;
        patientstemp = patientstemp->next;
    }

    patientstemp = *operatedData;
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

        // atur alignment
        gtk_widget_set_halign(label2, GTK_ALIGN_START);
        gtk_widget_set_halign(label3, GTK_ALIGN_START);
        gtk_widget_set_halign(label4, GTK_ALIGN_START);
        gtk_widget_set_halign(label5, GTK_ALIGN_START);
        gtk_widget_set_halign(label6, GTK_ALIGN_START);
        gtk_widget_set_halign(label7, GTK_ALIGN_START);
        gtk_widget_set_halign(label8, GTK_ALIGN_START);
        gtk_widget_set_halign(label9, GTK_ALIGN_START);

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
    // printf("Nama Pasien Pertama 2: %s\n", *operatedData->namaLengkap);
}

// callback function for search entry
void searchPatientDataOnChanged(GtkSearchEntry *entry, gpointer user_data) {
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    char *mutableText = g_strdup(text);
    PatientParams* params = (PatientParams*) user_data;
    // Handle the search event here
    // Implementasikan logika pencarian di sini
    
    searchPatient(*params->allPatientData, params->operatedData, mutableText);
    // printPatientList(*params->operatedData);
    // Implementasikan logika lain di sini
    addDataPatientToTable(params->table, params->operatedData);
    gtk_widget_show_all(params->table);
    char logMessage[100];
    sprintf(logMessage, "Search query: %s", mutableText);
    Logger(1, logMessage);
    g_free(mutableText);
}


// Callback function for toolbar buttons add patient data
void addPatientData(GtkWidget* button, gpointer data) {
    AddPatientParams* params = (AddPatientParams*) data;
    
    // ubah tanggal lahir dari parameter ke string biasa
    char* tanggalLahir = strdup(gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->tanggalLahir)));
    int dateChecking = stringDateFormatVerify(tanggalLahir);

    char* noBPJS = strdup(gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->noBPJS)));
    int isNumber = isOnlyNumber(noBPJS);


    int isError = 0;
    // cek apakah nama kosong
    if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->namaLengkap)), "") == 0){
        isError = 1;
    } else if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->alamat)), "") == 0){
        isError = 2;
    } else if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->kota)), "") == 0){
        isError = 3;
    } else if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->tempatLahir)), "") == 0){
        isError = 4;
    } else if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->tanggalLahir)), "") == 0){
        isError = 5;
    } else if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->noBPJS)), "") == 0){
        isError = 6;
    } else if (dateChecking == 0){
        isError = 7;
    } else if (dateChecking == -1){
        isError = 8;
    } else if (isNumber == 0){
        isError = 9;
    }

    if (isError == 0){
        // Create the new patient
        Patient* newPatient = malloc(sizeof(Patient));
        strcpy(newPatient->namaLengkap, gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->namaLengkap)));
        strcpy(newPatient->alamat, gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->alamat)));
        strcpy(newPatient->kota, gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->kota)));
        strcpy(newPatient->tempatLahir, gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->tempatLahir)));
        newPatient->tanggalLahir = convertStringToDate(tanggalLahir);
        newPatient->umur = hitungUmur(newPatient->tanggalLahir);
        newPatient->noBPJS = atoi(gtk_entry_get_text(GTK_ENTRY(params->newPatientFormPointer->noBPJS)));
        newPatient->history = NULL; 
        newPatient->next = NULL;
        strcpy(newPatient->idPasien, "0");

        // Add the new patient to the list
        addPatient(params->patientParams->allPatientData, newPatient);

        Patient** tempData = malloc(sizeof(Patient*));
        *tempData = NULL; // Initialize the result pointer to NULL



        copyPatient(*params->patientParams->allPatientData, tempData);

        freePatientList(*params->patientParams->operatedData);
        *params->patientParams->operatedData = *tempData;

        // Update the table
        addDataPatientToTable(params->patientParams->table, params->patientParams->operatedData);

        // Show the updated table
        gtk_widget_show_all(params->patientParams->table);
        
        // tutup jendela setelah data berhasil ditambahkan
        gtk_widget_destroy(params->window);

    } else {
        char* pesanError;
        switch (isError)
        {
        case 1:
            pesanError = "Nama Lengkap tidak boleh kosong";
            break;
        case 2:
            pesanError = "Alamat tidak boleh kosong";
            break;
        case 3:
            pesanError = "Kota tidak boleh kosong";
            break;
        case 4:
            pesanError = "Tempat Lahir tidak boleh kosong";
            break;
        case 5:
            pesanError = "Tanggal Lahir tidak boleh kosong";
            break;
        case 6:
            pesanError = "Nomor BPJS tidak boleh kosong";
            break;
        case 7:
            pesanError = "Format Tanggal Lahir tidak valid, gunakan format 'DD MMM YYYY' (Contoh: 15 Mei 2024)";
            break;
        case 8:
            pesanError = "Tanggal Lahir tidak valid, pastikan memasukkan tanggal yang benar";
            break;
        case 9:
            pesanError = "Nomor BPJS harus berupa angka";
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

void addDataPatientButtonHandler(GtkWidget* button, gpointer data)
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
    GtkWidget* namaLabel = gtk_label_new("Nama Lengkap:");
    GtkWidget* namaEntry = gtk_entry_new();
    GtkWidget* alamatLabel = gtk_label_new("Alamat:");
    GtkWidget* alamatEntry = gtk_entry_new();
    GtkWidget* kotaLabel = gtk_label_new("Kota:");
    GtkWidget* kotaEntry = gtk_entry_new();
    GtkWidget* kotaKelahiranLabel = gtk_label_new("Tempat Lahir:");
    GtkWidget* kotaKelahiranEntry = gtk_entry_new();
    GtkWidget* tanggalLahirLabel = gtk_label_new("Tanggal Lahir: (Contoh : 15 Mei 2024)");
    GtkWidget* tanggalLahirEntry = gtk_entry_new();
    GtkWidget* noBPJSLabel = gtk_label_new("Nomor BPJS:");
    GtkWidget* noBPJSEntry = gtk_entry_new();

    // Styling label
    gtk_widget_set_margin_top(namaLabel, 20);

    // Create the add button
    GtkWidget* addButton = gtk_button_new_with_label("Add Data");
    gtk_widget_set_margin_bottom(addButton, 20);

    GtkStyleContext *context = gtk_widget_get_style_context(addButton);
    gtk_style_context_add_class(context, "add-data-button-dialog");

    // Create the parameter for the add button
    NewPatientFormPointer* newPatientFormPointer = malloc(sizeof(NewPatientFormPointer));
    newPatientFormPointer->namaLengkap = namaEntry;
    newPatientFormPointer->alamat = alamatEntry;
    newPatientFormPointer->kota = kotaEntry;
    newPatientFormPointer->tempatLahir = kotaKelahiranEntry;
    newPatientFormPointer->tanggalLahir = tanggalLahirEntry;
    newPatientFormPointer->noBPJS = noBPJSEntry;

    // Create the parameter for the add button
    AddPatientParams* addParams = malloc(sizeof(AddPatientParams));
    addParams->patientParams = params;
    addParams->window = window;
    addParams->newPatientFormPointer = newPatientFormPointer;

    g_signal_connect(addButton, "clicked", G_CALLBACK(addPatientData), addParams);


    // Add the input fields and button to the main container
    gtk_box_pack_start(GTK_BOX(mainBox), namaLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), namaEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), alamatLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), alamatEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaKelahiranLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaKelahiranEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), tanggalLahirLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), tanggalLahirEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), noBPJSLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), noBPJSEntry, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(mainBox), addButton, FALSE, FALSE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);
}

// Callback function for toolbar delete patient data
void deletePatientData(GtkWidget* button, gpointer data) {
    PatientParams* params = (PatientParams*) data;
    // printf("Delete data pasien\n");

    // cari berapa banyak data yang dicentang
    Patient* currentPatient = *params->operatedData;
    // Assuming 'params' is a structure that contains the GTK grid 'table'
    // and 'currentPatient' is the head of a linked list of patients
    int row = 0; // Initialize row index to 0
    int count = 0;

    GtkWidget* checkbox;
    
    while (currentPatient != NULL) {
        checkbox = gtk_grid_get_child_at(GTK_GRID(params->table), 9, row + 1);
        // Check if checkbox is not NULL and is a GtkToggleButton
        if (checkbox != NULL && GTK_IS_TOGGLE_BUTTON(checkbox)) {
            if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox))) {
                // Checkbox is checked, process the patient data here
                // For example, you could print the patient's name or ID
                // printf("Patient at row %d is selected.\n", row + 1);
                count++;
            }
        }
        row++; // Move to the next row for the next patient
        currentPatient = currentPatient->next; // Move to the next patient in the list
    }

    
    if (count == 0) {
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
            // Pastikan params dan params->operatedData valid
            if (params == NULL || params->operatedData == NULL || params->allPatientData == NULL) {
                fprintf(stderr, "Invalid parameters\n");
                return; // Keluar dari fungsi jika parameter tidak valid
            }
            
            currentPatient = *params->operatedData;
            row = 0;
            int deleted = 0;
            while (currentPatient != NULL) {
                // printf("Row: %d\n", row);
                checkbox = gtk_grid_get_child_at(GTK_GRID(params->table), 9, row + 1);
                if (checkbox != NULL && GTK_IS_TOGGLE_BUTTON(checkbox)) {
                    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox))) {
                        // printf("Patient at row %d is selected.\n", row + 1);
                        deletePatient(params->allPatientData, currentPatient->idPasien);
                        deleted++;
                    }
                }
                row++;
                currentPatient = currentPatient->next;
            }
            
            // Pastikan copyPatient dan addDataPatientToTable mengelola memori dan pointer dengan benar
            Patient** tempData = malloc(sizeof(Patient*));
            *tempData = NULL; // Initialize the result pointer to NULL
            copyPatient(*params->allPatientData, tempData);
            freePatientList(*params->operatedData);
            *params->operatedData = *tempData;
        
            addDataPatientToTable(params->table, params->operatedData);
            gtk_widget_show_all(params->table);
            
            char message[100];
            sprintf(message, "Berhasil menghapus %d data pasien", deleted);
            GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }

    }


}


// Function to edit patient data

void saveEditPatientData(GtkWidget* button, gpointer data) {
    // Get the patient list
    EditPatientFormPointer* params = (EditPatientFormPointer*) data;

    // ubah tanggal lahir dari parameter ke string biasa
    char* tanggalLahir = strdup(gtk_entry_get_text(GTK_ENTRY(params->tanggalLahir)));
    int dateChecking = stringDateFormatVerify(tanggalLahir);

    char* noBPJS = strdup(gtk_entry_get_text(GTK_ENTRY(params->noBPJS)));
    int isNumber = isOnlyNumber(noBPJS);

    int isError = 0;
    // cek apakah nama kosong
    if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->namaLengkap)), "") == 0){
        isError = 1;
    } else if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->alamat)), "") == 0){
        isError = 2;
    } else if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->kota)), "") == 0){
        isError = 3;
    } else if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->tempatLahir)), "") == 0){
        isError = 4;
    } else if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->tanggalLahir)), "") == 0){
        isError = 5;
    } else if(strcmp(gtk_entry_get_text(GTK_ENTRY(params->noBPJS)), "") == 0){
        isError = 6;
    } else if (dateChecking == 0){
        isError = 7;
    } else if (dateChecking == -1){
        isError = 8;
    } else if (isNumber == 0){
        isError = 9;
    }


    if (isError == 0){
        // change the patient data
        strcpy(params->patient->namaLengkap, gtk_entry_get_text(GTK_ENTRY(params->namaLengkap)));
        strcpy(params->patient->alamat, gtk_entry_get_text(GTK_ENTRY(params->alamat)));
        strcpy(params->patient->kota, gtk_entry_get_text(GTK_ENTRY(params->kota)));
        strcpy(params->patient->tempatLahir, gtk_entry_get_text(GTK_ENTRY(params->tempatLahir)));
        params->patient->tanggalLahir = convertStringToDate(tanggalLahir);
        params->patient->umur = hitungUmur(params->patient->tanggalLahir);
        params->patient->noBPJS = atoi(gtk_entry_get_text(GTK_ENTRY(params->noBPJS)));

        // Update the table
        // Pastikan copyPatient dan addDataPatientToTable mengelola memori dan pointer dengan benar
        Patient** tempData = malloc(sizeof(Patient*));
        *tempData = NULL; // Initialize the result pointer to NULL
        copyPatient(*params->allPatientData, tempData);
        freePatientList(*params->operatedData);
        *params->operatedData = *tempData;

        addDataPatientToTable(params->table, params->operatedData);
        gtk_widget_show_all(params->table);

        // tuttp window
        gtk_widget_destroy(params->window);
    } else {
        char* pesanError;
        switch (isError)
        {
        case 1:
            pesanError = "Nama Lengkap tidak boleh kosong";
            break;
        case 2:
            pesanError = "Alamat tidak boleh kosong";
            break;
        case 3:
            pesanError = "Kota tidak boleh kosong";
            break;
        case 4:
            pesanError = "Tempat Lahir tidak boleh kosong";
            break;
        case 5:
            pesanError = "Tanggal Lahir tidak boleh kosong";
            break;
        case 6:
            pesanError = "Nomor BPJS tidak boleh kosong";
            break;
        case 7:
            pesanError = "Format Tanggal Lahir tidak valid, gunakan format 'DD MMM YYYY' (Contoh: 15 Mei 2024)";
            break;
        case 8:
            pesanError = "Tanggal Lahir tidak valid, pastikan memasukkan tanggal yang benar";
            break;
        case 9:
            pesanError = "Nomor BPJS harus berupa angka";
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

void cancelEditAction(GtkWidget* button, gpointer data) {
    // Get the patient list
    GtkWidget* params = (GtkWidget*) data;

    // tutup jendela editor
    gtk_widget_destroy(params);
}

void patientDataEditor(Patient** allPatientData, Patient** operatedData, GtkWidget* table , char idPasien[])
{   
    // cari data pasien yang akan diedit
    Patient* currentPatient = *allPatientData;
    while (currentPatient != NULL) {
        if (strcmp(currentPatient->idPasien, idPasien) == 0) {
            break;
        }
        currentPatient = currentPatient->next;
    }

    // Create the new window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Edit Patient Data");
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
    GtkWidget* tanggalLahirLabel = gtk_label_new("Tanggal Lahir: (Contoh : 15 Mei 2024)");
    GtkWidget* tanggalLahirEntry = gtk_entry_new();
    GtkWidget* noBPJSLabel = gtk_label_new("Nomor BPJS:");
    GtkWidget* noBPJSEntry = gtk_entry_new();

    // memasukkan data sementara ke dalam form
    gtk_entry_set_text(GTK_ENTRY(namaEntry), currentPatient->namaLengkap);
    gtk_entry_set_text(GTK_ENTRY(alamatEntry), currentPatient->alamat);
    gtk_entry_set_text(GTK_ENTRY(kotaEntry), currentPatient->kota);
    gtk_entry_set_text(GTK_ENTRY(kotaKelahiranEntry), currentPatient->tempatLahir);
    char tanggalLahir_text[20];
    convertDateToString(currentPatient->tanggalLahir, tanggalLahir_text);
    gtk_entry_set_text(GTK_ENTRY(tanggalLahirEntry), tanggalLahir_text);
    char noBPJS_text[20];
    sprintf(noBPJS_text, "%d", currentPatient->noBPJS);
    gtk_entry_set_text(GTK_ENTRY(noBPJSEntry), noBPJS_text);


    // Styling label
    gtk_widget_set_margin_top(namaLabel, 20);

    // Create the add button
    GtkWidget* confirmButton = gtk_button_new_with_label("Save");
    GtkWidget* cancelButton = gtk_button_new_with_label("Cancel");


    // Create the parameter for the add button
    EditPatientFormPointer* editPatientFormPointer = malloc(sizeof(EditPatientFormPointer));
    editPatientFormPointer->namaLengkap = namaEntry;
    editPatientFormPointer->alamat = alamatEntry;
    editPatientFormPointer->kota = kotaEntry;
    editPatientFormPointer->tempatLahir = kotaKelahiranEntry;
    editPatientFormPointer->tanggalLahir = tanggalLahirEntry;
    editPatientFormPointer->noBPJS = noBPJSEntry;
    editPatientFormPointer->patient = currentPatient;
    editPatientFormPointer->window = window;
    editPatientFormPointer->table = table;
    editPatientFormPointer->operatedData = operatedData;
    editPatientFormPointer->allPatientData = allPatientData;

    g_signal_connect(confirmButton, "clicked", G_CALLBACK(saveEditPatientData), editPatientFormPointer);

    // Set button size
    gtk_widget_set_size_request(confirmButton, 100, 30);
    gtk_widget_set_size_request(cancelButton, 100, 30);

    // Create a horizontal box to hold the buttons
    GtkWidget* buttonBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(buttonBox), TRUE);
    gtk_box_pack_start(GTK_BOX(buttonBox), confirmButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(buttonBox), cancelButton, TRUE, TRUE, 0);

    // menambahkan margin
    gtk_widget_set_margin_bottom(buttonBox, 20);
    gtk_widget_set_margin_top(buttonBox, 20);
    gtk_widget_set_margin_start(buttonBox, 20);
    gtk_widget_set_margin_end(buttonBox, 20);


    // Add the input fields and button to the main container
    gtk_box_pack_start(GTK_BOX(mainBox), namaLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), namaEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), alamatLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), alamatEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaKelahiranLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), kotaKelahiranEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), tanggalLahirLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), tanggalLahirEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), noBPJSLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), noBPJSEntry, FALSE, FALSE, 0);
    // Add the button box to the main container
    gtk_box_pack_start(GTK_BOX(mainBox), buttonBox, FALSE, FALSE, 0);

    // Show all the widgets
    gtk_widget_show_all(window);

    // tutup jendela editor saat tombol cancel ditekan
    g_signal_connect(cancelButton, "clicked", G_CALLBACK(cancelEditAction), window);
}

void editPatientData(GtkWidget* button, gpointer data) {

    // Get the patient list
    PatientParams* params = (PatientParams*) data;

    // Pastikan params dan params->operatedData valid
    if (params == NULL || params->operatedData == NULL || params->allPatientData == NULL) {
        fprintf(stderr, "Invalid parameters\n");
        return; // Keluar dari fungsi jika parameter tidak valid
    }
    
    Patient* currentPatient = *params->operatedData;
    int row = 0;
    int found = 0;
    GtkWidget* checkbox;
    while (currentPatient != NULL) {
        checkbox = gtk_grid_get_child_at(GTK_GRID(params->table), 9, row + 1);
        if (checkbox != NULL && GTK_IS_TOGGLE_BUTTON(checkbox)) {
            if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox))) {
                patientDataEditor(params->allPatientData, params->operatedData, params->table ,currentPatient->idPasien);
                found++;
                // aksi edit data pasien
            }
        }
        row++;
        currentPatient = currentPatient->next;
    }

    if(found == 0){
        GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Tidak ada data yang dipilih untuk diedit");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } 
}

// Function to build the patient data tab (Callable from activate.c)
void buildPatientDataTab(GtkWidget* userDataTab, Patient** operatedData, Patient** allPatientData) {
    Patient* patientList = *operatedData;
    // TOOLBAR
    // Create the toolbar
    GtkWidget* patientDataToolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(patientDataToolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(userDataTab), patientDataToolbar, FALSE, FALSE, 0);

    // Create the "Add Data" button
    GtkToolItem *addPatientDataButton = gtk_tool_button_new(NULL, "Add Data");
    GtkWidget *addPatientDataButtonWidget = gtk_bin_get_child(GTK_BIN(addPatientDataButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *addPatientContext = gtk_widget_get_style_context(addPatientDataButtonWidget);
    gtk_style_context_add_class(addPatientContext, "add-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(patientDataToolbar), addPatientDataButton, -1);

    // Create the "edit Data" button
    GtkToolItem *editPatientDataButton = gtk_tool_button_new(NULL, "Edit Data");
    GtkWidget *editPatientDataButtonWidget = gtk_bin_get_child(GTK_BIN(editPatientDataButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *editPatientContext = gtk_widget_get_style_context(editPatientDataButtonWidget);
    gtk_style_context_add_class(editPatientContext, "edit-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(patientDataToolbar), editPatientDataButton, -1);
    // g_signal_connect(addPatientDataButton, "clicked", G_CALLBACK(addDataPatientButtonHandler), operatedData);

    // Create the "delete Data" button
    GtkToolItem *deletePatientDataButton = gtk_tool_button_new(NULL, "Delete Data");
    GtkWidget *deletePatientDataButtonWidget = gtk_bin_get_child(GTK_BIN(deletePatientDataButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *deletePatientContext = gtk_widget_get_style_context(deletePatientDataButtonWidget);
    gtk_style_context_add_class(deletePatientContext, "delete-data-patient-button");
    gtk_toolbar_insert(GTK_TOOLBAR(patientDataToolbar), deletePatientDataButton, -1);
    

    // Set the button border
    gtk_container_set_border_width(GTK_CONTAINER(addPatientDataButton), 5);
    gtk_container_set_border_width(GTK_CONTAINER(editPatientDataButton), 5);
    gtk_container_set_border_width(GTK_CONTAINER(deletePatientDataButton), 5);

    // Create the search box
    GtkWidget* searchBox = gtk_search_entry_new();
    gtk_box_pack_start(GTK_BOX(userDataTab), searchBox, FALSE, FALSE, 0);

    // PATIENT DATA DISPLAY
    // Create the scrollable table
    GtkWidget* scrollable = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollable), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(userDataTab), scrollable, TRUE, TRUE, 0);

    // Create the table
    GtkWidget* table = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(scrollable), table);

    // buat seluruh isi table rata kiri kecuali kolom pertama



    // Adddata to the table
    addDataPatientToTable(table, operatedData);

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
    g_signal_connect(searchBox, "changed", G_CALLBACK(searchPatientDataOnChanged), PatientParameter);
    g_signal_connect(addPatientDataButton, "clicked", G_CALLBACK(addDataPatientButtonHandler), PatientParameter);
    g_signal_connect(deletePatientDataButton, "clicked", G_CALLBACK(deletePatientData), PatientParameter);
    g_signal_connect(editPatientDataButton, "clicked", G_CALLBACK(editPatientData), PatientParameter);

    // // print data pasien pertama
    // printf("Nama Pasien Pertama 1: %s\n", *operatedData->namaLengkap);
}