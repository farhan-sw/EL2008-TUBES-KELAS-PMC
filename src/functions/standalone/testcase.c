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

// Konversi tanggal dari string ke Date
Date convertStringToDate(const char tanggal[]) {
    // printf("Tanggal: %s\n", tanggal); // Debug statement
    Date newDate;
    char dateStr[30];
    strncpy(dateStr, tanggal, sizeof(dateStr) - 1);
    dateStr[sizeof(dateStr) - 1] = '\0';

    // deteksi apakah ada "-" di tanggal
    char *splitter;
    if (strchr(dateStr, '-') != NULL) {
        // printf("Format tanggal menggunakan strip\n"); // Debug statement
        splitter = "-";
    } else {
        // printf("Format tanggal menggunakan spasi\n"); // Debug statement
        splitter = " ";
    }

    char *token = strtok(dateStr, splitter);
    newDate.day = atoi(token);
    // printf("Day: %d\n", newDate.day); // Debug statement

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

    return newDate;
}

int main() {
    Date date;

    date = convertStringToDate("1 April 2021");
    printf("Day: %d\n", date.day);
    printf("Month: %d\n", date.month);
    printf("Year: %d\n", date.year);
    printf("\n");

    date = convertStringToDate("1-April-2021");
    printf("Day: %d\n", date.day);
    printf("Month: %d\n", date.month);
    printf("Year: %d\n", date.year);
    printf("\n");

    date = convertStringToDate("1-Apr-2021");
    printf("Day: %d\n", date.day);
    printf("Month: %d\n", date.month);
    printf("Year: %d\n", date.year);
    printf("\n");

    return 0;
}
