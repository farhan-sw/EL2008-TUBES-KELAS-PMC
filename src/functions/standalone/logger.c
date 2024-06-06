#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <sys/stat.h>

void Logger(char* session,int actionCode, char* message) {

    // deteksi apakah direktori ../logs sudah ada, jika belum maka buat direktori ../logs. Handling untuk semua jenis OS
    #ifdef _WIN32
        // cek apakah direktori sudah ada
        struct stat st = {0};
        if (stat("../logs", &st) == -1) {
            // jika belum ada, maka buat direktori
            if (mkdir("../logs") != 0) {
                printf("Error creating directory: ../logs\n");
                return;
            }
        }
    #else
        // cek apakah direktori sudah ada
        struct stat st = {0};
        if (stat("../logs", &st) == -1) {
            // jika belum ada, maka buat direktori
            if (mkdir("../logs", 0777) != 0) {
                printf("Error creating directory: ../logs\n");
                return;
            }
        }
    #endif

    // deteksi apakah file txt sudah ada, jika belum maka buat file txt
    char filename[100];
    sprintf(filename, "../logs/%s.txt", session);
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Log file not found, creating new log file\n");
        file = fopen(filename, "w");
        if (file == NULL) {
        printf("Error creating file: %s\n", filename);
        return;
        }
    }

    // Dapatkan waktu higga nanosecond
    char logTime[100]; // Added this line
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    sprintf(logTime, "HealthAdminLog:%d-%d-%d_%d:%d:%d:%ld", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ts.tv_nsec);

    // Cek apakah file log sudah memiliki header
    int needHeader = 0;
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        printf("Runtime info: Creating Log File\n"); 
        // Dapatkan nama komputer
        const gchar *hostname = g_get_host_name();
        // tampilkan host name
        g_print("Hostname: %s\n", hostname);
        // Menulis Header File Log
        fprintf(file, "================================================================\n");
        fprintf(file, "Health Management System Log File\n");
        fprintf(file, "Session: %s\n", session);
        fprintf(file, "Host: %s\n", hostname);
        fprintf(file, "================================================================\n\n");  
    }

    if(actionCode == 1){
        fprintf(file, "[%s] [INFO: %s]\n", logTime, message);
        printf("[%s] [INFO: %s]\n", logTime, message);
    } else if(actionCode == 2){
        fprintf(file, "[%s] [SUCCESS: %s]\n", logTime, message);
        printf("[%s] [SUCCESS: %s]\n", logTime, message);
    }else if(actionCode == 3){
        fprintf(file, "[%s] [WARNING: %s]\n", logTime, message);
        printf("[%s] [WARNING: %s]\n", logTime, message);
    } else if(actionCode == 4){
        fprintf(file, "[%s] [ERROR: %s\n]", logTime, message);
        printf("[%s] [ERROR: %s\n]", logTime, message);
    }

    fclose(file);
}