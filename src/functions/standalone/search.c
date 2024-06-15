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
        // jika tidak kosong maka lakukan pencarian berdasar keyword taboa mengecek history
        Patient *currentPatient = head;
        char tglLahir[20];
        char umur[5];
        char noBPJS[15];
        int i = 0;

        int copyData = 0;
        while (currentPatient != NULL) {
            // kosongkan variabel
            copyData = 0;
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
            if (strstr(toLowercase(currentPatient->namaLengkap), keywordLower) != NULL) {
                copyData = 1;
            } else if (strstr(toLowercase(currentPatient->alamat), keywordLower) != NULL) {
                copyData = 1;
            } else if (strstr(toLowercase(currentPatient->kota), keywordLower) != NULL) {
                copyData = 1;
            } else if (strstr(toLowercase(currentPatient->tempatLahir), keywordLower) != NULL) {
                copyData = 1;
            } else if (strstr(tglLahir, keywordLower) != NULL) {
                copyData = 1;
            } else if (strstr(umur, keywordLower) != NULL) {
                copyData = 1;
            } else if (strstr(noBPJS, keywordLower) != NULL) {
                copyData = 1;
            } else if (strstr(toLowercase(currentPatient->idPasien), keywordLower) != NULL) {
                copyData = 1;
            }

            if(copyData == 1){
                // buat node baru dan tambahkan ke result
                Patient* newPatient = createPatient(currentPatient->namaLengkap, currentPatient->alamat, currentPatient->kota, currentPatient->tempatLahir, currentPatient->tanggalLahir, currentPatient->umur, currentPatient->noBPJS, currentPatient->idPasien);
                // copy historynya
                History* currentHistory = currentPatient->history;
                while (currentHistory != NULL) {
                    History* newHistory = createHistory(currentHistory->tanggal, currentHistory->idPasien, currentHistory->diagnosis, currentHistory->tindakanID, currentHistory->kontrol, currentHistory->biaya);
                    addHistory(&newPatient->history, newHistory);
                    currentHistory = currentHistory->next;
                }
                addPatient(result, newPatient);
            }

            currentPatient = currentPatient->next;
            i++;
        }
    }
    // kosongkan result dengan bebaskan memorinya
    freePatientList(*output);
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