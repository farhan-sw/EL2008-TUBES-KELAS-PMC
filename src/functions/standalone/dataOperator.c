#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"



/**
 * @brief Create a Date function
 * @param day: int hari
 * @param month: int bulan
 * @param year: int tahun
 */
Date createDate(int day, int month, int year) {
    Date newDate;
    newDate.day = day;
    newDate.month = month;
    newDate.year = year;
    return newDate;
}

// Konversi tanggal dari string ke Date
Date convertStringToDate(char tanggal[]) {
    printf("Tanggal: %s\n", tanggal);
    Date newDate;

    // deteksi apakah ada "-" di tanggal
    int count = 0;
    char *splitter;
    for (int i = 0; i < strlen(tanggal); i++) {
        if (tanggal[i] == '-') {
            count++;
        }
    }

    if(count == 0) {
        printf("Format tanggal menggunakan spasi\n");
        splitter = " ";
    } else if(count == 2) {
        printf("Format tanggal menggunakan strip\n");
        splitter = "-";
    }

    char *token = strtok(tanggal, splitter);
    newDate.day = atoi(token);
    printf("Day: %d\n", newDate.day);

    token = strtok(NULL, splitter);

    // Membandingkan 3 huruf pertama dari bulan
    char month[4];
    strncpy(month, token, 3);
    month[3] = '\0';
    if (strcmp(month, "Jan") == 0) {
        newDate.month = 1;
    } else if (strcmp(month, "Feb") == 0) {
        newDate.month = 2;
    } else if (strcmp(month, "Mar") == 0) {
        newDate.month = 3;
    } else if (strcmp(month, "Apr") == 0) {
        newDate.month = 4;
    } else if (strcmp(month, "May") == 0) {
        newDate.month = 5;
    } else if (strcmp(month, "Jun") == 0) {
        newDate.month = 6;
    } else if (strcmp(month, "Jul") == 0) {
        newDate.month = 7;
    } else if (strcmp(month, "Aug") == 0) {
        newDate.month = 8;
    } else if (strcmp(month, "Sep") == 0) {
        newDate.month = 9;
    } else if (strcmp(month, "Oct") == 0) {
        newDate.month = 10;
    } else if (strcmp(month, "Nov") == 0) {
        newDate.month = 11;
    } else if (strcmp(month, "Dec") == 0) {
        newDate.month = 12;
    }

    token = strtok(NULL, splitter);
    newDate.year = atoi(token);
    
    return newDate;
}

// Membuat ID pasien baru yang unik


// Fungsi untuk membuat node patient baru
/**
 * @brief Create a Patient function
 * @param namaLengkap: char nama lengkap
 * @param alamat: char alamat
 * @param kota: char kota
 * @param tempatLahir: char tempat lahir
 * @param umur: int umur
 * @param noBPJS: int no BPJS
 * @param idPasien: char ID pasien
 */
Patient* createPatient(char namaLengkap[], char alamat[], char kota[], char tempatLahir[], int umur, int noBPJS, char idPasien[]) {
    Patient *newPatient = (Patient*) malloc(sizeof(Patient));
    strcpy(newPatient->namaLengkap, namaLengkap);
    strcpy(newPatient->alamat, alamat);
    strcpy(newPatient->kota, kota);
    strcpy(newPatient->tempatLahir, tempatLahir);
    newPatient->umur = umur;
    newPatient->noBPJS = noBPJS;
    strcpy(newPatient->idPasien, idPasien);
    newPatient->history = NULL;
    newPatient->next = NULL;
    return newPatient;
}

// Fungsi untuk menambahkan patient baru ke dalam linkedlist
void addPatient(Patient **head, Patient *newPatient) {
    if (*head == NULL) {
        *head = newPatient;
    } else {
        Patient *currentPatient = *head;
        while (currentPatient->next != NULL) {
            currentPatient = currentPatient->next;
        }
        currentPatient->next = newPatient;
    }
}


/**
 * @brief Create a History function
 * @param tanggal: Date tanggal
 * @param idPasien: char ID pasien
 * @param diagnosis: char diagnosis
 * @param tindakanID: int tindakan ID
 * @param kontrol: Date kontrol
 * @param biaya: int biaya
 */
History* createHistory(Date tanggal, char idPasien[], char diagnosis[], int tindakanID, Date kontrol, int biaya) {
    History *newHistory = (History*) malloc(sizeof(History));
    newHistory->tanggal = tanggal;
    strcpy(newHistory->idPasien, idPasien);
    strcpy(newHistory->diagnosis, diagnosis);
    newHistory->tindakanID = tindakanID;
    newHistory->kontrol = kontrol;
    newHistory->biaya = biaya;
    newHistory->next = NULL;
    return newHistory;
}


/**
 * @brief Print a Date function
 * @param date: Date tanggal
 */
void printDate(Date date) {
    printf("%02d-%02d-%04d", date.day, date.month, date.year);
}

/**
 * @brief Print a linked list function
 * @param head: Patient head
 */
void printLinkedList(Patient *head) {
    Patient *currentPatient = head;
    while (currentPatient != NULL) {
        printf("Nama Lengkap: %s\n", currentPatient->namaLengkap);
        printf("Alamat: %s\n", currentPatient->alamat);
        printf("Kota: %s\n", currentPatient->kota);
        printf("Tempat Lahir: %s\n", currentPatient->tempatLahir);
        printf("Umur: %d\n", currentPatient->umur);
        printf("No. BPJS: %d\n", currentPatient->noBPJS);
        printf("ID Pasien: %s\n", currentPatient->idPasien);
        printf("History:\n");
        History *currentHistory = currentPatient->history;
        while (currentHistory != NULL) {
            printf("- Tanggal: ");
            printDate(currentHistory->tanggal);
            printf("\n");
            printf("  ID Pasien: %s\n", currentHistory->idPasien);
            printf("  Diagnosis: %s\n", currentHistory->diagnosis);
            printf("  Tindakan (ID): %d\n", currentHistory->tindakanID);
            printf("  Kontrol: ");
            printDate(currentHistory->kontrol);
            printf("\n");
            printf("  Biaya: %d\n", currentHistory->biaya);
            currentHistory = currentHistory->next;
        }
        printf("\n");
        currentPatient = currentPatient->next;
    }
}


/**
 * @brief Sort the history function
 * @param head: Patient head
 */
void sortHistory(Patient *head) {
    Patient *currentPatient = head;
    while (currentPatient != NULL) {
        History *currentHistory = currentPatient->history;
        while (currentHistory != NULL) {
            History *nextHistory = currentHistory->next;
            while (nextHistory != NULL) {
                if (currentHistory->tanggal.year > nextHistory->tanggal.year) {
                    Date tempDate = currentHistory->tanggal;
                    currentHistory->tanggal = nextHistory->tanggal;
                    nextHistory->tanggal = tempDate;
                } else if (currentHistory->tanggal.year == nextHistory->tanggal.year) {
                    if (currentHistory->tanggal.month > nextHistory->tanggal.month) {
                        Date tempDate = currentHistory->tanggal;
                        currentHistory->tanggal = nextHistory->tanggal;
                        nextHistory->tanggal = tempDate;
                    } else if (currentHistory->tanggal.month == nextHistory->tanggal.month) {
                        if (currentHistory->tanggal.day > nextHistory->tanggal.day) {
                            Date tempDate = currentHistory->tanggal;
                            currentHistory->tanggal = nextHistory->tanggal;
                            nextHistory->tanggal = tempDate;
                        }
                    }
                }
                nextHistory = nextHistory->next;
            }
            currentHistory = currentHistory->next;
        }
        currentPatient = currentPatient->next;
    }
}


/**
 * @brief Delete Pasien berdasarkan ID (char)
 * @param head: Patient head
 * @param idPasien: char ID pasien
 */
void deletePatient(Patient **head, char idPasien[]) {
    Patient *currentPatient = *head;
    Patient *prevPatient = NULL;

    // Jika pasien yang ingin dihapus adalah head
    if (currentPatient != NULL && strcmp(currentPatient->idPasien, idPasien) == 0) {
        *head = currentPatient->next;
        free(currentPatient);
        return;
    }

    // Mencari pasien yang ingin dihapus
    while (currentPatient != NULL && strcmp(currentPatient->idPasien, idPasien) != 0) {
        prevPatient = currentPatient;
        currentPatient = currentPatient->next;
    }

    // Jika pasien tidak ditemukan
    if (currentPatient == NULL) {
        printf("Pasien dengan ID %s tidak ditemukan\n", idPasien);
        return;
    }

    // Menghapus pasien
    prevPatient->next = currentPatient->next;
    free(currentPatient);
}



/**
 * @brief Main function buat uji coba
 */
int debugging() {
    // Create the parent nodes
    Patient *nodeA = createPatient("A", "Alamat A", "Kota A", "Tempat Lahir A", 30, 12345, "ID_A");
    Patient *nodeB = createPatient("B", "Alamat B", "Kota B", "Tempat Lahir B", 25, 67890, "ID_B");

    // Create the child nodes for node B
    Date dateB1 = createDate(15, 9, 2021);
    Date kontrolB1 = createDate(20, 9, 2021);
    History *nodeB1 = createHistory(dateB1, "ID_B", "Diagnosis B1", 2, kontrolB1, 100000);
    
    Date dateB2 = createDate(10, 10, 2020);
    Date kontrolB2 = createDate(15, 10, 2020);
    History *nodeB2 = createHistory(dateB2, "ID_B", "Diagnosis B2", 3, kontrolB2, 25000);

    // Create the child nodes for node A
    Date dateA1 = createDate(1, 10, 2020);
    Date kontrolA1 = createDate(5, 10, 2020);
    History *nodeA1 = createHistory(dateA1, "ID_A", "Diagnosis A1", 0, kontrolA1, 15000);
    
    Date dateA2 = createDate(1, 11, 2018);
    Date kontrolA2 = createDate(5, 11, 2018);
    History *nodeA2 = createHistory(dateA2, "ID_A", "Diagnosis A2", 1, kontrolA2, 125000);

    // Connect the child nodes to the parent nodes
    nodeA->history = nodeA1;
    nodeA1->next = nodeA2;

    nodeB->history = nodeB1;
    nodeB1->next = nodeB2;

    // Connect the parent nodes
    nodeA->next = nodeB;
    nodeB->next = NULL;

    // Print the linked list
    printf("Before sorting:\n");
    printLinkedList(nodeA);

    // Sort the history
    sortHistory(nodeA);

    // Print the linked list
    printf("After sorting:\n");
    printLinkedList(nodeA);

    return 0;
}