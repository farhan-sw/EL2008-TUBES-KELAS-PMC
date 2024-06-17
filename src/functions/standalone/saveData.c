#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dataStructure.h"
#include "dataOperator.h"
#include <xlsxwriter.h>
#include "logger.h"

void saveData(Patient* allPatientData, Tindakan* allTindakanList , char filename[], char session[]){


    Logger(1, "Saving data to excel file");
    char* defaulDirectory = "../data/";

    // deklarasi nama sementara
    char tempFilename[100];
    // tambahkan tempFilename dengan session
    sprintf(tempFilename, "%s%s_%s.xlsx",defaulDirectory, filename, session);
    
    // Create a new workbook
    lxw_workbook  *workbook  = workbook_new(tempFilename);

    Logger(2, "Workbook created successfully.");
    
    // buat worksheet bernama "Data Pasien"
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, "Data Pasien");

    // Write header
    worksheet_write_string(worksheet, 0, 0, "No", NULL);
    worksheet_write_string(worksheet, 0, 1, "Nama Lengkap", NULL);
    worksheet_write_string(worksheet, 0, 2, "Alamat", NULL);
    worksheet_write_string(worksheet, 0, 3, "Kota", NULL);
    worksheet_write_string(worksheet, 0, 4, "Tempat Lahir", NULL);
    worksheet_write_string(worksheet, 0, 5, "Tanggal Lahir", NULL);
    worksheet_write_string(worksheet, 0, 6, "Umur (th)", NULL);
    worksheet_write_string(worksheet, 0, 7, "No BPJS", NULL);
    worksheet_write_string(worksheet, 0, 8, "ID Pasien", NULL);

    // Write data
    int i = 0;
    Patient* current = allPatientData;
    char tempString[20];
    while(current != NULL){
        worksheet_write_number(worksheet, i+1, 0, i+1, NULL);
        worksheet_write_string(worksheet, i+1, 1, current->namaLengkap, NULL);
        worksheet_write_string(worksheet, i+1, 2, current->alamat, NULL);
        worksheet_write_string(worksheet, i+1, 3, current->kota, NULL);
        worksheet_write_string(worksheet, i+1, 4, current->tempatLahir, NULL);

        convertDateToString(current->tanggalLahir, tempString);
        worksheet_write_string(worksheet, i+1, 5, tempString, NULL);

        worksheet_write_number(worksheet, i+1, 6, current->umur, NULL);
        worksheet_write_number(worksheet, i+1, 7, current->noBPJS, NULL);
        worksheet_write_string(worksheet, i+1, 8, current->idPasien, NULL);
        current = current->next;
        i++;
    }

    Logger(2, "Patient data saved.");

    // buat sheet baru "Riwayat Datang, Diag,, Tindakan"
    lxw_worksheet *worksheet2 = workbook_add_worksheet(workbook, "Riwayat Datang, Diag,, Tindakan");
    // Write header
    worksheet_write_string(worksheet2, 0, 0, "No", NULL);
    worksheet_write_string(worksheet2, 0, 1, "Tanggal", NULL);
    worksheet_write_string(worksheet2, 0, 2, "ID Pasien", NULL);
    worksheet_write_string(worksheet2, 0, 3, "Diagnosis", NULL);
    worksheet_write_string(worksheet2, 0, 4, "Tindakan", NULL);
    worksheet_write_string(worksheet2, 0, 5, "Kontrol", NULL);
    worksheet_write_string(worksheet2, 0, 6, "Biaya (Rp)", NULL);

    // Write data
    i = 0;
    current = allPatientData;
    History* currentHistory;
    while(current != NULL){
        currentHistory = current->history;
        while(currentHistory != NULL){
            worksheet_write_number(worksheet2, i+1, 0, i+1, NULL);
            convertDateToString(currentHistory->tanggal, tempString);
            worksheet_write_string(worksheet2, i+1, 1, tempString, NULL);
            worksheet_write_string(worksheet2, i+1, 2, currentHistory->idPasien, NULL);
            worksheet_write_string(worksheet2, i+1, 3, currentHistory->diagnosis, NULL);
            worksheet_write_string(worksheet2, i+1, 4, currentHistory->tindakan, NULL);
            convertDateToString(currentHistory->kontrol, tempString);
            worksheet_write_string(worksheet2, i+1, 5, tempString, NULL);
            worksheet_write_number(worksheet2, i+1, 6, currentHistory->biaya, NULL);
            currentHistory = currentHistory->next;
            i++;
        }
        current = current->next;
    }

    Logger(2, "Medical record saved.");

    // Buat sheet baru "Biaya Tindakan"
    lxw_worksheet *worksheet3 = workbook_add_worksheet(workbook, "Biaya Tindakan");
    // write header
    worksheet_write_string(worksheet3, 0, 0, "No", NULL);
    worksheet_write_string(worksheet3, 0, 1, "Aktivitas", NULL);
    worksheet_write_string(worksheet3, 0, 2, "Biaya", NULL);

    // Write data
    i = 0;
    Tindakan* currentTindakan = allTindakanList;
    while(currentTindakan != NULL){
        worksheet_write_number(worksheet3, i+1, 0, i+1, NULL);
        worksheet_write_string(worksheet3, i+1, 1, currentTindakan->Tindakan, NULL);
        worksheet_write_number(worksheet3, i+1, 2, currentTindakan->biaya, NULL);
        currentTindakan = currentTindakan->next;
        i++;
    }

    Logger(2, "Pricelist saved.");

    // Save the workbook
    workbook_close(workbook);

    // Check if there is a file with the same name but without session in the same directory
    char tempFilenameWithoutSession[100];
    sprintf(tempFilenameWithoutSession, "%s%s.xlsx", defaulDirectory, filename);

    if (access(tempFilenameWithoutSession, F_OK) != -1) {
        // File exists, delete it
        remove(tempFilenameWithoutSession);
    }

    // Rename the newly created file to the filename without session
    rename(tempFilename, tempFilenameWithoutSession);


    Logger(2, "Data saved successfully.");
}