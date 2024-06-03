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


// GTK4 Functions
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Health Admin Medika Karya");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800);
    gtk_window_present(GTK_WINDOW(window));

    // create menu tabs
    GtkWidget *notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // Membuat box vertikal untuk PatientTab
    GtkWidget *PatientTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Membuat toolbar horizontal
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_margin_top(toolbar, 10);    // tambahkan jeda 10 pixel di sisi atas

    // Membuat tombol "Tambah Data"
    GtkWidget *add_icon = gtk_image_new_from_icon_name("list-add-symbolic");
    GtkWidget *add_button = gtk_button_new();
    gtk_button_set_child(GTK_BUTTON(add_button), add_icon);
    gtk_widget_set_margin_start(add_button, 10);  // tambahkan jeda 10 pixel di sisi kiri
    gtk_widget_set_margin_end(add_button, 3);    // tambahkan jeda 10 pixel di sisi kanan
    gtk_box_append(GTK_BOX(toolbar), add_button);

    // Membuat tombol "Edit Data"
    GtkWidget *edit_icon = gtk_image_new_from_icon_name("document-edit-symbolic");
    GtkWidget *edit_button = gtk_button_new();
    gtk_button_set_child(GTK_BUTTON(edit_button), edit_icon);
    gtk_widget_set_margin_start(edit_button, 3);  // tambahkan jeda 10 pixel di sisi kiri
    gtk_widget_set_margin_end(edit_button, 3);    // tambahkan jeda 10 pixel di sisi kanan
    gtk_box_append(GTK_BOX(toolbar), edit_button);

    // Membuat tombol "Hapus Data"
    GtkWidget *delete_icon = gtk_image_new_from_icon_name("edit-delete-symbolic");
    GtkWidget *delete_button = gtk_button_new();
    gtk_button_set_child(GTK_BUTTON(delete_button), delete_icon);
    gtk_widget_set_margin_start(delete_button, 3);  // tambahkan jeda 10 pixel di sisi kiri
    gtk_widget_set_margin_end(delete_button, 3);    // tambahkan jeda 10 pixel di sisi kanan
    gtk_box_append(GTK_BOX(toolbar), delete_button);

    // Membuat kotak pencarian dan menambahkannya ke toolbar
    GtkWidget *search_entry = gtk_search_entry_new();
    gtk_widget_set_margin_start(search_entry, 10);  // tambahkan jeda 10 pixel di sisi kiri
    gtk_widget_set_margin_end(search_entry, 10);    // tambahkan jeda 10 pixel di sisi kanan
    gtk_box_append(GTK_BOX(toolbar), search_entry);

    gtk_box_append(GTK_BOX(PatientTab), toolbar);

    GtkWidget *HistoryTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *PriceTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *AboutTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), PatientTab, gtk_label_new("Patient Data"));
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), HistoryTab, gtk_label_new("Medical Record"));
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), PriceTab, gtk_label_new("Fee Management"));
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), AboutTab, gtk_label_new("About"));

    gtk_widget_set_visible(window, TRUE);
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

    // GTK4
    GtkApplication *app;
    int status;
    app = gtk_application_new("org.health.admin", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    

    return 0;
}


