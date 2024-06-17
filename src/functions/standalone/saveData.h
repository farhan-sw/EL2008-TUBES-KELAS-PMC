#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dataStructure.h>

// declarasikan bahwa ada variable bernama session
void saveData(Patient* allPatientData, Tindakan* allTindakanList , char filename[], char session[]);
void testExcel();

#endif // SAVEDATA_H