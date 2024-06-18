#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>


typedef struct YearlyReport {
    int year;
    float monthlyIncome[12];
    int monthlyPatients[12];
    int monthlyDiseases[12][50]; // Asumsi maksimum 50 jenis penyakit
    char diseases[50][50];       // Nama penyakit
    int diseaseCount;
} YearlyReport;

typedef struct DiseaseCount {
    int index;
    int count;
} DiseaseCount;



/**
 * @brief Date struct
 */
typedef struct Date {
    int day;
    int month;
    int year;
} Date;





// =================================== BAGIAN HISTORY =======================================
/**
 * @brief History struct
 */
typedef struct History {
    struct Patient *patient;
    Date tanggal;
    char idPasien[20];
    char diagnosis[50];
    char tindakan[50];
    Date kontrol;
    int biaya;
    struct History *next;
} History;
// =================================== END BAGIAN HISTORY =======================================



// =================================== BAGIAN TINDAKAN =======================================
/**
 * @brief Tindakan struct
 */
typedef struct Tindakan {
    int id;
    char Tindakan[50];
    int biaya;
    struct Tindakan *next;
} Tindakan;
// =================================== END BAGIAN TINDAKAN =======================================



// =================================== BAGIAN MEDICAL CHECKUP =======================================
/**
 * @brief Medical Checkup Struct
 */
typedef struct MedicalCheckup {
    char idPasien[20];
    char namaLengkap[50];
    char diagnosis[50];
    char tindakan[50];
    Date kontrol;

    struct MedicalCheckup *next;
} MedicalCheckup;


// =================================== END BAGIAN MEDICAL CHECKUP =======================================



/* ============================ BAGIAN PATIENT ============================ */
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

typedef struct PatientParams{
    GtkWidget *table;
    Patient** operatedData;
    Patient** allPatientData;
    Tindakan* allTindakanData;
} PatientParams;

typedef struct NewPatientFormPointer{
    GtkWidget *namaLengkap;
    GtkWidget *alamat;
    GtkWidget *kota;
    GtkWidget *tempatLahir;
    GtkWidget *tanggalLahir;
    GtkWidget *noBPJS;
} NewPatientFormPointer;

typedef struct AddPatientParams{
    PatientParams* patientParams;
    GtkWidget *window;
    NewPatientFormPointer* newPatientFormPointer;
} AddPatientParams;

typedef struct EditPatientFormPointer{
    GtkWidget *namaLengkap;
    GtkWidget *alamat;
    GtkWidget *kota;
    GtkWidget *tempatLahir;
    GtkWidget *tanggalLahir;
    GtkWidget *noBPJS;
    Patient* patient;
    GtkWidget *window;
    GtkWidget *table;
    Patient** operatedData;
    Patient** allPatientData;
} EditPatientFormPointer;



typedef struct HistoryParams{
    GtkWidget *table;
    MedicalCheckup** operatedData;
    MedicalCheckup** allMedicalCheckupData;
    Tindakan* allTindakanData;
} HistoryParams;


typedef struct NewHistoryFormPointer{
    GtkWidget *tanggal;
    GtkWidget *idPasien;
    GtkWidget *namaLengkap;
    GtkWidget *diagnosis;
    GtkWidget *tindakan;
    GtkWidget *kontrol;
} NewHistoryFormPointer;

typedef struct editHistoryFormPointer{
    GtkWidget *tanggal;
    GtkWidget *idPasien;
    GtkWidget *namaLengkap;
    GtkWidget *diagnosis;
    GtkWidget *tindakan;
    GtkWidget *kontrol;
    GtkWidget *window;
    GtkWidget *table;
    Patient** operatedData;
    Patient** allPatientData;
    Tindakan* allTindakanData;
    History* history;
} editHistoryFormPointer;


typedef struct AddHistoryParams{
    PatientParams* patientParams;
    GtkWidget *window;
    NewHistoryFormPointer* newHistoryFormPointer;
} AddHistoryParams;


typedef struct EditMedicalCheckupFormPointer{
    GtkWidget *idPasien;
    GtkWidget *namaLengkap;
    GtkWidget *diagnosis;
    GtkWidget *tindakan;
    GtkWidget *kontrol;
    MedicalCheckup* medicalCheckup;
    GtkWidget *window;
    GtkWidget *table;
    MedicalCheckup** operatedData;
    MedicalCheckup** allMedicalCheckupData;
} EditMedicalCheckupFormPointer;

typedef struct FinancialTabParams{
    GtkWidget *table;
    Tindakan** allTindakanData;
} FinancialTabParams;

typedef struct TindakanFormPointer{
    GtkWidget *tindakan;
    GtkWidget *biaya;
    GtkWidget *window;
    FinancialTabParams* financialTabParams;
} TindakanFormPointer;

#define MAX_REPORT 10

typedef struct AnalyticsPointer{
    GtkWidget *startYear;
    GtkWidget *endYear;
} AnalyticsPointer;
typedef struct AnalyticsParam {
    int startYear;
    int endYear;
    YearlyReport yearlyReports[MAX_REPORT]; // Misalnya, untuk 5 tahun
    int reportCount;
    Patient** operatedData;
    Patient** allPatientData;
    Tindakan* allTindakanData;
    GtkWidget *vbox;
    AnalyticsPointer* analyticsPointer;
} AnalyticsParam;




// =================================== END BAGIAN PATIENT =======================================


// buat dateParams dan addDateParams
typedef struct DatePointer{
    GtkWidget *startDate;
    GtkWidget *endDate;
} DatePointer;

typedef struct AddDateParams{
    PatientParams* patientParams;
    DatePointer* datePointer;
    GtkWidget *window;
} AddDateParams;


#endif /* DATASTRUCTURE_H */