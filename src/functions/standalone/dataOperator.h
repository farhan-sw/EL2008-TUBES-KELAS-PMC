#ifndef DATAOPERATOR_H
#define DATAOPERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
Date createDate(int day, int month, int year);
Patient* createPatient(char namaLengkap[], char alamat[], char kota[], char tempatLahir[], int umur, int noBPJS, char idPasien[]);
History* createHistory(Date tanggal, char idPasien[], char diagnosis[], int tindakanID, Date kontrol, int biaya);
printDate(Date date);
printLinkedList(Patient *head);
sortHistory(Patient *head);
deletePatient(Patient *head, char idPasien[]);
int debugging();


#endif /* DATAOPERATOR_H */