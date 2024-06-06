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
#include <time.h>
#include "./functions/logger.c"

char session[50];

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

#include "./functions/GTK/load_css.c"
#include "./functions/GTK/patient_data_tab.c"
#include "./functions/GTK/medical_records_tab.c"
#include "./functions/GTK/medical_checkup_tab.c"
#include "./functions/GTK/finance_tab.c"
#include "./functions/GTK/about_tab.c"

static void activate(){

    // ==================================================================================================

    // MAIN WINDOW INITIALIZATION
    // Create the main window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Healthcare Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // set app icon
    GdkPixbuf *icon = gdk_pixbuf_new_from_file("../resources/icons/icon.png", NULL);
    gtk_window_set_icon(GTK_WINDOW(window), icon);

    // Muat CSS
    load_css();

    // TABS INITIALIZATION
    // Create Section Tab With Notebook
    GtkWidget* notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);

    // Create the User Data tab
    GtkWidget* userDataTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), userDataTab, gtk_label_new("Patient Data"));

    // Create the Medical Check-Up tab
    GtkWidget* medicalCheckUpTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), medicalCheckUpTab, gtk_label_new("Medical Check-Up"));

    // Create the Medical Records tab
    GtkWidget* medicalRecordsTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), medicalRecordsTab, gtk_label_new("Medical Records"));

    // Create the pricing tab
    GtkWidget* financeTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), financeTab, gtk_label_new("Finance"));

    // Create the About Tab
    GtkWidget* aboutTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), aboutTab, gtk_label_new("About"));

    // Build the Patient Data tab, implemented in patient_data_tab.c
    buildPatientDataTab(userDataTab);

    // Build the Medical Records tab, implemented in medical_records_tab.c
    buildMedicalRecordTab(medicalRecordsTab);

    // Show all widgets
    gtk_widget_show_all(window);
}


int main(int argc, char **argv) {

    // Assign session berdasarkan waktu hingga milisecond
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    sprintf(session, "HealthAdminSessionStart_%d-%d-%d_%d-%d-%d-%ld", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ts.tv_nsec);
    printf("Session: %s\n", session);

    Logger(session,1, "Application started");
    

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
    // printLinkedList(nodeA);


    // GTK3 RUNNER

    // Initialize GTK
    gtk_init(&argc, &argv);
    // Initialize main window
    activate();
    // Start the GTK main loop
    gtk_main();
    

    return 0;
}


