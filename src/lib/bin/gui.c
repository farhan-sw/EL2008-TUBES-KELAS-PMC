/*

Buatkan program untuk membuat GUI dari data linked list yang telah dibuat sebelumnya. Program harus memiliki fitur sebagai berikut:
1. Menampilkan data pasien yang ada
2. Menambahkan data pasien baru
3. Menghapus data pasien
4. Menampilkan data riwayat penyakit pasien
5. Menambahkan data riwayat penyakit pasien
6. Menghapus data riwayat penyakit pasien
7. Menampilkan data pasien yang memiliki riwayat penyakit tertentu

*/

#include <gtk/gtk.h>

// Function to display the data of patients
void displayPatients()
{
    // TODO: Implement the logic to display the data of patients
}

// Function to add a new patient
void addPatient()
{
    // TODO: Implement the logic to add a new patient
}

// Function to remove a patient
void removePatient()
{
    // TODO: Implement the logic to remove a patient
}

// Function to display the medical history of a patient
void displayMedicalHistory()
{
    // TODO: Implement the logic to display the medical history of a patient
}

// Function to add a medical history to a patient
void addMedicalHistory()
{
    // TODO: Implement the logic to add a medical history to a patient
}

// Function to remove a medical history from a patient
void removeMedicalHistory()
{
    // TODO: Implement the logic to remove a medical history from a patient
}

// Function to display patients with a specific medical history
void displayPatientsWithMedicalHistory()
{
    // TODO: Implement the logic to display patients with a specific medical history
}

int main(int argc, char *argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Patient Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create buttons for each feature
    GtkWidget *btnDisplayPatients = gtk_button_new_with_label("Display Patients");
    GtkWidget *btnAddPatient = gtk_button_new_with_label("Add Patient");
    GtkWidget *btnRemovePatient = gtk_button_new_with_label("Remove Patient");
    GtkWidget *btnDisplayMedicalHistory = gtk_button_new_with_label("Display Medical History");
    GtkWidget *btnAddMedicalHistory = gtk_button_new_with_label("Add Medical History");
    GtkWidget *btnRemoveMedicalHistory = gtk_button_new_with_label("Remove Medical History");
    GtkWidget *btnDisplayPatientsWithMedicalHistory = gtk_button_new_with_label("Display Patients with Medical History");

    // Add the buttons to the vertical box container
    gtk_box_pack_start(GTK_BOX(vbox), btnDisplayPatients, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btnAddPatient, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btnRemovePatient, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btnDisplayMedicalHistory, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btnAddMedicalHistory, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btnRemoveMedicalHistory, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btnDisplayPatientsWithMedicalHistory, FALSE, FALSE, 0);

    // Connect button signals to their respective functions
    g_signal_connect(btnDisplayPatients, "clicked", G_CALLBACK(displayPatients), NULL);
    g_signal_connect(btnAddPatient, "clicked", G_CALLBACK(addPatient), NULL);
    g_signal_connect(btnRemovePatient, "clicked", G_CALLBACK(removePatient), NULL);
    g_signal_connect(btnDisplayMedicalHistory, "clicked", G_CALLBACK(displayMedicalHistory), NULL);
    g_signal_connect(btnAddMedicalHistory, "clicked", G_CALLBACK(addMedicalHistory), NULL);
    g_signal_connect(btnRemoveMedicalHistory, "clicked", G_CALLBACK(removeMedicalHistory), NULL);
    g_signal_connect(btnDisplayPatientsWithMedicalHistory, "clicked", G_CALLBACK(displayPatientsWithMedicalHistory), NULL);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}