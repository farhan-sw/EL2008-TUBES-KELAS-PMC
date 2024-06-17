#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"
#include "dataOperator.h"

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
        sprintf(year_text, "Year %d", report->year);
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
        GtkWidget* income_grid = gtk_grid_new();
        gtk_box_pack_start(GTK_BOX(vbox), income_grid, FALSE, FALSE, 20);

        double yearlyIncome = 0.0;
        for (int j = 0; j < 12; j++) {
            char month_income_text[30];
            sprintf(month_income_text, "Month %d: Rp %.2f", j + 1, report->monthlyIncome[j]);
            GtkWidget* label_month_income = gtk_label_new(month_income_text);
            gtk_widget_set_size_request(label_month_income, ANALYSIS_LABEL_WIDTH, -1);
            gtk_widget_set_halign(label_month_income, GTK_ALIGN_START);
            gtk_widget_set_margin_start(label_month_income, 5); // Jarak tambahan 5 piksel dari kiri
            gtk_grid_attach(GTK_GRID(income_grid), label_month_income, 0, j, 1, 1);
            yearlyIncome += report->monthlyIncome[j];
        }

        char avg_income_text[50];
        sprintf(avg_income_text, "Average Yearly Income: Rp %.2f", yearlyIncome / 12);
        GtkWidget* label_avg_income = gtk_label_new(avg_income_text);
        gtk_widget_set_size_request(label_avg_income, ANALYSIS_LABEL_WIDTH, -1);
        gtk_widget_set_halign(label_avg_income, GTK_ALIGN_START);
        gtk_widget_set_margin_start(label_avg_income, 5); // Jarak tambahan 5 piksel dari kiri
        gtk_grid_attach(GTK_GRID(income_grid), label_avg_income, 0, 12, 1, 1);

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

        // Set separator properties
        gtk_widget_set_hexpand(separator, TRUE);
        gtk_widget_set_halign(separator, GTK_ALIGN_FILL);

        // Set width height and alignment
        gtk_widget_set_size_request(label_year, ANALYSIS_LABEL_WIDTH, -1);
        gtk_widget_set_size_request(analysis_label, ANALYSIS_LABEL_WIDTH, -1);


    }
}

void RefreshAnalyticsButtonHandler(GtkWidget* widget, gpointer data) {
    AnalyticsParam* param = (AnalyticsParam*)data;

    // Contoh: Asumsi rentang tahun di-hardcode
    param->startYear = 2022;
    param->endYear = 2024;

    printf("Refresh Analytics Button Clicked\n");
    printf("Start Year: %d End Year: %d\n", param->startYear, param->endYear);

    // Clear previous content
    printf("Destroying previous content\n");
    GList* children = gtk_container_get_children(GTK_CONTAINER(param->vbox));
    for (GList* iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    // Recalculate reports for the selected year range
    printf("Recalculating reports\n");
    calculateReports(param->allPatientData, param->allTindakanData, param->yearlyReports, &param->reportCount, param->startYear, param->endYear);

    // Display updated reports
    printf("Displaying reports\n");
    displayReportsInTable(param->vbox, param->yearlyReports, param->reportCount);

    // Refresh the window
    gtk_widget_show_all(param->vbox);

    
}

void buildAnalyticsTab(GtkWidget* financeTab, Patient** operatedData, Patient** allPatientData, Tindakan* allTindakanList) {
    // Create Toolbar and Refresh Button
    GtkWidget* toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(financeTab), toolbar, FALSE, FALSE, 0);

    GtkToolItem* refreshButton = gtk_tool_button_new(NULL, "Select Year Range");
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


