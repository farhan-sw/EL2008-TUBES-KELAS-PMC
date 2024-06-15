#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"
#include "logger.h"



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

// Fungsi untuk memeriksa apakah string adalah angka
int isNumber(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

// Fungsi untuk menghitung apakah tahun adalah tahun kabisat
int isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                return 1;
            else
                return 0;
        } else
            return 1;
    } else
        return 0;
}

// Konversi nomor seri Excel ke Date
Date excelSerialToDate(int serial) {
    Date date;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dayCount = serial - 1;  // Mengurangi 1 karena 1-Jan-1900 adalah nomor seri 1
    date.year = 1900;

    while (dayCount >= 365) {
        if (isLeapYear(date.year)) {
            if (dayCount >= 366) {
                dayCount -= 366;
                date.year++;
            } else {
                break;
            }
        } else {
            dayCount -= 365;
            date.year++;
        }
    }

    if (isLeapYear(date.year)) {
        daysInMonth[1] = 29;
    } else {
        daysInMonth[1] = 28;
    }

    date.month = 0;
    while (dayCount >= daysInMonth[date.month]) {
        dayCount -= daysInMonth[date.month];
        date.month++;
    }

    date.month++; // Bulan dimulai dari 1
    date.day = dayCount + 1; // Hari dimulai dari 1

    return date;
}

// Konversi tanggal dari string ke Date
Date convertStringToDate(const char tanggal[]) {
    Date newDate;
    char dateStr[30];
    strncpy(dateStr, tanggal, sizeof(dateStr) - 1);
    dateStr[sizeof(dateStr) - 1] = '\0';

    // Cek apakah input adalah nomor seri
    if (isNumber(dateStr)) {
        int serial = atoi(dateStr);
        return excelSerialToDate(serial);
    }

    // deteksi apakah format tanggal menggunakan '/'
    if (strchr(dateStr, '/') != NULL) {
        // Memisahkan komponen hari, bulan, dan tahun dari format DD/MM/YYYY
        char *token = strtok(dateStr, "/");
        newDate.day = atoi(token);

        token = strtok(NULL, "/");
        newDate.month = atoi(token);

        token = strtok(NULL, "/");
        newDate.year = atoi(token);
    } else {
        // deteksi apakah format tanggal menggunakan "-"
        char *splitter;
        if (strchr(dateStr, '-') != NULL) {
            splitter = "-";
        } else {
            splitter = " ";
        }

        char *token = strtok(dateStr, splitter);
        newDate.day = atoi(token);

        token = strtok(NULL, splitter);

        // Membandingkan nama bulan
        if (strcmp(token, "Januari") == 0 || strcmp(token, "Jan") == 0) {
            newDate.month = 1;
        } else if (strcmp(token, "Februari") == 0 || strcmp(token, "Feb") == 0) {
            newDate.month = 2;
        } else if (strcmp(token, "Maret") == 0 || strcmp(token, "Mar") == 0) {
            newDate.month = 3;
        } else if (strcmp(token, "April") == 0 || strcmp(token, "Apr") == 0) {
            newDate.month = 4;
        } else if (strcmp(token, "Mei") == 0 || strcmp(token, "May") == 0) {
            newDate.month = 5;
        } else if (strcmp(token, "Juni") == 0 || strcmp(token, "Jun") == 0) {
            newDate.month = 6;
        } else if (strcmp(token, "Juli") == 0 || strcmp(token, "Jul") == 0) {
            newDate.month = 7;
        } else if (strcmp(token, "Agustus") == 0 || strcmp(token, "Aug") == 0) {
            newDate.month = 8;
        } else if (strcmp(token, "September") == 0 || strcmp(token, "Sep") == 0) {
            newDate.month = 9;
        } else if (strcmp(token, "Oktober") == 0 || strcmp(token, "Oct") == 0) {
            newDate.month = 10;
        } else if (strcmp(token, "November") == 0 || strcmp(token, "Nov") == 0) {
            newDate.month = 11;
        } else if (strcmp(token, "Desember") == 0 || strcmp(token, "Dec") == 0) {
            newDate.month = 12;
        }

        token = strtok(NULL, splitter);
        newDate.year = atoi(token);
    }

    return newDate;
}


// Konversi Date ke string dengan format DD-MM-YYYY
void convertDateToString(Date date, char *dateStr) {
    sprintf(dateStr, "%02d-%02d-%04d", date.day, date.month, date.year);
}

// Membuat ID Pasien baru yang unik
unsigned int patientCounter = 1230123;

void createIDPatient(char *idPasien) {
    // Format ID pasien: "KX " diikuti dengan nomor urut pasien
    sprintf(idPatient, "KX %07u", patientCounter);
    patientCounter++;  // Increment untuk pasien berikutnya
}

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
Patient* createPatient(char namaLengkap[], char alamat[], char kota[], char tempatLahir[], Date tanggalLahir, int umur, int noBPJS, char idPasien[]) {
    Patient *newPatient = (Patient*) malloc(sizeof(Patient));
    strcpy(newPatient->namaLengkap, namaLengkap);
    strcpy(newPatient->alamat, alamat);
    strcpy(newPatient->kota, kota);
    strcpy(newPatient->tempatLahir, tempatLahir);
    newPatient->tanggalLahir = tanggalLahir;
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
        while (currentPatient != NULL && currentPatient->next != NULL) {
            currentPatient = currentPatient->next;
        }
        currentPatient->next = newPatient;
    }
}

void addHistory(History **head, History *newHistory) {
    if (*head == NULL) {
        *head = newHistory;
    } else {
        History *currentHistory = *head;
        while (currentHistory->next != NULL) {
            currentHistory = currentHistory->next;
        }
        currentHistory->next = newHistory;
    }
}

Patient* findPatient(Patient *head, char idPasien[]) {
    Patient *currentPatient = head;
    while (currentPatient != NULL) {
        if (strcmp(currentPatient->idPasien, idPasien) == 0) {
            return currentPatient;
        }
        currentPatient = currentPatient->next;
    }
    return NULL;
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
    printf("%02d-%02d-%04d\n", date.day, date.month, date.year);
}

/**
 * @brief Print a linked list function
 * @param head: Patient head
 */
void printPatient(Patient *head) {
    Patient *currentPatient = head;
    while (currentPatient != NULL) {
        printf("Nama Lengkap: %s\n", currentPatient->namaLengkap);
        printf("Alamat: %s\n", currentPatient->alamat);
        printf("Kota: %s\n", currentPatient->kota);
        printf("Tempat Lahir: %s\n", currentPatient->tempatLahir);
        printf("Tanggal Lahir: "); printDate(currentPatient->tanggalLahir);
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

void printHistory(History *history) {
    printf("Tanggal: ");
    printDate(history->tanggal);
    printf("ID Pasien: %s\n", history->idPasien);
    printf("Diagnosis: %s\n", history->diagnosis);
    printf("Tindakan (ID): %d\n", history->tindakanID);
    printf("Kontrol: ");
    printDate(history->kontrol);
    printf("Biaya: %d\n", history->biaya);
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

void freePatientList(Patient *head) {
    Patient *currentPatient = head;
    while (currentPatient != NULL) {
        Patient *temp = currentPatient;
        currentPatient = currentPatient->next;
        // bebaskan history
        History *currentHistory = temp->history;
        while (currentHistory != NULL) {
            History *tempHistory = currentHistory;
            currentHistory = currentHistory->next;
            free(tempHistory);
        }
        free(temp);
    }
}

void printPatientList(Patient *head) {
    Patient *currentPatient = head;
    while (currentPatient != NULL) {
        printf("Nama Pasien: %s\n", currentPatient->namaLengkap);
        printf("Alamat Pasien: %s\n", currentPatient->alamat);
        printf("Kota Pasien: %s\n", currentPatient->kota);
        printf("Tempat Lahir Pasien: %s\n", currentPatient->tempatLahir);
        printf("Tanggal Lahir Pasien: %d-%d-%d\n", currentPatient->tanggalLahir.day, currentPatient->tanggalLahir.month, currentPatient->tanggalLahir.year);
        printf("Umur Pasien: %d\n", currentPatient->umur);
        printf("No BPJS Pasien: %d\n", currentPatient->noBPJS);
        printf("ID Pasien: %s\n\n", currentPatient->idPasien);
        currentPatient = currentPatient->next;
    }
}



/**
 * @brief Main function buat uji coba
 */
int debugging() {
    // Create the parent nodes
    Patient *nodeA = createPatient("A", "Alamat A", "Kota A", "Tempat Lahir A", createDate(1, 1, 2000), 20, 123456, "ID_A");
    Patient *nodeB = createPatient("B", "Alamat B", "Kota B", "Tempat Lahir B", createDate(1, 1, 2000), 20, 123456, "ID_B");

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
    printPatient(nodeA);

    // Sort the history
    sortHistory(nodeA);

    // Print the linked list
    printf("After sorting:\n");
    printPatient(nodeA);

    return 0;
}

/**
 * @brief Copy patient data
 * @param headSoure: pointer of patient source of copy
 * @param product : pointer of pointer patient product of copy
 */
void copyPatient(Patient *headSource, Patient **product){
    Patient *currentPatient = headSource;
    while (currentPatient != NULL) {
        Patient *newPatient = createPatient(currentPatient->namaLengkap, currentPatient->alamat, currentPatient->kota, currentPatient->tempatLahir, currentPatient->tanggalLahir, currentPatient->umur, currentPatient->noBPJS, currentPatient->idPasien);
        addPatient(product, newPatient);
        History *currentHistory = currentPatient->history;
        while (currentHistory != NULL) {
            History *newHistory = createHistory(currentHistory->tanggal, currentHistory->idPasien, currentHistory->diagnosis, currentHistory->tindakanID, currentHistory->kontrol, currentHistory->biaya);
            addHistory(&newPatient->history, newHistory);
            currentHistory = currentHistory->next;
        }
        currentPatient = currentPatient->next;
    }
}

/**
 * @brief Print the patient history khusus pasien itu saja
 */
void printPatientHistory(Patient *head){
    History *currentHistory = head->history;
    while (currentHistory != NULL) {
        printf("Tanggal: ");
        printDate(currentHistory->tanggal);
        printf("ID Pasien: %s\n", currentHistory->idPasien);
        printf("Diagnosis: %s\n", currentHistory->diagnosis);
        printf("Tindakan (ID): %d\n", currentHistory->tindakanID);
        printf("Kontrol: ");
        printDate(currentHistory->kontrol);
        printf("Biaya: %d\n", currentHistory->biaya);
        currentHistory = currentHistory->next;
    }
}


/* ==================== UNTUK TINDAKAN =========================== */

/**
 * @brief Create a Tindakan function
 * @param tindakan: char tindakan
 * @param biaya: int biaya
 * @param id: int ID
 */
Tindakan* createTindakan(char tindakan[], int biaya, int id) {
    Tindakan *newTindakan = (Tindakan*) malloc(sizeof(Tindakan));
    newTindakan->id = id;
    strcpy(newTindakan->Tindakan, tindakan);
    newTindakan->biaya = biaya;
    newTindakan->next = NULL;
    return newTindakan;
}

void addTindakan(Tindakan **head, Tindakan *newTindakan) {
    if (*head == NULL) {
        *head = newTindakan;
    } else {
        Tindakan *currentTindakan = *head;
        while (currentTindakan->next != NULL) {
            currentTindakan = currentTindakan->next;
        }
        currentTindakan->next = newTindakan;
    }
}

void printTindakan(Tindakan *head) {
    Tindakan *currentTindakan = head;
    while (currentTindakan != NULL) {
        printf("ID: %d\n", currentTindakan->id);
        printf("Tindakan: %s\n", currentTindakan->Tindakan);
        printf("Biaya: %d\n", currentTindakan->biaya);
        currentTindakan = currentTindakan->next;
    }
}

void idToTindakan(Tindakan *head, int id, char *tindakan, int *biaya) {
    Tindakan *currentTindakan = head;
    while (currentTindakan != NULL) {
        if (currentTindakan->id == id) {
            strcpy(tindakan, currentTindakan->Tindakan);
            *biaya = currentTindakan->biaya;
            return;
        }
        currentTindakan = currentTindakan->next;
    }
}

int idToBiaya(Tindakan *head, int id) {
    Tindakan *currentTindakan = head;
    while (currentTindakan != NULL) {
        if (currentTindakan->id == id) {
            return currentTindakan->biaya;
        }
        currentTindakan = currentTindakan->next;
    }
    return 0;
}

int TindakanToID(Tindakan *head, char tindakan[]) {
    Tindakan *currentTindakan = head;
    while (currentTindakan != NULL) {
        if (strcmp(currentTindakan->Tindakan, tindakan) == 0) {
            return currentTindakan->id;
        }
        currentTindakan = currentTindakan->next;
    }
    return -1;
}