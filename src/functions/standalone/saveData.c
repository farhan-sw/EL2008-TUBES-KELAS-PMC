#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dataStructure.h"
#include <xlsxwriter.h>

void saveData(Patient* allPatientData, char filename[]){
    printf("function invoked"); 
    
}

void testExcel(){
    // Create a new workbook
    lxw_workbook  *workbook  = workbook_new("test.xlsx");
    // Create a new worksheet
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
    // Add a format
    lxw_format *bold = workbook_add_format(workbook);
    format_set_bold(bold);
    // Write some simple text
    worksheet_write_string(worksheet, 0, 0, "Hello", NULL);
    // Text with formatting
    worksheet_write_string(worksheet, 1, 0, "World", bold);
    // Write some numbers
    worksheet_write_number(worksheet, 2, 0, 123, NULL);
    worksheet_write_number(worksheet, 3, 0, 123.456, NULL);
    // Insert an image
    worksheet_insert_image(worksheet, 1, 2, "logo.png");
    // Save the workbook
    workbook_close(workbook);
}