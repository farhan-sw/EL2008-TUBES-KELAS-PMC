#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the date
typedef struct Date {
    int day;
    int month;
    int year;
} Date;

// Define the structure for the patient node
typedef struct Patient {
    char namaLengkap[50];
    char alamat[100];
    char kota[50];
    char tempatLahir[50];
    int umur;
    int noBPJS;
    char idPasien[20];
    struct History *history;
    struct Patient *next;
} Patient;

// Define the structure for the history node
typedef struct History {
    Date tanggal;
    char idPasien[20];
    char diagnosis[50];
    int tindakanID;
    char kontrol[20];
    int biaya;
    struct History *next;
} History;

// Function to create a new date
Date createDate(int day, int month, int year) {
    Date newDate;
    newDate.day = day;
    newDate.month = month;
    newDate.year = year;
    return newDate;
}

// Function to create a new patient node
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

// Function to create a new history node
History* createHistory(Date tanggal, char idPasien[], char diagnosis[], int tindakanID, char kontrol[], int biaya) {
    History *newHistory = (History*) malloc(sizeof(History));
    newHistory->tanggal = tanggal;
    strcpy(newHistory->idPasien, idPasien);
    strcpy(newHistory->diagnosis, diagnosis);
    newHistory->tindakanID = tindakanID;
    strcpy(newHistory->kontrol, kontrol);
    newHistory->biaya = biaya;
    newHistory->next = NULL;
    return newHistory;
}

// Function to print the date
void printDate(Date date) {
    printf("%02d-%02d-%04d", date.day, date.month, date.year);
}

// Function to print the linked list
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
            printf("  Kontrol: %s\n", currentHistory->kontrol);
            printf("  Biaya: %d\n", currentHistory->biaya);
            currentHistory = currentHistory->next;
        }
        printf("\n");
        currentPatient = currentPatient->next;
    }
}

// Buatkan Sort history berdasarkan tanggal
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


int main() {
    // Create the parent nodes
    Patient *nodeA = createPatient("A", "Alamat A", "Kota A", "Tempat Lahir A", 30, 12345, "ID_A");
    Patient *nodeB = createPatient("B", "Alamat B", "Kota B", "Tempat Lahir B", 25, 67890, "ID_B");

    // Create the child nodes for node B
    Date dateB1 = createDate(15, 9, 2021);
    History *nodeB1 = createHistory(dateB1, "ID_B", "Diagnosis B1", 2, "2021-09-20", 100000);
    Date dateB2 = createDate(10, 10, 2020);
    History *nodeB2 = createHistory(dateB2, "ID_B", "Diagnosis B2", 3, "2021-10-15", 25000);

    // Create the child nodes for node A
    Date dateA1 = createDate(1, 10, 2020);
    History *nodeA1 = createHistory(dateA1, "ID_A", "Diagnosis A1", 0, "2021-10-05", 15000);
    Date dateA2 = createDate(1, 11, 2018);
    History *nodeA2 = createHistory(dateA2, "ID_A", "Diagnosis A2", 1, "2021-11-05", 125000);



    // Connect the child nodes to the parent nodes
    nodeA->history = nodeA1;
    nodeA1->next = nodeA2;

    nodeB->history = nodeB1;
    nodeB1->next = nodeB2;

    // Connect the parent nodes
    nodeA->next = nodeB;
    nodeB->next = NULL;

    // Print the linked list
    printLinkedList(nodeA);

    // Sort the history
    sortHistory(nodeA);

    // Print the linked list
    printLinkedList(nodeA);

    return 0;
}
