#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include "logger.h"
#include "dataStructure.h"
#include "test.h"
#include "dataOperator.h"
#include "loader.h"
#include "search.h"

char session[50];

const char* medRec[][7] = {
    {"1 Januari", "KX 12345", "Dehidrasi", "Pemasangan Infus", "4 Januari 2022", "Rp 265.000,00" },
    {"1 Januari", "KX 12345", "Dehidrasi", "Pemasangan Infus", "4 Januari 2022", "Rp 265.000,00" },
    {"1 Januari", "KX 12345", "Dehidrasi", "Pemasangan Infus", "4 Januari 2022", "Rp 265.000,00" },
};

void initializeSession(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    sprintf(session, "HealthAdminSessionStart_%d-%d-%d_%d-%d-%d-%ld", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ts.tv_nsec);
    printf("Session: %s\n", session);
}

// GTK 3 Functions

#include "./functions/GTK/activate.c"

int main(int argc, char **argv) {
    char* filename = "../data/DataPMC20232024.xlsx";

    initializeSession();
    Logger(1, "Application started");

    // LOAD DATA
    // Inisiasi data pasien
    Patient** allPatientData = malloc(sizeof(Patient*));
    Patient** operatedData = malloc(sizeof(Patient*));
    Tindakan** allTindakanList = malloc(sizeof(Tindakan*));
    loadData(allPatientData, allTindakanList, filename);
    copyPatient(*allPatientData, operatedData);
    printf("Pointer allPatientList: %p\n", allPatientData);

    // // test search 
    // Patient* result = NULL;
    // searchPatient(*allPatientData, &result, "Tulungagung");

    // printf("Hasil pencarian: \n");
    // printPatientList(result);

    // GTK3 RUNNER

    // Initialize GTK
    gtk_init(&argc, &argv);
    // Initialize main window
    // print pointer allPatientData
    
    activate(operatedData, allPatientData, *allTindakanList);
    // Start the GTK main loop
    Logger(1, "Initializing GTK window");
    gtk_main();
    Logger(1, "Terminating Application, Cleaning up memory");

    // Pembersihan memori

    Logger(2, "Cleaning up memory success, have a nice day!");

    return 0;
}


