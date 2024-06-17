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
int stringDateFormatVerify(char tanggal[]);
int hitungUmur(Date tanggalLahir) ;
int isOnlyNumber(char str[]) ;
Date getCurrentDate();
void setDate(Date *date, int day, int month, int year);
int compareDate(Date date1, Date date2);


Patient* createPatient(char namaLengkap[], char alamat[], char kota[], char tempatLahir[], Date tanggalLahir, int umur, int noBPJS, char idPasien[]);
void copyPatient(Patient *headSource, Patient **product);
void addPatient(Patient **head, Patient *newPatient);
void addHistory(History **head, History *newHistory);
void printPatient(Patient *head);

/**
 * @brief Fungsi untuk mengecek apakah idPasien sudah ada di linked list
 * @param head Pointer ke head linked list
 * @param idPasien ID Pasien yang akan dicek
 * @return 1 jika idPasien sudah ada, 0 jika belum ada
 */
int isIdPatientExist(Patient *head, char idPasien[]);
/**
 * @brief Fungsi untuk mengembalikan string dari ID Pasien
 * @param head Pointer ke head linked list
 * @param idPasien ID Pasien yang akan dicari
 * @return Pointer ke string ID Pasien
 */
char* findIdPatient(Patient *head, char idPasien[]);

Patient* findPatient(Patient *head, char idPasien[]);
char* createPatientID(Patient* allPatientData);

History* createHistory(Date tanggal, char idPasien[], char diagnosis[], char tindakan[], Date kontrol, int biaya);
void addHistory(History **head, History *newHistory);
// Delete Single History
void deleteHistory(History **head, Date tanggal);
void deleteHistorybyIndex(History **head, int index);
void printHistory(History *history);
void sortHistory(Patient *head);

Tindakan* createTindakan(char tindakan[], int biaya, int id);
void addTindakan(Tindakan **head, Tindakan *newTindakan);
void printTindakan(Tindakan *head);
void idToTindakan(Tindakan *head, int id, char *tindakan, int *biaya);
int idToBiaya(Tindakan *head, int id);
int TindakanToID(Tindakan *head, char tindakan[]);
int TindakanToBiaya(Tindakan *head, char tindakan[]);
int isTindakanExist(Tindakan *head, char tindakan[]);

MedicalCheckup* createMedicalCheckup(char idPasien[], char namaLengkap[], char diagnosis[], char tindakan[], Date kontrol);
void addMedicalCheckup(MedicalCheckup **head, MedicalCheckup *newMedicalCheckup);
void printMedicalCheckup(MedicalCheckup *head);
void sortMedicalCheckup(MedicalCheckup *head);
void loadMedicalCheckup(MedicalCheckup **head, Patient *patientHead);

// Fungsi untuk print data pasien sekaligus rekam medis pada pasien tersebut
void printPatientHistory(Patient *head);

void deletePatient(Patient **head, char idPasien[]);
void freePatientList(Patient *head);

int debugging();
void printDate(Date date);
void printPatientList(Patient *head);


#endif /* DATAOPERATOR_H */