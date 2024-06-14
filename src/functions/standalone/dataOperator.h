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


Patient* createPatient(char namaLengkap[], char alamat[], char kota[], char tempatLahir[], Date tanggalLahir, int umur, int noBPJS, char idPasien[]);
void copyPatient(Patient *headSource, Patient **product);
void addPatient(Patient **head, Patient *newPatient);
void addHistory(History **head, History *newHistory);
void printPatient(Patient *head);
Patient* findPatient(Patient *head, char idPasien[]);

History* createHistory(Date tanggal, char idPasien[], char diagnosis[], int tindakanID, Date kontrol, int biaya);
void addHistory(History **head, History *newHistory);
void printHistory(History *history);
void sortHistory(Patient *head);

Tindakan* createTindakan(char tindakan[], int biaya, int id);
void addTindakan(Tindakan **head, Tindakan *newTindakan);
void printTindakan(Tindakan *head);
void idToTindakan(Tindakan *head, int id, char *tindakan, int *biaya);
int idToBiaya(Tindakan *head, int id);
int TindakanToID(Tindakan *head, char tindakan[]);

// Fungsi untuk print data pasien sekaligus rekam medis pada pasien tersebut
void printPatientHistory(Patient *head);

void deletePatient(Patient *head, char idPasien[]);
int debugging();
void printDate(Date date);


#endif /* DATAOPERATOR_H */