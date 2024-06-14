// Callback function for toolbar buttons
void on_toolbar_button_clicked(GtkWidget* button, gpointer data)
{
  // Handle toolbar button click events here
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

// Function to build the medical record tab (Callable from main.c)
void buildMedicalRecordTab(GtkWidget* medicalRecordsTab, Patient* patientList, Tindakan* allTindakanList) {
    // Creating Tabs for Medical Records
    // TOOLBAR
    // Create the toolbar
    GtkWidget* medicalRecordToolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(medicalRecordToolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(medicalRecordsTab), medicalRecordToolbar, FALSE, FALSE, 0);

    // Create the "Add Data" button
    GtkToolItem* addMedRecordButton = gtk_tool_button_new(NULL, "Add Data");
    gtk_toolbar_insert(GTK_TOOLBAR(medicalRecordToolbar), addMedRecordButton, -1);
    g_signal_connect(addMedRecordButton, "clicked", G_CALLBACK(on_toolbar_button_clicked), NULL);

    // Set the button border
    gtk_container_set_border_width(GTK_CONTAINER(addMedRecordButton), 5);

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
    gtk_widget_set_size_request(header4MedRec, 100, -1);
    gtk_widget_set_size_request(header5MedRec, 250, -1);

    // tambahkan margin kiri pada tabel
    gtk_widget_set_margin_start(header1MedRec, 10);

    // // Add dummy data to the table
    // addMedicalRecordToTable(tableMedRec);

    // Input data rekam medis dari patientList
    addHistoryToTable(tableMedRec, patientList, allTindakanList);

    // Set table properties
    gtk_widget_set_hexpand(tableMedRec, TRUE);
    gtk_widget_set_halign(tableMedRec, GTK_ALIGN_FILL);
    gtk_grid_set_row_spacing(GTK_GRID(tableMedRec), 7);
    gtk_grid_set_column_spacing(GTK_GRID(tableMedRec), 15); 
}

