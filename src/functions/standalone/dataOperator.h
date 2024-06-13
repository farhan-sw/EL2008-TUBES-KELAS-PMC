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


History* createHistory(Date tanggal, char idPasien[], char diagnosis[], int tindakanID, Date kontrol, int biaya);

void printLinkedList(Patient *head);
void sortHistory(Patient *head);
void deletePatient(Patient *head, char idPasien[]);
int debugging();


#endif /* DATAOPERATOR_H */