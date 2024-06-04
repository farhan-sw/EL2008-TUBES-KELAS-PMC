/*

Buatkan sebuah program linked list secara simpel dengan ketentuan sebagai berikut:
Node A
Node B
Node parent (indikator huruf besar A, B, C..) menyimpan data pasien, seperti nama, umur, dan jenis kelamin tanggal terakhir kontrol
dan next tanggal kontrol dan node menuju data riwayat penyakit pasien dan pointer ke node pasien selanjutnya
NOde A
 - Node A. 1
 - Node A. 2
Node B
- Node B. 1
- Node B. 2
Di anat parrent, seperti A. 1, A. 2 .. B. 1, B. 2, dst akan menyimpan data riwayat penyakit pasien yaitu deskripsi penyakit, obat yang diberikan, dan tanggal kontrol selanjutnya, harga obat, dan biaya kunjungan pada saat itu, kemudian pointer ke historis dari pasien selanjutnya
tersebut. Sehingga jika pasien melakukan konsul, akan menambah node di historis pasien tersebut.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>


// Define the structure for the patient node
typedef struct Patient {
    char name[50];
    int age;
    char gender;
    char lastControlDate[20];
    struct History *history;
    struct Patient *next;
} Patient;

// Define the structure for the history node
typedef struct History {
    char disease[50];
    char medicine[50];
    char nextControlDate[20];
    float medicinePrice;
    float visitCost;
    struct History *next;
} History;


// Dummy data for patients
const char* patients[][8] = {
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  {"John Doe", "Jl. Ganesha No.696966969696969", "Kota Bandung","Tanah Grogol", "30 Februari 1969", "69", "476947476947", "SCP-69"},
  
  // Add more dummy data here
};

const char* medRec[][7] = {
    {"1 Januari", "KX 12345", "Dehidrasi", "Pemasangan Infus", "4 Januari 2022", "Rp 265.000,00" },
    {"1 Januari", "KX 12345", "Dehidrasi", "Pemasangan Infus", "4 Januari 2022", "Rp 265.000,00" },
    {"1 Januari", "KX 12345", "Dehidrasi", "Pemasangan Infus", "4 Januari 2022", "Rp 265.000,00" },
};

// Callback function for toolbar buttons
void on_toolbar_button_clicked(GtkWidget* button, gpointer data)
{
  // Handle toolbar button click events here
}


// Function to create a new patient node
Patient* createPatient(char name[], int age, char gender, char lastControlDate[]) {
    Patient *newPatient = (Patient*) malloc(sizeof(Patient));
    strcpy(newPatient->name, name);
    newPatient->age = age;
    newPatient->gender = gender;
    strcpy(newPatient->lastControlDate, lastControlDate);
    newPatient->history = NULL;
    newPatient->next = NULL;
    return newPatient;
}

// Function to create a new history node
History* createHistory(char disease[], char medicine[], char nextControlDate[], float medicinePrice, float visitCost) {
    History *newHistory = (History*) malloc(sizeof(History));
    strcpy(newHistory->disease, disease);
    strcpy(newHistory->medicine, medicine);
    strcpy(newHistory->nextControlDate, nextControlDate);
    newHistory->medicinePrice = medicinePrice;
    newHistory->visitCost = visitCost;
    newHistory->next = NULL;
    return newHistory;
}

// Function to print the linked list
void printLinkedList(Patient *head) {
    Patient *currentPatient = head;
    while (currentPatient != NULL) {
        printf("Patient Name: %s\n", currentPatient->name);
        printf("Age: %d\n", currentPatient->age);
        printf("Gender: %c\n", currentPatient->gender);
        printf("Last Control Date: %s\n", currentPatient->lastControlDate);
        printf("History:\n");
        History *currentHistory = currentPatient->history;
        while (currentHistory != NULL) {
            printf("- Disease: %s\n", currentHistory->disease);
            printf("  Medicine: %s\n", currentHistory->medicine);
            printf("  Next Control Date: %s\n", currentHistory->nextControlDate);
            printf("  Medicine Price: %.2f\n", currentHistory->medicinePrice);
            printf("  Visit Cost: %.2f\n", currentHistory->visitCost);
            currentHistory = currentHistory->next;
        }
        printf("\n");
        currentPatient = currentPatient->next;
    }
}

// GTK 3 Functions

void addDataPatientToTable(GtkWidget* table) {
    for (int i = 0; i < sizeof(patients) / sizeof(patients[0]); i++) {
        char label1_text[10];
        sprintf(label1_text, "%d", i+1);
        GtkWidget* label1 = gtk_label_new(label1_text);
        GtkWidget* label2 = gtk_label_new(patients[i][0]);
        GtkWidget* label3 = gtk_label_new(patients[i][1]);
        GtkWidget* label4 = gtk_label_new(patients[i][2]);
        GtkWidget* label5 = gtk_label_new(patients[i][3]);
        GtkWidget* label6 = gtk_label_new(patients[i][4]);
        GtkWidget* label7 = gtk_label_new(patients[i][5]);
        GtkWidget* label8 = gtk_label_new(patients[i][6]);
        GtkWidget* label9 = gtk_label_new(patients[i][7]);
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
    }
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

static void activate(){

    // ==================================================================================================

    // MAIN WINDOW INITIALIZATION
    // Create the main window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Healthcare Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // set app icon
    GdkPixbuf *icon = gdk_pixbuf_new_from_file("../icon/icon.png", NULL);
    gtk_window_set_icon(GTK_WINDOW(window), icon);

    // ==================================================================================================

    // TABS INITIALIZATION
    // Create Section Tab With Notebook
    GtkWidget* notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);

    // Create the User Data tab
    GtkWidget* userDataTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), userDataTab, gtk_label_new("Patient Data"));

    // Create the Medical Records tab
    GtkWidget* medicalRecordsTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), medicalRecordsTab, gtk_label_new("Medical Records"));

    // Create the pricing tab
    GtkWidget* pricingManagementTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), pricingManagementTab, gtk_label_new("Pricing Management"));

    // Create the About Tab
    GtkWidget* aboutTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), aboutTab, gtk_label_new("About"));

    // ==================================================================================================
    
    // ######## PATIENT DATA TAB ########
    // TOOLBAR
    // Create the toolbar
    GtkWidget* patientDataToolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(patientDataToolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(userDataTab), patientDataToolbar, FALSE, FALSE, 0);

    // Create the "Add Data" button
    GtkToolItem* addButton = gtk_tool_button_new(NULL, "Add Data");
    gtk_toolbar_insert(GTK_TOOLBAR(patientDataToolbar), addButton, -1);
    g_signal_connect(addButton, "clicked", G_CALLBACK(on_toolbar_button_clicked), NULL);

    // Set the button border
    gtk_container_set_border_width(GTK_CONTAINER(addButton), 5);

    // Create the search box
    GtkWidget* searchBox = gtk_search_entry_new();
    gtk_box_pack_start(GTK_BOX(userDataTab), searchBox, FALSE, FALSE, 0);

    // ==================================================================================================

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
    addDataPatientToTable(table);

    // Set table properties
    gtk_widget_set_hexpand(table, TRUE);
    gtk_widget_set_halign(table, GTK_ALIGN_FILL);
    gtk_grid_set_row_spacing(GTK_GRID(table), 7);
    gtk_grid_set_column_spacing(GTK_GRID(table), 15); 

    // ==================================================================================================

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

    // Add dummy data to the table
    addMedicalRecordToTable(tableMedRec);

    // Set table properties
    gtk_widget_set_hexpand(tableMedRec, TRUE);
    gtk_widget_set_halign(tableMedRec, GTK_ALIGN_FILL);
    gtk_grid_set_row_spacing(GTK_GRID(tableMedRec), 7);
    gtk_grid_set_column_spacing(GTK_GRID(tableMedRec), 15); 
    


    // Show all widgets
    gtk_widget_show_all(window);
}



int main(int argc, char **argv) {
    // Create the parent nodes
    Patient *nodeA = createPatient("A", 30, 'M', "2021-10-01");
    Patient *nodeB = createPatient("B", 25, 'F', "2021-09-15");

    // Create the child nodes for node A
    History *nodeA1 = createHistory("Flu", "Paracetamol", "2021-10-05", 10.0, 50.0);
    History *nodeA2 = createHistory("Headache", "Aspirin", "2021-11-02", 8.0, 40.0);

    // Create the child nodes for node B
    History *nodeB1 = createHistory("Cough", "Cough Syrup", "2021-09-20", 15.0, 60.0);
    History *nodeB2 = createHistory("Fever", "Ibuprofen", "2021-10-10", 12.0, 55.0);

    // Connect the child nodes to the parent nodes
    nodeA->history = nodeA1;
    nodeA1->next = nodeA2;

    nodeB->history = nodeB1;
    nodeB1->next = nodeB2;

    // Connect the parent nodes
    nodeA->next = nodeB;
    nodeB->next = NULL;

    // Print the linked list
    printLinkedList(nodeA);


    // GTK3 RUNNER

    // Initialize GTK
    gtk_init(&argc, &argv);
    // Initialize main window
    activate();
    // Start the GTK main loop
    gtk_main();
    

    return 0;
}


