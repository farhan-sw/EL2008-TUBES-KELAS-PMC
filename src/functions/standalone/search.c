#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dataStructure.h"
#include "search.h"
#include "logger.h"
#include "dataOperator.h"
#include <ctype.h>

char* toLowercase(const char* input) {
    if (input == NULL) return NULL;
    char* result = malloc(strlen(input) + 1); // +1 for the null terminator
    if (result == NULL) return NULL; // Check for malloc failure

    for (int i = 0; input[i]; i++) {
        result[i] = tolower((unsigned char)input[i]);
    }
    result[strlen(input)] = '\0';
    return result;
}

// ====================== SEARCH ENGINE =========================
void searchPatient(Patient *head, Patient **output, char keyword[]){

    // printf("menerima keyword: %s\n", keyword);
    // cek apakah keyword kosong, bila kosong result diisi head

    // buat list baru
    Patient** result = malloc(sizeof(Patient*));
    *result = NULL; // Initialize the result pointer to NULL

    if (strcmp(keyword, "") == 0){
        // printf("keyword kosong\n");
        copyPatient(head, result);
        return;
    } else {
        // ubah keyword menjadi lowercase
        char* keywordLower = toLowercase(keyword);
        // printf("Data tidak kosong\n");
        // jika tidak kosong maka lakukan pencarian berdasar keyword taboa mengecek history
        Patient *currentPatient = head;
        char tglLahir[20];
        char umur[5];
        char noBPJS[15];
        int i = 0;
        while (currentPatient != NULL) {
            // printf("Mengecek data pasien ke : %d\n",i);
            // printf("Nama Pasien: %s\n", currentPatient->namaLengkap);
            // printf("Alamat Pasien: %s\n", currentPatient->alamat);
            // printf("Kota Pasien: %s\n", currentPatient->kota);
            // printf("Tempat Lahir Pasien: %s\n", currentPatient->tempatLahir);
            // printf("Tanggal Lahir Pasien: %d-%d-%d\n", currentPatient->tanggalLahir.day, currentPatient->tanggalLahir.month, currentPatient->tanggalLahir.year);
            // printf("Umur Pasien: %d\n", currentPatient->umur);
            // printf("No BPJS Pasien: %d\n", currentPatient->noBPJS);
            // printf("ID Pasien: %s\n\n", currentPatient->idPasien);

            // kosongkan variabel
            memset(tglLahir, 0, sizeof(tglLahir));
            memset(umur, 0, sizeof(umur));
            memset(noBPJS, 0, sizeof(noBPJS));
            
            convertDateToString(currentPatient->tanggalLahir, tglLahir);
            sprintf(umur, "%d", currentPatient->umur);
            sprintf(noBPJS, "%d", currentPatient->noBPJS);

            // ubah data menjadi lowercase
            strcpy(tglLahir, toLowercase(tglLahir));
            strcpy(umur, toLowercase(umur));
            strcpy(noBPJS, toLowercase(noBPJS));
            

            // cek apakah keyword ada di namaLengkap
            // printf("Mengecek keyword di namaLengkap\n");
            if (strstr(toLowercase(currentPatient->namaLengkap), keywordLower) != NULL) {
                // buat node baru dan tambahkan ke result
                Patient* newPatient = createPatient(currentPatient->namaLengkap, currentPatient->alamat, currentPatient->kota, currentPatient->tempatLahir, currentPatient->tanggalLahir, currentPatient->umur, currentPatient->noBPJS, currentPatient->idPasien);
                addPatient(result, newPatient);
                // printf("Data ditemukan\n");
            } else { // cek apakah keywordLower ada di alamat
                // printf("Mengecek keywordLower di alamat\n");
                if (strstr(toLowercase(currentPatient->alamat), keywordLower) != NULL) {
                    // buat node baru dan tambahkan ke result
                    Patient* newPatient = createPatient(currentPatient->namaLengkap, currentPatient->alamat, currentPatient->kota, currentPatient->tempatLahir, currentPatient->tanggalLahir, currentPatient->umur, currentPatient->noBPJS, currentPatient->idPasien);
                    addPatient(result, newPatient);
                    // printf("Data ditemukan\n");
                } else { // cek apakah keywordLower ada di kota
                    // printf("Mengecek keywordLower di kota\n");
                    if (strstr(toLowercase(currentPatient->kota), keywordLower) != NULL) {
                        // buat node baru dan tambahkan ke result
                        Patient* newPatient = createPatient(currentPatient->namaLengkap, currentPatient->alamat, currentPatient->kota, currentPatient->tempatLahir, currentPatient->tanggalLahir, currentPatient->umur, currentPatient->noBPJS, currentPatient->idPasien);
                        addPatient(result, newPatient);
                        // printf("Data ditemukan\n");
                    } else { // cek apakah keywordLower ada di tempatLahir
                        // printf("Mengecek keywordLower di tempatLahir\n");
                        if (strstr(toLowercase(currentPatient->tempatLahir), keywordLower) != NULL) {
                            // buat node baru dan tambahkan ke result
                            Patient* newPatient = createPatient(currentPatient->namaLengkap, currentPatient->alamat, currentPatient->kota, currentPatient->tempatLahir, currentPatient->tanggalLahir, currentPatient->umur, currentPatient->noBPJS, currentPatient->idPasien);
                            addPatient(result, newPatient);
                            // printf("Data ditemukan\n");
                        } else { // cek apakah keywordLower ada di tanggalLahir
                            // printf("Mengecek keywordLower di tanggalLahir\n");
                            if (strstr(tglLahir, keywordLower) != NULL) {
                                // buat node baru dan tambahkan ke result
                                Patient* newPatient = createPatient(currentPatient->namaLengkap, currentPatient->alamat, currentPatient->kota, currentPatient->tempatLahir, currentPatient->tanggalLahir, currentPatient->umur, currentPatient->noBPJS, currentPatient->idPasien);
                                addPatient(result, newPatient);
                                // printf("Data ditemukan\n");
                            } else { // cek apakah keywordLower ada di umur
                                // printf("Mengecek keywordLower di umur\n");
                                if (strstr(umur, keywordLower) != NULL) {
                                    // buat node baru dan tambahkan ke result
                                    Patient* newPatient = createPatient(currentPatient->namaLengkap, currentPatient->alamat, currentPatient->kota, currentPatient->tempatLahir, currentPatient->tanggalLahir, currentPatient->umur, currentPatient->noBPJS, currentPatient->idPasien);
                                    addPatient(result, newPatient);
                                    // printf("Data ditemukan\n");
                                } else {// cek apakah keywordLower ada di noBPJS
                                    // printf("Mengecek keywordLower di noBPJS\n");
                                    if (strstr(noBPJS, keywordLower) != NULL) {
                                        // buat node baru dan tambahkan ke result
                                        Patient* newPatient = createPatient(currentPatient->namaLengkap, currentPatient->alamat, currentPatient->kota, currentPatient->tempatLahir, currentPatient->tanggalLahir, currentPatient->umur, currentPatient->noBPJS, currentPatient->idPasien);
                                        addPatient(result, newPatient);
                                        // printf("Data ditemukan\n");
                                    } else {// cek apakah keywordLower ada di idPasien
                                        // printf("Mengecek keywordLower di idPasien\n");
                                        if (strstr(toLowercase(currentPatient->idPasien), keywordLower) != NULL) {
                                            // buat node baru dan tambahkan ke result
                                            Patient* newPatient = createPatient(currentPatient->namaLengkap, currentPatient->alamat, currentPatient->kota, currentPatient->tempatLahir, currentPatient->tanggalLahir, currentPatient->umur, currentPatient->noBPJS, currentPatient->idPasien);
                                            addPatient(result, newPatient);
                                            // printf("Data ditemukan\n");
                                        } else {
                                            // printf("Data tidak ditemukan\n");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            currentPatient = currentPatient->next;
            i++;
            // printf("\n");
        }
    }
    // kosongkan result dengan bebaskan memorinya
    freePatientList(*output);
    // printf("result dibersihkan\n");
    // isi result dengan hasil pencarian
    *output = *result;

    // Logger(1, ("Searching patient with keywordLower %s\n", keywordLower));
}

void searchMedicalRecord(Patient *head, Patient **result, char keyword[]){
    // printf("Search Engine\n");
}

void searchService(Tindakan *head, Tindakan **result, char keyword[]){
    // printf("Search Engine\n");
}