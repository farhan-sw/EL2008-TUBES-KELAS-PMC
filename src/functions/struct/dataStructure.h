#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Date struct
 */
typedef struct Date {
    int day;
    int month;
    int year;
} Date;

// Define the structure for the patient node

/**
 * @brief Patient struct
 */
typedef struct Patient {
    char namaLengkap[50];
    char alamat[100];
    char kota[50];
    char tempatLahir[50];
    Date tanggalLahir;
    int umur;
    int noBPJS;
    char idPasien[20];
    struct History *history;
    struct Patient *next;
} Patient;

/**
 * @brief History struct
 */
typedef struct History {
    Date tanggal;
    char idPasien[20];
    char diagnosis[50];
    int tindakanID;
    Date kontrol;
    int biaya;
    struct History *next;
} History;


#endif /* DATASTRUCTURE_H */