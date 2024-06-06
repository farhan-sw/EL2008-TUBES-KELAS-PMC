#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"

void printPatient(Patient *patient) {
    printf("Name: %s\n", patient->name);
    printf("Age: %d\n", patient->age);
}

// Function to create a new patient node
Patient* createPatient(char name[], int age, char gender, char lastControlDate[]) {
    Patient *newPatient = (Patient*) malloc(sizeof(Patient));
    strcpy(newPatient->name, name);
    newPatient->age = age;
    newPatient->gender = gender;
    strcpy(newPatient->lastControlDate, lastControlDate);
    newPatient->history = NULL;
    newPatient->next = NULL;
    return newPatient;
}

// Function to create a new history node
History* createHistory(char disease[], char medicine[], char nextControlDate[], float medicinePrice, float visitCost) {
    History *newHistory = (History*) malloc(sizeof(History));
    strcpy(newHistory->disease, disease);
    strcpy(newHistory->medicine, medicine);
    strcpy(newHistory->nextControlDate, nextControlDate);
    newHistory->medicinePrice = medicinePrice;
    newHistory->visitCost = visitCost;
    newHistory->next = NULL;
    return newHistory;
}

// Function to print the linked list
void printLinkedList(Patient *head) {
    Patient *currentPatient = head;
    while (currentPatient != NULL) {
        printf("Patient Name: %s\n", currentPatient->name);
        printf("Age: %d\n", currentPatient->age);
        printf("Gender: %c\n", currentPatient->gender);
        printf("Last Control Date: %s\n", currentPatient->lastControlDate);
        printf("History:\n");
        History *currentHistory = currentPatient->history;
        while (currentHistory != NULL) {
            printf("- Disease: %s\n", currentHistory->disease);
            printf("  Medicine: %s\n", currentHistory->medicine);
            printf("  Next Control Date: %s\n", currentHistory->nextControlDate);
            printf("  Medicine Price: %.2f\n", currentHistory->medicinePrice);
            printf("  Visit Cost: %.2f\n", currentHistory->visitCost);
            currentHistory = currentHistory->next;
        }
        printf("\n");
        currentPatient = currentPatient->next;
    }
}