// // Callback function for toolbar buttons
// void on_toolbar_button_clicked(GtkWidget* button, gpointer data) {
//     // Handle toolbar button click events here
// }

// void addHistoryToTable(GtkWidget* table, MedicalCheckup* medicalCheckupList) {
//     int row = 1; // Start from the first row after the header
//     MedicalCheckup* current = medicalCheckupList;

//     while (current != NULL) {
//         GtkWidget* labelNo = gtk_label_new(g_strdup_printf("%d", row));
//         GtkWidget* labelTanggal = gtk_label_new(g_strdup_printf("%02d-%02d-%04d", current->kontrol.day, current->kontrol.month, current->kontrol.year));
//         GtkWidget* labelIdPasien = gtk_label_new(current->idPasien);
//         GtkWidget* labelDiagnosis = gtk_label_new(current->diagnosis);
//         GtkWidget* labelTindakan = gtk_label_new(current->tindakan);
//         GtkWidget* labelKontrol = gtk_label_new(g_strdup_printf("%02d-%02d-%04d", current->kontrol.day, current->kontrol.month, current->kontrol.year));

//         gtk_grid_attach(GTK_GRID(table), labelNo, 0, row, 1, 1);
//         gtk_grid_attach(GTK_GRID(table), labelTanggal, 1, row, 1, 1);
//         gtk_grid_attach(GTK_GRID(table), labelIdPasien, 2, row, 1, 1);
//         gtk_grid_attach(GTK_GRID(table), labelDiagnosis, 3, row, 1, 1);
//         gtk_grid_attach(GTK_GRID(table), labelTindakan, 4, row, 1, 1);
//         gtk_grid_attach(GTK_GRID(table), labelKontrol, 5, row, 1, 1);

//         row++;
//         current = current->next;
//     }
// }

// void buildMedicalCheckUpTab(GtkWidget* medicalCheckUpTab, MedicalCheckup* operatedData, MedicalCheckup* allPatientData, MedicalCheckup* tindakanList) {
//     // Creating Tabs for Medical Check-Up
//     // TOOLBAR
//     // Create the toolbar
//     GtkWidget* medicalCheckupToolbar = gtk_toolbar_new();
//     gtk_toolbar_set_style(GTK_TOOLBAR(medicalCheckupToolbar), GTK_TOOLBAR_ICONS);
//     gtk_box_pack_start(GTK_BOX(medicalCheckUpTab), medicalCheckupToolbar, FALSE, FALSE, 0);

//     // Create the "Add Data" button
//     GtkToolItem* addMedCheckupButton = gtk_tool_button_new(NULL, "Add Data");
//     gtk_toolbar_insert(GTK_TOOLBAR(medicalCheckupToolbar), addMedCheckupButton, -1);
//     g_signal_connect(addMedCheckupButton, "clicked", G_CALLBACK(on_toolbar_button_clicked), NULL);

//     // Set the button border
//     gtk_container_set_border_width(GTK_CONTAINER(addMedCheckupButton), 5);

//     // Create the search box
//     GtkWidget* searchMedCheckupBox = gtk_search_entry_new();
//     gtk_box_pack_start(GTK_BOX(medicalCheckUpTab), searchMedCheckupBox, FALSE, FALSE, 0);

//     // ==================================================================================================

//     // MEDICAL CHECK-UP DATA DISPLAY
//     // Create the scrollable table
//     GtkWidget* scrollableMedCheckup = gtk_scrolled_window_new(NULL, NULL);
//     gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollableMedCheckup), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
//     gtk_box_pack_start(GTK_BOX(medicalCheckUpTab), scrollableMedCheckup, TRUE, TRUE, 0);

//     // Create the table
//     GtkWidget* tableMedCheckup = gtk_grid_new();
//     gtk_container_add(GTK_CONTAINER(scrollableMedCheckup), tableMedCheckup);

//     // Add table headers
//     GtkWidget* header1MedCheckup = gtk_label_new("No");
//     GtkWidget* header2MedCheckup = gtk_label_new("Tanggal");
//     GtkWidget* header3MedCheckup = gtk_label_new("ID Pasien");
//     GtkWidget* header4MedCheckup = gtk_label_new("Diagnosis");
//     GtkWidget* header5MedCheckup = gtk_label_new("Tindakan");
//     GtkWidget* header6MedCheckup = gtk_label_new("Kontrol");

//     gtk_grid_attach(GTK_GRID(tableMedCheckup), header1MedCheckup, 0, 0, 1, 1);
//     gtk_grid_attach(GTK_GRID(tableMedCheckup), header2MedCheckup, 1, 0, 1, 1);
//     gtk_grid_attach(GTK_GRID(tableMedCheckup), header3MedCheckup, 2, 0, 1, 1);
//     gtk_grid_attach(GTK_GRID(tableMedCheckup), header4MedCheckup, 3, 0, 1, 1);
//     gtk_grid_attach(GTK_GRID(tableMedCheckup), header5MedCheckup, 4, 0, 1, 1);
//     gtk_grid_attach(GTK_GRID(tableMedCheckup), header6MedCheckup, 5, 0, 1, 1);

//     // Set the width of headers
//     gtk_widget_set_size_request(header4MedCheckup, 100, -1);
//     gtk_widget_set_size_request(header5MedCheckup, 250, -1);

//     // Add margin left to the table
//     gtk_widget_set_margin_start(header1MedCheckup, 10);

//     // Input data rekam medis from medicalCheckupList
//     addHistoryToTable(tableMedCheckup, operatedData);

//     // Set table properties
//     gtk_widget_set_hexpand(tableMedCheckup, TRUE);
//     gtk_widget_set_halign(tableMedCheckup, GTK_ALIGN_FILL);
//     gtk_grid_set_row_spacing(GTK_GRID(tableMedCheckup), 7);
//     gtk_grid_set_column_spacing(GTK_GRID(tableMedCheckup), 15); 
// }