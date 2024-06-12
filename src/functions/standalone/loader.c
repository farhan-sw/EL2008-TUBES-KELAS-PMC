#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"
#include "dataOperator.h"
#include <xlsxio_read.h>
#include <xlsxio_write.h>

//fungsi yang membaca file xlxs

void readExcelFile() {
    xlsxioreader xlsxioread;
    xlsxioreadersheet sheet;
    const char* filename = "../data/DataPMC20232024.xlsx";
    
    xlsxioread = xlsxioread_open(filename);
    if (xlsxioread == NULL) {
        printf("Failed to open the Excel file.\n");
        return;
    }
    
    sheet = xlsxioread_sheet_open(xlsxioread, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
    if (sheet == NULL) {
        printf("Failed to open the sheet in the Excel file.\n");
        xlsxioread_close(xlsxioread);
        return;
    }
    
    const char* cell_data;
    while (xlsxioread_sheet_next_row(sheet)) {
        while ((cell_data = xlsxioread_sheet_next_cell(sheet)) != NULL) {
            // Process the cell data
            printf("%s\t", cell_data);
        }
        printf("\n");
    }
    
    xlsxioread_sheet_close(sheet);
    xlsxioread_close(xlsxioread);
}

