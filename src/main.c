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

char session[50];

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
    Patient** displayData = malloc(sizeof(Patient*));
    Tindakan* allTindakanList = NULL;
    loadData(allPatientData, &allTindakanList, filename);
    copyPatient(*allPatientData, displayData);
    printf("Pointer allPatientList: %p\n", allPatientData);

    // printLinkedList(allPatientData);

    // printf("Test mengubah tanggal\n");
    // // Test mengubah tanggal
    // Date testDate = convertStringToDate("1 Januari 2022");
    // printDate(testDate);

    // // Testing print history pasien KX 1230123
    // Patient* testPatient = findPatient(allPatientList, "KX 1230123");
    // printPatientHistory(testPatient);

    // GTK3 RUNNER

    // Initialize GTK
    gtk_init(&argc, &argv);
    // Initialize main window
    // print pointer allPatientData
    
    activate(*displayData, allPatientData, allTindakanList);
    // Start the GTK main loop
    Logger(1, "Initializing GTK window");
    gtk_main();
    Logger(1, "Terminating Application, Cleaning up memory");

    // Pembersihan memori

    Logger(2, "Cleaning up memory success, have a nice day!");

    return 0;
}


