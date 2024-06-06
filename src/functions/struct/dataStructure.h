#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the patient node
typedef struct Patient {
    char name[50];
    int age;
    char gender;
    char lastControlDate[20];
    struct History *history;
    struct Patient *next;
} Patient;

// Define the structure for the history node
typedef struct History {
    char disease[50];
    char medicine[50];
    char nextControlDate[20];
    float medicinePrice;
    float visitCost;
    struct History *next;
} History;

// Function prototypes
void printPatient(Patient *patient);
Patient* createPatient(char name[], int age, char gender, char lastControlDate[]);
History* createHistory(char disease[], char medicine[], char nextControlDate[], float medicinePrice, float visitCost);
void printLinkedList(Patient *head);


#endif /* DATASTRUCTURE_H */