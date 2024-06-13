#ifndef DATAOPERATOR_H
#define DATAOPERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
Date createDate(int day, int month, int year);
Date convertStringToDate(char tanggal[]);
Patient* createPatient(char namaLengkap[], char alamat[], char kota[], char tempatLahir[], int umur, int noBPJS, char idPasien[]);
void addPatient(Patient **head, Patient *newPatient);
History* createHistory(Date tanggal, char idPasien[], char diagnosis[], int tindakanID, Date kontrol, int biaya);
void printDate(Date date);
void printLinkedList(Patient *head);
void sortHistory(Patient *head);
void deletePatient(Patient *head, char idPasien[]);
int debugging();


#endif /* DATAOPERATOR_H */