#ifndef DATAOPERATOR_H
#define DATAOPERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
Date createDate(int day, int month, int year);
int isNumber(const char *str);
int isLeapYear(int year);
Date excelSerialToDate(int serial);
Date convertStringToDate(const char tanggal[]);
void convertDateToString(Date date, char *dateStr);
void printDate(Date date);

Patient* createPatient(char namaLengkap[], char alamat[], char kota[], char tempatLahir[], Date tanggalLahir, int umur, int noBPJS, char idPasien[]);
void addPatient(Patient **head, Patient *newPatient);
void printPatient(Patient *head);
Patient* findPatient(Patient *head, char idPasien[]);

History* createHistory(Date tanggal, char idPasien[], char diagnosis[], int tindakanID, Date kontrol, int biaya);
void addHistory(History **head, History *newHistory);
void printHistory(History *history);
void sortHistory(Patient *head);

// Fungsi untuk print data pasien sekaligus rekam medis pada pasien tersebut
void printPatientHistory(Patient *head);

void deletePatient(Patient *head, char idPasien[]);
int debugging();


#endif /* DATAOPERATOR_H */