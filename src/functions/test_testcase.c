// Test case 1: Create history with valid inputs
Date tanggal1 = {2022, 10, 15};
char idPasien1[] = "P001";
char diagnosis1[] = "Flu";
int tindakanID1 = 1;
Date kontrol1 = {2022, 10, 20};
int biaya1 = 100000;

History* history1 = createHistory(tanggal1, idPasien1, diagnosis1, tindakanID1, kontrol1, biaya1);

// Test case 2: Create history with empty strings
Date tanggal2 = {2022, 10, 16};
char idPasien2[] = "";
char diagnosis2[] = "";
int tindakanID2 = 2;
Date kontrol2 = {2022, 10, 21};
int biaya2 = 200000;

History* history2 = createHistory(tanggal2, idPasien2, diagnosis2, tindakanID2, kontrol2, biaya2);

// Test case 3: Create history with negative biaya
Date tanggal3 = {2022, 10, 17};
char idPasien3[] = "P003";
char diagnosis3[] = "Headache";
int tindakanID3 = 3;
Date kontrol3 = {2022, 10, 22};
int biaya3 = -50000;

History* history3 = createHistory(tanggal3, idPasien3, diagnosis3, tindakanID3, kontrol3, biaya3);