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

int main() {
    Date date;

    date = convertStringToDate("29857");
    printf("Day: %d\n", date.day);
    printf("Month: %d\n", date.month);
    printf("Year: %d\n", date.year);
    printf("\n");

    date = convertStringToDate("28/09/1981");
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
