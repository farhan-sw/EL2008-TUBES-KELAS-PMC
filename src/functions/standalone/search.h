#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dataStructure.h"

// FUNCTION PROTOTYPE
void searchPatient(Patient *head, Patient **result, char keyword[]);
void searchMedicalRecord(Patient *head, Patient **result, char keyword[]);
void searchService(Tindakan *head, Tindakan **result, char keyword[]);

#endif 