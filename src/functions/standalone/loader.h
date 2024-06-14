#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"
#include "dataOperator.h"
#define XML_UNICODE
#include <xlsxio_read.h>

//fungsi yang membaca file xlxs
void loadData(Patient** patientList, Tindakan** tindakanList, char* filename);

#endif // LOADER_H