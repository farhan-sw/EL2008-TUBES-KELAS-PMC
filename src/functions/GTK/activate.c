#include "./load_css.c"
#include "./patient_data_tab.c"
#include "./medical_records_tab.c"
#include "./medical_checkup_tab.c"
#include "./finance_tab.c"
#include "./about_tab.c"

static void activate(){
    Logger(1, "Building Main Window");
    // MAIN WINDOW INITIALIZATION
    // Create the main window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Healthcare Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    Logger(1, "Setting up Main Window");

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
    Logger(1, "Initializing Tabs");
    GtkWidget* userDataTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), userDataTab, gtk_label_new("Patient Data"));

    // Create the Medical Check-Up tab
    GtkWidget* medicalCheckUpTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), medicalCheckUpTab, gtk_label_new("Medical Check-Up"));

    // Create the Medical Records tab
    GtkWidget* medicalRecordsTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), medicalRecordsTab, gtk_label_new("Medical Records"));

    // Create the financial tab
    GtkWidget* financeTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), financeTab, gtk_label_new("Finance"));

    // Create the About Tab
    GtkWidget* aboutTab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), aboutTab, gtk_label_new("About"));
    if(userDataTab == NULL || medicalCheckUpTab == NULL || medicalRecordsTab == NULL || financeTab == NULL || aboutTab == NULL){
        Logger(3, "Failed to initialize tabs");
    } else {
        Logger(2, "Tabs initialized successfully");
    }

    // Build the Patient Data tab, implemented in patient_data_tab.c
    buildPatientDataTab(userDataTab);

    // Build the Medical Records tab, implemented in medical_records_tab.c
    buildMedicalRecordTab(medicalRecordsTab);

    // Show all widgets
    gtk_widget_show_all(window);
}