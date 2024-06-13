#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"
#include "dataOperator.h"
#include <xlsxio_read.h>
#include <xlsxio_write.h>
#include "logger.h"

//fungsi yang membaca file xlxs

void loadData(Patient** patientList, char* filename) {
    xlsxioreader xlsxioread;
    xlsxioreadersheet sheet_data_pasien;
    xlsxioreadersheet sheet_rekam_medis;
    xlsxioreadersheet sheet_biaya;
    
    xlsxioread = xlsxioread_open(filename);
    if (xlsxioread == NULL) {
        Logger(3, "Failed to open the Excel file.");
        return;
    }
    
    sheet_data_pasien = xlsxioread_sheet_open(xlsxioread, "Data Pasien", XLSXIOREAD_SKIP_EMPTY_ROWS);
    sheet_rekam_medis = xlsxioread_sheet_open(xlsxioread, "Riwayat Datang, Diag,, Tindakan", XLSXIOREAD_SKIP_EMPTY_ROWS);
    sheet_biaya = xlsxioread_sheet_open(xlsxioread, "Biaya Tindakan", XLSXIOREAD_SKIP_EMPTY_ROWS);
    if (sheet_data_pasien == NULL) {
        Logger(3, "Failed to open patient data sheet in the Excel file.");
        xlsxioread_close(xlsxioread);
        return;
    }
    if (sheet_rekam_medis == NULL) {
        Logger(3, "Failed to open the medical record sheet in the Excel file.");
        xlsxioread_close(xlsxioread);
        return;
    }
    if (sheet_biaya == NULL) {
        Logger(3, "Failed to open the treatment cost sheet in the Excel file.");
        xlsxioread_close(xlsxioread);
        return;
    }
    
    // Memasukkan data pasien ke dalam linked list
    const char* cell_data;
    int itterasi = 0;
    // variabel penampung sementara
    char namaLengkap[50];
    char alamat[100];
    char kota[50];
    char tempatLahir[50];
    int umur;
    int noBPJS;
    char idPasien[20];
    int row_count = 0;

    Date tanggalLahirTemp;

    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    int current_year = local_time->tm_year + 1900;
    int age;
    
    
    while (xlsxioread_sheet_next_row(sheet_data_pasien)) {
        if (row_count == 0) {
            row_count++;
            continue; // Skip the first row
        }
        itterasi = 0;
        while ((cell_data = xlsxioread_sheet_next_cell(sheet_data_pasien)) != NULL) {
            // Process the cell data
            // printf("%s\t", cell_data);
            switch (itterasi)
            {
            case 1:
                // salin nama lengkap
                strcpy(namaLengkap, cell_data);
                break;
            case 2:
                // salin alamat
                strcpy(alamat, cell_data);
                break;
            case 3:
                // salin kota
                strcpy(kota, cell_data);
                break;
            case 4:
                // salin tempat lahir
                strcpy(tempatLahir, cell_data);
                break;
            case 5:
                // salin tanggal lahir
                tanggalLahirTemp = convertStringToDate(cell_data);
                break;
            case 6:
                // salin umur
                umur = atoi(cell_data);
                break;
            case 7:
                // salin no BPJS
                noBPJS = atoi(cell_data);
                break;
            case 8:
                // salin id pasien
                strcpy(idPasien, cell_data);
                break;
            default:
                break;
            }

            itterasi++;
        }
        // printf("\n");
        // buat node pasien

        // Hitung umur berdasarkan tanggal lahir dan waktu sekarang
        
        age = current_year - tanggalLahirTemp.year;
        if (local_time->tm_mon < tanggalLahirTemp.month) {
            age--;
        } else if (local_time->tm_mon == tanggalLahirTemp.month) {
            if (local_time->tm_mday < tanggalLahirTemp.day) {
                age--;
            }
        }

        Patient* newPatient = createPatient(namaLengkap, alamat, kota, tempatLahir, tanggalLahirTemp, age, noBPJS, idPasien);
        // tambahkan node pasien ke dalam linked list
        addPatient(patientList, newPatient);
        row_count++;
    }

    // // Memasukkan data rekam medis
    // row_count = 0;
    // // Variabel penampung sementara
    // Date tanggal;
    // char diagnosis[50];
    // int tindakanID;
    // Date kontrol;
    // int biaya;
    // while (xlsxioread_sheet_next_row(sheet_rekam_medis)) {
    //     if (row_count == 0) {
    //         row_count++;
    //         continue; // Skip the first row
    //     }
    //     itterasi = 0;
    //     while ((cell_data = xlsxioread_sheet_next_cell(sheet_rekam_medis)) != NULL) {
    //         // Process the cell data

    //         switch (itterasi)
    //         {
    //         case 1:
    //             // Baca Tanggal
                
    //             break;
    //         case 2:
    //             // salin id pasien
    //             strcpy(idPasien, cell_data);
    //             break;
    //         case 3:
    //             // Salin data diagnosa
    //             strcpy(diagnosis, cell_data);
    //             break;
    //         case 4:
    //             //
    //         default:
    //             break;
    //         }

    //         itterasi++;
    //     }
    //     // printf("\n");
    //     // buat node rekam medis
        
    //     // tambahkan node pasien ke dalam linked list
        
    //     row_count++;
    // }
    
    xlsxioread_sheet_close(sheet_data_pasien);
    xlsxioread_sheet_close(sheet_rekam_medis);
    xlsxioread_sheet_close(sheet_biaya);
    xlsxioread_close(xlsxioread);
    Logger(1, "Data loaded successfully");

    printf("Pointer patientList di Loader: %p\n", patientList);
}

