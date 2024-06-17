#include   <gtk/gtk.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <time.h>
#include   "dataStructure.h"
#include   "search.h"
#include   "logger.h"
#include   "dataOperator.h"

#define ANALYSIS_LABEL_WIDTH 250


// Fungsi untuk menghitung laporan pendapatan bulanan, tahunan, dan jumlah pasien serta penyakit
void calculateReports(Patient** allPatients, Tindakan* allTindakanList, YearlyReport* yearlyReports, int* reportCount, int startYear, int endYear) {
    *reportCount = 0;

    for (int year = startYear; year <= endYear; year++) {
        YearlyReport* report = &yearlyReports[*reportCount];
        report->year = year;
        memset(report->monthlyIncome, 0, sizeof(report->monthlyIncome));
        memset(report->monthlyPatients, 0, sizeof(report->monthlyPatients));
        memset(report->monthlyDiseases, 0, sizeof(report->monthlyDiseases));
        report->diseaseCount = 0;

        Patient* currentPatient = *allPatients;
        while (currentPatient) {
            History* history = currentPatient->history;
            while (history) {
                if (history->tanggal.year == year) {
                    report->monthlyIncome[history->tanggal.month - 1] += history->biaya;
                    report->monthlyPatients[history->tanggal.month - 1]++;
                    
                    int diseaseIndex = -1;
                    for (int i = 0; i < report->diseaseCount; i++) {
                        if (strcmp(report->diseases[i], history->diagnosis) == 0) {
                            diseaseIndex = i;
                            break;
                        }
                    }
                    if (diseaseIndex == -1) {
                        diseaseIndex = report->diseaseCount;
                        strcpy(report->diseases[report->diseaseCount], history->diagnosis);
                        report->diseaseCount++;
                    }
                    report->monthlyDiseases[history->tanggal.month - 1][diseaseIndex]++;
                }
                history = history->next;
            }
            currentPatient = currentPatient->next;
        }
        (*reportCount)++;
    }
}

// Fungsi untuk menampilkan laporan dalam tabel GTK
void displayReportsInTable(GtkWidget* vbox, YearlyReport* yearlyReports, int reportCount) {
    for (int i = 0; i < reportCount; i++) {
        YearlyReport* report = &yearlyReports[i];

        // Header tahun
        char year_text[10];
        sprintf(year_text, "YEAR %d", report->year);
        GtkWidget* label_year = gtk_label_new(year_text);
        gtk_box_pack_start(GTK_BOX(vbox), label_year, FALSE, FALSE, 5);
        gtk_widget_set_halign(label_year, GTK_ALIGN_CENTER);

        // Beri CSS untuk header tahun
        GtkStyleContext *context = gtk_widget_get_style_context(label_year);
        gtk_style_context_add_class(context, "analysis-year-header");
        

        // Header bulan, pasien, penyakit
        GtkWidget* grid = gtk_grid_new();
        gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Month"), 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Patients"), 1, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Diseases"), 2, 0, 1, 1);
        gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 5);

        // Set header width height and alignment
        gtk_widget_set_size_request(gtk_grid_get_child_at(GTK_GRID(grid), 0, 0), ANALYSIS_LABEL_WIDTH, -1);
        gtk_widget_set_size_request(gtk_grid_get_child_at(GTK_GRID(grid), 1, 0), ANALYSIS_LABEL_WIDTH, -1);
        gtk_widget_set_size_request(gtk_grid_get_child_at(GTK_GRID(grid), 2, 0), ANALYSIS_LABEL_WIDTH, -1);

        // Isi data bulanan
        for (int j = 0; j < 12; j++) {
            char month_text[20];
            sprintf(month_text, "Month %d", j + 1);
            GtkWidget* label_month = gtk_label_new(month_text);
            gtk_grid_attach(GTK_GRID(grid), label_month, 0, j + 1, 1, 1);

            char patients_text[20];
            sprintf(patients_text, "%d", report->monthlyPatients[j]);
            GtkWidget* label_patients = gtk_label_new(patients_text);
            gtk_grid_attach(GTK_GRID(grid), label_patients, 1, j + 1, 1, 1);

            GtkWidget* diseases_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            for (int k = 0; k < report->diseaseCount; k++) {
                if (report->monthlyDiseases[j][k] > 0) {
                    char disease_text[50];
                    sprintf(disease_text, "%s: %d", report->diseases[k], report->monthlyDiseases[j][k]);
                    GtkWidget* label_disease = gtk_label_new(disease_text);
                    gtk_box_pack_start(GTK_BOX(diseases_box), label_disease, FALSE, FALSE, 2);
                }
            }
            gtk_grid_attach(GTK_GRID(grid), diseases_box, 2, j + 1, 1, 1);

            // Set data width height and alignment
            gtk_widget_set_size_request(label_month, ANALYSIS_LABEL_WIDTH, -1);
            gtk_widget_set_size_request(label_patients, ANALYSIS_LABEL_WIDTH, -1);
            gtk_widget_set_size_request(diseases_box, ANALYSIS_LABEL_WIDTH, -1);

        }

        // Header analisis pendapatan
        GtkWidget* analysis_label = gtk_label_new("ANALISIS PENDAPATAN");
        gtk_box_pack_start(GTK_BOX(vbox), analysis_label, FALSE, FALSE, 5);
        gtk_widget_set_halign(analysis_label, GTK_ALIGN_CENTER);

        // Beri CSS untuk header analisis pendapatan
        GtkStyleContext *context_year_header = gtk_widget_get_style_context(analysis_label);
        gtk_style_context_add_class(context_year_header, "analysis-income-header");


        // Tabel analisis pendapatan
        GtkWidget* income_frame = gtk_frame_new(NULL);
        gtk_box_pack_start(GTK_BOX(vbox), income_frame, FALSE, FALSE, 20);

        gtk_frame_set_label_align(GTK_FRAME(income_frame), 0.5, 0.5);
        gtk_frame_set_shadow_type(GTK_FRAME(income_frame), GTK_SHADOW_ETCHED_OUT);

        GtkWidget* income_grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(income_frame), income_grid);

        double yearlyIncome = 0.0;
        for (int j = 0; j < 12; j++) {
            // Label untuk bulan
            char month_text[20];
            sprintf(month_text, "Month %d:", j + 1);
            GtkWidget* label_month = gtk_label_new(month_text);
            gtk_widget_set_size_request(label_month, ANALYSIS_LABEL_WIDTH, -1);
            gtk_widget_set_halign(label_month, GTK_ALIGN_START);
            gtk_grid_attach(GTK_GRID(income_grid), label_month, 0, j, 1, 1);

            // Nominal pendapatan
            char income_text[30];
            sprintf(income_text, "Rp %.2f", report->monthlyIncome[j]);
            GtkWidget* label_income = gtk_label_new(income_text);
            gtk_widget_set_size_request(label_income, ANALYSIS_LABEL_WIDTH, -1);
            gtk_widget_set_halign(label_income, GTK_ALIGN_START);
            gtk_widget_set_margin_start(label_income, 5); // Jarak tambahan 5 piksel dari kiri
            gtk_grid_attach(GTK_GRID(income_grid), label_income, 1, j, 1, 1);

            yearlyIncome += report->monthlyIncome[j];
        }

        // Grid untuk Average dan Total Yearly Income
        GtkWidget* income_summary_grid = gtk_grid_new();
        gtk_box_pack_start(GTK_BOX(vbox), income_summary_grid, FALSE, FALSE, 20);
        gtk_grid_set_column_spacing(GTK_GRID(income_summary_grid), 20);

        // Average Yearly Income
        char avg_income_text[50];
        sprintf(avg_income_text, "Average Yearly Income:");
        GtkWidget* label_avg_income_desc = gtk_label_new(avg_income_text);
        gtk_widget_set_size_request(label_avg_income_desc, ANALYSIS_LABEL_WIDTH, -1);
        gtk_widget_set_halign(label_avg_income_desc, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(income_summary_grid), label_avg_income_desc, 0, 0, 1, 1);

        char avg_income_value_text[50];
        sprintf(avg_income_value_text, "Rp %.2f", yearlyIncome / 12);
        GtkWidget* label_avg_income_value = gtk_label_new(avg_income_value_text);
        gtk_widget_set_size_request(label_avg_income_value, ANALYSIS_LABEL_WIDTH, -1);
        gtk_widget_set_halign(label_avg_income_value, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(income_summary_grid), label_avg_income_value, 1, 0, 1, 1);

        // Total Yearly Income
        char total_income_text[50];
        sprintf(total_income_text, "Total Yearly Income:");
        GtkWidget* label_total_income_desc = gtk_label_new(total_income_text);
        gtk_widget_set_size_request(label_total_income_desc, ANALYSIS_LABEL_WIDTH, -1);
        gtk_widget_set_halign(label_total_income_desc, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(income_summary_grid), label_total_income_desc, 0, 1, 1, 1);

        char total_income_value_text[50];
        sprintf(total_income_value_text, "Rp %.2f", yearlyIncome);
        GtkWidget* label_total_income_value = gtk_label_new(total_income_value_text);
        gtk_widget_set_size_request(label_total_income_value, ANALYSIS_LABEL_WIDTH, -1);
        gtk_widget_set_halign(label_total_income_value, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(income_summary_grid), label_total_income_value, 1, 1, 1, 1);

        // Tambahkan pemisah antara tahun
        GtkWidget* separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
        gtk_box_pack_start(GTK_BOX(vbox), separator, FALSE, FALSE, 10);

        // Set grid properties
        gtk_widget_set_hexpand(grid, TRUE);
        gtk_widget_set_halign(grid, GTK_ALIGN_FILL);
        gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
        gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

        // Set income grid properties
        gtk_widget_set_hexpand(income_grid, TRUE);
        gtk_widget_set_halign(income_grid, GTK_ALIGN_FILL);
        gtk_grid_set_row_spacing(GTK_GRID(income_grid), 5);

        // Set income summary grid properties
        gtk_widget_set_hexpand(income_summary_grid, TRUE);
        gtk_widget_set_halign(income_summary_grid, GTK_ALIGN_FILL);
        gtk_grid_set_row_spacing(GTK_GRID(income_summary_grid), 5);
        gtk_grid_set_column_spacing(GTK_GRID(income_summary_grid), 20);

        // Set separator properties
        gtk_widget_set_hexpand(separator, TRUE);
        gtk_widget_set_halign(separator, GTK_ALIGN_FILL);

        // Set width height and alignment
        gtk_widget_set_size_request(label_year, ANALYSIS_LABEL_WIDTH, -1);

        GtkStyleContext* context_income = gtk_widget_get_style_context(income_frame);
        gtk_style_context_add_class(context_income, "income-frame");


    }
}

void SubmitAnalyticsButtonHandler(GtkWidget* widget, gpointer data) {
    AnalyticsParam* param = (AnalyticsParam*)data;

    // Get the start year and end year from the input fields
    char* startYearText = strdup(gtk_entry_get_text(GTK_ENTRY(param->analyticsPointer->startYear)));
    char* endYearText = strdup(gtk_entry_get_text(GTK_ENTRY(param->analyticsPointer->endYear)));

    // Convert the text to integer
    int startYear = atoi(startYearText);
    int endYear = atoi(endYearText);

    // Check if the input is valid
    if (startYear > endYear) {
        GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(param->vbox), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Invalid year range");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Check selisih cuman boleh dibawah 10 tahun
    if (endYear - startYear > 10) {
        GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(param->vbox), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Year range must be less than 10 years");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Update Tabel
    // Clear previous content
    GList* children = gtk_container_get_children(GTK_CONTAINER(param->vbox));
    for (GList* iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    // Recalculate reports for the selected year range
    calculateReports(param->allPatientData, param->allTindakanData, param->yearlyReports, &param->reportCount, startYear, endYear);

    // Display updated reports
    displayReportsInTable(param->vbox, param->yearlyReports, param->reportCount);

    // Refresh the window
    // Show all the widgets
    gtk_widget_show_all(param->vbox);

    // Free the memory
    free(startYearText);
    free(endYearText);
    free(param->analyticsPointer);
    free(param);
}
    

void RefreshAnalyticsButtonHandler(GtkWidget* widget, gpointer data) {
    AnalyticsParam* param = (AnalyticsParam*)data;

    // Create New WIndow
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Select Year Range");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    

    // Create Main Box
    GtkWidget* mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), mainBox);

    // VCreate Input FIeld
    GtkWidget* startYearLabel = gtk_label_new("Start Year");
    GtkWidget* startYearEntry = gtk_entry_new();
    GtkWidget* endYearLabel = gtk_label_new("End Year");
    GtkWidget* endYearEntry = gtk_entry_new();

    // Styling Label
    gtk_widget_set_halign(startYearLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(endYearLabel, GTK_ALIGN_CENTER);

    // Create SUbmit Button
    GtkWidget* submitButtonAnalytics = gtk_button_new_with_label("Submit");
    gtk_widget_set_margin_bottom (submitButtonAnalytics, 10);

    GtkStyleContext *context_analytics_add = gtk_widget_get_style_context(submitButtonAnalytics);
    gtk_style_context_add_class(context_analytics_add, "add-data-button-dialog");

    // Create Pointer for Submit Button
    AnalyticsPointer* submitParam = malloc(sizeof(AnalyticsPointer));
    submitParam->startYear = startYearEntry;
    submitParam->endYear = endYearEntry;

    // Create Param for Submit Button
    AnalyticsParam* addYearParam = malloc(sizeof(AnalyticsParam));
    addYearParam->allPatientData = param->allPatientData;
    addYearParam->allTindakanData = param->allTindakanData;
    addYearParam->vbox = param->vbox;
    addYearParam->reportCount = param->reportCount;
    memccpy(addYearParam->yearlyReports, param->yearlyReports, sizeof(YearlyReport), param->reportCount);
    addYearParam->analyticsPointer = submitParam;


    g_signal_connect(submitButtonAnalytics, "clicked", G_CALLBACK(SubmitAnalyticsButtonHandler), addYearParam);

    // Clear previous content
    GList* children = gtk_container_get_children(GTK_CONTAINER(param->vbox));
    for (GList* iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    // Recalculate reports for the selected year range
    calculateReports(param->allPatientData, param->allTindakanData, param->yearlyReports, &param->reportCount, param->startYear, param->endYear);

    // Display updated reports
    displayReportsInTable(param->vbox, param->yearlyReports, param->reportCount);

    // Add the input fields and button to the main container
    gtk_box_pack_start(GTK_BOX(mainBox), startYearLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), startYearEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), endYearLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), endYearEntry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainBox), submitButtonAnalytics, FALSE, FALSE, 0);


    // Refresh the window
    // Show all the widgets
    gtk_widget_show_all(window);
    gtk_widget_show_all(param->vbox);

    
}

void buildAnalyticsTab(GtkWidget* financeTab, Patient** operatedData, Patient** allPatientData, Tindakan* allTindakanList) {
    // Create Toolbar and Refresh Button
    GtkWidget* toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(financeTab), toolbar, FALSE, FALSE, 0);

    // GtkToolItem* refreshButton = gtk_tool_button_new(NULL, "Select Year Range");
    // gtk_toolbar_insert(GTK_TOOLBAR(toolbar), refreshButton, -1);

    // Create the "Add Data" button
    GtkToolItem *refreshButton = gtk_tool_button_new(NULL, "Set Dates");
    GtkWidget *addPatientDataButtonWidget = gtk_bin_get_child(GTK_BIN(refreshButton)); // Ambil widget internal dari GtkToolButton
    GtkStyleContext *RefreshContext = gtk_widget_get_style_context(addPatientDataButtonWidget);
    gtk_style_context_add_class(RefreshContext, "add-data-patient-button");
    // ALightment ke center
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), refreshButton, -1);
    

    // Allocate and initialize AnalyticsParam
    AnalyticsParam* param = malloc(sizeof(AnalyticsParam));
    param->startYear = 2024;  // Default start year
    param->endYear = 2024;    // Default end year
    param->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    param->reportCount = 0;
    param->allPatientData = allPatientData;
    param->allTindakanData = allTindakanList;

    // Calculate and display reports for the default range
    calculateReports(allPatientData, allTindakanList, param->yearlyReports, &param->reportCount, param->startYear, param->endYear);
    displayReportsInTable(param->vbox, param->yearlyReports, param->reportCount);

    // Connect Refresh button click signal to handler
    g_signal_connect(refreshButton, "clicked", G_CALLBACK(RefreshAnalyticsButtonHandler), param);

    // Create scrolled window and pack vbox into it
    GtkWidget* scrollableFinance = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollableFinance), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(financeTab), scrollableFinance, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(scrollableFinance), param->vbox);
}


