#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlsxio_write.h>

// declarasikan bahwa ada variable bernama session
void saveData(Patient* allPatientData, char filename[]);

#endif // SAVEDATA_H